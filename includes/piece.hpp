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
  Piece() = delete;

protected:
  Grid grid;
  PieceType type;
};

#endif
