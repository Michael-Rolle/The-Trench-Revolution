#ifndef SCREENRENDERER_H
#define SCREENRENDERER_H

#include <SFML/Graphics.hpp>
#include "Drawable.h"

class ScreenRenderer : public Drawable//Renders the background image as well as all buttons
{
    public:
        ScreenRenderer(const float gameWidth, const float gameHeight);
        //void renderStartScreen();
        //void renderPlayingField();
        virtual void draw(sf::RenderWindow& window) override;

    private:
        sf::Font font;
        sf::Text title;
        sf::Texture startButtonText;
        sf::Sprite startButton;
        sf::Texture startBackgroundText;
        sf::Sprite startBackground;
};

#endif // SCREENRENDERER_H
