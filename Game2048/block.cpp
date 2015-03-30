//
//  block.cpp
//  Game2048
//
//  Created by Chi Gao on 1/24/15.
//  Copyright (c) 2015 Chi Gao. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include "block.h"

block::block(){}

// block constructor
block::block(const int X,const int Y,const double size, const double blockSize, const double charSize, const int value_, const sf::Color fillColor, const sf::Color textColor, sf::Font& font){
    
    value = value_;
    svalue = "";
    double centerX = (X+0.5)*size;
    double centerY = (Y+0.5)*size;
    if (value != 0) {
        svalue = std::to_string(value);
    }
    //sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(blockSize,blockSize));
    rect.setOrigin(blockSize/2.0, blockSize/2.0);
    rect.setPosition(centerX, centerY);
    rect.setFillColor(fillColor);
    
    //sf::Text text
    text.setStyle(sf::Text::Bold);
    text.setCharacterSize(charSize);
    text.setString(svalue);
    text.setFont(font);
    text.setColor(textColor);
    text.setOrigin(round(text.getLocalBounds().width/2.0),round(text.getLocalBounds().height/2.0));
    text.setPosition(centerX, centerY);
}

// set the value of a block
void block::setValue(int value_){
    value = value_;
    svalue = "";
    if (value != 0) {
        svalue = std::to_string(value);
    }
    text.setString(svalue);
    text.setOrigin(round(text.getLocalBounds().width/2.0),round(text.getLocalBounds().height/2.0));
    text.setPosition(rect.getPosition());
}

// get the value of a block
int block::getValue(){
    return value;
}


