# Windows 개발 환경

설정 날짜: 2026-10-24. 이 문서는 Windows 환경에 대한 기록이며 Mac 설치·실행은 별도로 확인한다.

## 설치와 설정

- CMake 4.4.4, Ninja 1.13.2를 사용자 범위의 WinGet portable 패키지로 설치했다. WinGet의 다운로드 해시 검증을 통과했다.
- 도구 명령 별칭은 `%LOCALAPPDATA%/Microsoft/WinGet/Links`에 있다. 사용자 PATH에 등록되며 기존 터미널에는 재시작이 필요할 수 있다.
- 기존 Visual Studio 2026 Community의 MSVC x64 도구를 사용한다.
- 사용자가 선택한 IDE는 CLion이다. **CLion 2026.2.3 설치와 GUI 툴체인 설정을 완료했다.** 공식 설치 파일의 SHA-256 검증과 사용자 범위 설치 종료 코드 0을 확인했다. 첫 실행 명령의 자동 승인 거절 후 사용자가 직접 “CLion 창을 열었습니다”라고 응답했고, 조율자가 실제 환영 창을 관찰한 뒤 설정을 진행했다. 라이선스 상태를 검사·변경하지 않았으며 엔진의 IDE 빌드·디버깅은 아직 확인하지 않았다.
- 이 Windows 기기의 CLion 실행 파일 예정 경로는 `C:/Users/choja/Applications/CLion/2026.2.3/bin/clion64.exe`다. 다른 기기나 버전에서는 해당 기기의 설치 경로를 별도로 확인한다.
- GUI의 툴체인 페이지에서 Visual Studio 2026 설치 경로와 amd64 감지를 확인하고, Visual Studio/MSVC를 기본 툴체인으로 올렸다. CMake는 `C:/Users/choja/AppData/Local/Microsoft/WinGet/Links/cmake.exe`(감지 버전 4.4.4), 빌드 도구는 같은 폴더의 ninja.exe(명령줄 확인 버전 1.13.2)로 저장했다.
- 저장 근거는 `C:/Users/choja/AppData/Roaming/JetBrains/CLion2026.2/options/windows/toolchains.xml`이다. 첫 툴체인의 toolSetKind가 MSVC이고 customCMakePath·customMakePath와 설치 경로가 일치한다. `.ai-team/environment/clion-setup.json`에 파일 해시와 UI 관찰 결과를 기록했다. 앞서 대기했던 사용자 첫 실행 조건은 충족됐다.
- [Start-Dev.cmd](../Start-Dev.cmd)가 Visual Studio 설치를 검색해 x64 개발 환경을 불러온다. SDK·링커 경로는 Visual Studio가 제공한다.
- [Start-CLion.cmd](../Start-CLion.cmd)는 위 실행 파일이 있는지 확인하고 `Start-Dev.cmd --terminal`로 환경을 준비한 뒤 기존 프로젝트 폴더를 CLion에 전달한다. `--check`로 호출하면 IDE를 실행하지 않고 실행 파일과 빌드 도구만 확인한다. 실행 파일이 없거나 환경 준비가 실패하면 오류로 종료한다. 실행 요청의 성공만으로 IDE 설정이나 빌드가 검증되는 것은 아니다.
- 기존 VS Code와 Microsoft C++·CMake Tools 확장은 선택 사항이다. [.vscode/settings.json](../.vscode/settings.json)의 `Engine MSVC x64` 터미널 프로필과 [.vscode/c_cpp_properties.json](../.vscode/c_cpp_properties.json)의 C++20 IntelliSense 설정은 그대로 보존한다. CMake 자동 구성은 아직 빌드 파일이 없으므로 꺼져 있다. Windows 컴파일러를 업데이트하면 IntelliSense 경로를 다시 확인한다. Mac 항목은 제안 설정이며 미검증이다.

## IDE와 공통 빌드의 경계

CMakeLists.txt를 공통 빌드 정의로 사용할 계획이다. CLion·Visual Studio·VS Code 등은 각각의 CMake 연동과 로컬 도구 체인을 설정하고, Rider는 지원하는 OS와 프로젝트 형식에 맞춰 연결하는 등 IDE별 방법이 다를 수 있다. 현재 모든 IDE의 엔진 빌드를 검증한 것은 아니다. IDE 프로젝트 설정을 엔진 실행이나 공개 SDK의 의존성으로 만들지 않는다. Windows 전용 실행 스크립트도 공통 빌드 정의를 대신하지 않는다.

