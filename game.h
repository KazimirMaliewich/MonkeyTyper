#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "word.h"
#include "menu.h"

const std::string SAVE_PATH = "C:/Users/ivann/CLionProjects/MonkeyTyper/save.txt";

struct Settings {
    std::vector<std::string> fontFiles = {
        "C:/Windows/Fonts/arial.ttf",
        "C:/Windows/Fonts/times.ttf",
        "C:/Windows/Fonts/comic.ttf"
    };
    int currentFontIndex = 0;
    float spawnInterval = 1.5f;
    float minSpeed = 50.f;
    float maxSpeed = 100.f;
    bool highlightEnabled = true;
};

class Game {
public:
    Game(sf::RenderWindow& win);
    void start();
    void selectFont(int fontIndex);
    void applyMenuSettings(const MenuResult& result);

private:
    void update(float dt);
    void render();
    void handleInput(const sf::Event& event);
    void saveProgress();
    void loadProgress();
    void resetGame();
    void loadWordsFromFile(const std::string& fileName);
    void switchFont();
    void toggleHighlight();

    sf::RenderWindow& window;
    sf::Font font;
    std::string inputBuffer;
    std::vector<std::string> baseWords;
    std::vector<Word> words;

    bool isRunning;
    bool gameOver = false;
    int score = 0;
    unsigned int gameFontSize = 24;
    Settings settings;
};

#endif