// copyright 2024 Sameera Sakinala

#include <iostream>
#include <SFML/Graphics.hpp>
#include "FibLFSR.hpp"
#include "PhotoMagic.hpp"

int main(int argc, char* argv[]) {
if (argc != 4) {
std::cerr << "Usage: " << argv[0]
<< " <input-file> <output-file> <LFSR-seed>" << std::endl;
return 1;
}

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    std::string Seed = argv[3];

    sf::Image image;
    if (!image.loadFromFile(inputFile)) {
        std::cerr << "Error loading image: " << inputFile << std::endl;
        return 1;
    }

    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);
    sf::RenderWindow window(sf::VideoMode(texture.getSize().x,
    texture.getSize().y), "Original Image");

    PhotoMagic::FibLFSR lfsr(Seed);

    PhotoMagic::transform(image, &lfsr);

    if (!image.saveToFile(outputFile)) {
        std::cerr << "Error saving image: " << outputFile << std::endl;
        return 1;
    }

    sf::Texture transformedTexture;
    transformedTexture.loadFromImage(image);
    sf::Sprite transformedSprite(transformedTexture);
    sf::RenderWindow transformedWindow
    (sf::VideoMode(transformedTexture.getSize().x,
    transformedTexture.getSize().y), "Transformed Image");

    while (window.isOpen() && transformedWindow.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        while (transformedWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                transformedWindow.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();

        transformedWindow.clear();
        transformedWindow.draw(transformedSprite);
        transformedWindow.display();
    }
return 0;
}
