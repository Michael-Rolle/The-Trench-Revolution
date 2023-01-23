#ifndef SCREENRENDERER_H
#define SCREENRENDERER_H

#include <SFML/Graphics.hpp>
#include "Drawable.h"
#include "GameState.h"

class ScreenRenderer : public Drawable//Renders the background image as well as all buttons
{
    public:
        ScreenRenderer(const float gameWidth, const float gameHeight);
        //void renderStartScreen();
        //void renderPlayingField();
        virtual void draw(sf::RenderWindow& window) override;

    private:
        GameState gameState;
        sf::Font font;
        sf::Text title;
        sf::Texture startButtonText;
        sf::Sprite startButton;
        sf::Texture quitButtonText;
        sf::Sprite quitButton;
        sf::Texture startBackgroundText;
        sf::Sprite startBackground;
        sf::Texture playingFieldBackgroundText;
        sf::Sprite playingFieldBackground;
        sf::Texture endBackgroundText;
        sf::Sprite endBackground;
};

#endif // SCREENRENDERER_H
