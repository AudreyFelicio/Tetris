#include <SFML/Graphics.hpp>
#include "unit_square.hpp"

auto main() -> int {
  UnitSquare u;

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
