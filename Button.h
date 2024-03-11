//
// Created by Julia on 4/18/23.
//

#ifndef INC_2048_BUTTON_H
#define INC_2048_BUTTON_H
#include <SFML/Graphics.hpp>
#include <string>

class Button : public sf::Drawable
{
private:
    sf::RectangleShape button;
    sf::Text text;
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Color color;
public:
    Button(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Font& font, std::string text, int charSize);
    void draw(sf::RenderTarget &window, sf::RenderStates states) const;
    bool isMouseOver(sf::RenderWindow& window);
    sf::FloatRect getGlobalBounds() const;
};


#endif //INC_2048_BUTTON_H
