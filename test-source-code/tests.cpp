#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <SFML/Graphics.hpp>
#include <memory>

using namespace std;

shared_ptr<sf::Texture> startButtonText;

TEST_CASE("Shared pointer texture can load a file")
{
    startButtonText = make_shared<sf::Texture>();
    CHECK(startButtonText->loadFromFile("resources/startButton.png"));
}
