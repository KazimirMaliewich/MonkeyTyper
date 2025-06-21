#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

struct MenuResult {
    int fontIndex;
    sf::Vector2u windowSize;
    unsigned int fontSize;
    float wordSpeed;
};

class Menu {
public:
    Menu() = default;
    MenuResult show(sf::RenderWindow& window, sf::Font& font);

private:
    int currentFontIndex = 0;
    int currentSizeIndex = 0;
    int currentFontSizeIndex = 2;
    int currentSpeedIndex = 2;

    std::vector<std::string> fontNames = {
        "Arial",
        "Times New Roman",
        "Comic Sans"
    };

    std::vector<sf::Vector2u> windowSizes = {
        {800, 600},
        {1024, 768},
        {1280, 720},
        {1600, 900},
        {1920, 1080}
    };

    std::vector<unsigned int> fontSizes = {
        16, 20, 24, 30, 36, 48
    };

    std::vector<float> speeds = {
        50.f, 75.f, 100.f, 125.f, 150.f
    };

    void removeSaveFile();
};

#endif // MENU_H