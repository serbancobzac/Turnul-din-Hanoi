#include "rod.h"
#include "disc.h"
#include "button.h"
#include <SFML/Audio.hpp>

sf::RenderWindow window(sf::VideoMode(800, 600), "Hanoi", sf::Style::Close);
sf::Music menuMusic, happyEnd;
sf::Event event;
sf::Font font1, font2;
sf::Text text;
sf::Image screenshot;
sf::Clock timer;
sf::Texture blurredBackgroundTexture, inputBoxTexture, titleTexture;
sf::Sprite  blurredBackground, inputBox, title;
sf::Vector2f cursorPosition;
button  invataButton, invataButtonActive, joacaButton, joacaButtonActive, simuleazaButton, simuleazaButtonActive,
        numarDiscuri, exitButton, exitButtonActive, instructiuniButton, instructiuniButtonActive;

int numberOfDiscs;

void loadResources();
void menu(sf::RenderWindow& window);
void showInvata();
int displayBox();
void launchGame(int numberOfDiscs);
void succesGameScreen();
void launchSimulation(int numberOfDiscs);
void succesSimulationScreen();

int main(){
    loadResources();
    menuMusic.play();
    while (window.isOpen()){
        while (window.pollEvent(event))
            switch (event.type){
                case sf::Event::Closed:
                    window.close();
                case sf::Event::MouseButtonPressed:{
                    if(event.mouseButton.button == sf::Mouse::Left){
                        if(exitButtonActive.isMouseOverSprite(window))
                            window.close();
                        if(invataButtonActive.isMouseOverSprite(window))
                            showInvata();
                        if(joacaButtonActive.isMouseOverSprite(window)){
                            numberOfDiscs=displayBox();
                            if(numberOfDiscs){
                                launchGame(numberOfDiscs);
                                succesGameScreen();
                            }
                        }
                        if(simuleazaButtonActive.isMouseOverSprite(window)){
                            numberOfDiscs=displayBox();
                            if(numberOfDiscs){
                                launchSimulation(numberOfDiscs);
                                succesSimulationScreen();
                            }
                        }
                    }
                }
                default: break;
            }
        menu(window);
    }
    return 0;
}

void loadResources(){
    menuMusic.openFromFile("./files/audio/menu.wav");
    menuMusic.setVolume(50);
    menuMusic.setLoop(true);

    blurredBackgroundTexture.loadFromFile("./files/images/blurredBackground.png");
    blurredBackground.setTexture(blurredBackgroundTexture);

    titleTexture.loadFromFile("./files/images/title.png");
    title.setTexture(titleTexture);
    title.setOrigin(150, 100);
    title.setPosition(400, 150);

    invataButton.load("./files/images/invataButton.png", 250, 100, 250, 300);
    invataButtonActive.load("./files/images/invataButtonActive.png", 250, 100, 250, 300);

    joacaButton.load("./files/images/joacaButton.png", 200, 100, 550, 300);
    joacaButtonActive.load("./files/images/joacaButtonActive.png", 200, 100, 550, 300);

    simuleazaButton.load("./files/images/simuleazaButton.png", 300, 100, 400, 400);
    simuleazaButtonActive.load("./files/images/simuleazaButtonActive.png", 300, 100, 400, 400);

    numarDiscuri.load("./files/images/numarDiscuri.png", 500, 100, 350, 500);

    exitButton.load("./files/images/exitButton.png", 50, 50, 765, 35);
    exitButtonActive.load("./files/images/exitButtonActive.png", 50, 50, 765, 35);

    font1.loadFromFile("./files/fonts/againts.otf");
    font2.loadFromFile("./files/fonts/amatic.ttf");

    text.setFont(font1);
    text.setCharacterSize(96);
    text.setPosition(560, 430);
    text.setColor(sf::Color(246, 156, 14));
}

void menu(sf::RenderWindow& window){
    window.clear();
    window.draw(blurredBackground);
    window.draw(title);

    if(invataButton.isMouseOverSprite(window)) invataButtonActive.draw(window);
    else invataButton.draw(window);

    if(joacaButton.isMouseOverSprite(window)) joacaButtonActive.draw(window);
    else joacaButton.draw(window);

    if(simuleazaButton.isMouseOverSprite(window)) simuleazaButtonActive.draw(window);
    else simuleazaButton.draw(window);

    if(exitButton.isMouseOverSprite(window)) exitButtonActive.draw(window);
    else exitButton.draw(window);

    window.display();
}

void showInvata(){}

int displayBox(){
    bool done = 0;

    screenshot = window.capture();
    inputBoxTexture.loadFromImage(screenshot);
    inputBox.setTexture(inputBoxTexture);
    text.setString(" ");

    while (!done && window.isOpen()){
        while (window.pollEvent(event))
            switch (event.type){
                case sf::Event::Closed:
                    window.close();

                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Left){
                        if(numarDiscuri.isMouseOverSprite(window))
                            done=1;
                        if(exitButtonActive.isMouseOverSprite(window)){
                            window.close(); exit(0);
                        }
                    }

                case sf::Event::TextEntered:{
                    if (event.text.unicode>=51 && event.text.unicode<=56) //3-8
                        text.setString((char)event.text.unicode);
                    if (event.text.unicode==13){ //enter
                        std::string nText=text.getString();
                        int val=std::atoi(nText.c_str());
                        return val;
                    }
                    if (event.text.unicode==8) //backspace
                        text.setString(" ");
                }
                default: break;
            }

        window.clear();
        window.draw(inputBox);
        numarDiscuri.draw(window);

        if(exitButton.isMouseOverSprite(window)) exitButtonActive.draw(window);
        else exitButton.draw(window);

        window.draw(text);
        window.display();
    }
    return 0;
}

void launchGame(int numberOfDiscs){}
void succesGameScreen(){}
void launchSimulation(int numberOfDiscs){}
void succesSimulationScreen(){}
