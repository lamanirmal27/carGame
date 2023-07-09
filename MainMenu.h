#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class MainMenu 
{
public:
    MainMenu();
    void run();
    void start();
    bool isMuted;

private:
    void processEvents();
    void handleKeyPress(const sf::Keyboard::Key& key);
    void update();
    void render();
    void mute();
    void instruction();
    void exit();

    sf::RenderWindow window;
    sf::Font font;
    sf::SoundBuffer gameSound, playSound, buttonSound;
    sf::Sound sound, button;

    sf::Text options[4];
    sf::Text exitOptions[2];

    sf::Texture arrowTexture, buttonTexture;
    sf::Sprite arrowSprite, buttonSprite;

    int selectedOption;
    const float scaleFactor = 0.4f;
    
};
