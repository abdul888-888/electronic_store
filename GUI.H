// GUI.h
#pragma once
#include <SFML/Graphics.hpp>
#include "strings.h"
#include "vectors.h"

class GUI {
protected:
    sf::RenderWindow window;
    sf::Font mainFont;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    void loadResources() {
        if (!mainFont.loadFromFile("arial.ttf")) {
            // Handle error
        }
        if (!backgroundTexture.loadFromFile("background.jpg")) {
            // Handle error
        }
        backgroundSprite.setTexture(backgroundTexture);
    }

public:
    GUI() : window(sf::VideoMode(1024, 768), "Online Electronic Store") {
        loadResources();
    }

    virtual void handleEvents() = 0;
    virtual void render() = 0;

    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                handleEvents();
            }
            render();
        }
    }
};