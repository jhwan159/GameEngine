#include "EngineApplication.h"
#include <iostream>

#include "EngineStartup.h"

EngineApplication::EngineApplication()
{
    PrintStartupMessage();
}
EngineApplication::~EngineApplication()
{
    std::cout << "EngineStop!\n";
}
void EngineApplication::Run(int frameCount)
{
    for (int frame = 0; frame < frameCount; ++frame)
    {
        std::cout << "Frame" << (frame + 1) << '\n';
    }
}