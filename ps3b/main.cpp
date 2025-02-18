// copyright 2024 Sameera Sakinala

#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "Universe.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

void playAudio(sf::Music& music) {
    music.play();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./NBody T dt < universe_file" << std::endl;
        return 1;
    }

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "N-Body Simulation");
    window.setFramerateLimit(60);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("starfield.jpg")) {
        std::cerr << "Failed to load background image" << std::endl;
        return 1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(SCREEN_WIDTH) / backgroundTexture.getSize().x,
        static_cast<float>(SCREEN_HEIGHT) / backgroundTexture.getSize().y);

    sf::Music backgroundMusic;
    if (backgroundMusic.openFromFile("2001.wav")) {
        backgroundMusic.setLoop(true);
        std::thread audioThread(playAudio, std::ref(backgroundMusic));
        audioThread.detach();
    } else {
        std::cerr << "Failed to load background music" << std::endl;
    }

    double T = std::stod(argv[1]);
    double dt = std::stod(argv[2]);

    NB::Universe universe;
    std::cin >> universe;

    std::vector<sf::Texture> textures(universe.size());
    std::vector<sf::Sprite> sprites(universe.size());

    for (size_t i = 0; i < universe.size(); ++i) {
        textures[i].loadFromFile(universe[i].getFilename());
        sprites[i].setTexture(textures[i]);
        sprites[i].setOrigin(textures[i].getSize().x / 2.0f, textures[i].getSize().y / 2.0f);
    }

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return 1;
    }

    sf::Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(20);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(10, 10);

    auto start_time = std::chrono::high_resolution_clock::now();
    double t = 0.0;
    sf::Clock clock;

    while (window.isOpen() && t < T) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        universe.step(dt);
        t += dt;

        window.clear();
        window.draw(backgroundSprite);

        for (size_t i = 0; i < universe.size(); ++i) {
            double scaleFactor = SCREEN_WIDTH / (2 * universe.getRadius());
            sf::Vector2<double> pos = universe[i].getPosition();
            sprites[i].setPosition(
                (pos.x * scaleFactor) + SCREEN_WIDTH / 2,
                (pos.y * scaleFactor) + SCREEN_HEIGHT / 2);
            window.draw(sprites[i]);
        }

        auto current_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_time = current_time - start_time;
        timeText.setString("Elapsed time: " + std::to_string(elapsed_time.count()) + " s");
        window.draw(timeText);

        window.display();}

    std::cout << universe;

    std::ofstream newUniverseFile("new_universe.txt");
    newUniverseFile << universe;
    newUniverseFile.close();

    return 0;
}
