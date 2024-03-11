//
// Created by Julia on 4/7/23.
//

#ifndef INC_2048_GAME_H
#define INC_2048_GAME_H
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Button.h"
#include "MainMenu.h"
#include "Board.h"
#include "GameColors.h"
#include "GameSizes.h"

class Game
{
public:
    Game(int w, int h);
    void eventHandler(sf::Event event);
    void update();
    void draw(sf::RenderTarget& target);
    void spawn();
    void reset();
    bool isGameOver;


private:
    sf::RectangleShape tile;
    sf::Text text;
    sf::Font font;
    sf::Clock clock;
    int tileSize;
    char sourceTile;
    char destinTile;
    char map[windowWidth][windowHeight] = { 0 };
    char tempMap[windowWidth][windowHeight] = { 0 };
    bool animState;
    std::vector<std::pair<std::pair<sf::Vector2i, sf::Vector2i>, char>> moves;
    void move(char dirX, char dirY);
    bool isFilled;
    void applyMove(sf::Vector2i f, sf::Vector2i t, int dx, int dy);
};

#endif //INC_2048_GAME_H
