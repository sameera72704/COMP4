// Copyright 2024 Sameera Sakinala
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Sokoban.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <level_file>" << std::endl;
        return 1;
    }

    std::ifstream levelFile(argv[1]);
    if (!levelFile) {
        std::cerr << "Error: Could not open level file." << std::endl;
        return 1;
    }

    SB::Sokoban game;
    levelFile >> game;

    sf::RenderWindow window(sf::VideoMode(
                                game.width() * SB::Sokoban::TILE_SIZE,
                                game.height() * SB::Sokoban::TILE_SIZE),
                                "Sokoban");

    sf::Clock clock;  // Clock to track elapsed time

    // Text to display elapsed time
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error: Could not load font." << std::endl;
        return 1;
    }

    sf::Text timerText;
    timerText.setFont(font);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(10, 10);  // Display timer at the top-left corner

    sf::Text winText;
    winText.setFont(font);
    winText.setString("You Won!");
    winText.setCharacterSize(48);
    winText.setFillColor(sf::Color::Green);
    winText.setPosition(
        (window.getSize().x - winText.getLocalBounds().width) / 2,
        (window.getSize().y - winText.getLocalBounds().height) / 2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::W:
                    case sf::Keyboard::Up:
                        game.movePlayer(SB::Direction::Up);
                        break;
                    case sf::Keyboard::S:
                    case sf::Keyboard::Down:
                        game.movePlayer(SB::Direction::Down);
                        break;
                    case sf::Keyboard::A:
                    case sf::Keyboard::Left:
                        game.movePlayer(SB::Direction::Left);
                        break;
                    case sf::Keyboard::D:
                    case sf::Keyboard::Right:
                        game.movePlayer(SB::Direction::Right);
                        break;
                    case sf::Keyboard::R:
                        game.reset();
                        clock.restart();  // Reset the timer
                        break;
                    case sf::Keyboard::Z:
                        if (game.canUndo()) game.undo();
                        break;
                    case sf::Keyboard::Y:
                        if (game.canRedo()) game.redo();
                        break;
                    default:
                        break;
                }
            }
        }

        // Format elapsed time in MM:SS
        sf::Time elapsed = clock.getElapsedTime();
        int minutes = static_cast<int>(elapsed.asSeconds()) / 60;
        int seconds = static_cast<int>(elapsed.asSeconds()) % 60;
        std::ostringstream timeStream;
        timeStream << std::setw(2) << std::setfill('0') << minutes << ":"
                   << std::setw(2) << std::setfill('0') << seconds;
        timerText.setString(timeStream.str());

        window.clear();
        window.draw(game);
        window.draw(timerText);  // Draw the elapsed time

        if (game.isWon()) {
            window.draw(winText);
        }

        window.display();
    }

    return 0;
}
