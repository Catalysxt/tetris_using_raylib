// main.cpp
//
// This file is intentionally minimal. All it does is create an Application
// object and call Run(). The Application's constructor opens the window (RAII),
// Run() executes the game loop, and when Run() returns, the Application
// destructor automatically closes the window — clean and predictable.

#include "core/application.h"

int main()
{
    // Configure the window. These could come from a config file in the future,
    // but compile-time defaults are perfectly fine for now.
    constexpr WindowConfig config{
        .width     = 500,
        .height    = 620,
        .title     = "Tetris",
        .targetFps = 60
    };

    Application app{config};
    app.Run();

    return 0;
}