// copyright 2024 Sameera Sakinala
#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"

namespace NB {

class Universe : public sf::Drawable {
 private:
  std::vector<CelestialBody> bodies;
  double radius;

 protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 public:
  Universe() = default;
  size_t size() const { return bodies.size(); }
  double getRadius() const { return radius; }
  CelestialBody& operator[](size_t index) { return bodies[index]; }
  const CelestialBody& operator[](size_t index) const { return bodies[index]; }
  void updatePositions(double scale, int windowWidth, int windowHeight);
  void logDetails() const;  // Ensure this method is declared
  void computeScreenPositions(double scale,
                              int windowWidth, int windowHeight);

  friend std::istream& operator>>(std::istream& is, Universe& universe);
  friend std::ostream& operator<<(std::ostream& os, const Universe& universe);
};

}  // namespace NB
