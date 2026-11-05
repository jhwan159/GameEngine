# PersonalGameEngine

사용자가 C++을 배우며 직접 만드는 개인 게임 엔진. 현재는 계획·AI 검토 설정 단계이며, 엔진 소스와 빌드 파일은 첫 실습에서 직접 작성한다.

- 플랫폼: Windows + M5 macOS.
- 그래픽: D3D12 + Metal.
- 개발 시간: 주 10시간, 학습 포함.
- 첫 게임: 힐링·농사 게임. 2D부터 시작해 3D로 확장.

협업 규칙은 [AGENTS.md](AGENTS.md), 실제 운영 순서는 [검토 흐름](docs/REVIEW_WORKFLOW.md)에 있다. 옵시디언의 전체 계획은 각 기기의 PLAN_PATHS.json으로 찾는다.

## 지금 할 일

선호 IDE는 CLion이다. **CLion 2026.2.3 설치와 GUI 툴체인 설정을 완료했다.** 사용자가 첫 실행을 마친 뒤 Visual Studio/MSVC를 기본 툴체인으로 지정하고 CMake 4.4.4와 Ninja 1.13.2 경로를 연결·저장했다. [Start-CLion.cmd](Start-CLion.cmd)로 기존 프로젝트 폴더를 연다. `Start-CLion.cmd --check`는 IDE를 실행하지 않고 실행 파일과 도구만 점검한다. 새 프로젝트 마법사로 main.cpp나 CMakeLists.txt를 자동 생성하지 않는다. [개발 환경 안내](docs/DEVELOPMENT_ENVIRONMENT.md)를 참고한 뒤 src/main.cpp와 CMakeLists.txt를 직접 작성한다. 첫 목표는 EngineSandbox 실행 파일에서 `Engine boot OK`를 출력하는 것이다.

CMake를 공통 빌드 정의로 사용하고 명령행 빌드를 유지할 계획이다. 다른 IDE도 지원 범위와 프로젝트 연결 방식에 맞춰 사용할 수 있도록 하며, 현재 모든 IDE에서 검증한 것은 아니다. 기존 VS Code 설정은 선택 사항이고, `.idea`와 `CMakeUserPresets.json`은 기기별 로컬 설정이다. IDE 설정을 엔진 실행이나 공개 SDK의 필수 조건으로 만들지 않는다.

CMake 4.4.4와 Ninja 1.13.2를 설치했고 개발 환경 진입 명령을 준비했다. 외부 MSVC 개발자 터미널은 Start-Dev.cmd로 연다. Windows 임시 C++20 Debug·Release 빌드와 CTest 검증 결과는 .ai-team/environment/toolchain-verification.json, CLion 설정 근거는 .ai-team/environment/clion-setup.json에 기록돼 있다. Git 저장소 초기화와 첫 프로그램의 구현은 남아 있다. 엔진의 IDE 빌드·디버깅과 Mac 설치·빌드는 아직 확인하지 않았다. 라이선스 상태 자체를 검사하거나 변경하지 않았다.
