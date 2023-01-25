#ifndef MONEY_H
#define MONEY_H

#include <SFML/Graphics.hpp>
#include "Drawable.h"
#include <string>

using std::to_string;

class Money : public Drawable
{
    public:
        Money(const float gameWidth, const float gameHeight);
        void update(const float deltaTime);
        void subtract(const int amount) { money -= amount; moneyText.setString(to_string(money)); }
        void add(const int amount) { money += amount; moneyText.setString(to_string(money)); }
        virtual void draw(sf::RenderWindow& window, const GameState gameState) override;

    private:
        sf::Font font;
        sf::Text moneyText;
        int money;
        float totalTime;
};

#endif // MONEY_H
