#pragma once

#include "GameState.h"

#include <random>

class Gameplay : public GameState {
private:
    std::unique_ptr<GameMap> m_map = std::make_unique<GameMap>();
    unsigned long long m_game_data = 0;

    void flipHorizontally();
    void flipDiagonally();

    [[nodiscard]] bool checkEmptyTiles() const;
    [[nodiscard]] bool checkEmptySingleTile(int x, int y) const;
    void handleInput(sf::RenderWindow& gameWindow) override;


public:
    void play();
    void renderWindow(sf::RenderWindow& gameWindow) override;
    void drawGame(sf::RenderWindow& gameWindow) override;

    static int generateRandomTileValue();
    std::pair<int, int> generateRandomCoordinates();

    //   static int get2Power(int val);
    static int create2Power(uint8_t power);

    [[nodiscard]] unsigned long long extractTileValue(int line, int column) const;
    void updateTileValue(int line, int column, unsigned long long updateValue);
    void swapTiles(int x1, int y1, int x2, int y2);
    bool moveTiles();
    void continueGame(sf::RenderWindow& gameWindow);

    [[nodiscard]] bool gameOver() const;

    Gameplay() = default;

    Gameplay(Gameplay&& other) noexcept
            : m_map(std::move(other.m_map)), m_game_data(other.m_game_data) {
    }

    Gameplay& operator=(Gameplay&& other) noexcept {
        if (this != &other) {
            this->m_game_data = other.m_game_data;
            this->m_map = std::move(other.m_map);
        }
        return *this;
    }

    ~Gameplay() override = default;
};