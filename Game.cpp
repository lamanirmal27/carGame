#include "Game.h"
#include "MainMenu.h"
//#include "main.cpp"
const float borderLeft = 220.0f;
const float borderRight = 555.0f;
const float borderUp = 100.0f;
const float borderDown = 600.0f;

//sf::Sound MainMenu::mainsound;
Game::Game() 
{
    isMuted = false;
    isPaused = false;
    userX = 282.0f; 
    userY = 600.0f;
    scalefactor = 0.2f;
    backgroundSpeed = 0.1f;
    carspeed = 1.5f;
    movespeed = 30.f;
    backgroundY1 = 0;
    backgroundY2 = -1000;
    opp1Y = -1200; opp2Y = -800; 
    score = 0; prevscore =0; scoreInterval = 10;
    //stringscore = "YOU SCORED: " + std::to_string(score);
    
    srand(static_cast<unsigned>(time(0)));
    
    opp1X = getRandomNumber(borderLeft, borderRight);
    opp2X = getRandomNumber(borderLeft, borderRight);
    
    //loading font
    if(!myfont.loadFromFile("game_resrc/Giveny.ttf")) std::cout<< "Error in loading font" << std::endl;
    //stringscore = "SCORE: " + std::to_string(score);
    text.setFont(myfont); // Assuming myfont is already loaded
    //text.setString(stringscore);
    
    

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
        if(!isPaused)
        {
            update();
            render();
            checkColl();
        }
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
        //MainMenu::mainsound.play();
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
    if(key == sf::Keyboard::Tab)
    {
        togglePause();
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
    game_win.draw(text);
    game_win.display();
}

void Game::update()
{
    if(!isPaused)
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
        if (opp1Y > 750)
        {
            opp1Y = -100;
            opp1X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else
        {
            opp1Y += backgroundSpeed*carspeed;
        }

        if (opp2Y > 750)
        {
            opp2Y = -100;
            opp2X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else
        {
            opp2Y += backgroundSpeed*carspeed;
        }

        //setting position
        opp1.setPosition(sf::Vector2f(opp1X, opp1Y));
        opp2.setPosition(sf::Vector2f(opp2X, opp2Y));
        
        //game level
        if(score >= prevscore+scoreInterval)
        {
                carspeed +=0.4f;
                prevscore=score;
        }
        stringscore = "SCORE: " + std::to_string(score);
        text.setString(stringscore);
        text.setCharacterSize(50);
        text.setPosition(550,0);
    }

}

int Game::getRandomNumber(int lower, int upper)
{
    int range = upper - lower + 1;
    int random = lower + (rand() % range);
    return random;
}
void Game::checkColl()
{
    // Bounding box for the player's car
    sf::FloatRect playerBoundingBox = userSprite.getGlobalBounds();

    // Bounding boxes for opponents
    sf::FloatRect opp1BoundingBox = opp1.getGlobalBounds();
    sf::FloatRect opp2BoundingBox = opp2.getGlobalBounds();

    if(playerBoundingBox.intersects(opp1BoundingBox))
    {
        //--countLife;
        soundgame.stop();
        game_win.close();
        gameOver();
    }
    if(playerBoundingBox.intersects(opp2BoundingBox))
    {
        //--countLife;
        soundgame.stop();
        game_win.close();
        gameOver();
    }
}

void Game::gameOver()
{

    endGame.create(sf::VideoMode(700, 400), "End Game");
    text.setCharacterSize(70);
    
    while (endGame.isOpen()) {
        sf::Event event;
        while (endGame.pollEvent(event)) {
            if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter) {
                endGame.close();
            }
        }

        
        stringscore = "YOU SCORED: " + std::to_string(score);
        text.setString(stringscore);
        text.setPosition(90, 150);
        
        endGame.clear();
        endGame.draw(text);
        endGame.display();
    }
    
}

void Game::togglePause()
{
    isPaused = !isPaused;
    if (isMuted)
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