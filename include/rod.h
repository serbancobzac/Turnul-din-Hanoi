#ifndef ROD_H
#define ROD_H

#include <SFML/Graphics.hpp>
#include "disc.h"
#include <vector>
#define neutral 0
#define green 1
#define red 2

class rod{
    std::vector <disc> discs;
    sf::Sprite rodState;
    sf::Texture greenStateTexture, redStateTexture;
    int xCoordinate = 0, yCoordinate = 500, state, discNumber;
    static int difference;

    public:
        rod();
        void addDisc(disc newDisc);
        disc removeDisc();
        void draw(sf::RenderWindow& window);
        void drawState(sf::RenderWindow& window){ window.draw(rodState);}

        int getDiscNumber(){ return discNumber;}
        int getState(){ return state;}
        int getTopDiscNumber();

        void changeState(int newState);
        void changeTopState(sf::Texture& newStateTexture){ discs[discNumber-1].setDiscTexture(newStateTexture);}
};

#endif
