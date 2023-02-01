#include "UnitController.h"

UnitController::UnitController():
    riflemanTextures{ make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>() },
    baseTextures{ make_shared<sf::Texture>(), make_shared<sf::Texture>() },
    friendlyUnits{},
    enemyUnits{}
{
    totalTime = 0;

    if(!riflemanTextures.at(0)->loadFromFile("resources/Rifleman/Idle.png"))
        throw "Cannot load texture";
    if(!riflemanTextures.at(1)->loadFromFile("resources/Rifleman/Run.png"))
        throw "Cannot load texture";
    if(!riflemanTextures.at(2)->loadFromFile("resources/Rifleman/Shoot.png"))
        throw "Cannot load texture";
    if(!riflemanTextures.at(3)->loadFromFile("resources/Rifleman/Die.png"))
        throw "Cannot load texture";

    if(!baseTextures.at(0)->loadFromFile("resources/friendlyBase.jpg"))
        throw "Cannot load texture";
    if(!baseTextures.at(0)->loadFromFile("resources/enemyBase.jpg"))
        throw "Cannot load texture";
    auto friendlyBase = make_shared<Base>(baseTextures.at(0), 1920.0f, 1080.0f, 1, 1, true);
    this->addFriendlyUnit(friendlyBase);
    auto enemyBase = make_shared<Base>(baseTextures.at(1), 1920.0f, 1080.0f, 1, 1, false);
    this->addEnemyUnit(enemyBase);
}

struct sortUnit
{
    inline bool operator() (const shared_ptr<Unit>& unit1, const shared_ptr<Unit>& unit2)
    {
        return (unit1->row < unit2->row);
    }
};

void UnitController::addFriendlyUnit(shared_ptr<Unit> unit)
{
    friendlyUnits.push_back(unit);
    sort(friendlyUnits.begin(), friendlyUnits.end(), sortUnit()); //sorts them based on the row they're in
}

void UnitController::addEnemyUnit(shared_ptr<Unit> unit)
{
    enemyUnits.push_back(unit);
    sort(enemyUnits.begin(), enemyUnits.end(), sortUnit());
}

void UnitController::updateUnits(const float deltaTime, shared_ptr<Money> money, const float gameWidth, const float gameHeight)
{
    totalTime += deltaTime;
    for(auto& unit : friendlyUnits)
    {
        switch(unit->unitType)
        {
            case UnitType::Rifleman:
                unit->updateAnimation(riflemanTextures, deltaTime);
                break;
            case UnitType::Base:
                break;
            default:
                throw "Invalid unit type";
        }
        if(unit->alive && !unit->dying)
        {
            if(unit->reloading)
                unit->reload(deltaTime);
            if(unit->getPositionX() < (0.01*gameWidth)*unit->blockNum)
            {
                unit->advance(deltaTime);
            }
            else//Check for enemies in range
            {
                //if(unit->blockNum < 70)
                    unit->blockNum++;
            }
            unit->fire(enemyUnits);
        }
        else if(!unit->alive && !unit->dying)
        {
            std::remove(friendlyUnits.begin(), friendlyUnits.end(), unit);
            friendlyUnits.erase(friendlyUnits.end());
            break;
        }
    }

    if(totalTime > 5+(rand()%10))
    {
        totalTime = 0;
        UnitController::addEnemyUnit(make_shared<Rifleman>(riflemanTextures.at(0), gameWidth, gameHeight, 10, 0.1, false));
    }

    for(auto& unit: enemyUnits)
    {
        switch(unit->unitType)
        {
            case UnitType::Rifleman:
                unit->updateAnimation(riflemanTextures, deltaTime);
                break;
            case UnitType::Base:
                break;
            default:
                throw "Invalid unit type";
        }
        if(unit->alive && !unit->dying)
        {
            if(unit->reloading)
                unit->reload(deltaTime);
            if(unit->getPositionX() > (0.01*gameWidth)*unit->blockNum)
            {
                unit->advance(deltaTime);
            }
            else
            {
                //if(unit->blockNum > 10)
                    unit->blockNum--;
            }
            unit->fire(friendlyUnits);
        }
        else if(!unit->alive && !unit->dying)
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


