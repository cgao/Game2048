#include <SFML/Graphics.hpp>
#include "block.h"
#include "board.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    
    // window configuration
    int winSizeX = 1024*5/4;
    int winSizeY = 1024;
    int margin = 16;
    int charSize = 64;
    int winNum  = 2048;
    string title = "Game 2048";
    sf::RenderWindow window(sf::VideoMode(winSizeX,winSizeY),title,sf::Style::Close);

    // font
    sf::Font font;
    if(!font.loadFromFile("./sansation.ttf")){
        exit(EXIT_FAILURE);
    };
    
    // create a board
    board myBoard(winSizeX,winSizeY,margin,charSize, font);

    // create the first block (random position)
    myBoard.info.setNewSeed(true);
    int rd = myBoard.random();
    //vector<int> index = {0,0};
    vector<int> index = myBoard.findRandom(rd);
    myBoard.setValue(2,index[0],index[1]);
    //myBoard.setValue(2,1,1);
    //myBoard.setValue(0,1,2);
    //myBoard.setValue(4,2,1);
    //myBoard.setValue(8,2,2);
    
    // if newSeed = ture, a new "2" will be filled in an empty block after next keyboard event
    myBoard.info.setNewSeed(false);
    // window background
    sf::Color bg = sf::Color(210,180,140); //background color: tan
    // clear the window with black color
    window.clear(bg);
    // draw the board
    myBoard.draw(window);
    // display the board on the window
    window.display();
    
    
    // keyboard events: Up, Down, Left, Right, 1(restart game)
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            window.clear(bg);
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            
            // Keyboard::Down
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                if (myBoard.isGameOver()){
                    myBoard.drawGameOver(window);
                    window.display();
                }
                else{
                    myBoard.info.setNewSeed(false);
                    for (int i = 0; i < 4; ++i){
                        vector<int> arr(4,0);
                        arr[0] = myBoard.getValue(i,0);
                        arr[1] = myBoard.getValue(i,1);
                        arr[2] = myBoard.getValue(i,2);
                        arr[3] = myBoard.getValue(i,3);
                        myBoard.gameEngine(arr);
                        myBoard.setValue(arr[0],i,0);
                        myBoard.setValue(arr[1],i,1);
                        myBoard.setValue(arr[2],i,2);
                        myBoard.setValue(arr[3],i,3);
                    }
                    if (myBoard.info.getNewSeed()){
                        rd = myBoard.random();
                        index = myBoard.findRandom(rd);
                        myBoard.setValue(2,index[0],index[1]);
                    }
                    myBoard.info.setNewSeed(false);
                    myBoard.draw(window);
                    window.display();
                }
                if (myBoard.findMax() == winNum){
                    myBoard.drawWin(window);
                    window.display();
                }
                if (myBoard.isGameOver()){
                    myBoard.drawGameOver(window);
                    window.display();
                }
            }
            
            // Keyboard::Up
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                if (myBoard.isGameOver()){
                    myBoard.drawGameOver(window);
                    window.display();
                }
                else{
                    myBoard.info.setNewSeed(false);
                    for (int i = 0; i < 4; ++i){
                        vector<int> arr(4,0);
                        arr[0] = myBoard.getValue(i,3);
                        arr[1] = myBoard.getValue(i,2);
                        arr[2] = myBoard.getValue(i,1);
                        arr[3] = myBoard.getValue(i,0);
                        myBoard.gameEngine(arr);
                        myBoard.setValue(arr[0],i,3);
                        myBoard.setValue(arr[1],i,2);
                        myBoard.setValue(arr[2],i,1);
                        myBoard.setValue(arr[3],i,0);
                    }
                    if (myBoard.info.getNewSeed()){
                        rd = myBoard.random();
                        index = myBoard.findRandom(rd);
                        myBoard.setValue(2,index[0],index[1]);
                    }
                    myBoard.info.setNewSeed(false);
                    myBoard.draw(window);
                    window.display();
                }
                if (myBoard.findMax() == winNum){
                    myBoard.drawWin(window);
                    window.display();
                }
                if (myBoard.isGameOver()){
                    myBoard.drawGameOver(window);
                    window.display();
                }
            }
            
            // Keyboard::Right
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                if (myBoard.isGameOver()){
                    myBoard.drawGameOver(window);
                    window.display();
                }
                else{
                    myBoard.info.setNewSeed(false);
                    for (int j = 0; j < 4; ++j){
                        vector<int> arr(4,0);
                        arr[0] = myBoard.getValue(0,j);
                        arr[1] = myBoard.getValue(1,j);
                        arr[2] = myBoard.getValue(2,j);
                        arr[3] = myBoard.getValue(3,j);
                        myBoard.gameEngine(arr);
                        myBoard.setValue(arr[0],0,j);
                        myBoard.setValue(arr[1],1,j);
                        myBoard.setValue(arr[2],2,j);
                        myBoard.setValue(arr[3],3,j);
                    }
                    if (myBoard.info.getNewSeed()){
                        rd = myBoard.random();
                        index = myBoard.findRandom(rd);
                        myBoard.setValue(2,index[0],index[1]);
                    }
                    myBoard.info.setNewSeed(false);
                    myBoard.draw(window);
                    window.display();
                }
                if (myBoard.findMax() == winNum){
                    myBoard.drawWin(window);
                    window.display();
                }
                if (myBoard.isGameOver()){
                    myBoard.drawGameOver(window);
                    window.display();
                }
            }
            
            // Keyboard::Left
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                if (myBoard.isGameOver()){
                    myBoard.drawGameOver(window);
                    window.display();
                }
                else{
                    myBoard.info.setNewSeed(false);
                    for (int j = 0; j < 4; ++j){
                        vector<int> arr(4,0);
                        arr[0] = myBoard.getValue(3,j);
                        arr[1] = myBoard.getValue(2,j);
                        arr[2] = myBoard.getValue(1,j);
                        arr[3] = myBoard.getValue(0,j);
                        myBoard.gameEngine(arr);
                        myBoard.setValue(arr[0],3,j);
                        myBoard.setValue(arr[1],2,j);
                        myBoard.setValue(arr[2],1,j);
                        myBoard.setValue(arr[3],0,j);
                    }
                    if (myBoard.info.getNewSeed()){
                        rd = myBoard.random();
                        index = myBoard.findRandom(rd);
                        myBoard.setValue(2,index[0],index[1]);
                    }
                    myBoard.info.setNewSeed(false);
                    myBoard.draw(window);
                    window.display();
                }
                if (myBoard.findMax() == winNum){
                    myBoard.drawWin(window);
                    window.display();
                }
                if (myBoard.isGameOver()){
                    myBoard.drawGameOver(window);
                    window.display();
                }
            }

            // Keyboard::Num1 (reset game)
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
                myBoard.resetBoard();
                myBoard.draw(window);
                window.display();
            }
        }
    }
    return EXIT_SUCCESS;
}
