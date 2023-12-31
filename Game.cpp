#include "MainMenu.h"
#include "Game.h"

const float borderLeft = 175.0f;
const float borderRight = 555.0f;
const float borderUp = 100.0f;
const float borderDown = 900.0f;


Game::Game() 
{
    isPaused = false;
    gamewinX = 800;
    gamewinY = 1030;
    lifeX = gamewinX -280;
    lifeY = gamewinY - 995;
    countLife = 4;
    userX = 360.0f; 
    userY = 850.0f;
    scalefactor = 0.13f;
    backgroundSpeed = 200.f;
    carspeed = 0.2f;
    movespeed = 30.f;
    backgroundY1 = 0;
    backgroundY2 = -1020;
    opp1Y = -1400; opp2Y = -900; 
    score = 0; prevscore =0; scoreInterval = 100;

    //options for pause
    pauseOption[0].setString("Continue");
    pauseOption[1].setString("Exit");
    
    srand(static_cast<unsigned>(time(0)));
    
    opp1X = getRandomNumber(borderLeft, borderRight);
    opp2X = getRandomNumber(borderLeft, borderRight);
    
    //loading font
    if(!myfont.loadFromFile("game_resrc/Giveny.ttf")) std::cout<< "Error in loading font" << std::endl;
    text.setFont(myfont); 
    
    //loading sound
    if (!playSound.loadFromFile("game_resrc/sound1.wav")) std::cout << "Error in loading audio"<< std::endl;
    soundgame.setBuffer(playSound);

    //loading texture
    if (!userCar.loadFromFile("game_resrc/new_car.png")) std::cout << "Error in loading texture"<< std::endl;
    if(!oppCar1.loadFromFile("game_resrc/opp_car1.png")) std::cout << "Error in loading texture"<< std::endl;
    if(!oppCar2.loadFromFile("game_resrc/opp_car2.png")) std::cout << "Error in loading texture"<< std::endl;
    if(!game_back.loadFromFile("game_resrc/new_back.png")) std::cout << "Error in loading texture" << std::endl;
    userSprite.setTexture(userCar);
    opp1.setTexture(oppCar1);
    opp2.setTexture(oppCar2);

    //Sprite for Life
    for(int i = 0; i<3; i++)
    {
        if(!heart[i].loadFromFile("game_resrc/heart.png")) std::cout<< "error in loading texture" << std::endl;
        life[i].setTexture(heart[i]);
        life[i].setScale(0.4,0.4);
        life[i].setPosition(lifeX + i * 80.0f, lifeY);
    }

    // Two sprites for the background
    background1.setTexture(game_back);
    background2.setTexture(game_back);

    //setting up user sprite car
    userSprite.setPosition(sf::Vector2f(userX, userY));
    userSprite.setScale(scalefactor +0.02, scalefactor);

    //setting up opponent sprite car 
    opp1.setScale(0.9, 0.9);
    opp2.setScale(0.4, 0.4);
    
    //setting opp position
    opp1.setPosition(opp1X, opp1Y);
    opp2.setPosition(opp2X, opp2Y);

}
void Game::gameRun()
{    
    game_win.create(sf::VideoMode(gamewinX, gamewinY), "IN Game");

    if(isMuted)
        soundgame.pause();
    else 
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
    //sf::Sound mainsound;
    if (key == sf::Keyboard::Escape) 
    {
        soundgame.pause();
        //MainMenu mainMenu;
        if(isMuted)
            mainsound.pause();
        else
            mainsound.play();
        game_win.close();
    }
    if(key == sf::Keyboard::Tab)
    {
        togglePause();
    }
    if (key == sf::Keyboard::Left || key == sf::Keyboard::A)
    {
        if (userSprite.getPosition().x + 1 >= borderLeft)
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
    for(int i = 0; i < 3; i++)
    {
        game_win.draw(life[i]);
    }
    game_win.display();
}

void Game::update()
{
    if(!isPaused)
    {
        deltaTime = clock.restart();
        //moving the background
        backgroundY1+=backgroundSpeed * deltaTime.asSeconds() ;
        backgroundY2+=backgroundSpeed * deltaTime.asSeconds() ;

        //checking if the background has moved off
        if (backgroundY2>0)
        {
            backgroundY1=0;
            backgroundY2=backgroundY1-1020;

        }
        //setting the position of the background 
        background1.setPosition(0,backgroundY1);
        background2.setPosition(0, backgroundY2);

        deltaTime1 = clock1.restart();
        // Moving the opponent cars
        if (opp1Y > 1030)
        {
            opp1Y = -100;
            opp1X = getRandomNumber(borderLeft, borderRight);
            score = score + 10; 
        }
        else
        {
            opp1Y += carspeed;
        }

        if (opp2Y > 1030)
        {
            opp2Y = opp1Y-600;
            opp2X = getRandomNumber(borderLeft, borderRight);
            score= score +10;
        }
        else
        {
            opp2Y += carspeed;
        }

        //setting position
        opp1.setPosition(sf::Vector2f(opp1X, opp1Y));
        opp2.setPosition(sf::Vector2f(opp2X, opp2Y));
        
        //game level
        if(score >= prevscore+scoreInterval)
        {
                carspeed +=0.05f;
                prevscore=score;
        }
        
        //displaying score
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

    if(playerBoundingBox.intersects(opp1BoundingBox) ||playerBoundingBox.intersects(opp2BoundingBox))
    {
        --countLife;
        if(countLife<=1)
        {
            soundgame.stop();
            game_win.close();
            gameOver();
        }
        else
        {
            reset();
        }
    }

    switch (countLife)
    {
    case 3:
        life[2].setColor(sf::Color::Black);
        break;

    case 2:
        life[1].setColor(sf::Color::Black);
        break;
    
    case 1:
        life[0].setColor(sf::Color::Black);
        break;

    default:
        break;
    }
}

void Game::reset()
{
    // Reset positions of the player and opponents to continue the game
    userX = 360.0f; 
    userY = 850.0f;
    userSprite.setPosition(sf::Vector2f(userX, userY));
    opp1Y = -1400;
    opp2Y = -900;
    carspeed = 0.2f;
    opp1X = getRandomNumber(borderLeft, borderRight);
    opp2X = getRandomNumber(borderLeft, borderRight);
    opp1.setPosition(sf::Vector2f(opp1X, opp1Y));
    opp2.setPosition(sf::Vector2f(opp2X, opp2Y));
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
    if(isMuted)
        mainsound.pause();
    else
        mainsound.play();
}

void Game::togglePause()
{
    resume();

    sf::RenderWindow pauseWindow(sf::VideoMode(600,400),"Notice");
    sf::Text msg;
    msg.setString("Are you sure?");
    msg.setFont(myfont);
    msg.setCharacterSize(40);
    msg.setPosition(180, 70);
    buttonSprite.setScale(0.6f, 0.6f);
    for(int i=0; i<2; i++)
    {
        pauseOption[i].setFont(myfont);
        pauseOption[i].setCharacterSize(40);
        pauseOption[i].setPosition(290 * i + 110, 250);
    }
    int exitOption = 0;
    buttonSprite.setPosition(90.0f,245.0f);
    while (pauseWindow.isOpen())
    {
        sf::Event pauseEvent;
        while (pauseWindow.pollEvent(pauseEvent))
        {
            if (pauseEvent.type == sf::Event::KeyPressed)
            {
                if (pauseEvent.key.code == sf::Keyboard::Left)
                {
                    if(exitOption == 1)
                    {
                        buttonSprite.move(-235, 0);
                        --exitOption;
                        button.play();
                    }

                }
                else if (pauseEvent.key.code == sf::Keyboard::Right)
                {
                    if(exitOption == 0)
                    {
                        buttonSprite.move(235, 0);
                        ++exitOption;
                        button.play();
                    }
                }
                else if(pauseEvent.key.code == sf::Keyboard::Enter)
                {
                    if(exitOption == 0)
                    {
                        
                        pauseWindow.close();
                        resume();
                        if(isMuted)
                            soundgame.pause();
                        else
                            soundgame.play();
                    }
                    else
                    {
                        pauseWindow.close();
                        game_win.close();
                        if(isMuted)
                            mainsound.pause();
                        else
                            mainsound.play();
                    }
                }
            }
        }
        
        pauseWindow.clear();
        pauseWindow.draw(msg);
        for(int i=0; i<2; i++)
        {
            pauseWindow.draw(pauseOption[i]);
        }
        pauseWindow.draw(buttonSprite);
        pauseWindow.display();
    }
    
}

void Game::resume()
{
    isPaused = !isPaused;
    if(!pauseWindow.isOpen())
    {
        soundgame.pause();
    }
}