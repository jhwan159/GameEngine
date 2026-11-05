#pragma once

struct SDL_Window; // 전방 선언 : "이 파일에서 SDL_Window 구조체를 사용하지만, 정의는 다른 곳에 있음"을 의미합니다.
class EngineApplication
{
    public:
        EngineApplication();
        ~EngineApplication();
    void Run();

private:
    SDL_Window* window = nullptr; // SDL_Window 구조체에 대한 포인터 멤버 변수
};
bool sdlInitialized = false; // SDL 초기화 상태를 추적하는 전역 변수