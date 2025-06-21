#include "word.h"

Word::Word(const std::string& text, sf::Font& font, int y, float spd, int size)
    : speed(spd) {
    drawable.setFont(font);
    drawable.setString(text);
    drawable.setCharacterSize(size);
    drawable.setFillColor(sf::Color::White);
    drawable.setPosition(0.f, static_cast<float>(y));
}

void Word::move(float deltaTime) {
    drawable.move(speed * deltaTime, 0.f);
}

bool Word::reachedRightEdge(float windowWidth) const {
    auto bounds = drawable.getLocalBounds();
    float rightEdge = drawable.getPosition().x + bounds.width;
    return rightEdge >= windowWidth;
}

bool Word::matches(const std::string& input) const {
    return drawable.getString().toAnsiString() == input;
}

void Word::updateHighlight(const std::string& input) {
    int matchLen = 0;
    std::string wordStr = drawable.getString().toAnsiString();
    while (matchLen < (int)input.size() && matchLen < (int)wordStr.size()
           && input[matchLen] == wordStr[matchLen]) {
        ++matchLen;
           }
    highlightLength = matchLen;
}

void Word::setFont(sf::Font& font) {
    drawable.setFont(font);
}

void Word::draw(sf::RenderWindow& window) const {
    if (highlightLength == 0) {
        window.draw(drawable);
        return;
    }

    // Отрисовка подсвеченной части зеленым цветом
    sf::Text highlightText = drawable;
    highlightText.setString(drawable.getString().substring(0, highlightLength));
    highlightText.setFillColor(sf::Color::Green);
    highlightText.setStyle(sf::Text::Italic);

    sf::Text restText = drawable;
    restText.setString(drawable.getString().substring(highlightLength));
    restText.setFillColor(sf::Color::White);
    restText.setPosition(highlightText.getPosition().x + highlightText.getLocalBounds().width, highlightText.getPosition().y);

    window.draw(highlightText);
    window.draw(restText);
}

std::string Word::getText() const {
    return drawable.getString().toAnsiString();
}

int Word::getY() const {
    return static_cast<int>(drawable.getPosition().y);
}
