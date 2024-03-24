#pragma once
#include <SFML/Graphics.hpp>

class Tile {
public:
    Tile() : m_tile_size(0), m_tile_position(sf::Vector2f(0, 0)), m_tile_value(0) {}

    explicit Tile(float input_tile_size, sf::Vector2f input_position = sf::Vector2f(0,0), int input_tile_value = 0)
                                    : m_tile_size(input_tile_size), m_tile_position(input_position), m_tile_value(input_tile_value) {}

    Tile(const Tile& other) {
        this->m_tile_value = other.m_tile_value;
        this->m_tile_position = other.m_tile_position;
        this->m_tile_size = other.m_tile_size;
    }

    // Overloaded assignment operator
    Tile& operator=(const Tile& other) {
        if (this != &other) {
            this->m_tile_size = other.m_tile_size;
            this->m_tile_position = other.m_tile_position;
            this->m_tile_value = other.m_tile_value;
        }
        return *this;
    }

    Tile(Tile&& other) noexcept : m_tile_size(other.m_tile_size), m_tile_position(other.m_tile_position), m_tile_value(other.m_tile_value) {}

    Tile& operator=(Tile&& other) noexcept {
        if (this != &other) {
            this->m_tile_size = other.m_tile_size;
            this->m_tile_position = other.m_tile_position;
            this->m_tile_value = other.m_tile_value;
        }
        return *this;
    }

    ~Tile() = default;

    friend std::ostream& operator<<(std::ostream& stream, const Tile&tile) {
        stream << "Tile size: " << tile.m_tile_size << '\n';
        stream << "Tile value: " << tile.m_tile_value << '\n';
        stream << "Tile position: " << "x = " << tile.m_tile_position.x << ", y = " << tile.m_tile_position.y;
        return stream;
    }

protected:
    float m_tile_size;
    sf::Vector2f m_tile_position;
    int m_tile_value;
};