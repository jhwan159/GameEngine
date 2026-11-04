cmake_minimum_required(VERSION 3.28) #cmake 최소 버전
project(PersonalGameEngine LANGUAGES CXX) #project를 선언하고 이름과 언어 지정
add_executable(EngineSandbox src/main.cpp)#뭘로 어떤 실행파일을 만들겠다는지 적는것이다.
target_compile_features(EngineSandbox PRIVATE cxx_std_20) # 컴파일 기능 지정 C++20을 요구

include(FetchContent)            # FetchContent 기능 불러오기
FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.4.20   # 버전을 고정해야 기기마다 같은 SDL로 빌드됨
        GIT_SHALLOW TRUE)        # 전체 기록 말고 해당 버전만 받기
set(SDL_SHARED OFF CACHE BOOL "" FORCE)  # DLL 대신
set(SDL_STATIC ON CACHE BOOL "" FORCE)   # 정적 라이브러리로 빌드
FetchContent_MakeAvailable(SDL3) # 받아서 SDL3::SDL3 타깃 만들기

add_library(EngineCore STATIC
        src/EngineStartup.cpp
        src/EngineApplication.cpp)
target_compile_features(EngineCore PUBLIC cxx_std_20)
target_include_directories(EngineCore PUBLIC src)
target_link_libraries(EngineSandbox PRIVATE EngineCore)
target_link_libraries(EngineCore PUBLIC SDL3::SDL3)
