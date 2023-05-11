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
    Piece piece = generateRandomPiece(pos);
    Piece next_piece = generateRandomPiece(pos); 
    Board board(newGrid, sf::Color::White, pos, piece, next_piece);
    return board;
  }

  Board(BaseBoard grid, sf::Color color, sf::Vector2f top_left, Piece piece, Piece next_piece):
    grid{grid}, color{color}, top_left{top_left}, piece{piece}, next_piece{next_piece} {
      background = createBackground();
    }

  auto spawnRandomPiece() -> void {
    updatePieceInGrid(piece);
    piece = next_piece;
    next_piece = generateRandomPiece(top_left);
  }

  auto draw(sf::RenderWindow& window) const -> void {
    // window.draw(background); // only render to reposition bacground
    // for (auto &piece: pieces) {
    //   piece.draw(window);
    // }
    piece.draw(window);

    for (auto i = 0; i < BOARD_HEIGHT; ++i) {
      for (auto j = 0; j < BOARD_WIDTH; ++j) {
        if (grid[i][j] != -1) {
          sf::Sprite sprite = blocks[grid[i][j]];
          sprite.setPosition(top_left.x + j * UNIT_SQUARE_LENGTH, top_left.y + i * UNIT_SQUARE_LENGTH);
          window.draw(sprite);
        }
      }
    }
  }

  auto next() -> void {
    // updateGrid();

    piece.moveDown();
    if (!validMove()) {
      piece.moveUp();
      // clearLines();
      spawnRandomPiece();
      if (!validMove()) {
        has_ended = true;
      }
    }
  }

  auto handleKeyboardInput(sf::Keyboard::Key input) -> void {
    switch (input) {
      case sf::Keyboard::Left:
        piece.moveLeft();
        if (!validMove()) {
          piece.moveRight();
        }
        break;
      case sf::Keyboard::Right:
        piece.moveRight();
        if (!validMove()) {
          piece.moveLeft();
        }
        break;
      case sf::Keyboard::Up:
        piece.rotateClockwise();
        if (!validMove()) {
          piece.rotateCounterclockwise();
        }
        break;
      case sf::Keyboard::Down:
        piece.rotateCounterclockwise();
        if (!validMove()) {
          piece.rotateClockwise();
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
  Piece piece; 
  Piece next_piece;
  sf::RectangleShape background;
  bool has_ended = false;
  
  auto createBackground() -> sf::RectangleShape {
    sf::RectangleShape square(sf::Vector2f(UNIT_SQUARE_LENGTH * BOARD_WIDTH, UNIT_SQUARE_LENGTH * BOARD_HEIGHT));
    square.setPosition(top_left);
    square.setFillColor(color);
    return square;
  }

  auto validMove() -> bool {
    if (piece.outsideBoundaries(top_left.x, top_left.x + (BOARD_WIDTH * UNIT_SQUARE_LENGTH), top_left.y, top_left.y + (BOARD_HEIGHT * UNIT_SQUARE_LENGTH))) {
      return false;
    }

    // for (int i = 0; i < pieces.size(); ++i) {
    //   if (i == control_index) {
    //     continue;
    //   }

    //   if (piece.collidesWithOtherPiece(pieces[i])) {
    //     return false;
    //   }
    // }

    return true;
  }

  auto updateGrid() -> void {
    BaseBoard newGrid;
    for (auto i = 0; i < BOARD_HEIGHT; ++i) {
      std::fill(newGrid[i].begin(), newGrid[i].end(), -1);
    }
    grid = newGrid;
  }

  auto updatePieceInGrid(Piece& piecex) -> void {
    const auto piece_top_left = piece.getTopleft();
    const auto piece_grid = piece.getGrid();
    const auto [gridX, gridY] = std::make_pair((piece_top_left.x - top_left.x) / UNIT_SQUARE_LENGTH, (piece_top_left.y - top_left.y) / UNIT_SQUARE_LENGTH);
    for (auto i = 0; i < piece_grid.size(); ++i) {
      for (auto j = 0; j < piece_grid[0].size(); ++j) {
        if (piece_grid[i][j]) {
          grid[gridY + i][gridX + j] = piece.getType();
        }
      }
    }
  }

  // auto clearLines() -> void {
  //   for (auto i = 0; i < BOARD_HEIGHT; ++i) {
  //     size_t count_non_zero = 0;
  //     for (auto j = 0; j < BOARD_WIDTH; ++j) {
  //       if (grid[i][j] >= 0) {
  //         count_non_zero++;
  //       }
  //     }
  //     if (count_non_zero < BOARD_WIDTH) {
  //       continue;
  //     }
  //     for (auto j = 0; j < BOARD_WIDTH; ++j) {
  //       auto& curr_piece = pieces[grid[i][j]];
  //       const auto piece_top_left = curr_piece.getTopleft();
  //       const auto [gridX, gridY] = std::make_pair((piece_top_left.x - top_left.x) / UNIT_SQUARE_LENGTH, (piece_top_left.y - top_left.y) / UNIT_SQUARE_LENGTH);
  //       curr_piece.clearGrid(i - gridY, j - gridX);
  //     }
  //   }
  // }
};

#endif
