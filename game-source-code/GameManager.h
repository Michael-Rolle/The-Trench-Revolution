#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML/Graphics.hpp>
#include "ScreenRenderer.h"
#include "GameState.h"
#include "Drawable.h"
#include "Unit.h"
#include "ButtonController.h"
#include "UnitController.h"
#include "Money.h"
#include "Base.h"
#include <memory>
#include <vector>

using namespace std;

class GameManager
{
    //Member Functions
    public:
        GameManager();
        void run();
    private:
        void pollEvent();
        void update();
        void render();
        void resetGame();
        void draw(shared_ptr<Drawable> drawable);

    public:
        static const float gameWidth;
        static const float gameHeight;
    private:
        sf::RenderWindow window;
        const unsigned short frameRate = 60;
        float elapsedTransitionTime;
        bool victory;
        sf::Clock clock;
        sf::Clock scrollClock;
        GameState gameState;
        shared_ptr<ScreenRenderer> screenRenderer;
        shared_ptr<ButtonController> buttonController;
        shared_ptr<UnitController> unitController;
        shared_ptr<Money> money;
        vector<shared_ptr<Drawable>> drawableObjects;
        sf::Font font;
        float totalTime;
        sf::Text time;
};

#endif // GAMEMANAGER_H
