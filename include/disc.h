#ifndef DISC_H
#define DISC_H

#include <SFML/Graphics.hpp>

class disc{
    sf::Sprite disk;
    int xCoordinate, yCoordinate, discNumber;

    public:
        disc();
        void draw(sf::RenderWindow& window);

        int getDiscNumber();

        void setPosition(int xCoordinate, int yCoordinate);
        void setDiscTexture(sf::Texture& texture);
        void setDiscNumber(int number);
};

#endif
