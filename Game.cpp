//
// Created by Julia on 4/7/23.
//

#include "Game.h"

Game::Game(int width, int height)
{
    tileSize = (width - windowMargin * 2 - tileMargin * (windowWidth - 1)) / windowWidth;
    animState = false;

    font.loadFromFile("Insight Sans SSi.ttf");
    reset();
}

void Game::eventHandler(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (animState)
            return;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            move(-1, 0);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            move(1, 0);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            move(0, -1);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            move(0, 1);
    }
}

void Game::update()
{
    if (animState)
    {
        if (clock.getElapsedTime().asSeconds() >= speed)
        {
            animState = false;

            for (int i = 0; i < moves.size(); i++)
            {
                sf::Vector2i fromTile = moves[i].first.first;
                sf::Vector2i toTile = moves[i].first.second;

                char sourceTile = moves[i].second;
                char& destinTile = map[toTile.x][toTile.y];

                map[fromTile.x][fromTile.y] = 0;

                if (sourceTile == destinTile && fromTile != toTile)
                    destinTile++;
                else
                    destinTile = sourceTile;
            }
            moves.clear();
            spawn();
            return;
        }
    }
}

void Game::draw(sf::RenderTarget& target)
{
    text.setFont(font);
    tile.setSize(sf::Vector2f(tileSize, tileSize));

    for (int x = 0; x < windowWidth; x++)
    {
        for (int y = 0; y < windowHeight; y++)
        {
            tile.setPosition(windowMargin + x * (tileSize + tileMargin), windowMargin + y * (tileSize + tileMargin));
            tile.setFillColor(GameColors::getTileColor(map[x][y]));
            target.draw(tile);

            if (map[x][y] != 0)
            {
                text.setCharacterSize(Tile::getTextSize(map[x][y]));
                text.setString(Tile::getText(map[x][y]));

                sf::FloatRect rect = text.getLocalBounds();

                text.setPosition(windowMargin + x * (tileSize + tileMargin) + (tileSize - rect.width) / 2 - rect.left,
                                 windowMargin + y * (tileSize + tileMargin) + (tileSize - rect.height) / 2 - rect.top);
                text.setFillColor(Tile::getTextColor(map[x][y]));
                target.draw(text);
            }
        }
    }

    sf::Vector2i board(windowMargin, windowMargin);

    for (int i = 0; i < moves.size(); i++)
    {
        sf::Vector2i orig = moves[i].first.first;
        sf::Vector2i fromTile = board + orig * (tileSize + tileMargin);
        sf::Vector2i toTile = board + moves[i].first.second * (tileSize + tileMargin);

        float moveSpeed = (clock.getElapsedTime().asSeconds() / speed);
        sf::Vector2f curPos = sf::Vector2f(fromTile) + sf::Vector2f(toTile - fromTile) * moveSpeed;

        text.setCharacterSize(Tile::getTextSize(moves[i].second));
        text.setString(Tile::getText(moves[i].second));

        sf::FloatRect rect = text.getLocalBounds();

        text.setPosition(curPos.x + (tileSize - rect.width) / 2 - rect.left, curPos.y + (tileSize - rect.height) / 2 - rect.top);
        text.setFillColor(Tile::getTextColor(moves[i].second));

        tile.setPosition(curPos);
        tile.setFillColor(GameColors::getTileColor(moves[i].second));

        target.draw(tile);
        target.draw(text);
    }
}

void Game::spawn()
{
    int availableCount = 0;
    sf::Vector2i availableMoves[windowWidth*windowHeight];

    for (int x = 0; x < windowWidth; x++)
    {
        for (int y = 0; y < windowHeight; y++)
        {
            if (map[x][y] == 0)
            {
                availableMoves[availableCount] = sf::Vector2i(x, y);
                availableCount++;
            }
        }
    }
    if (availableCount == 0)
    {
        reset();
        return;
    }
    int newNum = rand() % availableCount;
    sf::Vector2i newPos = availableMoves[newNum];
    map[newPos.x][newPos.y] = 1;
}

void Game::reset()
{
    for (int x = 0; x < windowWidth; x++)
        for (int y = 0; y < windowHeight; y++)
            map[x][y] = 0;
    spawn();
    //add game over
}

