// Copyright 2024 Sameera Sakinala
#include "Sokoban.hpp"
#include <iostream>
#include <fstream>
#include <utility>

namespace SB {

Sokoban::Sokoban() : m_width(0), m_height(0),
m_playerPosition(0, 0), m_playerDirection(Direction::Down) {
    loadTextures();
    if (!m_moveSoundBuffer.loadFromFile("move.wav")) {
        std::cerr << "Failed to load move sound" << std::endl;
    }
    m_moveSound.setBuffer(m_moveSoundBuffer);

    if (!m_victorySoundBuffer.loadFromFile("victory.wav")) {
        std::cerr << "Failed to load victory sound" << std::endl;
    }
    m_victorySound.setBuffer(m_victorySoundBuffer);
}

void Sokoban::loadTextures() {
    std::vector<std::pair<char, std::string>> texturePaths = {
        {'#', "block_06.png"},
        {'A', "crate_03.png"},
        {'.', "ground_01.png"},
        {'a', "ground_04.png"},
        {'*', "crate_03.png"},
        {'+', "player_05.png"},
    };

    for (const auto& [key, path] : texturePaths) {
        sf::Texture texture;
        if (!texture.loadFromFile(path)) {
            std::cerr << "Failed to load texture: " << path << std::endl;
        } else {
            m_textures[key] = texture;
        }
    }

    std::vector<std::pair<Direction, std::string>> playerTextures = {
        {Direction::Up, "player_08.png"},
        {Direction::Down, "player_05.png"},
        {Direction::Left, "player_20.png"},
        {Direction::Right, "player_17.png"}
    };

    for (const auto& [dir, path] : playerTextures) {
        sf::Texture texture;
        if (!texture.loadFromFile(path)) {
            std::cerr << "Failed to load player texture: " << path << std::endl;
        } else {
            m_textures[static_cast<char>(dir)] = texture;
        }
    }
}

unsigned int Sokoban::width() const { return m_width; }
unsigned int Sokoban::height() const { return m_height; }
sf::Vector2u Sokoban::playerLoc() const { return m_playerPosition; }

bool Sokoban::isWon() const {
    for (unsigned int y = 0; y < m_height; ++y) {
        for (unsigned int x = 0; x < m_width; ++x) {
            if (m_grid[y][x] == 'A' || m_grid[y][x] == 'a') {
                return false;
            }
        }
    }
    return true;
}

void Sokoban::movePlayer(Direction dir) {
    saveState();
    // Clear redo stacks when a new move is made
    while (!m_redoStack.empty()) m_redoStack.pop();
    while (!m_redoPlayerPositionStack.empty()) m_redoPlayerPositionStack.pop();

    m_playerDirection = dir;
    int newX = m_playerPosition.x;
    int newY = m_playerPosition.y;

    switch (dir) {
        case Direction::Up: newY--; break;
        case Direction::Down: newY++; break;
        case Direction::Left: newX--; break;
        case Direction::Right: newX++; break;
    }

    if (canMove(newX, newY)) {
        char currentTile = m_grid[m_playerPosition.y][m_playerPosition.x];
        m_grid[m_playerPosition.y][m_playerPosition.x] =
            (currentTile == '@' || currentTile == '+') ?
            (isStorage(m_initialGrid[m_playerPosition.y]
            [m_playerPosition.x]) ? 'a' : '.') :
            currentTile;
        if (m_grid[newY][newX] == 'A' || m_grid[newY][newX] == '*') {
            doPushBox(newX, newY, dir);
        }
        m_playerPosition = {static_cast<unsigned int>(newX),
        static_cast<unsigned int>(newY)};
        char newTile = m_grid[newY][newX];
        m_grid[newY][newX] = isStorage(newTile) ? '+' : '@';
        playMoveSound();

        if (isWon()) {
            playVictorySound();
        }
    }
}

void Sokoban::reset() {
    while (!m_undoStack.empty()) m_undoStack.pop();
    while (!m_playerPositionStack.empty()) m_playerPositionStack.pop();
    while (!m_redoStack.empty()) m_redoStack.pop();
    while (!m_redoPlayerPositionStack.empty()) m_redoPlayerPositionStack.pop();
    m_grid = m_initialGrid;
    for (unsigned int y = 0; y < m_height; ++y) {
        for (unsigned int x = 0; x < m_width; ++x) {
            if (m_grid[y][x] == '@' || m_grid[y][x] == '+') {
                m_playerPosition = {x, y};
                m_playerDirection = Direction::Down;
                return;
            }
        }
    }
}

char Sokoban::getTile(unsigned int x, unsigned int y) const {
    if (x < m_width && y < m_height) {
        return m_grid[y][x];
    }
    return ' ';
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (unsigned int y = 0; y < m_height; ++y) {
        for (unsigned int x = 0; x < m_width; ++x) {
            char tile = m_grid[y][x];
            if (tile == '@' || tile == '+') {
                sf::Sprite floorSprite(m_textures.at(tile == '+' ? 'a' : '.'));
                floorSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                target.draw(floorSprite, states);
                sf::Sprite playerSprite
                (m_textures.at(static_cast<char>(m_playerDirection)));
                playerSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                target.draw(playerSprite, states);
            } else if (m_textures.count(tile) > 0) {
                sf::Sprite sprite(m_textures.at(tile));
                sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                target.draw(sprite, states);
            }
        }
    }
}

bool Sokoban::canMove(int x, int y) const {
    if (x < 0 || x >= static_cast<int>(m_width)
    || y < 0 || y >= static_cast<int>(m_height)) {
        return false;
    }

    char cell = m_grid[y][x];
    if (cell == '#') return false;
    if (cell == 'A' || cell == '*') {
        return canPushBox(x, y, m_playerDirection);
    }
    return true;
}

bool Sokoban::canPushBox(int x, int y, Direction dir) const {
    int newX = x, newY = y;
    switch (dir) {
        case Direction::Up: newY--; break;
        case Direction::Down: newY++; break;
        case Direction::Left: newX--; break;
        case Direction::Right: newX++; break;
    }

    if (newX < 0 || newX >= static_cast<int>(m_width)
    || newY < 0 || newY >= static_cast<int>(m_height)) {
        return false;
    }

    char nextCell = m_grid[newY][newX];
    return (nextCell == '.' || nextCell == 'a');
}

void Sokoban::doPushBox(int x, int y, Direction dir) {
    int newX = x, newY = y;
    switch (dir) {
        case Direction::Up: newY--; break;
        case Direction::Down: newY++; break;
        case Direction::Left: newX--; break;
        case Direction::Right: newX++; break;
    }

    char nextCell = m_grid[newY][newX];
    m_grid[newY][newX] = isStorage(nextCell) ? '*' : 'A';
    m_grid[y][x] = isStorage(m_initialGrid[y][x]) ? 'a' : '.';
}

bool Sokoban::isStorage(char tile) const {
    return tile == 'a' || tile == '*' || tile == '+';
}

bool Sokoban::isBoxOnStorage(char tile) const {
    return tile == '*';
}

void Sokoban::saveState() {
    m_undoStack.push(m_grid);
    m_playerPositionStack.push(m_playerPosition);
}

void Sokoban::undo() {
    if (!m_undoStack.empty()) {
        m_redoStack.push(m_grid);
        m_redoPlayerPositionStack.push(m_playerPosition);

        m_grid = m_undoStack.top();
        m_undoStack.pop();
        m_playerPosition = m_playerPositionStack.top();
        m_playerPositionStack.pop();
    }
}

void Sokoban::redo() {
    if (!m_redoStack.empty()) {
        saveState();
        m_grid = m_redoStack.top();
        m_redoStack.pop();
        m_playerPosition = m_redoPlayerPositionStack.top();
        m_redoPlayerPositionStack.pop();
    }
}

bool Sokoban::canUndo() const {
    return !m_undoStack.empty();
}

bool Sokoban::canRedo() const {
    return !m_redoStack.empty();
}

void Sokoban::playMoveSound() {
    m_moveSound.play();
}

void Sokoban::playVictorySound() {
    m_victorySound.play();
}

std::istream& operator>>(std::istream& in, Sokoban& s) {
    in >> s.m_height >> s.m_width;
    s.m_grid.resize(s.m_height, std::vector<char>(s.m_width));
    s.m_initialGrid.resize(s.m_height, std::vector<char>(s.m_width));
    for (unsigned int y = 0; y < s.m_height; ++y) {
        for (unsigned int x = 0; x < s.m_width; ++x) {
            in >> s.m_grid[y][x];
            s.m_initialGrid[y][x] = s.m_grid[y][x];
            if (s.m_grid[y][x] == '@' || s.m_grid[y][x] == '+') {
                s.m_playerPosition = {x, y};
            }
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Sokoban& s) {
    out << s.height() << " " << s.width() << "\n";
    for (unsigned int y = 0; y < s.height(); ++y) {
        for (unsigned int x = 0; x < s.width(); ++x) {
            out << s.getTile(x, y);
        }
        out << "\n";
    }
    return out;
}
}  // namespace SB
