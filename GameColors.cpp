//
// Created by Julia on 4/27/23.
//

#include "GameColors.h"
sf::Color GameColors::getTileColor(char tile)
{
    static const sf::Color colors[] = {
            sf::Color(238, 228, 218, 97),		// empty
            sf::Color(238, 228, 218),			// 2^1 = 2
            sf::Color(237, 224, 200),			// 2^2 = 4
            sf::Color(242, 177, 121),			// 2^3 = 8
            sf::Color(245, 149, 99),			// 2^4 = 16
            sf::Color(246, 124, 95),			// 2^5 = 32
            sf::Color(246, 94, 59),				// 2^6 = 64
            sf::Color(237, 207, 114),			// 2^7 = 128
            sf::Color(237, 204, 97),			// 2^8 = 256
            sf::Color(237, 200, 80),			// 2^9 = 512
            sf::Color(237, 197, 63),			// 2^10 = 1024
            sf::Color(237, 194, 46),			// 2^11 = 2048
    };
    return colors[tile];
}