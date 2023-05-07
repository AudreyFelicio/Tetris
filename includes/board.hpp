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
#include "piece.hpp"
#include "constants.hpp"

class Board {
using BaseBoard = std::array<std::array<bool, BOARD_WIDTH>, BOARD_HEIGHT>;
public:
  static auto createNewBoard(sf::Vector2f pos) -> Board {
    std::array<std::array<bool, BOARD_WIDTH>, BOARD_HEIGHT> newGrid;
    Board board(newGrid, sf::Color::White, pos);
    return board;
  }

  Board(BaseBoard grid, sf::Color color, sf::Vector2f top_left):
    grid{grid}, color{color}, top_left{top_left} {
      background = createBackground();
    }

  auto spawnRandomPiece() -> void {
    std::random_device rng;

    std::uniform_int_distribution<size_t> color_distribution(0, 255);
    sf::Color random_color(color_distribution(rng), color_distribution(rng), color_distribution(rng));

    std::uniform_int_distribution<size_t> dist(0, BOARD_WIDTH - BASE_SIZE);
    sf::Vector2f random_position(top_left.x + dist(rng) * UNIT_SQUARE_LENGTH, top_left.y);

    Piece random_piece = generateRandomPiece(random_color, random_position);
    
    pieces.push_back(random_piece);
    control_index = pieces.size() - 1;
  }

  auto draw(sf::RenderWindow& window) const -> void {
    window.draw(background);
    for (auto &piece: pieces) {
      piece.draw(window);
    }
  }

  auto next() -> void {
    if (control_index == -1) {
      spawnRandomPiece();
      return;
    }

    if (control_index < 0 or control_index >= pieces.size()) {
      return;
    }

    pieces[control_index].moveDown();
    if (!validMove()) {
      pieces[control_index].moveUp();
      spawnRandomPiece();

      pieces[control_index].moveDown();
      if (!validMove()) {
        pieces[control_index].moveUp();
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
  

protected:
  BaseBoard grid;
  sf::Color color;
  sf::Vector2f top_left;
  std::vector<Piece> pieces;
  sf::RectangleShape background;
  int control_index = -1;
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
};

#endif
