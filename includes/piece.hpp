#ifndef PIECE_HPP
#define PIECE_HPP

#include <array>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <iostream>
#include <set>
#include <math.h>
#include <tuple>
#include <random>
#include "constants.hpp"
#include "utils.hpp"

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
using BaseSquare = std::array<std::array<bool, LARGE_SIZE>, LARGE_SIZE>;

public:
  auto draw(sf::RenderWindow& window) const -> void {
    for (auto row = 0; row < BASE_SIZE; row++) {
      for (auto col = 0; col < BASE_SIZE; col++) {
        if (grid[row][col]) {
          sf::RectangleShape square(sf::Vector2f(UNIT_SQUARE_LENGTH, UNIT_SQUARE_LENGTH));
          square.setPosition(sf::Vector2f(top_left.x + UNIT_SQUARE_LENGTH * col, top_left.y + UNIT_SQUARE_LENGTH * row));
          square.setFillColor(color);
          // window.draw(square);

          sf::Sprite curr_block = blocks[block_type];
          curr_block.setPosition(sf::Vector2f(top_left.x + UNIT_SQUARE_LENGTH * col, top_left.y + UNIT_SQUARE_LENGTH * row));
          window.draw(curr_block);
        }
      }
    }
  }

  auto moveRight() -> void {
    top_left.x += UNIT_SQUARE_LENGTH;
  }

  auto moveLeft() -> void {
    top_left.x -= UNIT_SQUARE_LENGTH;
  }

  auto moveDown() -> void {
    top_left.y += UNIT_SQUARE_LENGTH;
  }

  auto moveUp() -> void {
    top_left.y -= UNIT_SQUARE_LENGTH;
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

  auto getLeftBoundary() {
    int leftMost = 0;
    for (int col = 0; col < BASE_SIZE; col++) {
      bool edgeFound = false;
      for (int row = 0; row < BASE_SIZE; row++) {
        if (grid[row][col]) {
          edgeFound = true;
          break;
        }
      }
      if (edgeFound) {
        break;
      }
      leftMost++;
    }
    return top_left.x + leftMost * UNIT_SQUARE_LENGTH;
  }

  auto getRightBoundary() {
    int rightMost = BASE_SIZE;
    for (int col = BASE_SIZE - 1; col >= 0; col--) {
      bool edgeFound = false;
      for (int row = 0; row < BASE_SIZE; row++) {
        if (grid[row][col]) {
          edgeFound = true;
          break;
        }
      }
      if (edgeFound) {
        break;
      }
      rightMost--;
    }
    return top_left.x + rightMost * UNIT_SQUARE_LENGTH;
  }

  auto getBottomBoundary() {
    int bottomMost = BASE_SIZE;
    for (int row = BASE_SIZE - 1; row >= 0; row--) {
      bool edgeFound = false;
      for (int col = 0; col < BASE_SIZE; col++) {
        if (grid[row][col]) {
          edgeFound = true;
          break;
        }
      }
      if (edgeFound) {
        break;
      }
      bottomMost--;
    }
    return top_left.y + bottomMost * UNIT_SQUARE_LENGTH;
  }

  auto getPoints() -> std::set<std::pair<int, int> > {
    std::set<std::pair<int, int> > points;
    int i_offset = round(top_left.y / UNIT_SQUARE_LENGTH);
    int j_offset = round(top_left.x / UNIT_SQUARE_LENGTH);

    for (int i = 0; i < BASE_SIZE; ++i) {
      for (int j = 0; j < BASE_SIZE; ++j) {
        if (grid[i][j]) {
          points.insert(std::make_pair(i + i_offset, j + j_offset));
        }
      }
    }
    return points;
  }

  auto collidesWithOtherPiece(Piece otherPiece) -> bool {
    std::set<std::pair<int, int> > myPoints = getPoints(), otherPoints = otherPiece.getPoints();
    for (auto &p: myPoints) {
      if (otherPoints.count(p)) {
        return true;
      }
    }
    return false;
  }

  auto outsideBoundaries(float left, float right, float top, float bottom) -> bool {
    return getLeftBoundary() < left or getRightBoundary() > right or getBottomBoundary() > bottom;
  }

  auto getGrid() -> BaseSquare {
    return grid;
  }

  auto getTopleft() -> sf::Vector2f {
    return top_left;
  }

  auto clearGrid(int i, int j) -> void {
    grid[i][j] = 0;
  }

protected:
  BaseSquare grid;
  const size_t BASE_SIZE;
  sf::Color color;
  int block_type;
  sf::Vector2f top_left;
  PieceType type;
  std::chrono::high_resolution_clock::time_point last_keyboard_input;

  Piece(BaseSquare grid, sf::Color color, sf::Vector2f top_left, PieceType type, size_t base_size):
    grid{grid}, color{color}, top_left{top_left}, type{type}, BASE_SIZE{base_size} {
      last_keyboard_input = std::chrono::high_resolution_clock::now();
      block_type = genRandomBlockType();
    }
};

class OShape : public Piece {
public:
  OShape(sf::Color color, sf::Vector2f top_left):
    Piece{{{ {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} }}, color, top_left, PieceType::O_SHAPE, SMALL_SIZE} {}
};

class LShape : public Piece {
public:
  LShape(sf::Color color, sf::Vector2f top_left):
    Piece{{{ {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0} }}, color, top_left, PieceType::L_SHAPE, MEDIUM_SIZE} {}
};

class IShape : public Piece {
public:
  IShape(sf::Color color, sf::Vector2f top_left):
    Piece{{{ {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0} }}, color, top_left, PieceType::I_SHAPE, LARGE_SIZE} {}
};

class JShape : public Piece {
public:
  JShape(sf::Color color, sf::Vector2f top_left):
    Piece{{{ {0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0} }}, color, top_left, PieceType::J_SHAPE, MEDIUM_SIZE} {}
};

class ZShape : public Piece {
public:
  ZShape(sf::Color color, sf::Vector2f top_left):
    Piece{{{ {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} }}, color, top_left, PieceType::Z_SHAPE, MEDIUM_SIZE} {}
};

class TShape : public Piece {
public:
  TShape(sf::Color color, sf::Vector2f top_left):
    Piece{{{ {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} }}, color, top_left, PieceType::T_SHAPE, MEDIUM_SIZE} {}
};

class SShape : public Piece {
public:
  SShape(sf::Color color, sf::Vector2f top_left):
    Piece{{{ {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} }}, color, top_left, PieceType::S_SHAPE, MEDIUM_SIZE} {}
};

auto generateRandomPiece(sf::Color color, sf::Vector2f top_left) -> Piece {
  std::random_device rng;
  std::uniform_int_distribution<size_t> choice_distribution(0, 7);

  int choice = choice_distribution(rng);
    switch (choice) {
      case 0:
        return OShape(color, top_left);
      case 1:
        return LShape(color, top_left);
      case 2:
        return IShape(color, top_left);
      case 3:
        return JShape(color, top_left);
      case 4:    
        return ZShape(color, top_left);
      case 5:
        return TShape(color, top_left);
      default:
        return SShape(color, top_left);
    }
}

#endif
