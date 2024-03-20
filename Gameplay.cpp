#include "headers/Gameplay.h"

#include <cmath>
#include <random>

// method to put everything together, represents one more step into the game logic
void Gameplay::play() {
    int generatedValue = generateRandomTileValue();
    std::pair<int, int>coord = generateRandomCoordinates();

    updateTileValue(coord.first, coord.second, generatedValue);
}

// game rendering method for gameplay
void Gameplay::renderWindow(sf::RenderWindow &gameWindow) {
    // creating game window
    gameWindow.create(sf::VideoMode({800, 800}), "2048", sf::Style::Default);
    gameWindow.setVerticalSyncEnabled(true);

    continueGame(gameWindow);

    // Main game loop
    while (gameWindow.isOpen()) {
        if (!gameOver()) {
            handleInput(gameWindow);
        } else {
            sf::Font font;
            if (!font.loadFromFile(R"(D:\coding\C++ Projects\oop-template\fonts\Roboto-Black.ttf)"))
            {
                // TODO throw error
            }
            sf::Text text;
            text.setFont(font);
            text.setString("Game over!");
            text.setCharacterSize(50);
            text.setFillColor(sf::Color::White);
            sf::FloatRect textBounds = text.getLocalBounds();
            text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                           textBounds.top + textBounds.height / 2.0f);
            text.setPosition(gameWindow.getSize().x / 2.0f, gameWindow.getSize().y / 2.0f);
            gameWindow.clear();
            gameWindow.draw(text);
            gameWindow.display();
            handleInput(gameWindow);
        }
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

                if(e.key.code == sf::Keyboard::Right) {
                    bool available = moveTiles();

                    if (available) continueGame(gameWindow);
                }
                if (e.key.code == sf::Keyboard::Left) {
                    flipHorizontally();
                    bool available = moveTiles();
                    flipHorizontally();

                    if (available) continueGame(gameWindow);
                }
                if (e.key.code == sf::Keyboard::Down) {
                    flipDiagonally();
                    bool available = moveTiles();
                    flipDiagonally();

                    if (available) continueGame(gameWindow);
                }
                if (e.key.code == sf::Keyboard::Up) {
                    flipDiagonally();
                    flipHorizontally();
                    bool available = moveTiles();
                    flipHorizontally();
                    flipDiagonally();

                    if (available) continueGame(gameWindow);
                }
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

void Gameplay::continueGame(sf::RenderWindow& gameWindow) {
    play();
    drawGame(gameWindow);
    gameWindow.display();
}

void Gameplay::drawGame(sf::RenderWindow& gameWindow) {
    this->m_map->drawMap(gameWindow, std::sqrt(static_cast<float>(gameWindow.getSize().x * gameWindow.getSize().y) / 16), *this);
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

// method for swapping 2 tiles
void Gameplay::swapTiles(int x1, int y1, int x2, int y2) {
    int bitPos1 = (x1 * 4 + y1) * 4;
    int bitPos2 = (x2 * 4 + y2) * 4;

    unsigned long long mask1 = 0xFULL << bitPos1;
    unsigned long long mask2 = 0xFULL << bitPos2;

    unsigned long long value1 = (this->m_game_data & mask1) >> bitPos1;
    unsigned long long value2 = (this->m_game_data & mask2) >> bitPos2;

    unsigned long long clearedData = this->m_game_data & ~(mask1 | mask2);

    unsigned long long shiftedValue1 = value1 << bitPos2;
    unsigned long long shiftedValue2 = value2 << bitPos1;

    this->m_game_data = clearedData | shiftedValue1 | shiftedValue2;
}

// method called when keypress detected
bool Gameplay::moveTiles() {
    bool ok = false;
    for (int line = 0; line < 4; line++) {
        for (int to = 3; to >= 0; to--) {
            int from = to - 1;
            while (from >= 0 && extractTileValue(line, from) == 0) from--;
            if (from < 0) break;
            if (extractTileValue(line, to) == extractTileValue(line, from)){
                ok = true;
                updateTileValue(line, to, extractTileValue(line, to) + 1);
                updateTileValue(line, from, 0);
            }
            if (extractTileValue(line, to) == 0) {
                ok = true;
                swapTiles(line, to, line, from);
                ++to;
            }
        }
    }
    if (ok) return true;
    return false;
}

// methods for creating a 2's power or getting a 2's power

//int Gameplay::get2Power(int val) {
//    int power = __builtin_ctz(val);
//    return power;
//}

int Gameplay::create2Power(uint8_t power) {
    return 1 << power;
}

// private flip grid methods
void Gameplay::flipHorizontally() {
    for (int x = 0; x < 4; x++) {
        swapTiles(x, 0, x, 3);
        swapTiles(x, 1, x, 2);
    }
}

void Gameplay::flipDiagonally(){
    for (int i = 0; i < 3; i++)
        for (int j = i + 1; j < 4; j++)
            swapTiles(i, j, j, i);
}

bool Gameplay::gameOver() const {
    if (checkEmptyTiles())
        return false;

    // Check horizontally
    for (int line = 0; line < 4; line++) {
        for (int col = 0; col < 3; col++) {
            unsigned long long value1 = extractTileValue(line, col);
            unsigned long long value2 = extractTileValue(line, col + 1);

            if (value1 == value2)
                return false;
        }
    }

    // Check vertically
    for (int col = 0; col < 4; col++) {
        for (int line = 0; line < 3; line++) {
            unsigned long long value1 = extractTileValue(line, col);
            unsigned long long value2 = extractTileValue(line + 1, col);

            if (value1 == value2)
                return false;
        }
    }

    return true;
}
