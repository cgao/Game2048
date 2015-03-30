//
//  board.cpp
//  Game2048
//
//  Created by Chi Gao on 1/26/15.
//  Copyright (c) 2015 Chi Gao. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include "block.h"
#include "board.h"
#include <vector>
#include <random>
#include <cmath>

board::board(){}

// board constructor
board::board(int winSizeX_,int winSizeY_,int margin_, double charSize_, sf::Font& font){
    
    info.setWinSizeX(winSizeX_);
    info.setWinSizeY(winSizeY_);
    info.setMargin(margin_);
    info.setCharSize(charSize_);
    info.setZeroCounts(16);
    info.setNewSeed(false);
    info.setScore(0);
    
    //color scheme
    info.blockColors = std::vector<sf::Color>(12);
    info.blockColors[0] = sf::Color(250,235,215); //antique white. For nonvalue
    info.blockColors[1] = sf::Color(255,235,205); //blanched almond. For value = 2 = 2^1
    info.blockColors[2] = sf::Color(255,228,196);
    info.blockColors[3] = sf::Color(245,222,179);
    info.blockColors[4] = sf::Color(255,192,203);
    info.blockColors[5] = sf::Color(255,105,180);
    info.blockColors[6] = sf::Color(255,20,147);
    info.blockColors[7] = sf::Color(199,21,133);
    info.blockColors[8] = sf::Color(128,0,128);
    info.blockColors[9] = sf::Color(205,92,92);
    info.blockColors[10] = sf::Color(255,51,51);
    info.blockColors[11] = sf::Color(255,0,0);   // For value = 2058 = 2^11

    info.fontColors = std::vector<sf::Color>(12);
    info.fontColors[0] = sf::Color::Black;
    info.fontColors[1] = sf::Color::Black;
    info.fontColors[2] = sf::Color::Black;
    info.fontColors[3] = sf::Color::Black;
    info.fontColors[4] = sf::Color::Black;
    info.fontColors[5] = sf::Color::White;
    info.fontColors[6] = sf::Color::White;
    info.fontColors[7] = sf::Color::White;
    info.fontColors[8] = sf::Color::White;
    info.fontColors[9] = sf::Color::White;
    info.fontColors[10] = sf::Color::White;
    info.fontColors[11] = sf::Color::White;

    matrix = std::vector<std::vector<block>>(4,std::vector<block>(4));
    double size = info.getWinSizeX()/5.0; // = 256
    double blockSize = size - 2*info.getMargin();
    const sf::Color fillColor = sf::Color::Red;
    const sf::Color textColor = sf::Color::White;
    
    info.scoreLabel.setString("Score");
    info.scoreLabel.setFont(font);
    info.scoreLabel.setCharacterSize(info.getCharSize());
    info.scoreLabel.setColor(sf::Color::White);
    info.scoreLabel.setOrigin(info.scoreLabel.getLocalBounds().width/2.0, info.scoreLabel.getLocalBounds().height/2.0);
    info.scoreLabel.setPosition(info.getWinSizeX()*4.5/5, info.getWinSizeY()*0.5/4);
    
    info.scoreString.setString(std::to_string(info.getScore()));
    info.scoreString.setFont(font);
    info.scoreString.setCharacterSize(info.getCharSize());
    info.scoreString.setColor(sf::Color::White);
    info.scoreString.setOrigin(info.scoreLabel.getLocalBounds().width/2.0, info.scoreLabel.getLocalBounds().height/2.0);
    info.scoreString.setPosition(info.getWinSizeX()*4.5/5, info.getWinSizeY()*1.5/4);
    
    info.newGame.setString("New Game: Press 1");
    info.newGame.setFont(font);
    info.newGame.setCharacterSize(info.getCharSize()/2.5);
    info.newGame.setColor(sf::Color::White);
    info.newGame.setOrigin(info.newGame.getLocalBounds().width/2.0, info.newGame.getLocalBounds().height/2.0);
    info.newGame.setPosition(info.getWinSizeX()*4.5/5, info.getWinSizeY()*2.5/4);
    
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j){
            int value = 0;
            matrix[i][j] = block(i,j,size,blockSize, info.getCharSize(),value,info.blockColors[0],info.fontColors[0], font);
            matrix[i][j].text.setOrigin(matrix[i][j].text.getLocalBounds().width/2.0,matrix[i][j].text.getLocalBounds().height);
        }
    }
    
}

// draw the board on game window
void board::draw(sf::RenderWindow& window){
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j){
            window.draw(matrix[i][j].rect);
            window.draw(matrix[i][j].text);
        }
    }
    
    window.draw(info.scoreLabel);
    window.draw(info.scoreString);
    window.draw(info.newGame);
}

