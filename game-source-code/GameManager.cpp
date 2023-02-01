#include "GameManager.h"

const float GameManager::gameWidth = 1920.0f;
const float GameManager::gameHeight = 1080.0f;

GameManager::GameManager():
    window{sf::VideoMode(1280.0f, 720.0f), "The Trench Revoltion"},
    gameState{GameState::StartScreen},
    screenRenderer{make_shared<ScreenRenderer>(gameWidth, gameHeight)},
    buttonController{make_shared<ButtonController>(gameWidth, gameHeight)},
    unitController{make_shared<UnitController>()},
    money{make_shared<Money>(gameWidth, gameHeight)},
    drawableObjects{ screenRenderer, unitController, buttonController, money }
{
    //Window
    window.setView(sf::View(sf::FloatRect(0.0f, 0.0f, gameWidth, gameHeight)));
    window.setFramerateLimit(frameRate);
}

void GameManager::run() //Main game loop
{
    while(window.isOpen())
    {
        pollEvent();
        update();
        render();
    }
}

void GameManager::pollEvent()
{
    auto event = make_shared<sf::Event>();
    while(window.pollEvent(*event))
    {
        if(event->type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
            break;
        }
        if(gameState == GameState::Playing)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                auto windowWidth = window.getView().getSize().x;
                auto windowHeight = window.getView().getSize().y;
                auto windowLeft = window.getView().getCenter().x - 0.5f*windowWidth;
                auto windowTop = window.getView().getCenter().y - 0.5f*windowHeight;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (windowLeft + windowWidth < gameWidth))
                {
                    window.setView(sf::View{sf::FloatRect{windowLeft+0.1*clock.getElapsedTime().asSeconds()*gameWidth, windowTop, windowWidth, windowHeight}});
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (windowLeft > 0.0f))
                {
                    window.setView(sf::View{sf::FloatRect{windowLeft-0.1*clock.getElapsedTime().asSeconds()*gameWidth, windowTop, windowWidth, windowHeight}});
                }
            }
        }
        buttonController->checkButtonClicks(*event, window, clock, gameState, unitController, money, gameWidth, gameHeight);
    }
}

void GameManager::update()
{
    if(gameState == GameState::Playing)
    {
        unitController->updateUnits(clock.getElapsedTime().asSeconds(), money, gameWidth, gameHeight);
        money->update(clock.getElapsedTime().asSeconds());
        clock.restart();
    }
}

void GameManager::render()
{
    window.clear(sf::Color(50, 200, 50));

    for(auto& elem : drawableObjects)
        draw(elem);

    window.display();
}

void GameManager::resetGame()
{

}

void GameManager::draw(shared_ptr<Drawable> drawable)
{
    drawable->draw(window, gameState);
}
