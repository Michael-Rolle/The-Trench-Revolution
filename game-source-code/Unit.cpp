#include "Unit.h"

Unit::Unit(shared_ptr<sf::Texture> texture, unsigned int frameCount, float switchTime, bool friendly):
    greenHealthBar{sf::Vector2f{0.3, 0.03}},
    redHealthBar{sf::Vector2f{0.3, 0.03}},
    animation{texture, frameCount, switchTime}
{
    unitSprite.setTexture(*texture);
    this->row = 1+rand()%50; //Random number between 1 and 50
    if(friendly)
        blockNum = 1;
    else
        blockNum = 100;
    this->alive = true;
    this->friendly = friendly;
    this->canAdvance = true;
    this->reloading = false;
    this->canShoot = true;
    this->shooting = false;
    this->dying = false;
    this->animationMode = AnimationMode::None;

    if(this->friendly)
        this->greenHealthBar.setFillColor(sf::Color::Green);
    else
        this->greenHealthBar.setFillColor(sf::Color::Blue);
    this->redHealthBar.setFillColor(sf::Color::Red);
}

/*void Unit::draw(sf::RenderWindow& window, const GameState gameState)
{
    window.draw(unitSprite);
    window.draw(redHealthBar);
    window.draw(greenHealthBar);
}*/

void Unit::updateAnimation(const vector<shared_ptr<sf::Texture>>& textures, const float deltaTime)
{
    switch(this->animationMode)
    {
        case AnimationMode::None:
            break;
        case AnimationMode::Idle:
            unitSprite.setTexture(*textures.at(0));
            animation.update(textures.at(0), AnimationMode::Idle, this->unitType, this->shooting, this->dying, this->canShoot, deltaTime, this->friendly);
            break;
        case AnimationMode::Run:
            unitSprite.setTexture(*textures.at(1));
            animation.update(textures.at(1), AnimationMode::Run, this->unitType, this->shooting, this->dying, this->canShoot, deltaTime, this->friendly);
            break;
        case AnimationMode::Shoot:
            unitSprite.setTexture(*textures.at(2));
            animation.update(textures.at(2), AnimationMode::Shoot, this->unitType, this->shooting, this->dying, this->canShoot, deltaTime, this->friendly);
            break;
        case AnimationMode::Die:
            unitSprite.setTexture(*textures.at(3));
            animation.update(textures.at(3), AnimationMode::Die, this->unitType, this->shooting, this->dying, this->canShoot, deltaTime, this->friendly);
            break;
        default:
            throw "Invalid animation mode";
    }
    unitSprite.setTextureRect(animation.textRect);
    unitSprite.setOrigin(unitSprite.getLocalBounds().left + 0.5*unitSprite.getLocalBounds().width, unitSprite.getLocalBounds().top + unitSprite.getLocalBounds().height); //set origin at feet

    greenHealthBar.setScale((this->health/this->maxHealth)*0.02*1920.0f/greenHealthBar.getLocalBounds().width, 0.002*1920.0f/greenHealthBar.getLocalBounds().height);
    greenHealthBar.setPosition(unitSprite.getPosition().x-0.5f*redHealthBar.getGlobalBounds().width, unitSprite.getPosition().y-0.5f*redHealthBar.getGlobalBounds().height - 1.1*unitSprite.getGlobalBounds().height);
    redHealthBar.setScale(0.02*1920.0f/greenHealthBar.getLocalBounds().width, 0.002*1920.0f/greenHealthBar.getLocalBounds().height);
    redHealthBar.setPosition(unitSprite.getPosition().x-0.5f*redHealthBar.getGlobalBounds().width, unitSprite.getPosition().y-0.5f*redHealthBar.getGlobalBounds().height - 1.1*unitSprite.getGlobalBounds().height);
}
