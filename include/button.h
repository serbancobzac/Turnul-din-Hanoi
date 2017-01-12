#ifndef BUTTON_H
#define BUTTON_H
#define active 1
#define inactive 0

#include <SFML/Graphics.hpp>
#include <string>

class button{
    sf::FloatRect bounds;
    sf::Texture inactiveTexture, activeTexture;
    sf::Sprite button;
    sf::Vector2i cursorPosition;
    sf::Vector2f buttonPosition;

    public:
        void load(const std::string& inactiveFileName, const std::string& activeFileName,
                  int width, int height, int xCoordinate, int yCoordinate);
        void draw(sf::RenderWindow& window);
        void changeState(int newState);

        bool isMouseOverSprite(sf::RenderWindow& window);
};

#endif
