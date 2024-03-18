#pragma once

#include "GameState.h"

#include <random>

class Gameplay : public GameState {
private:
    std::unique_ptr<GameMap> m_map = std::make_unique<GameMap>();
    unsigned long long m_game_data = 0;

    [[nodiscard]] bool checkEmptyTiles() const;
    [[nodiscard]] bool checkEmptySingleTile(int x, int y) const;
    void handleInput(sf::RenderWindow& gameWindow) override;


public:
    void renderWindow(sf::RenderWindow& gameWindow) override;
    void drawGame(sf::RenderWindow& gameWindow) override;

    static int generateRandomTileValue();
    std::pair<int, int> generateRandomCoordinates();

    [[nodiscard]] unsigned long long extractTileValue(int line, int column) const;
    void updateTileValue(int line, int column, unsigned long long updateValue);

    ~Gameplay() override = default;
};