#include <iostream>
#include "EngineApplication.h"

int main()
    {
        {
            EngineApplication app;
            std::cout << "Engine running\n";

            app.Run(1);
        }
        std::cout << "Main finished\n";
        return 0;
    }