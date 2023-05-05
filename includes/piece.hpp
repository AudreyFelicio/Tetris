#ifndef PIECE_HPP
#define PIECE_HPP

#include <array>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <iostream>

enum class PieceType {
  I_SHAPE,
  J_SHAPE,
  L_SHAPE,
  O_SHAPE,
  Z_SHAPE,
  T_SHAPE,
  S_SHAPE
};

class Piece {

static constexpr float LENGTH = 5.0;
static constexpr size_t BASE_SIZE = 4;
using BaseSquare = std::array<std::array<bool, BASE_SIZE>, BASE_SIZE>;

public:
  auto draw(sf::RenderWindow& window) const -> void {
    for (auto row = 0; row < BASE_SIZE; row++) {
      for (auto col = 0; col < BASE_SIZE; col++) {
        if (grid[row][col]) {
          sf::RectangleShape square(sf::Vector2f(LENGTH, LENGTH));
          square.setPosition(sf::Vector2f(top_left.x + LENGTH * col, top_left.y + LENGTH * row));
          square.setFillColor(sf::Color::Blue);
          window.draw(square);
        }
      }
    }
  }

  auto handleKeyboardInput(sf::Keyboard::Key input) -> void {
    switch (input) {
      case sf::Keyboard::Left:
        moveLeft();
        break;
      case sf::Keyboard::Right:
        moveRight();
        break;
      case sf::Keyboard::Up:
        rotateClockwise();
        break;
      case sf::Keyboard::Down:
        rotateCounterclockwise();
        break;
      default:
        break;
    }
  }

  auto moveDown() -> void {
    top_left.y += LENGTH;
  }

protected:
  BaseSquare grid;
  sf::Color color;
  sf::Vector2f top_left;
  PieceType type;
  std::chrono::high_resolution_clock::time_point last_keyboard_input;

  Piece(BaseSquare grid, sf::Color color, sf::Vector2f top_left, PieceType type):
    grid{grid}, color{color}, top_left{top_left}, type{type} {
      last_keyboard_input = std::chrono::high_resolution_clock::now();
    }

  auto moveRight() -> void {
    top_left.x += LENGTH;
  }

  auto moveLeft() -> void {
    top_left.x -= LENGTH;
  }

  auto rotateClockwise() -> void {
    BaseSquare result;

    for (int i = 0; i < BASE_SIZE; i++) {
      for (int j = 0; j < BASE_SIZE; j++) {
        result[i][j] = grid[BASE_SIZE - j - 1][i];
      }
    }

    for (int i = 0; i < BASE_SIZE; i++) {
      for (int j = 0; j < BASE_SIZE; j++) {
        grid[i][j] = result[i][j];
      }
    }
  }

  auto rotateCounterclockwise() -> void {
    BaseSquare result;

    for (int i = 0; i < BASE_SIZE; i++) {
      for (int j = 0; j < BASE_SIZE; j++) {
        result[i][j] = grid[j][BASE_SIZE - i - 1];
      }
    }

    for (int i = 0; i < BASE_SIZE; i++) {
      for (int j = 0; j < BASE_SIZE; j++) {
        grid[i][j] = result[i][j];
      }
    }
  }
};

class OShape : public Piece {
public:
  OShape(sf::Color color, sf::Vector2f top_left):
    Piece{{{ {{1, 1, 0, 0}}, {{1, 1, 0, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}} }}, color, top_left, PieceType::O_SHAPE} {}
};

class LShape : public Piece {
public:
  LShape(sf::Color color, sf::Vector2f top_left):
    Piece{{{ {{1, 0, 0, 0}}, {{1, 0, 0, 0}}, {{1, 1, 0, 0}}, {{0, 0, 0, 0}} }}, color, top_left, PieceType::L_SHAPE} {}
};

class IShape : public Piece {
public:
  IShape(sf::Color color, sf::Vector2f top_left):
    Piece{{{ {{1, 0, 0, 0}}, {{1, 0, 0, 0}}, {{1, 0, 0, 0}}, {{1, 0, 0, 0}} }}, color, top_left, PieceType::I_SHAPE} {}
};

class JShape : public Piece {
public:
  JShape(sf::Color color, sf::Vector2f top_left):
    Piece{{{ {{0, 1, 0, 0}}, {{0, 1, 0, 0}}, {{1, 1, 0, 0}}, {{0, 0, 0, 0}} }}, color, top_left, PieceType::J_SHAPE} {}
};

class ZShape : public Piece {
public:
  ZShape(sf::Color color, sf::Vector2f top_left):
    Piece{{{ {{1, 1, 0, 0}}, {{0, 1, 1, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}} }}, color, top_left, PieceType::Z_SHAPE} {}
};

class TShape : public Piece {
public:
  TShape(sf::Color color, sf::Vector2f top_left):
    Piece{{{ {{1, 1, 1, 0}}, {{0, 1, 0, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}} }}, color, top_left, PieceType::T_SHAPE} {}
};

class SShape : public Piece {
public:
  SShape(sf::Color color, sf::Vector2f top_left):
    Piece{{{ {{0, 1, 1, 0}}, {{1, 1, 0, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}} }}, color, top_left, PieceType::S_SHAPE} {}
};

#endif
