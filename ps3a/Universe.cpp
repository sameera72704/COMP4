//  copyright 2024 Sameera Sakinala
#include "Universe.hpp"
#include <iostream>
#include <iomanip>

namespace NB {
void Universe::draw(sf::RenderTarget& target, sf::RenderStates states) const {
for (const auto& body : bodies) {
target.draw(body, states);
}
}

void Universe::updatePositions(double scale,
 int windowWidth, int windowHeight) {
for (auto& body : bodies) {
sf::Vector2f pos = body.getPosition();
float x = (pos.x * scale) + (windowWidth / 2.0);
float y = (windowHeight / 2.0) - (pos.y * scale);
body.setScreenPosition(x, y);
}
}

void Universe::logDetails() const {
std::cout << "Universe radius: " << radius << std::endl;
std::cout << "Number of bodies: " << bodies.size() << std::endl;
for (size_t i = 0; i < bodies.size(); ++i) {
std::cout << "Body " << i << ":" << std::endl;
bodies[i].debugPrint();
std::cout << std::endl;
}
}

void Universe::computeScreenPositions(double scale,
int windowWidth, int windowHeight) {
for (auto& body : bodies) {
sf::Vector2f pos = body.getPosition();
float x = (pos.x * scale) + (windowWidth / 2.0);
float y = (windowHeight / 2.0) - (pos.y * scale);
body.setScreenPosition(x, y);
        }
    }

std::istream& operator>>(std::istream& is, Universe& universe) {
int n;
is >> n >> universe.radius;

universe.bodies.resize(n);
for (auto& body : universe.bodies) {
is >> body;
}
return is;
}

std::ostream& operator<<(std::ostream& os, const Universe& universe) {
os << universe.size() << "\n";
os << std::scientific << std::setprecision(4) << universe.getRadius() << "\n";
for (const auto& body : universe.bodies) {
os << body << "\n";
}
return os;
}
}  // namespace NB
