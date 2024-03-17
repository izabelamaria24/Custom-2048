#include "headers/GameMap.h"

GameMap::GameMap() : game_map(4, std::vector<Tile>(4)) {}

void GameMap::drawMap(sf::RenderWindow& window, float tile_size) {
    for (int line = 0; line < 4; line++)
        for (int column = 0; column < 4; column++) {
            sf::RectangleShape tileShape(sf::Vector2f(tile_size, tile_size));
            tileShape.setPosition(static_cast<float>(column) * tile_size, static_cast<float>(line) * tile_size);
            if ((line + column) % 2 == 0)
                tileShape.setFillColor(sf::Color::Green); // Example color
            window.draw(tileShape);
            game_map[line][column] = Tile(tile_size, tileShape.getPosition(), 2);
        }
}