#ifndef PIECE_HPP
#define PIECE_HPP

#include <array>
#include "grid.hpp"

enum class PieceType {
  LINE,
  REVERSE_L,
  L,
  SQUARE,
  Z,
  REVERSE_Z,
  T
};

class Piece {
public:
  auto draw(sf::RenderWindow& window) -> void {
    for (const auto& pixel : grid.getDisplay()) {
      window.draw(pixel);
    }
  }

protected:
  Grid grid;
  PieceType type;

  Piece(BaseSquare square, std::string color, sf::Vector2f top_left, PieceType type):
    grid{square, color, top_left}, type{type} {}
};

#endif
