#include "GameManager.h"

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
