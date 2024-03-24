#include <SFML/Graphics.hpp>
#include "env_fixes.h"
#include "headers/Game.h"

int main() {
    init_threads();
    Game game;
    sf::RenderWindow window;
    game.getCurrentState()->renderWindow(window);
//    Tile tile;
//    std::cout << tile;
//    std::cout << '\n';
//    Tile tile2(2, sf::Vector2f(50, 50),50);
//    std::cout << tile2 << '\n';
//
//    Tile tile3(tile2);
//    std::cout << tile3;

    return 0;
}
