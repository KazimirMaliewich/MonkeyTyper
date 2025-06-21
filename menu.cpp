#include "menu.h"
#include <cstdio>

MenuResult Menu::show(sf::RenderWindow& window, sf::Font& font) {
    auto getFontSize = [this]() { return fontSizes[currentFontSizeIndex]; };
    auto getSpeed = [this]() { return speeds[currentSpeedIndex]; };

    // Элементы интерфейса
    sf::Text title("MonkeyTyper", font, 50);
    title.setPosition(200.f, 50.f);
    title.setFillColor(sf::Color::White);

    sf::Text fontLabel("", font, 24);
    fontLabel.setPosition(200.f, 120.f);
    fontLabel.setFillColor(sf::Color::Cyan);

    sf::Text sizeLabel("", font, 24);
    sizeLabel.setPosition(200.f, 170.f);
    sizeLabel.setFillColor(sf::Color::Magenta);

    sf::Text fontSizeLabel("", font, 24);
    fontSizeLabel.setPosition(200.f, 220.f);
    fontSizeLabel.setFillColor(sf::Color::Green);

    sf::Text speedLabel("", font, 24);
    speedLabel.setPosition(200.f, 270.f);
    speedLabel.setFillColor(sf::Color::Yellow);

    sf::Text info(
        "Controls:\n"
        "Enter: Start\n"
        "Left/Right: Font\n"
        "Up/Down: Window Size\n"
        "PageUp/PageDown: Font Size\n"
        "Delete: Reset Score",
        font, 18);
    info.setPosition(100.f, 320.f);
    info.setFillColor(sf::Color::Yellow);

    sf::Text resetStatus("", font, 20);
    resetStatus.setPosition(100.f, 470.f); // Позиция под инструкциями
    resetStatus.setFillColor(sf::Color::Red);

    while (window.isOpen()) {
        fontLabel.setString("Font: " + fontNames[currentFontIndex]);
        sf::Vector2u ws = windowSizes[currentSizeIndex];
        sizeLabel.setString("Window Size: " + std::to_string(ws.x) + "x" + std::to_string(ws.y));
        fontSizeLabel.setString("Font Size: " + std::to_string(getFontSize()));
        //speedLabel.setString("Speed: " + std::to_string(getSpeed()));

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                return { -1, {0, 0}, 0, 0.f };

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter)
                    return { currentFontIndex, windowSizes[currentSizeIndex], getFontSize(), getSpeed() };

                if (event.key.code == sf::Keyboard::Right)
                    currentFontIndex = (currentFontIndex + 1) % fontNames.size();

                if (event.key.code == sf::Keyboard::Left)
                    currentFontIndex = (currentFontIndex - 1 + fontNames.size()) % fontNames.size();

                if (event.key.code == sf::Keyboard::Up)
                    currentSizeIndex = (currentSizeIndex + 1) % windowSizes.size();

                if (event.key.code == sf::Keyboard::Down)
                    currentSizeIndex = (currentSizeIndex - 1 + windowSizes.size()) % windowSizes.size();

                if (event.key.code == sf::Keyboard::PageUp)
                    currentFontSizeIndex = (currentFontSizeIndex + 1) % fontSizes.size();

                if (event.key.code == sf::Keyboard::PageDown)
                    currentFontSizeIndex = (currentFontSizeIndex - 1 + fontSizes.size()) % fontSizes.size();

                if (event.key.code == sf::Keyboard::Add)
                    currentSpeedIndex = (currentSpeedIndex + 1) % speeds.size();

                if (event.key.code == sf::Keyboard::Subtract)
                    currentSpeedIndex = (currentSpeedIndex - 1 + speeds.size()) % speeds.size();

                if (event.key.code == sf::Keyboard::Delete) {
                    removeSaveFile();
                    resetStatus.setString("Score reset successfully!");
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(title);
        window.draw(fontLabel);
        window.draw(sizeLabel);
        window.draw(fontSizeLabel);
        window.draw(speedLabel);
        window.draw(info);
        window.draw(resetStatus);
        window.display();
    }

    return { -1, {0, 0}, 0, 0.f };
}

void Menu::removeSaveFile() {
    std::remove("C:/Users/ivann/CLionProjects/MonkeyTyper/save.txt");
}