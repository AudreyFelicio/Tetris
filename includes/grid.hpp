#ifndef GRID_HPP
#define GRID_HPP

#include <array>
#include <string>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using BaseSquare = std::array<std::array<bool, 4>, 4>;

class Grid {
public:
  Grid(BaseSquare grid, std::string color, sf::Vector2f top_left):
    grid{grid}, color{color}, top_left{top_left} {}

  auto getDisplay() -> std::vector<sf::RectangleShape> {
    std::vector<sf::RectangleShape> toDisplay;

    for (int row = 0; row < 4; row++) {
      for (int col = 0; col < 4; col++) {
        if (grid[row][col]) {
          sf::RectangleShape square(sf::Vector2f(LENGTH, LENGTH));
          square.setPosition(sf::Vector2f(top_left.x + LENGTH * col, top_left.y + LENGTH * row));
          square.setFillColor(sf::Color::Blue);
          toDisplay.push_back(square);
        }
      }
    }

    return toDisplay;
  }

private:
  BaseSquare grid;
  std::string color;
  sf::Vector2f top_left;
  const float LENGTH = 5.0;
};

#endif
