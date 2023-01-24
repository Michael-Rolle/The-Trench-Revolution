#include "GameManager.h"

GameManager::GameManager():
    window{sf::VideoMode(1280, 720), "The Trench Revoltion"},
    gameState{GameState::StartScreen},
    screenRenderer{make_shared<ScreenRenderer>(gameWidth, gameHeight)},
    drawableObjects{ screenRenderer },
    friendlyUnits{},
    enemyUnits{}
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
        if(event->type == sf::Event::MouseButtonPressed && event->mouseButton.button == sf::Mouse::Left)
        {
            auto buttonRect = make_unique<sf::FloatRect>(screenRenderer->startButtonCoordinates());
            auto mouseX = make_unique<float>(sf::Mouse::getPosition(window).x);
            auto mouseY = make_unique<float>(sf::Mouse::getPosition(window).y);
            if((*mouseX - buttonRect->left <= buttonRect->width) && (*mouseX - buttonRect->left > 0) && (*mouseY - buttonRect->top  <= buttonRect->height) && (*mouseY - buttonRect->top  > 0))
                gameState = GameState::Playing;
        }
    }
}

void GameManager::update()
{

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
