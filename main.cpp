#include "rod.h"
#include "disc.h"
#include "button.h"
#include <SFML/Audio.hpp>
#include <sstream>

sf::RenderWindow window(sf::VideoMode(800, 600), "Hanoi", sf::Style::Close);
sf::Music menuMusic, happyEnd;
sf::SoundBuffer takeDiscBuffer, putDiscBuffer;
sf::Sound takeDisc, putDisc;
sf::Event event;
sf::Font font1, font2;
sf::Text text, firstRodIndicator, secondRodIndicator, moves;
sf::Image screenshot;
sf::Clock timer;
sf::Texture blurredBackgroundTexture, inputBoxTexture, titleTexture, descriereTextTexture, instructiuniTextTexture,
            solutieTextTexture, codTextTexture, backgroundTexture, arrowTexture, congratsTexture, doneTexture;
sf::Sprite  blurredBackground, inputBox, title, descriereText, instructiuniText, solutieText, codText, background, arrow, congrats, done;
sf::Vector2f cursorPosition;

std::vector <rod> rods;
std::vector <sf::Texture> discs, activeDiscs;
std::string s;

button  invataButton, joacaButton, simuleazaButton, numarDiscuri, exitButton,
        instructiuniButton, descriereButton, solutieButton, aiciButton, fastForwardButton;

int numberOfDiscs, movesCounter, ff, inSimulation;

void loadResources();
void uploadDiscs(std::string name, std::vector <sf::Texture> &discs);
void menu(sf::RenderWindow& window);
void updateButtonState(button Button);
void showInvata();
int displayBox();

bool launchGame(int numberOfDiscs);
int selectRod();
void takeDiscFromRod(int rodNumber);
void moveDisc(int x, int y);
void removeRemainingDiscs();
void succesGameScreen();

void launchSimulation(int numberOfDiscs);
void generateSimulationMoves(int numberOfDiscs, int initialRod, int finalRod);
void updateMove(sf::Text &rodIndicator, int rod);
void succesSimulationScreen();
void showUntilKeyPressed();

std::string numberToString(int number);
void displayState();

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
                            if(numberOfDiscs)
                                if(launchGame(numberOfDiscs))
                                    succesGameScreen();
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

    //joaca
    takeDiscBuffer.loadFromFile("./files/audio/takeDisc.wav");
    takeDisc.setBuffer(takeDiscBuffer);

    putDiscBuffer.loadFromFile("./files/audio/putDisc.wav");
    putDisc.setBuffer(putDiscBuffer);

    firstRodIndicator.setFont(font2);
    firstRodIndicator.setCharacterSize(70);
    firstRodIndicator.setPosition(325, -15);
    firstRodIndicator.setColor(sf::Color(246, 156, 14));

    arrowTexture.loadFromFile("./files/images/arrow.png");
    arrow.setTexture(arrowTexture);
    arrow.setOrigin(50, 50);
    arrow.setPosition(400, 35);

    secondRodIndicator.setFont(font2);
    secondRodIndicator.setCharacterSize(70);
    secondRodIndicator.setPosition(450, -15);
    secondRodIndicator.setColor(sf::Color(246, 156, 14));

    uploadDiscs("./files/images/disc.png", discs);
    uploadDiscs("./files/images/discActive.png", activeDiscs);

    rod newRod1, newRod2, newRod3;
    rods.push_back(newRod1);
    rods.push_back(newRod2);
    rods.push_back(newRod3);

    backgroundTexture.loadFromFile("./files/images/background.png");
    background.setTexture(backgroundTexture);

    congratsTexture.loadFromFile("./files/images/congrats.png");
    congrats.setTexture(congratsTexture);
    happyEnd.openFromFile("./files/audio/happyEnd.wav");
    happyEnd.setVolume(50);
    happyEnd.setLoop(true);

    moves.setFont(font2);
    moves.setCharacterSize(56);
    moves.setOrigin(28, 28);
    moves.setColor(sf::Color(58, 190, 0));

    // simulare
    fastForwardButton.load("./files/images/fastForward.png", "./files/images/fastForwardActive.png", 50, 50, 765, 35);
    doneTexture.loadFromFile("./files/images/done.png");
    done.setTexture(doneTexture);
}

