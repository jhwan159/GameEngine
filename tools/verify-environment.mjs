// Toolchain smoke test only. All generated C++ and CMake files live in TEMP.
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import assert from 'node:assert/strict';
import { spawnSync } from 'node:child_process';
import { fileURLToPath } from 'node:url';

const project = path.resolve(path.dirname(fileURLToPath(import.meta.url)), '..');
const output = path.join(project, '.ai-team', 'environment');
const report = { checkedAt: new Date().toISOString(), platform: process.platform, passed: false, commands: [], configurations: [] };
fs.mkdirSync(output, { recursive: true });
function run(executable, args, cwd = project) {
  const result = spawnSync(executable, args, { cwd, encoding: 'utf8', windowsHide: true, timeout: 120000 });
  const entry = { executable, args, cwd, exitCode: result.status, stdout: result.stdout || '', stderr: result.stderr || '' };
  report.commands.push(entry);
  if (result.error || result.status !== 0) {
    throw new Error(`${executable} failed: ${result.error?.message || entry.stderr || entry.stdout || result.signal}`);
  }
  return entry.stdout.trim();
}

try {
  assert.equal(process.platform, 'win32', 'This probe must run in the Windows developer terminal.');
  report.tools = {
    cmake: run('cmake', ['--version']).split(/\r?\n/)[0],
    ninja: run('ninja', ['--version']),
    ctest: run('ctest', ['--version']).split(/\r?\n/)[0],
    compiler: run('where.exe', ['cl.exe']).split(/\r?\n/)[0],
    git: run('git', ['--version'])
  };
  const temporary = fs.mkdtempSync(path.join(os.tmpdir(), 'PersonalGameEngine-toolchain-'));
  report.temporaryDirectory = temporary;
  fs.writeFileSync(path.join(temporary, 'probe.cpp'), '#include <span>\nint main() { int values[]{1,2,3}; return std::span<int>{values}.size() == 3 ? 0 : 1; }\n');
  fs.writeFileSync(path.join(temporary, 'CMakeLists.txt'), [
    'cmake_minimum_required(VERSION 3.28)',
    'project(ToolchainProbe LANGUAGES CXX)',
    'if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")',
    '  message(FATAL_ERROR "Expected MSVC in this Windows probe")',
    'endif()',
    'add_executable(ToolchainProbe probe.cpp)',
    'target_compile_features(ToolchainProbe PRIVATE cxx_std_20)',
    'enable_testing()',
    'add_test(NAME Cpp20ExecutableRuns COMMAND ToolchainProbe)',
    ''
  ].join('\n'));
  for (const configuration of ['Debug', 'Release']) {
    const build = path.join(temporary, `build-${configuration.toLowerCase()}`);
    run('cmake', ['-S', temporary, '-B', build, '-G', 'Ninja', `-DCMAKE_BUILD_TYPE=${configuration}`]);
    run('cmake', ['--build', build]);
    run('ctest', ['--test-dir', build, '--output-on-failure']);
    report.configurations.push({ configuration, passed: true });
  }
  report.passed = true;
} catch (error) {
  report.error = error.message;
  process.exitCode = 1;
} finally {
  const reportPath = path.join(output, 'toolchain-verification.json');
  fs.writeFileSync(reportPath, `${JSON.stringify(report, null, 2)}\n`);
  console.log(JSON.stringify({ passed: report.passed, tools: report.tools, configurations: report.configurations, reportPath, temporaryDirectory: report.temporaryDirectory, error: report.error }, null, 2));
}
