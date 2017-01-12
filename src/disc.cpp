#include "disc.h"

disc::disc(){
    discNumber = xCoordinate = yCoordinate = 0;
    disk.setOrigin(120, 60);
    disk.setPosition(0, 0);
}

void disc::draw(sf::RenderWindow& window){
    window.draw(disk);
}

void disc::setPosition(int xCoordinate, int yCoordinate){
    disk.setPosition(xCoordinate, yCoordinate);
}

void disc::setDiscTexture(sf::Texture& texture){
    disk.setTexture(texture);
}

void disc::setDiscNumber(int number){
    discNumber = number;
}
