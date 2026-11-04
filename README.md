# Personal Game Engine

C++20으로 게임 엔진의 기초를 배우는 프로젝트입니다.

Windows 데스크톱의 CLion과 macOS에서 같은 소스와 `debug` 빌드 프리셋을 사용합니다.
컴파일러와 디버거는 각 기기에 설치된 도구를 사용하며, 경로를 공통 설정에 고정하지 않습니다.

## 개발 환경 (macOS)

- Apple Clang: C++ 컴파일러 (Xcode 또는 Command Line Tools에 포함)
- CMake 3.28 이상: 빌드 설정 생성
- Ninja: 컴파일 및 링크 실행
- LLDB: 중단점과 변수 확인을 위한 디버거

Clang과 LLDB가 없다면 `xcode-select --install`로 설치합니다.
Homebrew가 설치된 환경에서 빌드 도구는 다음 명령으로 설치합니다.

```sh
brew install cmake ninja
```

## 빌드 및 실행 (macOS)

터미널에서 저장소 폴더로 이동한 뒤 실행합니다.

```sh
cmake --preset debug
cmake --build --preset debug
./build/debug/EngineSandbox
```

소스 수정 후에는 빌드와 실행 명령만 다시 사용하면 됩니다.
빌드 설정을 변경하거나 소스 파일을 추가했을 때는 구성 명령도 다시 실행합니다.

프로그램은 1280×720 빈 창을 띄우고, 창의 X 버튼을 누르면 종료합니다.

```text
EngineStart!
Engine running
Engine Stoped
Main finished
```

## macOS + VSCode

VSCode에서 `/Users/chojaehwan/Development/GameEngine` 폴더를 열어 개발합니다.
이 경로는 현재 Mac의 위치이며 다른 기기의 clone 경로와 같을 필요는 없습니다.

필요한 확장:

- CMake Tools (`ms-vscode.cmake-tools`): 프리셋으로 구성·빌드
- clangd (`llvm-vs-code-extensions.vscode-clangd`): 코드 자동완성과 오류 표시
- CodeLLDB (`vadimcn.vscode-lldb`): 디버깅

공통 설정은 `.vscode/`에 있으며 Git으로 공유합니다.

- `settings.json`: CMake Tools가 `CMakePresets.json`의 `debug` 프리셋을 사용하고,
  C/C++ 확장의 IntelliSense를 끄고 clangd를 사용합니다.
- `launch.json`: `build/debug/EngineSandbox`를 LLDB로 실행합니다.

폴더를 처음 열면 CMake Tools가 구성 프리셋을 묻습니다. `Debug (C++20)`을 선택합니다.
아래쪽 상태 표시줄의 Build 버튼(또는 F7)으로 빌드합니다.
디버깅할 때는 소스 줄 왼쪽에 중단점을 설정한 후 F5로 `EngineSandbox (LLDB)`를 실행합니다.
F5는 빌드하지 않으므로 코드를 고친 뒤에는 먼저 빌드합니다.

## Windows + CLion

Windows 데스크톱도 이후 VSCode로 옮길 예정입니다. 그때 `launch.json`에
`EngineSandbox.exe`용 디버깅 구성을 추가합니다.

1. GitHub에서 이 저장소를 clone하거나 기존 로컬 저장소를 최신 상태로 업데이트합니다.
2. CLion에서 저장소의 `CMakeLists.txt`가 있는 폴더를 엽니다.
3. `Settings > Build, Execution, Deployment > Toolchains`에서 기존에 정상 작동하는
   도구 구성을 사용합니다. 새로 설정한다면 `MinGW`의 `Bundled MinGW`와
   내장 CMake·Ninja·GDB를 선택합니다. CMake는 3.28 이상이어야 합니다.
4. `Settings > Build, Execution, Deployment > CMake`에서 가져온 `debug` 프리셋의
   `Enable profile`을 켜고 해당 툴체인이 선택되어 있는지 확인합니다.
   프리셋이 보이지 않으면 `Ctrl+Shift+A`에서 `Load CMake Presets`를 실행합니다.
5. 실행 구성에서 `EngineSandbox`와 `debug` 프로필을 선택하고 Build/Run을 실행합니다.
   디버깅은 소스 줄 왼쪽에 중단점을 찍고 Debug를 실행합니다.

이 프리셋의 Windows 실행 파일은 `build/debug/EngineSandbox.exe`입니다.
내장 도구가 Windows의 일반 터미널 PATH에 자동으로 등록되는 것은 아니므로,
위 과정은 CLion의 Build/Run 기능을 기준으로 합니다.

공식 안내: [Windows 툴체인 설정](https://www.jetbrains.com/help/clion/quick-tutorial-on-configuring-clion-on-windows.html),
[CMake 프리셋 가져오기와 활성화](https://www.jetbrains.com/help/clion/cmake-presets.html).

## 두 기기를 오가며 작업하기

각 기기에 저장소를 따로 clone하고 GitHub로 소스와 공통 설정을 동기화합니다.
`build/`, `cmake-build-*/`, `.idea/`와 `CMakeUserPresets.json`은 공유하지 않습니다.
실행 파일·정적 라이브러리·CMake 캐시는 각 운영체제에서 새로 만듭니다.
저장소 전체를 클라우드 폴더로 복사하여 두 기기에서 동시에 편집하지 않습니다.

작업을 시작할 때 저장소 폴더에서:

```sh
git status
git pull --ff-only
```

커밋하지 않은 변경사항이 있으면 먼저 확인하고 정리합니다.
`pull`이 충돌이나 분기 문제로 중단되면 강제 덮어쓰기 없이 원인을 확인합니다.
소스를 받은 뒤에는 각 기기에서 다시 빌드합니다.

작업을 끝내고 다른 기기로 이동하기 전:

```sh
git add .
git diff --cached
git commit -m "Describe the change"
git push
```

스테이징된 파일을 확인한 뒤 해당 작업에 맞는 커밋 메시지를 적습니다.
새 개발 환경 설정도 커밋·푸시해야 다른 기기에서 받을 수 있습니다.
두 기기 모두에서 같은 파일을 수정하기 전, 먼저 이전 기기의 변경사항을 올리고 받습니다.

## 디버깅 (macOS 터미널)

```sh
lldb ./build/debug/EngineSandbox
```

LLDB 프롬프트에서 다음 순서로 실행합니다.

```text
breakpoint set --name main
run
next
frame variable
continue
quit
```

`next`는 한 줄 실행, `frame variable`은 현재 함수의 지역 변수 확인입니다.
Debug 빌드에는 소스와 변수를 추적할 수 있는 디버그 정보가 포함됩니다.

## 프로젝트 구성

- `src/main.cpp`: 실행 프로그램의 시작점
- `src/EngineApplication.*`: 엔진의 생성·실행·종료
- `src/EngineStartup.*`: 시작 메시지 출력
- `EngineCore`: 공통 코드를 묶은 정적 라이브러리
- `EngineSandbox`: `EngineCore`를 연결하여 실행하는 학습 프로그램

`build/debug/compile_commands.json`은 각 소스의 컴파일 옵션을 기록합니다.
clangd를 사용하는 편집기는 `.clangd` 설정을 통해 이 파일을 읽습니다.
빌드 결과와 개인별 IDE 설정은 Git에서 제외합니다.

새 `.cpp` 파일을 추가하면 `CMakeLists.txt`의 해당 타깃에도 등록합니다.
창과 입력은 SDL3를 사용합니다. 첫 구성 때 CMake가 `FetchContent`로 SDL3 소스를 받아 함께 빌드하므로 인터넷 연결이 필요합니다.
