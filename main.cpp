#include <SFML/Graphics.hpp>
#include "menu.h"
#include "game.h"

int main() {
    // Временное окно для меню фиксированного размера
    sf::RenderWindow menuWindow(sf::VideoMode(1600, 900), "MonkeyTyper Menu");
    sf::Font font;

    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        return -1;
    }

    Menu menu;
    MenuResult menuResult = menu.show(menuWindow, font);
    menuWindow.close();

    if (menuResult.fontIndex == -1) return 0;

    // Создаём основное окно с выбранным размером
    sf::RenderWindow gameWindow(sf::VideoMode(menuResult.windowSize.x, menuResult.windowSize.y), "MonkeyTyper");
    Game game(gameWindow);

    game.applyMenuSettings(menuResult); // Устанавливаем все настройки из меню
    game.start();

    return 0;
}