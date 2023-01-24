#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML/Graphics.hpp>
#include "ScreenRenderer.h"
#include "GameState.h"
#include "Drawable.h"
#include "Unit.h"
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

    private:
        sf::RenderWindow window;
        const float gameWidth = 1920.0f;
        const float gameHeight = 1080.0f;
        const unsigned short frameRate = 60;
        GameState gameState;
        shared_ptr<ScreenRenderer> screenRenderer;
        vector<shared_ptr<Drawable>> drawableObjects;
        vector<shared_ptr<Unit>> friendlyUnits;
        vector<shared_ptr<Unit>> enemyUnits;
};

#endif // GAMEMANAGER_H
