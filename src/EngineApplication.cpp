#include <iostream>
#include <chrono>
#include <thread>
#include "EngineStartup.h"
#include "EngineApplication.h"
#include <SDL3/SDL.h>

EngineApplication::EngineApplication()
{
    PrintStartupMessage();

    if (SDL_Init(SDL_INIT_VIDEO) < 0) // SDL 초기화
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    }
    window = SDL_CreateWindow("Atelier Engine", 1280, 720, 0);
    if (window == nullptr) // 창 생성 실패 시
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    }
}
EngineApplication::~EngineApplication()
{
    SDL_DestroyWindow(window); // 창 파괴
    SDL_Quit(); // SDL 종료
    std::cout << "Engine Stoped" << std::endl;
}
void EngineApplication::Run()
{
    using Clock = std::chrono::steady_clock;
    auto previous = Clock::now();
    bool running = true;
   while (running) 
    {
        SDL_Event event; // 이벤트 처리 : 쌓인 이벤트를 전부 꺼낼 때까지 반복
        while (SDL_PollEvent(&event)) // 이벤트 큐에서 이벤트를 가져와 처리
        {
            if (event.type == SDL_EVENT_QUIT) // 종료 이벤트 처리
            {
                running = false;
            }
        }
        auto current = Clock::now();
        std::chrono::duration<double> elapsed = current - previous;
        previous = current;
        
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

}