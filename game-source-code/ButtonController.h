#ifndef BUTTONCONTROLLER_H
#define BUTTONCONTROLLER_H

#include "Button.h"
#include "GameState.h"

class ButtonController
{
    public:
        ButtonController(const float gameWidth, const float gameHeight);
        void checkButtonClicks(const sf::Event& event, sf::RenderWindow& window, GameState& gameState);

    private:
        void startGame(GameState& gameState) { gameState = GameState::Playing; }

    private:
        sf::Texture startButtonText;
        Button startButton;
        sf::Texture riflemanButtonText;
        Button riflemanButton;
};

#endif // BUTTONCONTROLLER_H
