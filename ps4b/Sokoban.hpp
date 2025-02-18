// Copyright 2024 Sameera Sakinala
#pragma once

#include <vector>
#include <map>
#include <string>
#include <stack>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace SB {

enum class Direction { Up, Down, Left, Right };

class Sokoban : public sf::Drawable {
 public:
    static const int TILE_SIZE = 64;

    Sokoban();
    unsigned int width() const;
    unsigned int height() const;
    sf::Vector2u playerLoc() const;
    bool isWon() const;
    void movePlayer(Direction dir);
    void reset();
    char getTile(unsigned int x, unsigned int y) const;
    void undo();
    bool canUndo() const;
    void redo();
    bool canRedo() const;

    friend std::istream& operator>>(std::istream& in, Sokoban& s);
    friend std::ostream& operator<<(std::ostream& out, const Sokoban& s);

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    unsigned int m_width;
    unsigned int m_height;
    sf::Vector2u m_playerPosition;
    std::vector<std::vector<char>> m_grid;
    std::vector<std::vector<char>> m_initialGrid;
    std::map<char, sf::Texture> m_textures;
    Direction m_playerDirection;
    sf::SoundBuffer m_moveSoundBuffer;
    sf::Sound m_moveSound;
    sf::SoundBuffer m_victorySoundBuffer;
    sf::Sound m_victorySound;
    std::stack<std::vector<std::vector<char>>> m_undoStack;
    std::stack<sf::Vector2u> m_playerPositionStack;
    std::stack<std::vector<std::vector<char>>> m_redoStack;
    std::stack<sf::Vector2u> m_redoPlayerPositionStack;

    void loadTextures();
    bool canMove(int x, int y) const;
    bool canPushBox(int x, int y, Direction dir) const;
    void doPushBox(int x, int y, Direction dir);
    bool isStorage(char tile) const;
    bool isBoxOnStorage(char tile) const;
    void saveState();
    void playMoveSound();
    void playVictorySound();
};

std::istream& operator>>(std::istream& in, Sokoban& s);
std::ostream& operator<<(std::ostream& out, const Sokoban& s);

}  // namespace SB
