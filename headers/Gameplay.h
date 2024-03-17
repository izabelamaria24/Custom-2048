#pragma once
#include "GameState.h"
#include <random>

class Gameplay : public GameState {
private:
    std::unique_ptr<GameMap> m_map = std::make_unique<GameMap>();
//    long long m_game_data;

    void handleInput(sf::RenderWindow& gameWindow) override;

//    [[nodiscard]] bool checkEmptyTiles() const;
//    [[nodiscard]] bool checkEmptySingleTile(int x, int y) const;

//    static uint8_t get2Power(int val);
//    static int create2Power(uint8_t power);

public:
    void renderWindow(sf::RenderWindow& gameWindow) override;
    std::unique_ptr<GameMap>& drawGame(sf::RenderWindow& gameWindow) override;

//    static int generateRandomTileValue();
//    std::pair<int, int> generateRandomCoordinates();
//
//    [[nodiscard]] std::uint8_t extractTileValue(int line, int column) const;

//    void updateTileValue(int line, int column);

    ~Gameplay() override = default;
};