#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <iostream>
#include <piece.hpp>
#include <vector>

class Board {

static constexpr float LENGTH = 5.0;
static constexpr size_t BASE_SIZE = 4, WIDTH = 10, HEIGHT = 20;
using BaseBoard = std::array<std::array<bool, WIDTH>, HEIGHT>;

public:
  
  

protected:
  BaseBoard grid;
  sf::Color color;
  sf::Vector2f top_left;
  std::vector<Piece> pieces;
  
  Board(BaseBoard grid, sf::Color color, sf::Vector2f top_left):
    grid{grid}, color{color}, top_left{top_left} {}
  
  auto spawnRandomPiece() {
    srand((unsigned) time(NULL));
    LShape random_piece(sf::Color::Blue, sf::Vector2f(rand() % (WIDTH - BASE_SIZE) * LENGTH, 0.0));
    pieces.push_back(random_piece);
  }
};

#endif
