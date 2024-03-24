#pragma once

#include "Tile.h"

#include <vector>
#include <cstdint>

class Gameplay;

class GameMap{
private:
    std::vector<std::vector<Tile>> game_map;

public:
    GameMap();
    void drawMap(sf::RenderWindow& window, float tile_size, Gameplay& gameplay);

    GameMap(GameMap&& other) noexcept : game_map(std::move(other.game_map)) {}

    GameMap& operator=(GameMap&& other) noexcept {
        if (this != &other) {
            this->game_map = std::move(other.game_map);
        }
        return *this;
    }

    ~GameMap() = default;
};