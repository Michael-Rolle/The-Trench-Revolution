#ifndef UNITCONTROLLER_H
#define UNITCONTROLLER_H

#include "Unit.h"
#include "Drawable.h"
#include "Rifleman.h"
#include "Money.h"
#include "AnimationMode.h"
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

class UnitController : public Drawable
{
    public:
        UnitController();
        void addFriendlyUnit(shared_ptr<Unit> unit);
        void addEnemyUnit(shared_ptr<Unit> unit);
        void updateUnits(const float deltaTime, shared_ptr<Money> money, const float gameWidth, const float gameHeight); //must involve removing dead units
        virtual void draw(sf::RenderWindow& window, const GameState gameState) override;

    private:
        float totalTime;
        sf::Texture enemyRiflemanText;
        vector<shared_ptr<Unit>> friendlyUnits;
        vector<shared_ptr<Unit>> enemyUnits;
};

#endif // UNITCONTROLLER_H
