#pragma once

#include "GameState.h"

#include <random>

class Gameplay : public GameState {
private:
    std::unique_ptr<GameMap> m_map = std::make_unique<GameMap>();
    unsigned long long m_game_data = 0;

    void flipHorizontally();
    void flipDiagonally();

//   static int get2Power(int val);
    static int create2Power(uint8_t power);
    [[nodiscard]] bool checkEmptyTiles() const;
    [[nodiscard]] bool checkEmptySingleTile(int x, int y) const;
    void handleInput(sf::RenderWindow& gameWindow) override;


public:
    void play();
    void renderWindow(sf::RenderWindow& gameWindow) override;
    void drawGame(sf::RenderWindow& gameWindow) override;

    static int generateRandomTileValue();
    std::pair<int, int> generateRandomCoordinates();

    [[nodiscard]] unsigned long long extractTileValue(int line, int column) const;
    void updateTileValue(int line, int column, unsigned long long updateValue);
    void swapTiles(int x1, int y1, int x2, int y2);
    void moveTiles();

    ~Gameplay() override = default;
};