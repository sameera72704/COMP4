// copyright 2024 Sameera Sakinala
#include "CelestialBody.hpp"
#include <iostream>
#include <iomanip>

namespace NB {
void CelestialBody::draw(sf::RenderTarget& target,
sf::RenderStates states) const {
        target.draw(sprite, states);
    }

    void CelestialBody::setScreenPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    void CelestialBody::setPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }

void CelestialBody::debugPrint() const {
std::cout << "Position: (" << position.x << ", "
<< position.y << ")" << std::endl;
std::cout << "Velocity: (" << velocity.x
<< ", " << velocity.y << ")" << std::endl;
std::cout << "Mass: " << mass << std::endl;
std::cout << "Filename: " << filename << std::endl;
std::cout << "Sprite position: (" << sprite.getPosition().x
<< ", " << sprite.getPosition().y << ")" << std::endl;
}

std::istream& operator>>(std::istream& is, CelestialBody& body) {
is >> body.position.x >> body.position.y
>> body.velocity.x >> body.velocity.y
>> body.mass >> body.filename;
if (!body.texture.loadFromFile(body.filename)) {
std::cerr << "Failed to load texture: "
<< body.filename << std::endl;
}
body.sprite.setTexture(body.texture);
body.sprite.setOrigin(body.texture.getSize().x / 2.0f,
body.texture.getSize().y / 2.0f);
return is;
}

std::ostream& operator<<(std::ostream& os, const CelestialBody& body) {
os << std::scientific << std::setprecision(4)
<< body.position.x << " " << body.position.y << " "
<< body.velocity.x << " " << body.velocity.y << " "
<< body.mass << " " << body.filename;
        return os;
    }
}  // namespace NB
