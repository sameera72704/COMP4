// copyright 2024 Sameera Sakinala
#pragma once
#include <string>
#include <SFML/Graphics.hpp>

namespace NB {

class CelestialBody : public sf::Drawable {
 private:
  sf::Vector2f position;
  sf::Vector2f velocity;
  double mass;
  sf::Texture texture;
  sf::Sprite sprite;
  std::string filename;

 protected:
  void draw(sf::RenderTarget& target,
            sf::RenderStates states) const override;

 public:
  CelestialBody() = default;
  sf::Vector2f getPosition() const { return position; }
  sf::Vector2f getVelocity() const { return velocity; }
  double getMass() const { return mass; }
  std::string getFilename() const { return filename; }
  void setScreenPosition(float x, float y);
  void setPosition(float x, float y);
  void debugPrint() const;

  friend std::istream& operator>>(std::istream& is, CelestialBody& body);
  friend std::ostream& operator<<(std::ostream& os, const CelestialBody& body);
};

}  // namespace NB
