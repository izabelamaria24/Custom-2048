#pragma once

#include <chrono>
#include <thread>
#include <memory>

#include "GameMap.h"
class Gameplay;

class GameState {
protected:
    virtual void handleInput(sf::RenderWindow& gameWindow) = 0;

public:
    GameState() = default;
    virtual void renderWindow(sf::RenderWindow& gameWindow) = 0;
    virtual ~GameState() = default;

    virtual void drawGame(sf::RenderWindow& gameWindow) = 0;
};