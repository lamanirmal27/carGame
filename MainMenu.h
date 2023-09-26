#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
extern sf::Sound mainsound;
extern bool isMuted;
extern sf::Texture buttonTexture;
extern sf::Sprite buttonSprite;
extern sf::Sound button;
class MainMenu 
{
public:
    MainMenu();
    void run();
    void start();
    void processEvents();
    void handleKeyPress(sf::Keyboard::Key& key);
    void render();
    void mute();
    void instruction();
    void exit();
    
private:

    sf::RenderWindow window;
    sf::Font font;
    sf::SoundBuffer gameSound, playSound, buttonSound;
    sf::Texture back;
    sf::Sprite main_back;
    sf::Text options[4];
    sf::Text exitOptions[2];

    sf::Texture arrowTexture;
    sf::Sprite arrowSprite;
    
    
    int selectedOption;
    float scaleFactor;
};

