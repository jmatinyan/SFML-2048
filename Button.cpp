//
// Created by Julia on 4/18/23.
//

#include "Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Font &font, std::string textString, int charSize)
{
    position = position;
    size = size;
    color = color;

    button.setSize(size);
    button.setPosition(position);
    button.setFillColor(color);

    text.setFont(font);
    text.setString(textString);
    text.setCharacterSize(charSize);
    text.setFillColor(sf::Color::White);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(position.x + size.x / 2, position.y + size.y / 2);
}

void Button::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
    window.draw(button);
    window.draw(text);
}

bool Button::isMouseOver(sf::RenderWindow &window)
{
    sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
    return button.getGlobalBounds().contains(mousePosition);
}

sf::FloatRect Button::getGlobalBounds() const
{
    return button.getGlobalBounds();
}
