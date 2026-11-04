#pragma once

struct SDL_Window; // 전방 선언 : "이 파일에서 SDL_Window 구조체를 사용하지만, 정의는 다른 곳에 있음"을 의미합니다.
class EngineApplication
{
    public:
        EngineApplication();
        ~EngineApplication();
    void Run();

private:
    SDL_Window* window = nullptr; // SDL_Window 구조체에 대한 포인터를 초기화합니다. nullptr로 초기화하여 아직 창이 생성되지 않았음을 나타냅니다.
};