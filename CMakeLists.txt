cmake_minimum_required(VERSION 3.28) #cmake 최소 버전
project(PersonalGameEngine LANGUAGES CXX) #project를 선언하고 이름과 언어 지정
add_executable(EngineSandbox src/main.cpp)#뭘로 어떤 실행파일을 만들겠다는지 적는것이다.
target_compile_features(EngineSandbox PRIVATE cxx_std_20) # 컴파일 기능 지정 C++20을 요구
add_library(EngineCore STATIC
        src/EngineStartup.cpp
        src/EngineApplication.cpp)
target_compile_features(EngineCore PUBLIC cxx_std_20)
target_include_directories(EngineCore PUBLIC src)
target_link_libraries(EngineSandbox PRIVATE EngineCore)