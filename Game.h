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
    void togglePause();
    void resume();
    void reset();
    
    private:

    
    sf::RenderWindow game_win, endGame, pauseWindow;
    sf::SoundBuffer playSound;
    sf::Texture userCar,game_back,oppCar1, oppCar2,oppCar3, heart[3];
    sf::Sprite userSprite, opp1,opp2,opp3, background1, background2, life[3];
    sf::Vector2f background1Position, background2Position;
    sf::Sound soundgame;
    sf::Text text, pauseOption[2];
    sf::Font myfont;
    sf::Time deltaTime, deltaTime1;
    sf::Clock clock, clock1;
    std::string stringscore;
    float scalefactor,userX,userY;
    float backgroundSpeed, backgroundY1, backgroundY2;
    float opp1X, opp1Y, opp2X, opp2Y, carspeed, movespeed, lifeX, lifeY, gamewinX, gamewinY;
    int score, countLife, prevscore, scoreInterval;
    bool isPaused;
};