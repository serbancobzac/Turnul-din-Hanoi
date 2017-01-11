#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class button{
    sf::Texture texture;
    sf::Sprite sprite;

    public:
        void load(const std::string& fileName, int xCoordinate, int yCoordinate, int width, int height);
        void draw(sf::RenderWindow& window);
};

#endif
