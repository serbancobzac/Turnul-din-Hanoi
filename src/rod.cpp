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

disc rod::removeDisc(){
    disc discCopy;
    discCopy = discs[--discNumber];
    yCoordinate += 40;
    discs.pop_back();
    return discCopy;
}

void rod::draw(sf::RenderWindow& window){
    for(int i = 0; i < discNumber; ++i)
        discs[i].draw(window);
}

int rod::getTopDiscNumber(){
    if(discNumber > 0) return discs[discNumber-1].getDiscNumber();
    return 0;
}

void rod::changeState(int newState){
    if(newState == green){
        state = green;
        rodState.setTexture(greenStateTexture);
    }
    else    if(newState == red){
                state = red;
                rodState.setTexture(redStateTexture);
            }
            else state = neutral;
}
