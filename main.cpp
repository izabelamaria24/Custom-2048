//#include <iostream>
//#include <thread>
//#include <Helper.h>

#include <SFML/Graphics.hpp>
#include "env_fixes.h"
#include "headers/Game.h"

int main() {
    init_threads();
    Game game;
    sf::RenderWindow window;
    game.getCurrentState()->renderWindow(window);


//    Helper helper;
//    helper.help();
//    sf::RenderWindow window;
//    GameMap gamemap;
    ///////////////////////////////////////////////////////////////////////////
    /// NOTE: sync with env variable APP_WINDOW from .github/workflows/cmake.yml:31
//    window.create(sf::VideoMode({800, 700}), "My Window", sf::Style::Default);

    /// NOTE: mandatory use one of vsync or FPS limit (not both)            ///
    /// This is needed so we do not burn the GPU                            ///
//    window.setVerticalSyncEnabled(true);                            ///
    /// window.setFramerateLimit(60);                                       ///
    ///////////////////////////////////////////////////////////////////////////
    return 0;
}
