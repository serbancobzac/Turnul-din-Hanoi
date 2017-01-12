#include "rod.h"

int rod::difference = 150;

rod::rod(){
    discNumber = state = 0;
    xCoordinate += rod::difference;
    rod::difference += 250;
    greenStateTexture.loadFromFile("./files/images/greenRod.png");
    redStateTexture.loadFromFile("./files/images/redRod.png");
    rodState.setPosition(xCoordinate-7, 129);
}

void rod::addDisc(disc newDisc){
    newDisc.setPosition(xCoordinate+5, yCoordinate-3);
    yCoordinate -= 40;
    discs.push_back(newDisc);
    ++discNumber;
}

void rod::removeDisc(){
    yCoordinate += 40;
    discs.pop_back();
    --discNumber;
}

void rod::draw(sf::RenderWindow& window){
    for(int i = 0; i < discNumber; ++i)
        discs[i].draw(window);
}

void rod::drawState(sf::RenderWindow& window){}

void rod::changeState(int newState){}
