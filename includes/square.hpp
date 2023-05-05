#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "piece.hpp"
#include <string>
#include <SFML/System.hpp>

class Square : public Piece {
public:
  Square(std::string color, sf::Vector2f top_left):
    Piece{{{ {{1, 1, 0, 0}}, {{1, 1, 0, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}} }}, color, top_left, PieceType::SQUARE} {}
};

#endif
