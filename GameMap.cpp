


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

            sf::RectangleShape tileShape(sf::Vector2f(tile_size, tile_size));
            tileShape.setPosition(static_cast<float>(column) * tile_size, static_cast<float>(line) * tile_size);

            sf::Text text;
            text.setFont(font);
            text.setString(std::to_string(realValue));
            text.setCharacterSize(50);
            text.setFillColor(sf::Color::Black);
            text.setPosition(
                    tileShape.getPosition().x + (tile_size - text.getLocalBounds().width) / 2,
                    tileShape.getPosition().y + (tile_size - text.getLocalBounds().height) / 2
            );

            sf::Color color;
            switch(realValue) {
                case 2:
                    color = sf::Color(243, 230, 250);
                    break;
                case 4:
                    color = sf::Color(239, 209, 255);
                    break;
                case 8:
                    color = sf::Color(231, 192, 252);
                    break;
                case 16:
                    color = sf::Color(222, 164, 252);
                    break;
                case 32:
                    color = sf::Color(216, 146, 252);
                    break;
                case 64:
                    color = sf::Color(210, 126, 252);
                    break;
                case 128:
                    color = sf::Color(203, 104, 252);
                    break;
                case 256:
                    color = sf::Color(155, 62, 201);
                    break;
                case 512:
                    color = sf::Color(100, 28, 135);
                    break;
                case 1024:
                    color = sf::Color(70, 14, 97);
                    break;
                case 2048:
                    color = sf::Color(52, 7, 74);
                    break;
                case 4096:
                    color = sf::Color(36, 5, 51);
                    break;
                default:
                    color = sf::Color::Black;
            }

            tileShape.setFillColor(color);

//            tileShape.setOutlineThickness(10); // Set outline thickness
//            tileShape.setOutlineColor(sf::Color::Black); // Set outline color

            window.draw(tileShape);

            if (realValue != 1)
                window.draw(text);
            game_map[line][column] = Tile(tile_size, tileShape.getPosition(), 2);
        }
}