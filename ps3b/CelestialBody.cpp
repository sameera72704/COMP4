// copyright 2024 Sameera Sakinala
#include "CelestialBody.hpp"
#include <iomanip>

namespace NB {

std::istream& operator>>(std::istream& is, CelestialBody& body) {
    is >> body.position.x >> body.position.y
       >> body.velocity.x >> body.velocity.y
       >> body.mass >> body.filename;
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
