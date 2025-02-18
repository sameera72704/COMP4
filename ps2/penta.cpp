// copyright Sameera Sakinala 2024
#include "penta.hpp"

Pentaflake::Pentaflake(double sideLength, int depth, double rotation)
    : m_sideLength(sideLength), m_depth(depth),
     m_rotation(rotation), m_animationTime(0) {}

void Pentaflake::generate() {
    m_pentagons.clear();
    generatePentaflake(0, 0, m_sideLength, m_depth);
}

void Pentaflake::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Transform rotation;
    rotation.rotate(m_rotation * 180 / M_PI);
    states.transform *= rotation;

    for (const auto& pentagon : m_pentagons) {
        target.draw(pentagon, states);
    }
}

void Pentaflake::generatePentaflake(double x, double y,
 double sideLength, int depth) {
    if (depth == 0) {
        m_pentagons.push_back(createPentagon(x, y, sideLength, PRIMARY_COLOR));
        return;
    }

    double newSideLength = sideLength / (1 + (1.0 + std::sqrt(5.0)) / 2.0);
    double R = sideLength / (2 * std::sin(M_PI / 5));
    double r = newSideLength / (2 * std::sin(M_PI / 5));

    generatePentaflake(x, y, newSideLength, depth - 1);

    for (int i = 0; i < 5; ++i) {
        double angle = 2 * M_PI * i / 5;
        double newX = x + (R - r) * std::cos(angle);
        double newY = y + (R - r) * std::sin(angle);
        generatePentaflake(newX, newY, newSideLength, depth - 1);
    }
}

sf::ConvexShape Pentaflake::createPentagon(double x, double y,
 double sideLength, const sf::Color& color) const {
    sf::ConvexShape pentagon;
    pentagon.setPointCount(5);
    double R = sideLength / (2 * std::sin(M_PI / 5));
    for (int i = 0; i < 5; ++i) {
        double angle = 2 * M_PI * i / 5;
        double px = x + R * std::cos(angle);
        double py = y + R * std::sin(angle);
        pentagon.setPoint(i, sf::Vector2f(px, py));
    }
    pentagon.setFillColor(color);
    pentagon.setOutlineColor(sf::Color::White);
    pentagon.setOutlineThickness(1);
    return pentagon;
}

void Pentaflake::animate(float deltaTime) {
    m_animationTime += deltaTime;
    m_rotation = std::fmod(m_animationTime * 0.5, 2 * M_PI);
}
