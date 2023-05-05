#include <SFML/Graphics.hpp>
#include "unit_square.hpp"
#include "grid.hpp"

auto main() -> int {
  UnitSquare u;
  std::array<std::array<bool, 4>, 4> grid;
  Grid g(grid, "test", sf::Vector2(0.0f, 0.0f));

  auto window = sf::RenderWindow{ { 1920u, 1080u }, "Tetris" };
  window.setFramerateLimit(144);
  while (window.isOpen()) {
    for (auto event = sf::Event{}; window.pollEvent(event); ) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    window.clear();
    window.display();
  }
}
