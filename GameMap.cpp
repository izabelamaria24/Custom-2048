


// GameMap.cpp
#include <iostream>
#include "headers/GameMap.h"
#include "headers/Gameplay.h"

GameMap::GameMap() : game_map(4, std::vector<Tile>(4)) {}

void GameMap::drawMap(sf::RenderWindow& window, float tile_size, Gameplay& gameplay) {
    sf::Font font;
    if (!font.loadFromFile(R"(D:\coding\C++ Projects\oop-template\fonts\Roboto-Black.ttf)"))
    {
        std::cerr <<"fail";
    }
    for (int line = 0; line < 4; line++)
        for (int column = 0; column < 4; column++) {
            uint8_t extractedValue = gameplay.extractTileValue(line, column);
            int realValue = Gameplay::create2Power(extractedValue);

            sf::Text text;
            text.setFont(font);
            text.setString(std::to_string(realValue));
            text.setCharacterSize(50);
            text.setFillColor(sf::Color::Black);
            text.setPosition(static_cast<float>(column) * tile_size + tile_size/2, static_cast<float>(line) * tile_size + tile_size/2);

            sf::RectangleShape tileShape(sf::Vector2f(tile_size, tile_size));
            tileShape.setPosition(static_cast<float>(column) * tile_size, static_cast<float>(line) * tile_size);
            tileShape.setFillColor(sf::Color::White);
            tileShape.setOutlineThickness(5); // Set outline thickness
            tileShape.setOutlineColor(sf::Color::Black); // Set outline color

            window.draw(tileShape);

            if (realValue != 1)
                window.draw(text);
            game_map[line][column] = Tile(tile_size, tileShape.getPosition(), 2);
        }
}