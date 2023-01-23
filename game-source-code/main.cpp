#include <SFML/Graphics.hpp>
#include "ScreenRenderer.h"

using namespace std;

const float gameWidth = 1920.0f;
const float gameHeight = 1080.0f;
const int frameRate = 60;

int main(){
    auto window = sf::RenderWindow{sf::VideoMode(gameWidth, gameHeight), "The Trench Revolution"};
    window.setView(sf::View(sf::FloatRect(0.0f, 0.0f, gameWidth, gameHeight)));
    window.setFramerateLimit(frameRate);

    auto screenRenderer = ScreenRenderer{gameWidth, gameHeight};

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
        }

        //Update

        //Draw
        window.clear(sf::Color(50, 200, 50));

        screenRenderer.draw(window);

        window.display();
    }

    return 0;
}
