// Copyright 2024 Sameera Sakinala

#pragma once

#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>

class Pentaflake : public sf::Drawable {
 public:
    Pentaflake(double sideLength, int depth, double rotation = -M_PI / 2);
    void generate();
    void animate(float deltaTime);

 private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void generatePentaflake(double x, double y, double sideLength, int depth);
    sf::ConvexShape createPentagon(double x, double y,
                                   double sideLength,
                                   const sf::Color& color) const;

    double m_sideLength;
    int m_depth;
    double m_rotation;
    float m_animationTime;
    std::vector<sf::ConvexShape> m_pentagons;

    const sf::Color PRIMARY_COLOR = sf::Color(100, 149, 237);
    const sf::Color SECONDARY_COLOR = sf::Color(255, 215, 0);
};
