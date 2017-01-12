#include "button.h"

void button::load(const std::string& inactiveFileName, const std::string& activeFileName,
                  int width, int height, int xCoordinate, int yCoordinate){
    inactiveTexture.loadFromFile(inactiveFileName);
    if(!activeFileName.empty())
        activeTexture.loadFromFile(activeFileName);

    button.setTexture(inactiveTexture);
    button.setOrigin(width/2, height/2);
    button.setPosition(xCoordinate, yCoordinate);

    bounds.top = yCoordinate-height/2; bounds.left = xCoordinate-width/2;
    bounds.height = height; bounds.width = width;
}

void button::draw(sf::RenderWindow& window){
    window.draw(button);
}

void button::changeState(int newState){
    if(newState == active){
        //state = active;
        button.setTexture(activeTexture);
    }
    else{
        //state = inactive;
        button.setTexture(inactiveTexture);
    }
}

bool button::isMouseOverSprite(sf::RenderWindow& window){
    cursorPosition = sf::Mouse::getPosition(window);
    buttonPosition = button.getPosition();
    buttonPosition.x -= bounds.width/2; buttonPosition.y -= bounds.height/2;
	return  (cursorPosition.x > buttonPosition.x
          && cursorPosition.y > buttonPosition.y
          && cursorPosition.x - bounds.width < buttonPosition.x
          && cursorPosition.y - bounds.height < buttonPosition.y);
}
