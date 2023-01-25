#ifndef BUTTONCONTROLLER_H
#define BUTTONCONTROLLER_H

#include "Button.h"
#include "GameState.h"
#include "Drawable.h"
#include "Unit.h"
#include "Rifleman.h"
#include "UnitController.h"
#include <vector>
#include <memory>

using namespace std;

class ButtonController : public Drawable
{
    public:
        ButtonController(const float gameWidth, const float gameHeight);
        void checkButtonClicks(const sf::Event& event, sf::RenderWindow& window, GameState& gameState, shared_ptr<UnitController> unitController, const float gameWidth, const float gameHeight);
        virtual void draw(sf::RenderWindow& window, const GameState gameState) override;

    private:
        void startGame(GameState& gameState) { gameState = GameState::Playing; }
        void spawnFriendlyUnit(shared_ptr<UnitController> unitController, shared_ptr<Unit> unit);

    private:
        sf::Texture startButtonText;
        Button startButton;
        sf::Texture riflemanButtonText;
        Button riflemanButton;
        sf::Texture riflemanText;
};

#endif // BUTTONCONTROLLER_H
