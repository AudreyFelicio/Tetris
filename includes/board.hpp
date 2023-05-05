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
using BaseBoard = std::array<std::array<bool, WIDTH>, HEIGHT>;
public:

protected:
  BaseBoard grid;
  sf::Color color;
  sf::Vector2f top_left;
  std::vector<Piece> pieces;
  
  Board(BaseBoard grid, sf::Color color, sf::Vector2f top_left):
    grid{grid}, color{color}, top_left{top_left} {}
  
  auto spawnRandomPiece() -> void {
    std::random_device rng;
    std::uniform_int_distribution<size_t> dist(0, WIDTH - BASE_SIZE);
    LShape random_piece(sf::Color::Blue, sf::Vector2f(dist(rng) * UNIT_SQUARE_LENGTH, 0.0));
    pieces.push_back(random_piece);
  }
};

#endif
