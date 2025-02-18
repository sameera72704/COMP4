// copyright 2024 Sameera Sakinala
#pragma once
#include <string>
#include <SFML/System/Vector2.hpp>

namespace NB {

class CelestialBody {
 private:
    sf::Vector2<double> position;
    sf::Vector2<double> velocity;
    double mass;
    std::string filename;

 public:
    CelestialBody() = default;
    sf::Vector2<double> getPosition() const { return position; }
    sf::Vector2<double> getVelocity() const { return velocity; }
    double getMass() const { return mass; }
    std::string getFilename() const { return filename; }
    void setPosition(double x, double y) { position = {x, y}; }
    void setVelocity(double x, double y) { velocity = {x, y}; }

    friend std::istream& operator>>(std::istream& is, CelestialBody& body);
    friend std::ostream& operator<<
    (std::ostream& os, const CelestialBody& body);
};

}  // namespace NB
