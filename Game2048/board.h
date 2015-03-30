//
//  board.h
//  Game2048
//
//  Created by Chi Gao on 1/26/15.
//  Copyright (c) 2015 Chi Gao. All rights reserved.
//

#ifndef __Game1024__board__
#define __Game1024__board__

#include <SFML/Graphics.hpp>
#include "block.h"
#include "infomation.h"
#include <vector>

class board{
public:
// members
    std::vector<std::vector<block>> matrix;     // 4x4 matrix of 16 blocks
    information info;                           //
// functions
    // constructors
    board();
    board(int winSizeX_,int winSizeY_,int margin_, double charSize_, sf::Font& font);
    // gameEngine:
    void gameEngine(std::vector<int>& arr);
    // manipulate the value of block matrix[i][j]
    void setValue(int value, int i, int j);
    int getValue(int i, int j);
    // add a number (addition) to the current score
    void addScore(int addition);
    // fill a new "2" randomly into an empty block
    int random();
    std::vector<int> findRandom(int rd);
    // reset board (to start a new game)
    void resetBoard();
    // check if the board is full and no more action is possible. If true, player loses and game is over
    bool isGameOver();
    // find the current max value on the board. If it is 2048, player wins and game is over
    int findMax();
    // draw functions
    void draw(sf::RenderWindow& window);
    void drawGameOver(sf::RenderWindow& window);
    void drawWin(sf::RenderWindow& window);
};

#endif /* defined(__Game1024__board__) */
