#include "UnitController.h"

UnitController::UnitController():
    riflemanTextures{ make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>() },
    shotgunnerTextures{ make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>() },
    sniperTextures{ make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>() },
    machineGunnerTextures{ make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>() },
    baseTextures{ make_shared<sf::Texture>(), make_shared<sf::Texture>() },
    units{}
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

    if(!machineGunnerTextures.at(0)->loadFromFile("resources/MachineGunner/Idle.png"))
        throw "Cannot load texture";
    if(!machineGunnerTextures.at(1)->loadFromFile("resources/MachineGunner/Run.png"))
        throw "Cannot load texture";
    if(!machineGunnerTextures.at(2)->loadFromFile("resources/MachineGunner/Shoot.png"))
        throw "Cannot load texture";
    if(!machineGunnerTextures.at(3)->loadFromFile("resources/MachineGunner/Die.png"))
        throw "Cannot load texture";

    if(!baseTextures.at(0)->loadFromFile("resources/friendlyBase.png"))
        throw "Cannot load texture";
    if(!baseTextures.at(1)->loadFromFile("resources/enemyBase.png"))
        throw "Cannot load texture";
    auto friendlyBase = make_shared<Base>(baseTextures.at(0), 1920.0f, 1080.0f, true);
    this->addUnit(friendlyBase);
    auto enemyBase = make_shared<Base>(baseTextures.at(1), 1920.0f, 1080.0f, false);
    this->addUnit(enemyBase);
}

struct sortUnit
{
    inline bool operator() (const shared_ptr<Unit>& unit1, const shared_ptr<Unit>& unit2)
    {
        return (unit1->row < unit2->row);
    }
};

void UnitController::addUnit(shared_ptr<Unit> unit)
{
    units.push_back(unit);
    sort(units.begin(), units.end(), sortUnit()); //sorts them based on the row they're in
}

void UnitController::spawnEnemies(const float gameWidth, const float gameHeight)
{
    if(totalTime > spawnTime)
    {
        totalTime = 0;
        spawnTime = 5+rand()%20;
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
                unit = make_shared<Rifleman>(riflemanTextures.at(0), gameWidth, gameHeight, false);
            else if(randNum <= 80)
                unit = make_shared<Shotgunner>(shotgunnerTextures.at(0), gameWidth, gameHeight, false);
            else if(randNum <= 90)
                unit = make_shared<Sniper>(sniperTextures.at(0), gameWidth, gameHeight, false);
            else
                unit = make_shared<MachineGunner>(machineGunnerTextures.at(0), gameWidth, gameHeight, false);
            UnitController::addUnit(unit);
        }
    }
}

void UnitController::updateUnits(const float deltaTime, shared_ptr<Money> money, bool& victory, GameState& gameState, const float gameWidth, const float gameHeight)
{
    totalTime += deltaTime;
    for(auto& unit : units)
    {
        switch(unit->unitType)
        {
            case UnitType::Rifleman:
                unit->update(units, riflemanTextures, deltaTime, gameWidth, gameHeight);
                break;
            case UnitType::Shotgunner:
                unit->update(units, shotgunnerTextures, deltaTime, gameWidth, gameHeight);
                break;
            case UnitType::Sniper:
                unit->update(units, sniperTextures, deltaTime, gameWidth, gameHeight);
                break;
            case UnitType::MachineGunner:
                unit->update(units, machineGunnerTextures, deltaTime, gameWidth, gameHeight);
                break;
            case UnitType::Base:
                unit->update(units, baseTextures, deltaTime, gameWidth, gameHeight);
                break;
            default:
                throw "Invalid unit type";
        }
        if(!unit->alive && !unit->dying)
        {
            if(unit->unitType == UnitType::Base)
            {
                gameState = GameState::EndScreen;
                if(unit->friendly)
                    victory = false;
                else
                    victory = true;
                return;
            }
            std::remove(units.begin(), units.end(), unit);
            units.erase(units.end());
            break;
        }
    }
    UnitController::spawnEnemies(gameWidth, gameHeight);
}

    /*for(auto& unit: enemyUnits)
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
            case UnitType::MachineGunner:
                unit->updateAnimation(machineGunnerTextures, deltaTime);
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
    }*/

void UnitController::draw(sf::RenderWindow& window, const GameState gameState)
{
    if(gameState == GameState::Playing || gameState == GameState::EndScreen)
    {
        for(auto& unit : units)
        {
            unit->draw(window, gameState);
        }
    }
}


