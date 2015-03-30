//
//  infomation.h
//  Game2048
//
//  Created by Chi Gao on 1/28/15.
//  Copyright (c) 2015 Chi Gao. All rights reserved.
//

#ifndef __Game2048__infomation__
#define __Game2048__infomation__

#include <stdio.h>
#include <SFML/Graphics.hpp>

class information{
private:
    int winSizeX;       // the Xsize of game window
    int winSizeY;       // the Ysize of game window
    int margin;         // margin between neighboring blocks
    double charSize;    // character size
    int zeroCounts;     // count how many empty blocks
    int score;          // current score
    bool newSeed;       // if newSeed = true: generate a new "2"
public:
    std::vector<sf::Color> blockColors; // color scheme
    std::vector<sf::Color> fontColors;  // color scheme
    sf::Text scoreLabel;                //
    sf::Text scoreString;               //
    sf::Text newGame;                   //
    
    information();
    void setWinSizeX(int winSizeX_);
    int getWinSizeX();
    void setWinSizeY(int winSizeY_);
    int getWinSizeY();
    void setMargin(int margin_);
    int getMargin();
    void setCharSize(double charSize_);
    double getCharSize();
    void setZeroCounts(int zeroCounts_);
    int getZeroCounts();
    void setScore(int score_);
    int getScore();
    void setNewSeed(bool newSeed_);
    bool getNewSeed();
};

#endif /* defined(__Game2048__infomation__) */
