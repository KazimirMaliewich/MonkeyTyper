#ifndef WORD_H
#define WORD_H

#include <SFML/Graphics.hpp>
#include <string>

class Word {
public:
    Word(const std::string& text, sf::Font& font, int y, float spd, int size = 24);
    int getY() const;
    void move(float deltaTime);
    bool reachedRightEdge(float windowWidth) const;
    bool matches(const std::string& input) const;
    void draw(sf::RenderWindow& window) const;
    void updateHighlight(const std::string& input);
    void setFont(sf::Font& font);
    std::string getText() const;

private:
    mutable sf::Text drawable;
    float speed;
    int highlightLength = 0;
};

#endif // WORD_H