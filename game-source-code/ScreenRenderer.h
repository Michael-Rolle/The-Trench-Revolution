#ifndef SCREENRENDERER_H
#define SCREENRENDERER_H

#include <SFML/Graphics.hpp>
#include "Drawable.h"
#include "GameState.h"

class ScreenRenderer : public Drawable//Renders the background image
{
    public:
        ScreenRenderer(const float gameWidth, const float gameHeight);
        virtual void draw(sf::RenderWindow& window, const GameState gameState) override;

    private:
        sf::Font font;
        sf::Text title;
        sf::Texture startBackgroundText;
        sf::Sprite startBackground;
        sf::Texture playingFieldBackgroundText;
        sf::Sprite playingFieldBackground;
        sf::Texture endBackgroundText;
        sf::Sprite endBackground;
};

#endif // SCREENRENDERER_H
