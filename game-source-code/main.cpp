#include <SFML/Graphics.hpp>

using namespace std;

const float gameWidth = 1920.0f;
const float gameHeight = 1080.0f;
const int frameRate = 60;

int main(){
    auto window = sf::RenderWindow{sf::VideoMode(1920, 1080), "The Trench Revolution"};
    window.setView(sf::View(sf::FloatRect(0.0f, 0.0f, gameWidth, gameHeight)));
    window.setFramerateLimit(frameRate);

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

    }

    return 0;
}
