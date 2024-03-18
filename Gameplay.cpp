#include "headers/Gameplay.h"

#include <cmath>
#include <random>

// game rendering method for gameplay
void Gameplay::renderWindow(sf::RenderWindow &gameWindow) {
    // creating game window
    gameWindow.create(sf::VideoMode({800, 800}), "2048", sf::Style::Default);
    gameWindow.setVerticalSyncEnabled(true);

    drawGame(gameWindow);
    gameWindow.display();
//
//    using namespace std::chrono_literals;
//    std::this_thread::sleep_for(300ms);
//
//    gameWindow.clear();
//    gameWindow.display();

    // Main game loop
    while (gameWindow.isOpen()) {
        handleInput(gameWindow);
    }

}

// input handling method
void Gameplay::handleInput(sf::RenderWindow& gameWindow) {
    sf::Event e{};
    bool exit = false;

    while (gameWindow.pollEvent(e)) {
        switch(e.type) {
            case sf::Event::Closed:
                gameWindow.close();
                break;
            case sf::Event::KeyPressed:
                if(e.key.code == sf::Keyboard::Escape)
                    exit = true;
                break;
            default:
                break;
        }

        if(exit) {
            gameWindow.close();
            break;
        }
    }
}

void Gameplay::drawGame(sf::RenderWindow& gameWindow) {
    this->m_map->drawMap(gameWindow, std::sqrt(static_cast<float>((gameWindow.getSize().x - 20) * gameWindow.getSize().y) / 16), *this);
}


// methods for checking empty tiles
bool Gameplay::checkEmptyTiles() const {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            unsigned long long copy_data = this->m_game_data;
            int bitPos = (i * 4 + j) * 4;

            // if we find an empty cell
            if (!((copy_data >> bitPos) & 0xFULL))
                return true;
        }
    }
    return false;
}

bool Gameplay::checkEmptySingleTile(int x, int y) const {
    return extractTileValue(x,y) == 0;
}


// methods for generating random cells and values for them

int Gameplay::generateRandomTileValue() {
//    std::random_device rd;
    std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(0, 99);

    int rand = dist(gen);

    return (rand < 90) ? 1 : 2;
}

std::pair<int, int> Gameplay::generateRandomCoordinates(){
    if (!checkEmptyTiles()) {
//        std::cout << "Game is over! No empty cells left!";
    }

//    std::random_device rd;
    std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(0, 16);

    int rand = dist(gen);

    int x = rand / 4, y = rand % 4;
    while (!checkEmptySingleTile(x, y)) {
        rand = dist(gen);
        x = rand / 4, y = rand % 4;
    }

    return {x, y};
}

// method for extracting a tile from the 64 bits number
unsigned long long Gameplay::extractTileValue(int line, int column) const{
    // m_game_data is 64 bits integer
    int bitPos = (line * 4 + column) * 4;
    return (this->m_game_data >> bitPos) & 0xFULL;
}

// method for updating a tile from the 64 bits number
void Gameplay::updateTileValue(int line, int column, unsigned long long updateValue) {
    int bitPos = (line * 4 + column) * 4;
    unsigned long long mask = ~(0xFULL << bitPos);

    unsigned long long clearedData = this->m_game_data & mask;

    unsigned long long shiftedUpdateValue = updateValue << bitPos;

    this->m_game_data = clearedData | shiftedUpdateValue;
}
