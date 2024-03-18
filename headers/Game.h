#pragma once
#include "GameState.h"

class Game {
public:
    Game();

//    void setGameState(std::unique_ptr<GameState> newState);
    std::unique_ptr<GameState>& getCurrentState();

private:
    std::unique_ptr<GameState> m_currentState;
    sf::RenderWindow gameWindow;
};