// calculate the result of a movement.
void board::gameEngine(std::vector<int>& arr){
    // purpose: transform the current array into the result. Assume the moving direction is RIGHT.
    // For example:
    //     input       --------->    output
    //  [2  0   0   2] ---------> [0  0   0   4]
    //  [2  2   2   0] ---------> [0  0   2   4]
    //  [2  2   2   2] ---------> [0  0   4   4]
    //  [0  2   2   4] ---------> [0  0   4   4]
    // input:  vector<int> = {x1,x2,x3,x4}
    // output: vector<int> = [{y1,y2,y3,y4}
    
    std::vector<bool> changed = {false,false,false,false};
    //if true, it means the corresponding element is already added by its left element. We will not add it again
    // so [4    2   2   0] will become [0   0   4   4]
    
    //arr[3]: no changes

    //arr[2]
    if (arr[2] != 0){
        if (arr[3] == 0){
            arr[3] = arr[2];
            arr[2] = 0;
            info.setNewSeed(true);
        }
        else{
            if (arr[3] == arr[2]){
                arr[3] *= 2;
                addScore(arr[3]);
                arr[2] = 0;
                changed[3] = true;
                info.setNewSeed(true);
            }
        }
    }
    //arr[1]
    if (arr[1] != 0){
        if (arr[2] == 0 && arr[3] == 0){
            arr[3] = arr[1];
            arr[1] = 0;
            info.setNewSeed(true);
        }
        else if (arr[2] == 0){ //arr[3]!=0
            if (arr[3] == arr[1] && !changed[3]){
                arr[3] *= 2;
                addScore(arr[3]);
            }
            else{
                arr[2] = arr[1];
            }
            arr[1] = 0;
            info.setNewSeed(true);
        }
        else{// arr[3]!=0, arr[2]!=0
            if (arr[2] == arr[1]){
                arr[2] *= 2;
                addScore(arr[2]);
                changed[2] = true;
                arr[1] = 0;
                info.setNewSeed(true);
            }
        }
    }
    //arr[0]
    if (arr[0]!=0){
        if (arr[1] == 0 && arr[2] == 0 && arr[3] == 0){
            arr[3] = arr[0];
            arr[0] = 0;
            info.setNewSeed(true);
        }
        else if(arr[1] == 0 && arr[2] ==0){  //arr[3]!=0
            if (arr[3] == arr[0] && !changed[3]){
                arr[3] *= 2;
                addScore(arr[3]);
                changed[3] = true;
            }
            else{
                arr[2] = arr[0];
            }
            arr[0] = 0;
            info.setNewSeed(true);
        }
        else if(arr[1] == 0 ){  //arr[2]!=0, arr[3]!=0
            if(arr[2] == arr[0] && !changed[2]){
                arr[2] *= 2;
                addScore(arr[2]);
            }
            else{
                arr[1] = arr[0];
            }
            arr[0] = 0;
            info.setNewSeed(true);
        }
        else { //arr[1]!=0, arr[2]!=0, arr[3]!=0
            if(arr[1] == arr[0]){
                arr[1] *= 2;
                addScore(arr[1]);
                //changed[1] = true; //not necessary
                arr[0] = 0;
                info.setNewSeed(true);
            }
        }
    }
}

// set the value of a block
void board::setValue(int value, int i, int j){
    if(matrix[i][j].getValue() == 0 && value != 0) {
        int zeroCounts = info.getZeroCounts();
        zeroCounts -= 1;
        info.setZeroCounts(zeroCounts);
    }
    if(matrix[i][j].getValue() !=0 && value == 0) {
        int zeroCounts = info.getZeroCounts();
        zeroCounts += 1;
        info.setZeroCounts(zeroCounts);
    }
    matrix[i][j].setValue(value);
    int index = 0;
    if (value >= 2){
        index = int(log2(value));
    }
    matrix[i][j].rect.setFillColor(info.blockColors[index]);
    matrix[i][j].text.setColor(info.fontColors[index]);
}

// get the value of a block
int board::getValue(int i, int j){
    return matrix[i][j].getValue();
}

// calculate the score
void board::addScore(int addition){
    int score = info.getScore();
    score += addition;
    info.setScore(score);
    info.scoreString.setString(std::to_string(score));
}

// generate a random number (based on # of empty blocks)
int board::random(){
    int zeroCounts = info.getZeroCounts();
    std::random_device seed; //non-deterministic random seed
    std::uniform_int_distribution<double> distribution(1,zeroCounts);
    if (zeroCounts > 0){
        return distribution(seed);
    }
    else{
        return -1;
    }
}

// randomly find an empty block and put "2" into it
std::vector<int> board::findRandom(int rd){
    int count = 0;
    int i = 0;
    for(int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j){
            if (matrix[i][j].getValue() == 0){
                ++count;
                if (count == rd) return {i,j};
            }
        }
    }
    exit(EXIT_FAILURE);
}

