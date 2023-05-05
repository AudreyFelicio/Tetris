#ifndef GRID_HPP
#define GRID_HPP

#include <array>
#include <string>
#include <SFML/System.hpp>

class Grid {
public:
  Grid(std::array<std::array<bool, 4>, 4> grid, std::string color, sf::Vector2f top_left):
    grid{grid}, color{color}, top_left{top_left} {}


private:
  std::array<std::array<bool, 4>, 4> grid;
  std::string color;
  sf::Vector2f top_left;
  const float WIDTH = 5.0;
  const float HEIGHT = 5.0;
};

#endif
