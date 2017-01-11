#ifndef ROD_H
#define ROD_H

#include <SFML/Graphics.hpp>
#include "disc.h"
#include <vector>

class rod{
    std::vector <disc> discs;
    sf::Sprite rodState;
    sf::Texture greenStateTexture, redStateTexture;
    int xCoordinate, yCoordinate, state, discNumber;

    public:
        rod();
        void addDisc(disc newDisc);
        void removeDisc();
        void draw(sf::RenderWindow& window);
        void drawState(sf::RenderWindow& window);

        int getDiscNumber();
        int getState();

        void changeState(int newState);
};

#endif
