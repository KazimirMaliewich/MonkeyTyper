#include "game.h"
#include <SFML/Window.hpp>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

Game::Game(sf::RenderWindow& win) : window(win), isRunning(true) {
    srand(static_cast<unsigned>(time(nullptr)));
    loadWordsFromFile("C:/Users/ivann/CLionProjects/MonkeyTyper/base.txt");
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    loadProgress();
}

void Game::loadWordsFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        return;
    };

    std::string line;
    while (file >> line) {
        baseWords.push_back(line);
    }
    std::reverse(baseWords.begin(), baseWords.end());
}

void Game::start() {
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else
                handleInput(event);
        }

        float dt = clock.restart().asSeconds();
        update(dt);
        render();
    }
}

void Game::switchFont() {
    settings.currentFontIndex = (settings.currentFontIndex + 1) % settings.fontFiles.size();
    font.loadFromFile(settings.fontFiles[settings.currentFontIndex]);
    for (auto& word : words) {
        word.setFont(font);
    }
}

void Game::toggleHighlight() {
    settings.highlightEnabled = !settings.highlightEnabled;
}

void Game::update(float dt) {
    if (gameOver) return;

    const int lineHeight = 30;
    const int maxY = static_cast<int>(window.getSize().y) - 50;
    const int numLines = maxY / lineHeight;
    static float spawnTimer = 0.0f;
    static std::vector<int> usedLines;

    spawnTimer += dt;

    const size_t maxActiveWords = 200;

    if (!baseWords.empty() &&
    spawnTimer >= settings.spawnInterval &&
    words.size() < maxActiveWords) {

        if (usedLines.size() >= static_cast<size_t>(numLines - 1)) {
            usedLines.clear();
        }

        int line = rand() % numLines;
        usedLines.push_back(line);
        int y = line * lineHeight;

        // Используем настройки скорости из меню
        float speed = settings.minSpeed + (rand() % static_cast<int>(settings.maxSpeed - settings.minSpeed + 1));
        std::string word = baseWords.back();
        baseWords.pop_back();

        words.emplace_back(word, font, y, speed, gameFontSize);
        spawnTimer = 0.0f;
    }

    for (auto it = words.begin(); it != words.end();) {
        it->move(dt);
        if (it->reachedRightEdge(window.getSize().x)) {
            gameOver = true;
            saveProgress();
            return;
        }

        if (it->getText().empty()) {
            int line = it->getY() / lineHeight;
            auto usedIt = std::find(usedLines.begin(), usedLines.end(), line);
            if (usedIt != usedLines.end()) {
                usedLines.erase(usedIt);
            }
            it = words.erase(it);
        } else {
            ++it;
        }
    }
}

void Game::render() {
    window.clear();

    for (auto& word : words) {
        word.draw(window);
    }

    // Ввод пользователя
    sf::Text inputText;
    inputText.setFont(font);
    inputText.setString(inputBuffer);
    inputText.setCharacterSize(20);
    inputText.setPosition(10.f, window.getSize().y - 30.f);
    inputText.setFillColor(sf::Color::Green);
    window.draw(inputText);

    // Очки
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setCharacterSize(20);
    scoreText.setPosition(10.f, 10.f);
    scoreText.setFillColor(sf::Color::White);
    window.draw(scoreText);

    // Game Over сообщение
    if (gameOver) {
        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString("Game Over! Press F1 to restart");
        gameOverText.setCharacterSize(30);
        gameOverText.setPosition(
            window.getSize().x / 2 - gameOverText.getLocalBounds().width / 2,
            window.getSize().y / 2 - gameOverText.getLocalBounds().height / 2
        );
        gameOverText.setFillColor(sf::Color::Red);
        window.draw(gameOverText);
    }

    window.display();
}

void Game::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::Resized) {
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));
    }

    if (event.type == sf::Event::TextEntered && !gameOver) {
        sf::Uint32 unicode = event.text.unicode;

        if (unicode == 8) {
            if (!inputBuffer.empty()) {
                inputBuffer.pop_back();
            }
        } else if (unicode < 128 && std::isprint(static_cast<char>(unicode))) {
            inputBuffer += static_cast<char>(unicode);

            auto it = std::find_if(words.begin(), words.end(),
                [&](Word& w) {
                    if (settings.highlightEnabled)
                        w.updateHighlight(inputBuffer);
                    return w.matches(inputBuffer);
                });

            if (it != words.end()) {
                words.erase(it);
                inputBuffer.clear();
                score++;
            }
        }
    }

    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::F1:
                if (gameOver) resetGame();
                break;
            case sf::Keyboard::F2:
                switchFont();
                break;
            case sf::Keyboard::F5:
                toggleHighlight();
                break;
            default:
                break;
        }
    }
}

void Game::resetGame() {
    gameOver = false;
    inputBuffer.clear();
    words.clear();
    score = 0;
    loadWordsFromFile("C:/Users/ivann/CLionProjects/MonkeyTyper/base.txt");
    font.loadFromFile(settings.fontFiles[settings.currentFontIndex]);
}

void Game::saveProgress() {
    std::ofstream saveFile(SAVE_PATH);
    if (saveFile.is_open())
        saveFile << score;
}

void Game::loadProgress() {
    std::ifstream saveFile(SAVE_PATH);
    if (saveFile.is_open())
        saveFile >> score;
}

void Game::selectFont(int fontIndex) {
    if (fontIndex >= 0 && fontIndex < settings.fontFiles.size()) {
        settings.currentFontIndex = fontIndex;
        font.loadFromFile(settings.fontFiles[fontIndex]);
    }
}

void Game::applyMenuSettings(const MenuResult& result) {
    settings.currentFontIndex = result.fontIndex;
    gameFontSize = result.fontSize;
    window.setSize(result.windowSize);

    // Устанавливаем скорость слов напрямую из меню
    settings.minSpeed = result.wordSpeed;
    settings.maxSpeed = result.wordSpeed + 40.f; // Добавляем небольшой разброс

    selectFont(result.fontIndex);
}