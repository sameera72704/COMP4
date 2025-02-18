// Copyright 2024 Sameera Sakinala

#include <iostream>
#include <SFML/Graphics.hpp>
#include "penta.hpp"

int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 4) {
        std::cerr << "Usage: " << argv[0]
                  << " <side_length> <depth> [rotation_degrees]" << std::endl;
        return 1;
    }

    double sideLength = std::stod(argv[1]);
    int depth = std::stoi(argv[2]);
    double rotation = -M_PI / 2;  // Default to pointing up

    if (argc == 4) {
        double rotationDegrees = std::stod(argv[3]);
        rotation = rotationDegrees * M_PI / 180.0;
    }

    double windowSize = sideLength * 2.5;
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize),
                            "Pentaflake");

    Pentaflake pentaflake(sideLength, depth, rotation);
    pentaflake.generate();

    sf::View view = window.getDefaultView();
    view.setCenter(0, 0);
    window.setView(view);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();
        pentaflake.animate(deltaTime);

        window.clear(sf::Color::Black);
        window.draw(pentaflake);
        window.display();
    }

    return 0;
}
