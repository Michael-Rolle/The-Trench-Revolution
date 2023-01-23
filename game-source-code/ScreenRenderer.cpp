#include "ScreenRenderer.h"

ScreenRenderer::ScreenRenderer(const float gameWidth, const float gameHeight)
{
    if(!startBackgroundText.loadFromFile("resources/startBackground.png"))
        throw "Cannot load background image";
    startBackground.setTexture(startBackgroundText);
    startBackground.setScale(gameWidth/startBackground.getLocalBounds().width, gameHeight/startBackground.getLocalBounds().height);
}

void ScreenRenderer::draw(sf::RenderWindow& window)
{

}

/*void ScreenRenderer::renderStartScreen()
{

}

void ScreenRenderer::renderPlayingField()
{

}*/
