#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "MainMenu.h"
class Game
{
    public:
    Game();
    void gameRun();
    void handleKeyPress(const sf::Keyboard::Key& key);
    void processEvents();
    void render();
    void update();
    int getRandomNumber(int lower, int upper);
    sf::Sound soundgame;
    
    private:

    
    sf::RenderWindow game_win;
    sf::SoundBuffer playSound;
    
    sf::Texture userCar,game_back,oppCar1, oppCar2, oppCar3;
    sf::Sprite userSprite, opp1,opp2,opp3, background1, background2;
    sf::Vector2f background1Position, background2Position;
    float scalefactor,userX,userY;
    float backgroundSpeed, backgroundY1, backgroundY2;
    float opp1X, opp1Y, opp2X, opp2Y, opp3X, opp3Y, carspeed;
    bool isMuted;
};