#include "EngineStartup.h"
#include <iostream>
#include "EngineApplication.h"

int main()
    {
        {
            EngineApplication app;
            std::cout << "Engine running\n";

            app.Run();
        }
        std::cout << "Main finished\n";
        return 0;
    }