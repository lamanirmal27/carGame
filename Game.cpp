#include "Game.h"
#include "MainMenu.h"

const float borderLeft = 178.0f;
const float borderRight = 493.0f;
const float borderUp = 100.0f;
const float borderDown = 845.0f;

Game::Game() : game_win(sf::VideoMode(800, 1000), "Game")
{
    userX = 282.0f; 
    userY = 700.0f;
    scalefactor = 0.2f;
    backgroundSpeed = 0.1f;
    carspeed = 1.2f;
    backgroundY1 = 0;
    backgroundY2 = -1000;
    opp1Y = -50; opp2Y = -450; opp3Y = -850;
    opp1X = getRandomNumber(borderLeft, borderRight);
    opp2X = getRandomNumber(borderLeft, borderRight);
    opp3X = getRandomNumber(borderLeft, borderRight);
    //loading sound
    if (!playSound.loadFromFile("game_resrc/sound1.wav")) std::cout << "Error in loading audio"<< std::endl;
    sound.setBuffer(playSound);

    //loading texture
    if (!userCar.loadFromFile("game_resrc/user_car.png")) std::cout << "Error in loading texture"<< std::endl;
    if(!oppCar1.loadFromFile("game_resrc/opp_car1.png")) std::cout << "Error in loading texture"<< std::endl;
    if(!oppCar2.loadFromFile("game_resrc/opp_car2.png")) std::cout << "Error in loading texture"<< std::endl;
    if(!oppCar3.loadFromFile("game_resrc/opp_car3.png")) std::cout << "Error in loading texture"<< std::endl;
    if(!game_back.loadFromFile("game_resrc/game_back2.png")) std::cout << "Error in loading texture" << std::endl;
    userSprite.setTexture(userCar);
    opp1.setTexture(oppCar1);
    opp2.setTexture(oppCar2);
    opp3.setTexture(oppCar3);

    // Two sprites for the background
    background1.setTexture(game_back);
    background2.setTexture(game_back);

    //setting up user sprite car
    userSprite.setPosition(sf::Vector2f(userX, userY));
    userSprite.setScale(scalefactor, scalefactor);

    //setting up opponent sprite car 
    opp1.setPosition(sf::Vector2f(282.f, 300));
    opp1.setScale(0.9, 0.9);
    opp2.setScale(0.4, 0.4);
    opp3.setScale(0.4, 0.4);
    
    //setting opp position
    opp1.setPosition(opp1X, opp1Y);
    opp2.setPosition(opp2X, opp2Y);
    opp3.setPosition(opp3X, opp3Y);
}
void Game::gameRun()
{   
    sound.play();
    sound.setLoop(true);
    while(game_win.isOpen())
    {
        processEvents();
        update();
        render();
    }
}
void Game::backSet()
{
    //
}
void Game::processEvents()
{
    sf::Event event;
    while(game_win.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed) 
        {
            handleKeyPress(event.key.code);
        }
    }
}
void Game::handleKeyPress(const sf::Keyboard::Key& key)
{
    if (key == sf::Keyboard::Escape) 
    {
        game_win.close();
        sound.stop();
        /*if(isMuted)
            sound.pause();
        else */   
            sound.play();
    }
    if(key == sf::Keyboard::Left || key == sf::Keyboard::A)
    {
        if(borderLeft<userX)
            userX -= 10.0f;
        }
        else if(key == sf::Keyboard::Right || key == sf::Keyboard::D)
        {
            if(borderRight>userX)
                userX += 10.0f;
            }
            else if(key == sf::Keyboard::Up || key == sf::Keyboard::W)
            {
                if(!(borderUp>userY))
                    userY -= 10.0f;
            }
            else if(key == sf::Keyboard::Down || key == sf::Keyboard::S)
            {
                if(!(borderDown<userY))
                    userY += 10.0f;
            }
            userSprite.setPosition(sf::Vector2f(userX, userY));
}
void Game::render()
{
    game_win.clear();
    game_win.draw(background1);
    game_win.draw(background2);
    game_win.draw(opp1);
    game_win.draw(opp2);
    game_win.draw(opp3);
    game_win.draw(userSprite);
    game_win.display();
}

void Game::update()
{
    //moving the background
    backgroundY1+=backgroundSpeed ;
    backgroundY2+=backgroundSpeed ;

    if (backgroundY2>0)
    {
        backgroundY1=0;
        backgroundY2=backgroundY1-900;
    }

    background1.setPosition(0,backgroundY1);
    background2.setPosition(0, backgroundY2);

    // Moving the opponent cars
    if (opp1Y > 1000)
    {
        opp1Y = 0;
        opp1X = getRandomNumber(borderLeft, borderRight);
    }
    else
    {
        opp1Y += backgroundSpeed*carspeed;
    }

    if (opp2Y > 1000)
    {
        opp2Y = 0;
        opp2X = getRandomNumber(borderLeft, borderRight);
    }
    else
    {
        opp2Y += backgroundSpeed*carspeed;
    }

    if (opp3Y > 1000)
    {
        opp3Y = 0;
        opp3X = getRandomNumber(borderLeft, borderRight);
    }
    else
    {
        opp3Y += backgroundSpeed*carspeed;
    }

    //setting position
    opp1.setPosition(sf::Vector2f(opp1X, opp1Y));
    opp2.setPosition(sf::Vector2f(opp2X, opp2Y));
    opp3.setPosition(sf::Vector2f(opp3X, opp3Y));
}

int Game::getRandomNumber(int a, int b)
{
    static std::mt19937 generator(std::time(0));
    std::uniform_int_distribution<int> distribution(a, b);

    return distribution(generator);
}