`.idea/`, `cmake-build-*/`, `CMakeUserPresets.json`은 기존 .gitignore에서 제외한 로컬 상태다. 다른 기기에서 이를 복사해야만 빌드되는 구조를 만들지 않는다. 공유 가능한 CMakePresets.json은 사용자가 해당 실습에 도달할 때 추가할 수 있다. IDE가 달라도 명령행 CMake 빌드를 계속 지원하며, IDE별 빌드 캐시는 별도 디렉터리에 둔다.

## 시작 방법

1. CLion의 열기(Open) 또는 Start-CLion.cmd로 이 기존 폴더를 연다. 실행 스크립트의 개발자 환경을 새 IDE 프로세스에 전달하려면 기존 CLion을 종료한 뒤 실행한다. GUI의 MSVC·CMake·Ninja 저장 경로는 확인했고, 엔진의 IDE 빌드 동작은 첫 소스 작성 후 별도로 검증한다.
2. 새 프로젝트 마법사를 사용하거나 IDE에서 main.cpp·CMakeLists.txt를 자동 생성하지 않는다. 아직 CMakeLists.txt가 없는 상태이며 두 파일은 첫 실습에서 사용자가 직접 작성한다.
3. IDE와 별개로 프로젝트의 Start-Dev.cmd를 더블클릭하면 MSVC 개발자 터미널을 연다. 도구만 확인할 때는 이 cmd 터미널에서 `Start-Dev.cmd --check`를 실행한다.
4. VS Code를 선택해서 사용할 때는 프로젝트 폴더를 열고 새 `Engine MSVC x64` 터미널을 사용한다. 기존 프로세스가 옛 PATH를 보유했다면 VS Code를 다시 시작한다.

첫 실습에서 두 파일을 직접 작성한 뒤, 준비된 MSVC cmd 터미널의 프로젝트 폴더에서 다음처럼 빌드·실행한다. 이 명령은 IDE 설정 없이 공통 CMake 정의를 사용한다.

```cmd
cmake -S . -B build/windows-debug -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/windows-debug
.\build\windows-debug\EngineSandbox.exe
```

이 엔진 빌드는 아직 실행하지 않았다. CLion의 구성·빌드·실행과 디버거 확인도 첫 실행 파일을 작성한 뒤 별도 결과로 기록한다.

## 실제 도구 검증

CLion이 저장한 customCMakePath·customMakePath를 조율자의 허용된 실행 환경에서 직접 호출해 CMake 4.4.4와 Ninja 1.13.2를 확인했다. 현재 결과는 `.ai-team/environment/clion-toolchain-verification.json`에 있으며 passed=true다. AI 작업자의 제한된 실행 환경에서는 같은 외부 실행 파일 호출이 거부될 수 있다. 작업자의 권한을 넓히지 않고 조율자가 실제 검증을 담당한다. 이 문서 기록 작업의 작업자는 해당 증거와 저장된 XML을 읽으면 되며, 버전 실행이나 GUI 실행을 반복하지 않는다. 문서가 이미 정확하면 변경 파일이 없어도 된다. 엔진 빌드와 Mac은 여전히 미검증이다.

```cmd
Start-Dev.cmd --verify
```

이 명령은 `tools/verify-environment.mjs`를 실행한다. 시스템 TEMP에 별도 검증 프로젝트를 만들어 MSVC+C++20+Ninja로 Debug/Release를 각각 빌드하고 CTest에서 실행한다. 검증용 C++/CMake 파일은 TEMP에만 생성하며 사용자의 엔진 소스나 CMakeLists.txt를 생성·수정하지 않는다.

실제 실행 결과는 `.ai-team/environment/toolchain-verification.json`에 기록한다. 테스트 로그와 임시 폴더 경로도 함께 남긴다. 이 검증은 Windows 도구의 동작만 확인하며 엔진 기능·Mac 빌드·GPU 동작을 검증하지 않는다.

## 첫 실습

옵시디언의 “04 첫 실습 - 공통 C++ 빌드”를 따른다. 먼저 사용자가 src/main.cpp를 직접 만들고 main 함수의 역할을 익힌다. 그다음 표준 출력, CMakeLists.txt 작성, 첫 빌드 순서로 진행한다. 엔진의 C++ 소스와 빌드 정의는 아직 작성하지 않았다.
