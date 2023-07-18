#include "Game.h"
#include "MainMenu.h"
//#include "main.cpp"
const float borderLeft = 205.0f;
const float borderRight = 555.0f;
const float borderUp = 100.0f;
const float borderDown = 600.0f;


Game::Game() 
{
    isMuted = false;
    userX = 282.0f; 
    userY = 600.0f;
    scalefactor = 0.2f;
    backgroundSpeed = 0.1f;
    carspeed = 1.08f;
    movespeed = 20.f;
    backgroundY1 = 0;
    backgroundY2 = -1000;
    opp1Y = 0; opp2Y = -480; 

    
    srand(static_cast<unsigned>(time(0)));
    
    opp1X = getRandomNumber(borderLeft, borderRight);
    opp2X = getRandomNumber(borderLeft, borderRight);
    
    //loading sound
    if (!playSound.loadFromFile("game_resrc/sound1.wav")) std::cout << "Error in loading audio"<< std::endl;
    soundgame.setBuffer(playSound);

    //loading texture
    if (!userCar.loadFromFile("game_resrc/user_car.png")) std::cout << "Error in loading texture"<< std::endl;
    if(!oppCar1.loadFromFile("game_resrc/opp_car1.png")) std::cout << "Error in loading texture"<< std::endl;
    if(!oppCar2.loadFromFile("game_resrc/opp_car2.png")) std::cout << "Error in loading texture"<< std::endl;
    if(!game_back.loadFromFile("game_resrc/game_back2.png")) std::cout << "Error in loading texture" << std::endl;
    userSprite.setTexture(userCar);
    opp1.setTexture(oppCar1);
    opp2.setTexture(oppCar2);


    // Two sprites for the background
    background1.setTexture(game_back);
    background2.setTexture(game_back);

    //setting up user sprite car
    userSprite.setPosition(sf::Vector2f(userX, userY));
    userSprite.setScale(scalefactor, scalefactor);

    //setting up opponent sprite car 
    //opp1.setPosition(sf::Vector2f(282.f, 300));
    opp1.setScale(0.9, 0.9);
    opp2.setScale(0.4, 0.4);
    
    //setting opp position
    opp1.setPosition(opp1X, opp1Y);
    opp2.setPosition(opp2X, opp2Y);

}
void Game::gameRun()
{    
    game_win.create(sf::VideoMode(800, 750), "IN Game");
    
    //obj.mainsound.pause();
    soundgame.play();
    soundgame.setLoop(true);

    while(game_win.isOpen())
    {
        processEvents();
        update();
        render();
    }
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
        soundgame.pause();
        //mainMenu.mainsound.play();
        game_win.close();
    }
    if(key == sf::Keyboard::M)
    {
        if(isMuted)
        {
            soundgame.play();
            isMuted = false;
        }
        else
        {
            soundgame.pause();
            isMuted = true;
        }
    }
    if (key == sf::Keyboard::Left || key == sf::Keyboard::A)
    {
        if (userSprite.getPosition().x - 5 >= borderLeft)
        {
            userSprite.move(-movespeed, 0);
        }
    }
    else if (key == sf::Keyboard::Right || key == sf::Keyboard::D)
    {
        if (userSprite.getPosition().x + 5 <= borderRight)
        {
            userSprite.move(movespeed, 0);
        }
    }
    else if (key == sf::Keyboard::Up || key == sf::Keyboard::W)
    {
        if (userSprite.getPosition().y - 5 >= borderUp)
        {
            userSprite.move(0, -movespeed);
        }
    }
    else if (key == sf::Keyboard::Down || key == sf::Keyboard::S)
    {
        if (userSprite.getPosition().y + 5 <= borderDown)
        {
            userSprite.move(0, movespeed);
        }
    }
}
void Game::render()
{
    game_win.clear();
    game_win.draw(background1);
    game_win.draw(background2);
    game_win.draw(userSprite);
    game_win.draw(opp1);
    game_win.draw(opp2);

    game_win.display();
}

void Game::update()
{
    //moving the background
    backgroundY1+=backgroundSpeed ;
    backgroundY2+=backgroundSpeed ;

    //checking if the background has moved off
    if (backgroundY2>0)
    {
        backgroundY1=0;
        backgroundY2=backgroundY1-1000;
    }
    //setting the position of the background 
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

    //setting position
    opp1.setPosition(sf::Vector2f(opp1X, opp1Y));
    opp2.setPosition(sf::Vector2f(opp2X, opp2Y));


    //collision
    // Bounding box for the player's car
    sf::FloatRect playerBoundingBox = userSprite.getGlobalBounds();

    // Bounding boxes for each obstacle 
    sf::FloatRect opp1BoundingBox = opp1.getGlobalBounds();
    sf::FloatRect opp2BoundingBox = opp2.getGlobalBounds();

    if(playerBoundingBox.intersects(opp1BoundingBox))
    {
        soundgame.stop();
        game_win.close();
    }
    if(playerBoundingBox.intersects(opp2BoundingBox))
    {
        soundgame.stop();
        game_win.close();
    }
    
}

int Game::getRandomNumber(int lower, int upper)
{
    int range = upper - lower + 1;
    int random = lower + (rand() % range);
    return random;
}