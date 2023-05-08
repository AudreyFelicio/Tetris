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

class Board {
using BaseBoard = std::array<std::array<int, BOARD_WIDTH>, BOARD_HEIGHT>;

public:
  static auto createNewBoard(sf::Vector2f pos) -> Board {
    BaseBoard newGrid;
    for (auto i = 0; i < BOARD_HEIGHT; ++i) {
      std::fill(newGrid[i].begin(), newGrid[i].end(), -1);
    }
    Board board(newGrid, sf::Color::White, pos);
    return board;
  }

  Board(BaseBoard grid, sf::Color color, sf::Vector2f top_left):
    grid{grid}, color{color}, top_left{top_left}, control_index{0} {
      background = createBackground();
      spawnRandomPiece();
    }

  auto spawnRandomPiece() -> void {
    std::random_device rng;

    std::uniform_int_distribution<size_t> color_distribution(0, 255);
    sf::Color random_color(color_distribution(rng), color_distribution(rng), color_distribution(rng));

    std::uniform_int_distribution<size_t> dist(0, BOARD_WIDTH - LARGE_SIZE);
    sf::Vector2f random_position(top_left.x + dist(rng) * UNIT_SQUARE_LENGTH, top_left.y);

    Piece random_piece = generateRandomPiece(random_color, random_position);
    
    pieces.push_back(random_piece);
    control_index = pieces.size() - 1;
    updatePieceInGrid(pieces.back(), control_index);
  }

  auto draw(sf::RenderWindow& window) const -> void {
    window.draw(background);
    for (auto &piece: pieces) {
      piece.draw(window);
    }
  }

  auto next() -> void {
    if (control_index < 0 or control_index >= pieces.size()) {
      return;
    }

    updateGrid();

    pieces[control_index].moveDown();
    if (!validMove()) {
      pieces[control_index].moveUp();
      clearLines();
      spawnRandomPiece();
      if (!validMove()) {
        has_ended = true;
      }
    }
  }

  auto handleKeyboardInput(sf::Keyboard::Key input) -> void {
    if (control_index < 0 or control_index >= pieces.size()) {
      return;
    }

    switch (input) {
      case sf::Keyboard::Left:
        pieces[control_index].moveLeft();
        if (!validMove()) {
          pieces[control_index].moveRight();
        }
        break;
      case sf::Keyboard::Right:
        pieces[control_index].moveRight();
        if (!validMove()) {
          pieces[control_index].moveLeft();
        }
        break;
      case sf::Keyboard::Up:
        pieces[control_index].rotateClockwise();
        if (!validMove()) {
          pieces[control_index].rotateCounterclockwise();
        }
        break;
      case sf::Keyboard::Down:
        pieces[control_index].rotateCounterclockwise();
        if (!validMove()) {
          pieces[control_index].rotateClockwise();
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
  sf::Color color;
  sf::Vector2f top_left;
  std::vector<Piece> pieces;
  sf::RectangleShape background;
  int control_index;
  bool has_ended = false;
  
  auto createBackground() -> sf::RectangleShape {
    sf::RectangleShape square(sf::Vector2f(UNIT_SQUARE_LENGTH * BOARD_WIDTH, UNIT_SQUARE_LENGTH * BOARD_HEIGHT));
    square.setPosition(top_left);
    square.setFillColor(color);
    return square;
  }

  auto validMove() -> bool {
    if (control_index < 0 or control_index >= pieces.size()) {
      return true;
    }

    if (pieces[control_index].outsideBoundaries(top_left.x, top_left.x + (BOARD_WIDTH * UNIT_SQUARE_LENGTH), top_left.y, top_left.y + (BOARD_HEIGHT * UNIT_SQUARE_LENGTH))) {
      return false;
    }

    for (int i = 0; i < pieces.size(); ++i) {
      if (i == control_index) {
        continue;
      }

      if (pieces[control_index].collidesWithOtherPiece(pieces[i])) {
        return false;
      }
    }

    return true;
  }

  auto updateGrid() -> void {
    BaseBoard newGrid;
    for (auto i = 0; i < BOARD_HEIGHT; ++i) {
      std::fill(newGrid[i].begin(), newGrid[i].end(), -1);
    }
    grid = newGrid;

    for (auto i = 0; i < pieces.size(); ++i) {
      updatePieceInGrid(pieces[i], i);
    }
  }

  auto updatePieceInGrid(Piece& piece, int index) -> void {
    const auto piece_top_left = piece.getTopleft();
    const auto piece_grid = piece.getGrid();
    const auto [gridX, gridY] = std::make_pair((piece_top_left.x - top_left.x) / UNIT_SQUARE_LENGTH, (piece_top_left.y - top_left.y) / UNIT_SQUARE_LENGTH);
    for (auto i = 0; i < piece_grid.size(); ++i) {
      for (auto j = 0; j < piece_grid[0].size(); ++j) {
        if (piece_grid[i][j]) {
          grid[gridY + i][gridX + j] = index;
        }
      }
    }
  }

  auto clearLines() -> void {
    for (auto i = 0; i < BOARD_HEIGHT; ++i) {
      size_t count_non_zero = 0;
      for (auto j = 0; j < BOARD_WIDTH; ++j) {
        if (grid[i][j] >= 0) {
          count_non_zero++;
        }
      }
      if (count_non_zero < BOARD_WIDTH) {
        continue;
      }
      for (auto j = 0; j < BOARD_WIDTH; ++j) {
        auto& curr_piece = pieces[grid[i][j]];
        const auto piece_top_left = curr_piece.getTopleft();
        const auto [gridX, gridY] = std::make_pair((piece_top_left.x - top_left.x) / UNIT_SQUARE_LENGTH, (piece_top_left.y - top_left.y) / UNIT_SQUARE_LENGTH);
        curr_piece.clearGrid(i - gridY, j - gridX);
      }
    }
  }
};

#endif
