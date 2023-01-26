#include "UnitController.h"

UnitController::UnitController(): \
    friendlyUnits{},
    enemyUnits{}
{
    totalTime = 0;
    if(!riflemanIdle.loadFromFile("resources/Rifleman/Idle.png"))
        throw "Cannot load texture";
    if(!riflemanRun.loadFromFile("resources/Rifleman/Run.png"))
        throw "Cannot load texture";
    if(!riflemanShoot.loadFromFile("resources/Rifleman/Shoot.png"))
        throw "Cannot load texture";
    if(!riflemanDie.loadFromFile("resources/Rifleman/Die.png"))
        throw "Cannot load texture";
}

void UnitController::addFriendlyUnit(shared_ptr<Unit> unit)
{
    friendlyUnits.push_back(unit);
    sort(friendlyUnits.begin(), friendlyUnits.end()); //sorts them based on the row they're in
}

void UnitController::addEnemyUnit(shared_ptr<Unit> unit)
{
    enemyUnits.push_back(unit);
    sort(enemyUnits.begin(), enemyUnits.end());
}

void UnitController::updateUnits(const float deltaTime, shared_ptr<Money> money, const float gameWidth, const float gameHeight)
{
    totalTime += deltaTime;
    for(auto& unit : friendlyUnits)
    {
        if(unit->blockNum < 70)
            unit->updateAnimation(AnimationMode::Run, &riflemanRun, deltaTime);
        else
            unit->updateAnimation(AnimationMode::Shoot, &riflemanShoot, deltaTime);
        if(unit->reloading)
            unit->reload(deltaTime);
        if(unit->getPositionX() < (0.01*gameWidth)*unit->blockNum)
        {
            unit->advance(deltaTime);
        }
        else//Check for enemies in range
        {
            if(unit->blockNum < 70)
                unit->blockNum++;
        }
        unit->fire(enemyUnits);
        if(!unit->alive)
        {
            std::remove(friendlyUnits.begin(), friendlyUnits.end(), unit);
            friendlyUnits.erase(friendlyUnits.end());
            break;
        }

    }

    if(totalTime > 5+(rand()%10))
    {
        totalTime = 0;
        UnitController::addEnemyUnit(make_shared<Rifleman>(&riflemanIdle, gameWidth, gameHeight, 10, 0.1, false));
    }

    for(auto& unit: enemyUnits)
    {
        unit->updateAnimation(AnimationMode::Run, &riflemanRun, deltaTime);
        if(unit->reloading)
            unit->reload(deltaTime);
        if(unit->getPositionX() > (0.01*gameWidth)*unit->blockNum)
        {
            unit->advance(deltaTime);
        }
        else
        {
            if(unit->blockNum > 10)
                unit->blockNum--;
        }
        unit->fire(friendlyUnits);
        if(!unit->alive)
        {
            money->add((int)unit->cost/2);
            std::remove(enemyUnits.begin(), enemyUnits.end(), unit);
            enemyUnits.erase(enemyUnits.end());
            break;
        }

    }
}

void UnitController::draw(sf::RenderWindow& window, const GameState gameState)
{
    if(gameState == GameState::Playing)
    {
        for(auto& unit : friendlyUnits)
        {
            unit->draw(window, gameState);
        }
        for(auto& unit : enemyUnits)
        {
            unit->draw(window, gameState);
        }
    }
}


