#include "UnitController.h"

UnitController::UnitController():
    riflemanTextures{ make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>() },
    shotgunnerTextures{ make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>() },
    sniperTextures{ make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>() },
    machineGunnerTextures{ make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>() },
    tankTextures{ make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>(), make_shared<sf::Texture>() },
    baseTextures{ make_shared<sf::Texture>(), make_shared<sf::Texture>() },
    units{}
{
    this->elapsedTime = 0;
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

    if(!tankTextures.at(0)->loadFromFile("resources/Tank/Idle.png"))
        throw "Cannot load texture";
    if(!tankTextures.at(1)->loadFromFile("resources/Tank/Run.png"))
        throw "Cannot load texture";
    if(!tankTextures.at(2)->loadFromFile("resources/Tank/Shoot.png"))
        throw "Cannot load texture";
    if(!tankTextures.at(3)->loadFromFile("resources/Tank/Die.png"))
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
    if(elapsedTime > spawnTime)
    {
        elapsedTime = 0;
        int baseTime;
        int addTime;
        int numEnemiesRand;
        if(totalTime > 360)
        {
            baseTime = 2;
            addTime = 3;
            numEnemiesRand = 61+rand()%20;
        }
        else if(totalTime > 240)
        {
            baseTime = 3;
            addTime = 5;
            numEnemiesRand = 41+rand()%40;
        }
        else if(totalTime > 120)
        {
            baseTime = 4;
            addTime = 10;
            numEnemiesRand = 21+rand()%60;
        }
        else
        {
            baseTime = 5;
            addTime = 20;
            numEnemiesRand = 1+rand()%100;
        }
        spawnTime = baseTime+rand()%addTime;
        int numEnemies;
        if(numEnemiesRand <= 40)
            numEnemies = 1; //40% chance
        else if(numEnemiesRand <= 70)
            numEnemies = 2; //30% chance
        else if(numEnemiesRand <= 90)
            numEnemies = 3; //20% chance
        else if(numEnemiesRand <= 98)
            numEnemies = 4; //8% chance
        else
            numEnemies = 5; //2% chance
        for(int i = 0; i < numEnemies; i++)
        {
            auto randNum = 1+rand()%100; //random number between 1 and 100
            shared_ptr<Unit> unit;
            if(randNum <= 60)
                unit = make_shared<Rifleman>(riflemanTextures.at(0), gameWidth, gameHeight, false);
            else if(randNum <= 75)
                unit = make_shared<Shotgunner>(shotgunnerTextures.at(0), gameWidth, gameHeight, false);
            else if(randNum <= 85)
                unit = make_shared<Sniper>(sniperTextures.at(0), gameWidth, gameHeight, false);
            else if(randNum <= 95)
                unit = make_shared<MachineGunner>(machineGunnerTextures.at(0), gameWidth, gameHeight, false);
            else
                unit = make_shared<Tank>(tankTextures.at(0), gameWidth, gameHeight, false);
            UnitController::addUnit(unit);
        }
    }
}

void UnitController::updateUnits(const float deltaTime, shared_ptr<Money> money, bool& victory, GameState& gameState, const float gameWidth, const float gameHeight)
{
    totalTime += deltaTime;
    elapsedTime += deltaTime;
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
            case UnitType::Tank:
                unit->update(units, tankTextures, deltaTime, gameWidth, gameHeight);
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
            if(!unit->friendly)
                money->add((int)unit->cost/2);
            std::remove(units.begin(), units.end(), unit);
            units.erase(units.end());
            break;
        }
    }
    UnitController::spawnEnemies(gameWidth, gameHeight);
}

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


