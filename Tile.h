//
// Created by Julia on 4/20/23.
//

#ifndef INC_2048_TILE_H
#define INC_2048_TILE_H

#include "Game.h"
#include <SFML/Graphics.hpp>

class Tile
{
public:
    static sf::Color getTextColor(char tile);
    static std::string getText(char tile);
    static int getTextSize(char tile);
};


#endif //INC_2048_TILE_H
