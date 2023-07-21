#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
extern sf::Sound mainsound;
extern bool isMuted;
class MainMenu 
{
public:
    MainMenu();
    void run();
    void start();
    
    

private:
    void processEvents();
    void handleKeyPress(sf::Keyboard::Key& key);
    void render();
    void mute();
    void instruction();
    void exit();

    sf::RenderWindow window;
    sf::Font font;
    sf::SoundBuffer gameSound, playSound, buttonSound;
    sf::Sound button;
    
    sf::Text options[4];
    sf::Text exitOptions[2];

    sf::Texture arrowTexture, buttonTexture;
    sf::Sprite arrowSprite, buttonSprite;
    
    
    int selectedOption;
    float scaleFactor;
};

