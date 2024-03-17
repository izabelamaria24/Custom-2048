#include "headers/Gameplay.h"
#include <cmath>

// input handling method
void Gameplay::handleInput(sf::RenderWindow& gameWindow) {
    sf::Event e{};
    bool exit = false;

    while (gameWindow.pollEvent(e)) {
        switch(e.type) {
            case sf::Event::Closed:
                gameWindow.close();
                break;
            case sf::Event::KeyPressed:
                if(e.key.code == sf::Keyboard::Escape)
                    exit = true;
                break;
            default:
                break;
        }

        if(exit) {
            gameWindow.close();
            break;
        }
    }
}

// game rendering method for gameplay
void Gameplay::renderWindow(sf::RenderWindow &gameWindow) {
    // creating game window
    gameWindow.create(sf::VideoMode({800, 800}), "2048", sf::Style::Default);
    gameWindow.setVerticalSyncEnabled(true);

    while (gameWindow.isOpen()) {
        drawGame(gameWindow);
        gameWindow.display();

        handleInput(gameWindow);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(300ms);

        gameWindow.clear();
        gameWindow.display();
    }
}

std::unique_ptr<GameMap> & Gameplay::drawGame(sf::RenderWindow& gameWindow) {
    this->m_map->drawMap(gameWindow, std::sqrt(static_cast<float>((gameWindow.getSize().x - 20) * gameWindow.getSize().y) / 16));

    return this->m_map;
}