void uploadDiscs(std::string name, std::vector <sf::Texture> &discs){
    sf::Texture newTexture;
    for(int i=1; i<=8; ++i){
        name.insert(name.begin()+19, (char)i+48);
        newTexture.loadFromFile(name);
        discs.push_back(newTexture);
        name.erase(name.begin()+19);
    }
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
    bool selectedRod = 0, cod = 0;
    int indicator = 0;
    descriereButton.changeState(active);

    while(!selectedRod){
        while(window.pollEvent(event))
            switch (event.type){
                case sf::Event::Closed:{
                    window.close(); exit(0);
                }
                case sf::Event::MouseButtonPressed:{
                    if(event.mouseButton.button == sf::Mouse::Left){
                        if(exitButton.isMouseOverSprite(window)){ selectedRod = 1; continue;}
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

bool launchGame(int numberOfDiscs){
    disc newDisc;
    for(int i = numberOfDiscs-1; i >= 0; --i){
        newDisc.setDiscTexture(discs[i]);
        newDisc.setDiscNumber(i+1);
        rods[0].addDisc(newDisc);
    }

    int x, y;
    bool finished = 0;
    movesCounter = 0;

    while(rods[2].getDiscNumber() != numberOfDiscs){
        firstRodIndicator.setString("");
        secondRodIndicator.setString("");

        x = selectRod();
        if(x == 3) break;

        y = selectRod();
        if(y == 3) break;

        moveDisc(x, y);
        if(x != y) ++movesCounter;

        displayState();

        timer.restart();
        while(timer.getElapsedTime().asSeconds() <= 0.5);
    }

    if(rods[2].getDiscNumber() == numberOfDiscs) finished = 1;

    removeRemainingDiscs();

    return finished;
}

int selectRod(){
    int selectedRod = 0;
    while(window.isOpen()){
        while(window.pollEvent(event))
            switch(event.type){
                case sf::Event::Closed:{
                    window.close(); exit(0);
                }
                case sf::Event::TextEntered:{
                    if(49 <= event.text.unicode && event.text.unicode <= 51){
                        if((firstRodIndicator.getString()).isEmpty() &&
                            rods[(event.text.unicode - '0') - 1].getDiscNumber() != 0){
                            takeDisc.play();
                            takeDiscFromRod((event.text.unicode - '0') - 1);
                        }
                        else if(rods[(event.text.unicode - '0') - 1].getState() == green){
                            putDisc.play();
                            secondRodIndicator.setString(numberToString(event.text.unicode - '0'));
                        }
                        selectedRod = event.text.unicode - '0';
                    }
                }
                case sf::Event::MouseButtonPressed:{
                    if(event.mouseButton.button == sf::Mouse::Left &&
                       exitButton.isMouseOverSprite(window)){
                        selectedRod = 4;
                    }
                }
                default: break;
            }

        displayState();

        if(!(secondRodIndicator.getString()).isEmpty()){
            rods[0].changeState(neutral);
            rods[1].changeState(neutral);
            rods[2].changeState(neutral);
        }

        if(1 <= selectedRod && selectedRod <= 4) return selectedRod - 1;
    }
    return 0;
}

void takeDiscFromRod(int rodNumber){
    firstRodIndicator.setString(numberToString(rodNumber+1));

    rods[rodNumber].changeTopState(activeDiscs[rods[rodNumber].getTopDiscNumber()-1]);
    rods[rodNumber].changeState(green);

    for(int i = 0; i <= 2; ++i)
        if(i != rodNumber){
            if(rods[i].getDiscNumber() == 0 ||
               rods[i].getTopDiscNumber() > rods[rodNumber].getTopDiscNumber())
                rods[i].changeState(green);
            else rods[i].changeState(red);
        }
}

void moveDisc(int x, int y){
    disc newDisc;
    rods[x].changeTopState(discs[rods[x].getTopDiscNumber()-1]);
    newDisc = rods[x].removeDisc();
    rods[y].addDisc(newDisc);
}

void removeRemainingDiscs(){
    for(int i = 0; i <= 2; ++i)
        while(rods[i].getDiscNumber())
            rods[i].removeDisc();
}

void succesGameScreen(){
    menuMusic.stop();
    happyEnd.play();

    s = numberToString(movesCounter);
    moves.setString(s);
    moves.setPosition(492, 350);

    window.clear();
    window.draw(blurredBackground);
    window.draw(congrats);
    window.draw(moves);

    showUntilKeyPressed();

    happyEnd.stop();
    menuMusic.play();
}

void launchSimulation(int numberOfDiscs){
    disc newDisc;
    for(int i = numberOfDiscs-1; i >= 0; --i){
        newDisc.setDiscTexture(discs[i]);
        newDisc.setDiscNumber(i+1);
        rods[0].addDisc(newDisc);
    }

    inSimulation = 1; ff = 1; movesCounter = 0;
    generateSimulationMoves(numberOfDiscs, 1, 3);
    inSimulation = 0;

    removeRemainingDiscs();
}

void generateSimulationMoves(int numberOfDiscs, int initialRod, int finalRod){
    while(window.pollEvent(event))
        switch (event.type){
            case sf::Event::Closed:{
                window.close(); exit(0);
            }
            case sf::Event::MouseButtonPressed:{
                if(event.mouseButton.button == sf::Mouse::Left &&
                   fastForwardButton.isMouseOverSprite(window)) ff = 0;
            }
            default: break;
        }
    if(numberOfDiscs > 0){
        generateSimulationMoves(numberOfDiscs-1, initialRod, 6-initialRod-finalRod);

        firstRodIndicator.setString("");
        secondRodIndicator.setString("");

        updateMove(firstRodIndicator, initialRod);
        updateMove(secondRodIndicator, finalRod);


        moveDisc(initialRod-1, finalRod-1);
        ++movesCounter;


        rods[initialRod-1].changeTopState(discs[rods[initialRod-1].getTopDiscNumber()-1]);
        rods[finalRod-1].changeState(0);

        displayState();

        timer.restart();
        while(ff && timer.getElapsedTime().asSeconds() <= 0.5);

        generateSimulationMoves(numberOfDiscs-1, 6-initialRod-finalRod, finalRod);
    }
}

void updateMove(sf::Text &rodIndicator, int rod){
    s = numberToString(rod);
    rodIndicator.setString(s);

    if(rodIndicator.getString() == firstRodIndicator.getString()) rods[rod-1].changeTopState(activeDiscs[rods[rod-1].getTopDiscNumber()-1]);
    else rods[rod-1].changeState(1);

    displayState();

    timer.restart();
    while(ff && timer.getElapsedTime().asSeconds() <= 0.5);
}

void succesSimulationScreen(){
    s = numberToString(movesCounter);
    moves.setString(s);
    moves.setPosition(635, 382);

    text.setFont(font2);
    text.setCharacterSize(56);
    text.setOrigin(28, 28);
    text.setPosition(350, 382);
    text.setColor(sf::Color(58, 190, 0));

    window.clear();
    window.draw(blurredBackground);
    window.draw(done);
    window.draw(text);
    window.draw(moves);

    showUntilKeyPressed();

    text.setFont(font1);
    text.setOrigin(0, 0);
    text.setCharacterSize(96);
    text.setPosition(560, 430);
    text.setColor(sf::Color(246, 156, 14));
}

void showUntilKeyPressed(){
    bool pressed = 0;

    while(!pressed){
        while(window.pollEvent(event))
            switch (event.type){
                case sf::Event::Closed:{
                    window.close(); exit(0);
                }
                case sf::Event::KeyPressed:
                    pressed = 1;
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Left &&
                       exitButton.isMouseOverSprite(window)){
                        pressed = 1;
                    }
                default: break;
            }

        updateButtonState(exitButton);
        window.display();
    }
}

std::string numberToString(int number){
    std::stringstream ss;
    ss << number;
    return ss.str();
}

void displayState(){
    window.clear();
    window.draw(background);
    window.draw(firstRodIndicator);
    window.draw(arrow);
    window.draw(secondRodIndicator);

    if(inSimulation) updateButtonState(fastForwardButton);
    else updateButtonState(exitButton);

    for(int i = 0; i <= 2; ++i){
        if(rods[i].getState()) rods[i].drawState(window);
        rods[i].draw(window);
    }

    window.display();
}
