#ifndef DRAWABLE_H
#define DRAWABLE_H


class Drawable //Abstract Base Class for drawable objects
{
    public:
        virtual void draw(sf::RenderWindow& window) = 0;
        virtual ~Drawable(){}
};

#endif // DRAWABLE_H
