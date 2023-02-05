#include "UnitController.h"

UnitController::UnitController():
    riflemanTextures{ make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>() },
    shotgunnerTextures{ make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>() },
    sniperTextures{ make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>() },
    baseTextures{ make_shared<sf::Texture>(), make_shared<sf::Texture>() },
    friendlyUnits{},
    enemyUnits{}
{
    this->totalTime = 0;
    this->spawnTime = 1;

    if(!riflemanTextures.at(0)->loadFromFile("resources/Rifleman/Idle.png"))
        throw "Cannot load texture";
    if(!riflemanTextures.at(1)->loadFromFile("resources/Rifleman/Run.png"))
        throw "Cannot load texture";
    if(!riflemanTextures.at(2)->loadFromFile("resources/Rifleman/Shoot.png"))
        throw "Cannot load texture";
    if(!riflemanTextures.at(3)->loadFromFile("resources/Rifleman/Die.png"))
        throw "Cannot load texture";

    if(!shotgunnerTextures.at(0)->loadFromFile("resources/Shotgunner/Idle.png"))
        throw "Cannot load texture";
    if(!shotgunnerTextures.at(1)->loadFromFile("resources/Shotgunner/Run.png"))
        throw "Cannot load texture";
    if(!shotgunnerTextures.at(2)->loadFromFile("resources/Shotgunner/Shoot.png"))
        throw "Cannot load texture";
    if(!shotgunnerTextures.at(3)->loadFromFile("resources/Shotgunner/Die.png"))
        throw "Cannot load texture";

    if(!sniperTextures.at(0)->loadFromFile("resources/Sniper/Idle.png"))
        throw "Cannot load texture";
    if(!sniperTextures.at(1)->loadFromFile("resources/Sniper/Run.png"))
        throw "Cannot load texture";
    if(!sniperTextures.at(2)->loadFromFile("resources/Sniper/Shoot.png"))
        throw "Cannot load texture";
    if(!sniperTextures.at(3)->loadFromFile("resources/Sniper/Die.png"))
        throw "Cannot load texture";

    if(!baseTextures.at(0)->loadFromFile("resources/friendlyBase.png"))
        throw "Cannot load texture";
    if(!baseTextures.at(1)->loadFromFile("resources/enemyBase.png"))
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
    unit->friendly = true;
    friendlyUnits.push_back(unit);
    sort(friendlyUnits.begin(), friendlyUnits.end(), sortUnit()); //sorts them based on the row they're in
}

void UnitController::addEnemyUnit(shared_ptr<Unit> unit)
{
    unit->friendly = false;
    enemyUnits.push_back(unit);
    sort(enemyUnits.begin(), enemyUnits.end(), sortUnit());
}

void UnitController::updateUnits(const float deltaTime, shared_ptr<Money> money, bool& victory, GameState& gameState, const float gameWidth, const float gameHeight)
{
    totalTime += deltaTime;
    for(auto& unit : friendlyUnits)
    {
        switch(unit->unitType)
        {
            case UnitType::Rifleman:
                unit->updateAnimation(riflemanTextures, deltaTime);
                break;
            case UnitType::Shotgunner:
                unit->updateAnimation(shotgunnerTextures, deltaTime);
                break;
            case UnitType::Sniper:
                unit->updateAnimation(sniperTextures, deltaTime);
                break;
            case UnitType::Base:
                unit->updateAnimation(baseTextures, deltaTime);
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
            else
            {
                unit->blockNum++;
            }
            unit->fire(enemyUnits);
        }
        else if(!unit->alive && !unit->dying)
        {
            if(unit->unitType == UnitType::Base)
            {
                gameState = GameState::EndScreen;
                victory = false;
                return;
            }
            std::remove(friendlyUnits.begin(), friendlyUnits.end(), unit);
            friendlyUnits.erase(friendlyUnits.end());
            break;
        }
    }

    if(totalTime > spawnTime)
    {
        totalTime = 0;
        spawnTime = 5+rand()%25;
        int numEnemies;
        auto numEnemiesRand = 1+rand()%100;
        if(numEnemiesRand <= 50)
            numEnemies = 1; //50% chance
        else if(numEnemiesRand <= 75)
            numEnemies = 2; //25% chance
        else if(numEnemiesRand <= 90)
            numEnemies = 3; //15% chance
        else if(numEnemiesRand <= 98)
            numEnemies = 4; //8% chance
        else
            numEnemies = 5; //2% chance
        for(int i = 0; i < numEnemies; i++)
        {
            auto randNum = 1+rand()%100; //random number between 1 and 100
            shared_ptr<Unit> unit;
            if(randNum <= 70)
            {
                unit = make_shared<Rifleman>(riflemanTextures.at(0), gameWidth, gameHeight, 10, 0.10, false);
            }
            else if(randNum <= 90)
            {
                unit = make_shared<Shotgunner>(shotgunnerTextures.at(0), gameWidth, gameHeight,  10, 0.08, false);
            }
            else
            {
                unit = make_shared<Sniper>(sniperTextures.at(0), gameWidth, gameHeight, 10, 0.12, false);
            }
            UnitController::addEnemyUnit(unit);
        }
    }

    for(auto& unit: enemyUnits)
    {
        switch(unit->unitType)
        {
            case UnitType::Rifleman:
                unit->updateAnimation(riflemanTextures, deltaTime);
                break;
            case UnitType::Shotgunner:
                unit->updateAnimation(shotgunnerTextures, deltaTime);
            case UnitType::Sniper:
                unit->updateAnimation(sniperTextures, deltaTime);
                break;
            case UnitType::Base:
                unit->updateAnimation(baseTextures, deltaTime);
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
                unit->blockNum--;
            }
            unit->fire(friendlyUnits);
        }
        else if(!unit->alive && !unit->dying)
        {
            if(unit->unitType == UnitType::Base)
            {
                gameState = GameState::EndScreen;
                victory = true;
                return;
            }
            money->add((int)unit->cost/2);
            std::remove(enemyUnits.begin(), enemyUnits.end(), unit);
            enemyUnits.erase(enemyUnits.end());
            break;
        }
    }
}

void UnitController::draw(sf::RenderWindow& window, const GameState gameState)
{
    if(gameState == GameState::Playing || gameState == GameState::EndScreen)
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


