#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "piece.hpp"
#include "constants.hpp"

enum class SquareState {
  ACTIVE,
  PASSIVE,
  EMPTY
};

class Board {
using BaseBoard = std::array<std::array<SquareState, BOARD_WIDTH>, BOARD_HEIGHT>;
using BaseColor = std::array<std::array<sf::Color, BOARD_WIDTH>, BOARD_HEIGHT>;

public:
  static auto createNewBoard(sf::Vector2f pos) -> Board {
    BaseBoard newGrid;
    BaseColor newColors;
    for (auto i = 0; i < BOARD_HEIGHT; ++i) {
      std::fill(newGrid[i].begin(), newGrid[i].end(), SquareState::EMPTY);
      std::fill(newColors[i].begin(), newColors[i].end(), sf::Color::White);
    }
    Board board(newGrid, newColors, sf::Color::White, pos);
    return board;
  }

  Board(BaseBoard grid, BaseColor colors, sf::Color color, sf::Vector2f top_left):
    grid{grid}, colors{colors}, color{color}, top_left{top_left}, active{spawnRandomPiece()} {
      background = createBackground();
      updateGrid();
    }

  auto draw(sf::RenderWindow& window) const -> void {
    window.draw(background);
    for (auto row = 0; row < BOARD_HEIGHT; row++) {
      for (auto col = 0; col < BOARD_WIDTH; col++) {
        if (grid[row][col] != SquareState::EMPTY) {
          sf::RectangleShape square(sf::Vector2f(UNIT_SQUARE_LENGTH, UNIT_SQUARE_LENGTH));
          square.setPosition(sf::Vector2f(top_left.x + UNIT_SQUARE_LENGTH * col, top_left.y + UNIT_SQUARE_LENGTH * row));
          square.setFillColor(colors[row][col]);
          window.draw(square);
        }
      }
    }
  }

  auto next() -> void {
    active.moveDown();
    if (!validMove()) {
      active.moveUp();
      fixActivePiece();
      clearLines();
      active = spawnRandomPiece();
    }
    if (!validMove()) {
      has_ended = true;
    }
    updateGrid();
  }

  auto handleKeyboardInput(sf::Keyboard::Key input) -> void {
    switch (input) {
      case sf::Keyboard::Left:
        active.moveLeft();
        if (!validMove()) {
          active.moveRight();
        }
        break;
      case sf::Keyboard::Right:
        active.moveRight();
        if (!validMove()) {
          active.moveLeft();
        }
        break;
      case sf::Keyboard::Up:
        active.rotateClockwise();
        if (!validMove()) {
          active.rotateCounterclockwise();
        }
        break;
      case sf::Keyboard::Down:
        active.rotateCounterclockwise();
        if (!validMove()) {
          active.rotateClockwise();
        }
        break;
      default:
        break;
    }
  }

  auto getHasEnded() -> bool {
    return has_ended;
  }

private:
  BaseBoard grid;
  BaseColor colors;
  sf::Color color;
  sf::Vector2f top_left;
  sf::RectangleShape background;
  Piece active;
  bool has_ended = false;

  auto createBackground() -> sf::RectangleShape {
    sf::RectangleShape square(sf::Vector2f(UNIT_SQUARE_LENGTH * BOARD_WIDTH, UNIT_SQUARE_LENGTH * BOARD_HEIGHT));
    square.setPosition(top_left);
    square.setFillColor(color);
    return square;
  }

  auto spawnRandomPiece() -> Piece {
    std::random_device rng;

    std::uniform_int_distribution<size_t> color_distribution(0, 255);
    sf::Color random_color(color_distribution(rng), color_distribution(rng), color_distribution(rng));

    std::uniform_int_distribution<size_t> dist(0, BOARD_WIDTH - LARGE_SIZE);
    sf::Vector2f random_position(top_left.x + dist(rng) * UNIT_SQUARE_LENGTH, top_left.y);

    return generateRandomPiece(random_color, random_position);
  }

  auto validMove() -> bool {
    if (active.outsideBoundaries(top_left.x, top_left.x + (BOARD_WIDTH * UNIT_SQUARE_LENGTH), top_left.y, top_left.y + (BOARD_HEIGHT * UNIT_SQUARE_LENGTH))) {
      return false;
    }

    const auto piece_top_left = active.getTopleft();
    const auto points = active.getPoints();
    const auto [gridX, gridY] = std::make_pair((piece_top_left.x - top_left.x) / UNIT_SQUARE_LENGTH, (piece_top_left.y - top_left.y) / UNIT_SQUARE_LENGTH);
    for (const auto [y, x] : points) {
      if (grid[gridY + y][gridX + x] == SquareState::PASSIVE) {
        return false;
      }
    }
    return true;
  }

  auto updateGrid() -> void {
    for (auto row = 0; row < BOARD_HEIGHT; ++row) {
      for (auto col = 0; col < BOARD_WIDTH; ++col) {
        if (grid[row][col] == SquareState::ACTIVE) {
          grid[row][col] = SquareState::EMPTY;
        }
      }
    }

    const auto piece_top_left = active.getTopleft();
    const auto points = active.getPoints();
    const auto [gridX, gridY] = std::make_pair((piece_top_left.x - top_left.x) / UNIT_SQUARE_LENGTH, (piece_top_left.y - top_left.y) / UNIT_SQUARE_LENGTH);
    for (const auto [y, x] : points) {
      grid[gridY + y][gridX + x] = SquareState::ACTIVE;
      colors[gridY + y][gridX + x] = active.getColor();
    }
  }

  auto clearLines() -> void {
    for (auto i = 0; i < BOARD_HEIGHT; ++i) {
      size_t count_non_empty = 0;
      for (auto j = 0; j < BOARD_WIDTH; ++j) {
        if (grid[i][j] != SquareState::EMPTY) {
          count_non_empty++;
        }
      }
      if (count_non_empty < BOARD_WIDTH) {
        continue;
      }
      for (auto j = 0; j < BOARD_WIDTH; ++j) {
        grid[i][j] = SquareState::EMPTY;
        colors[i][j] = sf::Color::White;
      }
    }

    for (auto i = BOARD_HEIGHT - 1; i > 0; --i) {
      bool is_row_empty = true;
      for (const auto state : grid[i]) {
        if (state != SquareState::EMPTY) {
          is_row_empty = false;
          break;
        }
      }
      if (is_row_empty) {
        std::swap(grid[i], grid[i - 1]);
        std::swap(colors[i], colors[i - 1]);
      }
    }
  }

  auto fixActivePiece() -> void {
    for (auto row = 0; row < BOARD_HEIGHT; ++row) {
      for (auto col = 0; col < BOARD_WIDTH; ++col) {
        if (grid[row][col] == SquareState::ACTIVE) {
          grid[row][col] = SquareState::PASSIVE;
        }
      }
    }
  }
};

#endif
