#include "./headers/Game.h"
#include "./headers/Gameplay.h"

// game constructor
Game::Game() : m_currentState(std::make_unique<Gameplay>()) {}

// method for changing game state
//void Game::setGameState(std::unique_ptr<GameState> newState) {
//    m_currentState = std::move(newState);
//}

// game state getter
std::unique_ptr<GameState>& Game::getCurrentState(){
    return m_currentState;
}