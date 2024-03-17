#include "Tile.h"
#include <vector>
#include <cstdint>

class GameMap{
private:
    std::vector<std::vector<Tile>> game_map;

public:
    GameMap();
    void drawMap(sf::RenderWindow& window, float tile_size);
};