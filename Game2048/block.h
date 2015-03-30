//
//  block.h
//  Game2048
//
//  Created by Chi Gao on 1/24/15.
//  Copyright (c) 2015 Chi Gao. All rights reserved.
//

#ifndef __Game1024__block__
#define __Game1024__block__

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
class block{
private:
    int value;          // number on this block
    std::string svalue; // std::to_string(value)
public:
    sf::RectangleShape rect;
    sf::Text text;
    block();
    block(const int X,const int Y,const double size, const double blockSize, const double charSize, const int value, const sf::Color fillColor, const sf::Color textColor, sf::Font& font);
    void setValue(int value_);
    int getValue();
};

#endif /* defined(__Game1024__block__) */

