#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string> 

class Game
{
    public:
    Game();
    void gameRun();
    void handleKeyPress(const sf::Keyboard::Key& key);
    void processEvents();
    void render();
    void update();
    void checkColl();
    void gameOver();
    int getRandomNumber(int lower, int upper);
    void updateGameElements(const sf::Vector2u& windowSize);
    void togglePause();
    
    private:

    
    sf::RenderWindow game_win, endGame;
    sf::SoundBuffer playSound;
    sf::Texture userCar,game_back,oppCar1, oppCar2, heart[3];
    sf::Sprite userSprite, opp1,opp2, background1, background2, life[3];
    sf::Vector2f background1Position, background2Position;
    sf::Sound soundgame;
    sf::Text text;
    sf::Font myfont;
    std::string stringscore;
    float scalefactor,userX,userY;
    float backgroundSpeed, backgroundY1, backgroundY2;
    float opp1X, opp1Y, opp2X, opp2Y, carspeed, movespeed;
    int score, countLife, prevscore, scoreInterval;
    bool isPaused;
};