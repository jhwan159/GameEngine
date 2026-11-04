#include "EngineApplication.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "EngineStartup.h"

EngineApplication::EngineApplication()
{
    PrintStartupMessage();
}
EngineApplication::~EngineApplication()
{
    std::cout << "EngineStop!\n";
}
void EngineApplication::Run()
{
    using Clock = std::chrono::steady_clock;
    auto start = Clock::now();
    auto previous = start;
   while (true)
    {
        auto now = Clock::now();
        std::chrono::duration<double> elapsed = now - previous;
        std::chrono::duration<double> total = now - start;
        previous = now;

        if (total.count() >= 3.0)
            break;
        std::cout <<"frame time: " << elapsed.count() << "s\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

}