#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Game
{
    public:
    Game();
    void gameRun();
    void backSet();
    void handleKeyPress(const sf::Keyboard::Key& key);
    void processEvents();
    void render();
    void update();
    private:


    sf::RenderWindow game_win;
    sf::SoundBuffer playSound;
    sf::Sound sound;
    sf::Texture userCar,game_back,oppCar1, oppCar2, oppCar3;
    sf::Sprite userSprite, opp1,opp2,opp3, background1, background2;
    sf::Vector2f background1Position, background2Position;
    float scalefactor,userX,userY;
    float backgroundSpeed, backgroundY1, backgroundY2;
};