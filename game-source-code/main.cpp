#include <SFML/Graphics.hpp>
#include "ScreenRenderer.h"
#include "GameState.h"
#include <memory>
#include <vector>
#include <string>

using namespace std;

const float gameWidth = 1920.0f;
const float gameHeight = 1080.0f;
const int frameRate = 60;

void draw(shared_ptr<Drawable> drawable, sf::RenderWindow& window, const GameState gameState)
{
    drawable->draw(window, gameState);
}

int main(){
    auto window = sf::RenderWindow{sf::VideoMode(gameWidth, gameHeight), "The Trench Revolution"};
    window.setView(sf::View(sf::FloatRect(0.0f, 0.0f, gameWidth, gameHeight)));
    window.setFramerateLimit(frameRate);

    auto gameState = GameState::StartScreen;
    auto screenRenderer = make_shared<ScreenRenderer>(gameWidth, gameHeight);

    auto drawableObjects = vector<shared_ptr<Drawable>>{ screenRenderer };

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
                break;
            }
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                auto buttonRect = make_unique<sf::FloatRect>(screenRenderer->startButtonCoordinates());
                auto mouseX = make_unique<float>(sf::Mouse::getPosition(window).x);
                auto mouseY = make_unique<float>(sf::Mouse::getPosition(window).y);
                if((*mouseX - buttonRect->left <= buttonRect->width) && (*mouseX - buttonRect->left > 0) && (*mouseY - buttonRect->top  <= buttonRect->height) && (*mouseY - buttonRect->top  > 0))
                    gameState = GameState::Playing;
            }
        }

        //Update

        //Draw
        window.clear(sf::Color(50, 200, 50));

        for(auto& elem : drawableObjects)
            draw(elem, window, gameState);

        window.display();
    }

    return 0;
}
