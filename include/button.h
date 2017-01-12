#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class button{
    sf::FloatRect bounds;
    sf::Texture texture;
    sf::Sprite button;
    sf::Vector2i cursorPosition;
    sf::Vector2f buttonPosition;

    public:
        void load(const std::string& fileName, int width, int height, int xCoordinate, int yCoordinate);
        void draw(sf::RenderWindow& window);

        bool isMouseOverSprite(sf::RenderWindow& window);
};

#endif
