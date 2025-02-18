// Copyright [2024] <sameera>
#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "GooPY");

    // Simple shape
    sf::RectangleShape square(sf::Vector2f(50.0f, 50.0f));  // 50x50 square
    square.setFillColor(sf::Color::Red);  // Set the color to red
    square.setPosition(30.0f, 30.0f);

    // Background
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("background.png")) {
        std::cerr << "Failed to load background texture!" << std::endl;
        return -1;
    }

    sf::Sprite bg;
    bg.setTexture(bgTexture);
    sf::Vector2u textureSize = bgTexture.getSize();  // Get size of the texture
    sf::Vector2u windowSize = window.getSize();      // Get size of the window
    bg.setScale(static_cast<float>(windowSize.x) / textureSize.x,
                static_cast<float>(windowSize.y) / textureSize.y);

    // Player
    sf::Texture texture;
    if (!texture.loadFromFile("sprite.png")) {
        std::cerr << "Failed to load player texture!" << std::endl;
        return -1;
    }

    sf::Sprite goopy;
    goopy.setTexture(texture);
    goopy.setScale(0.2f, 0.2f);
    goopy.setPosition(80, 450);
    sf::Vector2u ts = texture.getSize();
    goopy.setOrigin(ts.x / 2.0f, ts.y / 2.0f);

    // Boxing Glove (Projectile)
    sf::Texture box_img;
    if (!box_img.loadFromFile("glove.png")) {
        std::cerr << "Failed to load glove texture!" << std::endl;
        return -1;
    }

    sf::Sprite glove;
    glove.setTexture(box_img);
    glove.setScale(0.16f, 0.16f);
    glove.setPosition(goopy.getPosition().x - 30.f, goopy.getPosition().y);

    float gloveSpeed = -1.0f;
    bool gloveShot = false;
    float gloveDefaultY = goopy.getPosition().y;
    float speed = 3.0f;
    sf::Clock shootClock;  // Clock to measure time between shots
    float shootDelay = 0.5f;  // Delay in seconds

    while (window.isOpen()) {
        sf::Event event;
        sf::Vector2f currentPosition = goopy.getPosition();
        std::cout << "x = " << currentPosition.x << " y = "
        << currentPosition.y << std::endl;

        // Check for window events
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Move the player right
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (currentPosition.x + goopy.getGlobalBounds().width + speed
            <= window.getSize().x + 80) {
                goopy.move(speed, 0.f);
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (currentPosition.x - speed >= 80) {
                goopy.move(-speed, 0.f);
            }
        }

        if (!gloveShot) {
            glove.setPosition(goopy.getPosition().x - 30.f
            , goopy.getPosition().y);
        }

        // Shoot the glove (projectile)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !gloveShot) {
            if (shootClock.getElapsedTime().asSeconds() >= shootDelay) {
                shootClock.restart();  // Reset the clock after shooting
                gloveShot = true;
                glove.setPosition(goopy.getPosition().x - 30.f
                , goopy.getPosition().y);
            }
        }

        // Update glove position if shot
        if (gloveShot) {
            glove.move(0.0f, gloveSpeed);  // Move the glove upward

            // Reset the glove if it goes off-screen
            if (glove.getPosition().y + glove.getGlobalBounds().height < 0) {
                gloveShot = false;
                glove.setPosition(goopy.getPosition().x - 30.f, gloveDefaultY);
            }
        }

        // Draw everything
        window.clear(sf::Color::White);
        window.draw(bg);
        window.draw(square);
        window.draw(glove);
        window.draw(goopy);
        window.display();
    }

    return 0;
}