void Game::move(char dirX, char dirY)
{
    for (int x = 0; x < windowWidth; x++)
        for (int y = 0; y < windowHeight; y++)
            tempMap[x][y] = map[x][y];

    if (dirX == -1)
    {
        for (int x = 1; x < windowWidth; x++)
        {
            for (int y = 0; y < windowHeight; y++)
            {
                if (tempMap[x][y] == 0)
                    continue;

                sf::Vector2i finalPos = sf::Vector2i(x, y);
                for (int emptyX = x - 1; emptyX >= 0; emptyX--)
                {
                    finalPos = sf::Vector2i(emptyX, y);
                    if (tempMap[emptyX][y] != 0)
                        break;
                }
                applyMove(sf::Vector2i(x, y), finalPos, dirX, dirY);
            }
        }
    }
    else if (dirX == 1)
    {
        for (int x = windowWidth-2; x >= 0; x--)
        {
            for (int y = 0; y < windowHeight; y++)
            {
                if (tempMap[x][y] == 0)
                    continue;

                sf::Vector2i finalPos = sf::Vector2i(x, y);
                for (int emptyX = x + 1; emptyX < windowWidth; emptyX++)
                {
                    finalPos = sf::Vector2i(emptyX, y);
                    if (tempMap[emptyX][y] != 0)
                        break;
                }
                applyMove(sf::Vector2i(x, y), finalPos, dirX, dirY);
            }
        }
    }
    else if (dirY == -1)
    {
        for (int y = 1; y < windowHeight; y++)
        {
            for (int x = 0; x < windowWidth; x++)
            {
                if (tempMap[x][y] == 0)
                    continue;
                sf::Vector2i finalPos = sf::Vector2i(x, y);
                for (int emptyY = y - 1; emptyY >= 0; emptyY--)
                {
                    finalPos = sf::Vector2i(x, emptyY);
                    if (tempMap[x][emptyY] != 0)
                        break;
                }
                applyMove(sf::Vector2i(x, y), finalPos, dirX, dirY);
            }
        }
    }
    else if (dirY == 1)
    {
        for (int y = windowHeight-2; y >= 0; y--)
        {
            for (int x = 0; x < windowWidth; x++)
            {
                if (tempMap[x][y] == 0)
                    continue;
                sf::Vector2i finalPos = sf::Vector2i(x, y);
                for (int emptyY = y + 1; emptyY < windowHeight; emptyY++)
                {
                    finalPos = sf::Vector2i(x, emptyY);
                    if (tempMap[x][emptyY] != 0)
                        break;
                }
                applyMove(sf::Vector2i(x, y), finalPos, dirX, dirY);
            }
        }
    }

    bool isFilled = true;
    bool isGameOver = true;
    for (int x = 0; x < windowWidth; x++)
    {
        for (int y = 0; y < windowHeight; y++)
        {
            if (tempMap[x][y] == 0)
            {
                isFilled = false;
                isGameOver = false;
                break;
            }

            char val = tempMap[x][y];
            if (x != 0 && tempMap[x - 1][y] == val)
                isGameOver = false;
            else if (y != 0 && tempMap[x][y - 1] == val)
                isGameOver = false;
            else if (x != windowWidth - 1 && tempMap[x + 1][y] == val)
                isGameOver = false;
            else if (y != windowHeight - 1 && tempMap[x][y+1] == val)
                isGameOver = false;
        }
        if (!isFilled || !isGameOver)
            break;
    }
    if (isGameOver)
        reset();
}

void Game::applyMove(sf::Vector2i f, sf::Vector2i t, int dx, int dy)
{
    char sourceTile = tempMap[f.x][f.y];
    char destinTile = tempMap[t.x][t.y];

    tempMap[f.x][f.y] = 0;

    if (destinTile == sourceTile)
    {
        tempMap[t.x][t.y] = sourceTile + 1;
        if (sourceTile + 1 == 12)
            reset();
    }
    else
        tempMap[t.x - (dx * (destinTile != 0))][t.y - (dy * (destinTile != 0))] = sourceTile;

    sf::Vector2i from = f, to;

    if (destinTile == sourceTile)
        to = t;
    else
        to = sf::Vector2i(t.x - (dx * (destinTile != 0)), t.y - (dy * (destinTile != 0)));

    if (from != to)
    {
        map[f.x][f.y] = 0;
        moves.push_back({{from, to}, sourceTile});
        animState = true;
        clock.restart();
    }
}