#ifndef BUTTONCONTROLLER_H
#define BUTTONCONTROLLER_H

#include "Button.h"
#include "GameState.h"
#include "Drawable.h"
#include "Unit.h"
#include "Rifleman.h"
#include "UnitController.h"
#include "Money.h"
#include <vector>
#include <memory>

using namespace std;

class ButtonController : public Drawable
{
    public:
        ButtonController(const float gameWidth, const float gameHeight);
        void checkButtonClicks(const sf::Event& event, sf::RenderWindow& window, sf::Clock& clock, GameState& gameState, shared_ptr<UnitController> unitController, shared_ptr<Money> money, const float gameWidth, const float gameHeight);
        virtual void draw(sf::RenderWindow& window, const GameState gameState) override;

    private:
        void startGame(GameState& gameState) { gameState = GameState::Playing; }
        void spawnFriendlyUnit(shared_ptr<UnitController> unitController, shared_ptr<Unit> unit, shared_ptr<Money> money);

    private:
        sf::Font pointsFont;
        shared_ptr<sf::Texture> startButtonText;
        Button startButton;
        shared_ptr<sf::Texture> riflemanButtonText;
        Button riflemanButton;
        sf::Text riflemanPoints;
        shared_ptr<sf::Texture> riflemanText;
};

#endif // BUTTONCONTROLLER_H
