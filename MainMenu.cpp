//
// Created by Julia on 4/18/23.
//

#include "MainMenu.h"
#include "Game.h"
#include "Button.h"

void MainMenu::run()
{
    sf::RenderWindow window({900, 900, 32}, "2048");
    window.setFramerateLimit(60);
    window.clear(sf::Color(190, 173, 158));

    sf::Font font;
    font.loadFromFile("Insight Sans SSi.ttf");

    Game game(window.getSize().x, window.getSize().y);

    Button welcome(sf::Vector2f(330, 100), sf::Vector2f(230, 70), sf::Color::Transparent, font, "2048", 80);
    Button playButton(sf::Vector2f(330, 300), sf::Vector2f(250, 70), sf::Color(242, 177, 121), font, "PLAY", 45);
    Button exitButton(sf::Vector2f(330, 450), sf::Vector2f(250, 70), sf::Color(245, 149, 99), font, "EXIT", 45);

    bool inGame = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (playButton.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    inGame = true;
                    game.reset();
                }
                if (exitButton.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    window.close();
                }
            }
            if (inGame)
            {
                game.eventHandler(event);
            }
        }
        if(inGame)
        {
            game.update();
        }
        if (game.isGameOver)
        {
            inGame = false;
        }
        window.clear(sf::Color(190, 173, 158));
        if(!inGame)
        {
            MainMenu mainMenu;
            mainMenu.draw(window);
            window.draw(welcome);
            window.draw(playButton);
            window.draw(exitButton);
        }
        else(game.draw(window));
        window.display();
    }
}

void MainMenu::draw(sf::RenderTarget &target)
{
    sf::Text intro;
    sf::Font font;
    intro.setFont(font);
    font.loadFromFile("Insight Sans SSi.ttf");
    intro.setPosition({25, 25});
    intro.setFillColor(sf::Color(118,110,101));
    intro.setCharacterSize(30);
    intro.setString("Julia Matinyan\nCRN: 37045\nCS003A\nSpr23");
    target.draw(intro);
}
