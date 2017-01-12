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
sf::Texture blurredBackgroundTexture, inputBoxTexture, titleTexture, descriereTextTexture, instructiuniTextTexture,
            solutieTextTexture, codTextTexture;
sf::Sprite  blurredBackground, inputBox, title, descriereText, instructiuniText, solutieText, codText;
sf::Vector2f cursorPosition;

button  invataButton, joacaButton, simuleazaButton, numarDiscuri, exitButton,
        instructiuniButton, descriereButton, solutieButton, aiciButton;

int numberOfDiscs;

void loadResources();
void menu(sf::RenderWindow& window);
void updateButtonState(button Button);
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
                        if(exitButton.isMouseOverSprite(window))
                            window.close();
                        if(invataButton.isMouseOverSprite(window))
                            showInvata();
                        if(joacaButton.isMouseOverSprite(window)){
                            numberOfDiscs = displayBox();
                            if(numberOfDiscs){
                                //launchGame(numberOfDiscs);
                                succesGameScreen();
                            }
                        }
                        if(simuleazaButton.isMouseOverSprite(window)){
                            numberOfDiscs = displayBox();
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
    // menu
    menuMusic.openFromFile("./files/audio/menu.wav");
    menuMusic.setVolume(50);
    menuMusic.setLoop(true);

    blurredBackgroundTexture.loadFromFile("./files/images/blurredBackground.png");
    blurredBackground.setTexture(blurredBackgroundTexture);

    titleTexture.loadFromFile("./files/images/title.png");
    title.setTexture(titleTexture);
    title.setOrigin(150, 100);
    title.setPosition(400, 150);

    invataButton.load("./files/images/invataButton.png", "./files/images/invataButtonActive.png", 250, 100, 250, 300);

    joacaButton.load("./files/images/joacaButton.png", "./files/images/joacaButtonActive.png", 200, 100, 550, 300);

    simuleazaButton.load("./files/images/simuleazaButton.png", "./files/images/simuleazaButtonActive.png", 300, 100, 400, 400);

    numarDiscuri.load("./files/images/numarDiscuri.png", "", 500, 100, 350, 500);

    exitButton.load("./files/images/exitButton.png", "./files/images/exitButtonActive.png", 50, 50, 765, 35);

    font1.loadFromFile("./files/fonts/againts.otf");
    font2.loadFromFile("./files/fonts/amatic.ttf");

    text.setFont(font1);
    text.setCharacterSize(96);
    text.setPosition(560, 430);
    text.setColor(sf::Color(246, 156, 14));

    // invata
    descriereButton.load("./files/images/descriereButton.png", "./files/images/descriereButtonActive.png", 250, 100, 160, 60);

    instructiuniButton.load("./files/images/instructiuniButton.png", "./files/images/instructiuniButtonActive.png", 250, 100, 410, 60);

    solutieButton.load("./files/images/solutieButton.png", "./files/images/solutieButtonActive.png", 200, 100, 635, 60);

    descriereTextTexture.loadFromFile("./files/images/descriereText.png");
    descriereText.setTexture(descriereTextTexture);

    instructiuniTextTexture.loadFromFile("./files/images/instructiuniText.png");
    instructiuniText.setTexture(instructiuniTextTexture);

    solutieTextTexture.loadFromFile("./files/images/solutieText.png");
    solutieText.setTexture(solutieTextTexture);

    aiciButton.load("./files/images/aici.png", "", 65, 30, 345, 389);

    codTextTexture.loadFromFile("./files/images/codText.png");
    codText.setTexture(codTextTexture);
}

void updateButtonState(button Button){
    if(Button.isMouseOverSprite(window)) Button.changeState(active);
    else Button.changeState(inactive);

    Button.draw(window);
}

void menu(sf::RenderWindow& window){
    window.clear();
    window.draw(blurredBackground);
    window.draw(title);

    updateButtonState(invataButton);
    updateButtonState(joacaButton);
    updateButtonState(simuleazaButton);
    updateButtonState(exitButton);

    window.display();
}

void showInvata(){
    bool pressed = 0, cod = 0;
    int indicator = 0;
    descriereButton.changeState(active);

    while(!pressed){
        while(window.pollEvent(event))
            switch (event.type){
                case sf::Event::Closed:{
                    window.close(); exit(0);
                }
                case sf::Event::MouseButtonPressed:{
                    if(event.mouseButton.button == sf::Mouse::Left){
                        if(exitButton.isMouseOverSprite(window)){ pressed = 1; continue;}
                        if(descriereButton.isMouseOverSprite(window)){
                            indicator = 0; descriereButton.changeState(active); continue;}
                        if(instructiuniButton.isMouseOverSprite(window)){
                            indicator = 1; instructiuniButton.changeState(active); continue;}
                        if(solutieButton.isMouseOverSprite(window)){
                            indicator = 2; cod = 0; solutieButton.changeState(active); continue;}
                        if(aiciButton.isMouseOverSprite(window) && indicator==2){ cod = 1; continue;}
                    }
                }
                default: break;
            }

        window.clear();
        window.draw(blurredBackground);

        if(indicator == 0){
            window.draw(descriereText);
            descriereButton.draw(window);

            updateButtonState(instructiuniButton);
            updateButtonState(solutieButton);
        }
        else    if(indicator == 1){
                    window.draw(instructiuniText);
                    instructiuniButton.draw(window);

                    updateButtonState(descriereButton);
                    updateButtonState(solutieButton);
                }
                else{
                    if(!cod) window.draw(solutieText);
                    else window.draw(codText);
                    solutieButton.draw(window);

                    updateButtonState(descriereButton);
                    updateButtonState(instructiuniButton);

                    if(aiciButton.isMouseOverSprite(window) && !cod) aiciButton.draw(window);
                }
        updateButtonState(exitButton);

        window.display();
    }

    sf::Clock timer;
    while(timer.getElapsedTime().asSeconds() <= 0.25);
}

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
                            done = 1;
                        if(exitButton.isMouseOverSprite(window)){
                            window.close(); exit(0);
                        }
                    }

                case sf::Event::TextEntered:{
                    if (event.text.unicode>=51 && event.text.unicode<=56) //3-8
                        text.setString((char)event.text.unicode);
                    if (event.text.unicode==13){ //enter
                        std::string newText = text.getString();
                        int val = std::atoi(newText.c_str());
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

        updateButtonState(exitButton);

        window.draw(text);
        window.display();
    }
    return 0;
}

void launchGame(int numberOfDiscs){

}
void succesGameScreen(){}
void launchSimulation(int numberOfDiscs){}
void succesSimulationScreen(){}
