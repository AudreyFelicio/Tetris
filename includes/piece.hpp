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

  auto draw(sf::RenderWindow& window) -> void {
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

  void handleKeyboardInput(sf::Keyboard::Key input) {
    if (input == sf::Keyboard::Left)
    {
      moveLeft();
    }
    else if (input == sf::Keyboard::Right)
    {
      moveRight();
    }
    else if (input == sf::Keyboard::Up)
    {
      rotateClockwise();
    }    
    else if (input == sf::Keyboard::Down)
    {
      rotateCounterclockwise();
    }
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

  void moveRight() {
    top_left.x += LENGTH;
  }

  void moveLeft() {
    top_left.x -= LENGTH;
  }

  void rotateClockwise() {
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

  void rotateCounterclockwise() {
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

#endif