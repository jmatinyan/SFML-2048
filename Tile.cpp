//
// Created by Julia on 4/20/23.
//

#include "Tile.h"

sf::Color Tile::getTextColor(char tile)
{
    if (tile >= 3)
        return sf::Color(249, 246, 242);
    return sf::Color(119, 110, 101);
}

std::string Tile::getText(char tile)
{
    static const std::string text[] = {
            "",
            "2",			// 2^1 == 2
            "4",			// 2^2 == 4
            "8",			// 2^3 == 8
            "16",			// 2^4 == 16
            "32",			// 2^5 == 32
            "64",			// 2^6 == 64
            "128",			// 2^7 == 128
            "256",			// 2^8 == 256
            "512",			// 2^9 == 512
            "1024",			// 2^10 == 1024
            "2048"			// 2^11 == 2048
    };
    return text[tile];
}

int Tile::getTextSize(char tile)
{
    if (tile >= 10)
        return 35;
    else if (tile >= 7)
        return 45;
    return 55;
}