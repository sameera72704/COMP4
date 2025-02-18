// copyright 2024 Sameera Sakinala
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Universe.hpp"

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;
const float PI_VALUE = 3.14159265358979323846f;

sf::Vector2f transformPointByRotation(sf::Vector2f point,
 float angleInRadians) {
    float sineValue = std::sin(angleInRadians);
    float cosineValue = std::cos(angleInRadians);
    return sf::Vector2f(point.x * cosineValue - point.y * sineValue,
     point.x * sineValue + point.y * cosineValue);
}

int main() {
    NB::Universe galaxyModel;

    std::ifstream dataStream("planets.txt");
    if (!dataStream) {
        std::cerr << "Error: Unable to open planets.txt" << std::endl;
        return 1;
    }
    dataStream >> galaxyModel;
    dataStream.close();

    std::cout << "Galaxy model loaded. Details:" << std::endl;
    galaxyModel.logDetails();

    double scalingFactor = (SCREEN_WIDTH / 2.0) / galaxyModel.getRadius();
    std::cout << "Calculated scaling factor: " << scalingFactor << std::endl;

    sf::RenderWindow simulationWindow(sf::VideoMode
    (SCREEN_WIDTH, SCREEN_HEIGHT), "N-Body System");

    sf::Texture galaxyTexture;
    if (!galaxyTexture.loadFromFile("starfield.jpg")) {
        std::cerr << "Error: Failed to load background texture" << std::endl;
        return 1;
    }
    sf::Sprite galaxyBackground(galaxyTexture);
galaxyBackground.setScale
(static_cast<float>(SCREEN_WIDTH) / galaxyTexture.getSize().x,
static_cast<float>(SCREEN_HEIGHT) / galaxyTexture.getSize().y);

    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("2001.wav")) {
        std::cerr << "Warning: Unable to play background music" << std::endl;
    } else {
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(50);
        backgroundMusic.play();
    }

    galaxyModel.computeScreenPositions(scalingFactor,
     SCREEN_WIDTH, SCREEN_HEIGHT);

    std::cout << "Updated celestial body positions:" << std::endl;
    galaxyModel.logDetails();

    sf::Clock timeTracker;
    while (simulationWindow.isOpen()) {
        sf::Event simEvent;
        while (simulationWindow.pollEvent(simEvent)) {
            if (simEvent.type == sf::Event::Closed)
                simulationWindow.close();
        }

        float totalElapsedSeconds = timeTracker.getElapsedTime().asSeconds();
        float rotationalSpeed = 0.000001f;

        simulationWindow.clear();
        simulationWindow.draw(galaxyBackground);

        for (size_t i = 0; i < galaxyModel.size(); ++i) {
            NB::CelestialBody& celestial = galaxyModel[i];
            sf::Vector2f initialPos = celestial.getPosition();
            if (i > 0) {
                sf::Vector2f newPosition = transformPointByRotation(initialPos,
                 totalElapsedSeconds * rotationalSpeed);

                celestial.setPosition(newPosition.x, newPosition.y);
                celestial.setScreenPosition(
                    (newPosition.x * scalingFactor) + (SCREEN_WIDTH / 2.0),
                    (SCREEN_HEIGHT / 2.0) - (newPosition.y * scalingFactor));
            }

            simulationWindow.draw(celestial);
        }

        simulationWindow.display();

        sf::sleep(sf::milliseconds(10));
    }

    std::cout << "Simulation completed. Press Enter to exit...";
    std::cin.get();

    return 0;
}
