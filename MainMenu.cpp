#include "MainMenu.h"
#include "Game.h"

const float screenWidth = 1000.0f;
const float screenHeight = 800.0f;

sf::Sound mainsound;
bool isMuted;
sf::Texture buttonTexture;
sf::Sprite buttonSprite;
sf::Sound button;
MainMenu::MainMenu() 
{
    selectedOption=0;
    scaleFactor = 0.4f;
    isMuted = false;
    //loading font file
    if (!font.loadFromFile("game_resrc/Giveny.ttf")) std::cout << "Error in loading font"<< std::endl;

    //loading audio files
    if (!gameSound.loadFromFile("game_resrc/sound2.wav")) std::cout << "Error in loading audio"<< std::endl;
    if (!buttonSound.loadFromFile("game_resrc/button1.wav")) std::cout << "Error in loading audio"<< std::endl;

    mainsound.setBuffer(gameSound);
    button.setBuffer(buttonSound);

    
    //Optoins for our main menu
    options[0].setString("Start Game");
    options[1].setString("Mute");
    options[2].setString("Instruction");
    options[3].setString("Quit Game");

    //Options for our exitMenu
    exitOptions[0].setString("Exit");
    exitOptions[1].setString("Cancel");

    for (int i = 0; i < 4; ++i) {
        options[i].setFont(font);
        options[i].setCharacterSize(110);
        options[i].setPosition(200, 170 + i * 90);
    }
    
    //loading sprites
    if (!arrowTexture.loadFromFile("game_resrc/arrow.png")) std::cout << "Error in loading sprite"<< std::endl;
    if (!buttonTexture.loadFromFile("game_resrc/buttonExit.png")) std::cout << "Error in loading sprite"<< std::endl;
    arrowSprite.setTexture(arrowTexture);
    buttonSprite.setTexture(buttonTexture);
    arrowSprite.setScale(scaleFactor, scaleFactor);
    arrowSprite.setPosition(85, 190);
}

void MainMenu::run()
{
    window.create(sf::VideoMode(screenWidth, screenHeight), "Car Game");

    //playing menu sound
    mainsound.play();
    mainsound.setLoop(true);

    while (window.isOpen()) 
    {
        processEvents();
        render();
    }
}

void MainMenu::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event)) 
    {
        if (event.type == sf::Event::KeyPressed) 
        {
            handleKeyPress(event.key.code);
        }

    }
}

void MainMenu::handleKeyPress(sf::Keyboard::Key& key)
{
    if (key == sf::Keyboard::Up) 
    {
        if (selectedOption > 0) {
            arrowSprite.move(0, -90);
            --selectedOption;
            button.play();
        }
    } 
    else if (key == sf::Keyboard::Down) 
    {
        if (selectedOption < 3) {
            arrowSprite.move(0, 90);
            ++selectedOption;
            button.play();
        }
    } 
    else if (key == sf::Keyboard::Escape) 
    {
        window.close();
    } 
    else if (key == sf::Keyboard::Enter) 
    {
        switch (selectedOption)
        {
        case 0: 
            start();
            break;

        case 1:
            mute();
            break;
        
        case 2:
            instruction();
            break;

        case 3:
            exit();
            break;

        default:
            break;
        }
    }
}

void MainMenu::render()
{
    window.clear();
    for (int i = 0; i < 4; ++i)
        window.draw(options[i]);
    window.draw(arrowSprite);
    window.display();
}

void MainMenu::mute()
{
    if (isMuted)
    {
        mainsound.play(); 
        isMuted = false; 
    }
    else 
    {
        mainsound.pause(); 
        isMuted = true; 
    }
}

void MainMenu::instruction()
{
    sf::RenderWindow instruction(sf::VideoMode(600, 400), "Instruction");
    sf::Text msg;
    msg.setString("Press A to move vehicle to left\nPress D to move vehicle to right\nPress W to move vehicel UP\nPress S to move vehicle DOWN\nPress TAB to pause the game\nPress Esc key to exit Game");
    msg.setFont(font);
    msg.setCharacterSize(35);
    msg.setPosition(30, 60);

    while(instruction.isOpen())
    {
        sf::Event e;
        while(instruction.pollEvent(e))
        {
            if(e.key.code == sf::Keyboard::Enter)
            instruction.close();
        }

        instruction.clear();
        instruction.draw(msg);
        instruction.display();
    }
}

void MainMenu::exit()
{
    sf::RenderWindow exitWindow(sf::VideoMode(600,400),"Notice");
    sf::Text msg;
    msg.setString("Are you sure?");
    msg.setFont(font);
    msg.setCharacterSize(40);
    msg.setPosition(180, 70);
    buttonSprite.setScale(0.6f, 0.6f);
    for(int i=0; i<2; i++)
    {
        exitOptions[i].setFont(font);
        exitOptions[i].setCharacterSize(40);
        exitOptions[i].setPosition(210 * i + 150, 250);
    }
    int exitOption = 0;
    buttonSprite.setPosition(90.0f,245.0f);
    while (exitWindow.isOpen())
    {
        sf::Event exitEvent;
        while (exitWindow.pollEvent(exitEvent))
        {
            if (exitEvent.type == sf::Event::KeyPressed)
            {
                if (exitEvent.key.code == sf::Keyboard::Left)
                {
                    if(exitOption == 1)
                    {
                        buttonSprite.move(-235, 0);
                        --exitOption;
                        button.play();
                    }

                }
                else if (exitEvent.key.code == sf::Keyboard::Right)
                {
                    if(exitOption == 0)
                    {
                        buttonSprite.move(235, 0);
                        ++exitOption;
                        button.play();
                    }
                }
                else if(exitEvent.key.code == sf::Keyboard::Enter)
                {
                    if(exitOption == 0)
                    {
                        exitWindow.close();
                        window.close();
                    }
                    else
                    {
                        exitWindow.close();
                    }
                }
            }
        }
        
        exitWindow.clear();
        exitWindow.draw(msg);
        for(int i=0; i<2; i++)
        {
            exitWindow.draw(exitOptions[i]);
        }
        exitWindow.draw(buttonSprite);
        exitWindow.display();
    }
}
void MainMenu::start()
{
    Game game;
    mainsound.pause();
    game.gameRun();
}