// check if the game is over (no empty block && no possible movement)
bool board::isGameOver(){
    int zeroCounts = info.getZeroCounts();
    if (zeroCounts != 0) return false;
    for (int i = 1; i < 4; ++i){
        for (int j = 1; j < 4; ++j){
            if (matrix[i][j].getValue() == matrix[i][j-1].getValue()) return false;
        }
    }
    for (int i = 1; i < 4; ++i){
        for (int j = 0 ; j < 4; ++j){
            if (matrix[i][j].getValue() == matrix[i-1][j].getValue()) return false;
        }
    }
    return true;
}

// draw the "Game Over" window (and show your score)
void board::drawGameOver(sf::RenderWindow& window){
    sf::Font font = *info.scoreLabel.getFont();
    sf::Text gameOver;
    sf::Text yourScore;
    sf::Text playAgain;
    gameOver.setString("Game Over");
    gameOver.setFont(font);
    gameOver.setCharacterSize(info.getCharSize());
    gameOver.setColor(sf::Color::Red);
    gameOver.setOrigin(gameOver.getLocalBounds().width/2.0, gameOver.getLocalBounds().height/2.0);
    gameOver.setPosition(info.getWinSizeX()/2.0, info.getWinSizeY()/2.0*0.7);
    yourScore.setString("Your Score: " + std::to_string(info.getScore()));
    yourScore.setFont(font);
    yourScore.setCharacterSize(info.getCharSize());
    yourScore.setColor(sf::Color::Red);
    yourScore.setOrigin(yourScore.getLocalBounds().width/2.0, yourScore.getLocalBounds().height/2.0);
    yourScore.setPosition(info.getWinSizeX()/2.0, info.getWinSizeY()/2.0*1.0);
    playAgain.setString("Press 1 to play again");
    playAgain.setFont(font);
    playAgain.setCharacterSize(info.getCharSize());
    playAgain.setColor(sf::Color::Red);
    playAgain.setOrigin(playAgain.getLocalBounds().width/2.0, playAgain.getLocalBounds().height/2.0);
    playAgain.setPosition(info.getWinSizeX()/2.0, info.getWinSizeY()/2.0*1.3);
    sf::Color bg = sf::Color(210,180,140); //background color: tan
    window.clear(bg);
    window.draw(gameOver);
    window.draw(yourScore);
    window.draw(playAgain);
}

// start a new game
void board::resetBoard(){
    info.setScore(0);
    info.scoreString.setString(std::to_string(0));
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j){
            this->setValue(0, i, j);
        }
    }
    int rd = this->random();
    std::vector<int> index = this->findRandom(rd);
    this->setValue(2,index[0],index[1]);
    info.setNewSeed(false);
}

// find the current maximum number
int board::findMax(){
    int tmp = 0;
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j){
            if (tmp < this->getValue(i, j)){
                tmp = this->getValue(i, j);
            }
        }
    }
    return tmp;
}

// draw the "You Won" window (and show your score)
void board::drawWin(sf::RenderWindow& window){
    sf::Font font = *info.scoreLabel.getFont();
    sf::Text youWon;
    sf::Text yourScore;
    sf::Text playAgain;
    youWon.setString("You Won!");
    youWon.setFont(font);
    youWon.setCharacterSize(info.getCharSize());
    youWon.setColor(sf::Color::Red);
    youWon.setOrigin(youWon.getLocalBounds().width/2.0, youWon.getLocalBounds().height/2.0);
    youWon.setPosition(info.getWinSizeX()/2.0, info.getWinSizeY()/2.0*0.7);
    yourScore.setString("Your Score: " + std::to_string(info.getScore()));
    yourScore.setFont(font);
    yourScore.setCharacterSize(info.getCharSize());
    yourScore.setColor(sf::Color::Red);
    yourScore.setOrigin(yourScore.getLocalBounds().width/2.0, yourScore.getLocalBounds().height/2.0);
    yourScore.setPosition(info.getWinSizeX()/2.0, info.getWinSizeY()/2.0*1.0);
    playAgain.setString("Press 1 to play again");
    playAgain.setFont(font);
    playAgain.setCharacterSize(info.getCharSize());
    playAgain.setColor(sf::Color::Red);
    playAgain.setOrigin(playAgain.getLocalBounds().width/2.0, playAgain.getLocalBounds().height/2.0);
    playAgain.setPosition(info.getWinSizeX()/2.0, info.getWinSizeY()/2.0*1.3);
    
    sf::Color bg = sf::Color(210,180,140); //background color: tan
    window.clear(bg);
    window.draw(youWon);
    window.draw(yourScore);
    window.draw(playAgain);
}
