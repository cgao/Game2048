//
//  infomation.cpp
//  Game2048
//
//  Created by Chi Gao on 1/28/15.
//  Copyright (c) 2015 Chi Gao. All rights reserved.
//

#include "infomation.h"

information::information(){}


void information::setWinSizeX(int winSizeX_){
    winSizeX = winSizeX_;
}
int information::getWinSizeX(){
    return winSizeX;
}
void information::setWinSizeY(int winSizeY_){
    winSizeY = winSizeY_;
}
int information::getWinSizeY(){
    return winSizeY;
}
void information::setMargin(int margin_){
    margin = margin_;
}
int information::getMargin(){
    return margin;
}
void information::setCharSize(double charSize_){
    charSize = charSize_;
}
double information::getCharSize(){
    return charSize;
}
void information::setZeroCounts(int zeroCounts_){
    zeroCounts = zeroCounts_;
}
int information::getZeroCounts(){
    return zeroCounts;
}
void information::setScore(int score_){
    score = score_;
}
int information::getScore(){
    return score;
}
void information::setNewSeed(bool newSeed_){
    newSeed = newSeed_;
}
bool information::getNewSeed(){
    return newSeed;
}
