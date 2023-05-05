#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include "grid.hpp"

auto main() -> int {
  std::array<std::array<bool, 4>, 4> x {{
      {{true, false, false, false}},
      {{true, false, false, false}},
      {{true, false, false, false}},
      {{true, true, true, true}}
  }};
  Grid g(x, "#FFFFFF", sf::Vector2f(100.f, 100.f));

  const float LENGTH = 10.0;
  sf::Vector2f top_left(100.0f, 100.0f);

  sf::RectangleShape square(sf::Vector2f(LENGTH, LENGTH));
  square.setPosition(sf::Vector2f(top_left.x + LENGTH * 1, top_left.y + LENGTH * 1));
  square.setFillColor(sf::Color::Blue);

  auto window = sf::RenderWindow{ { 1920u, 1080u }, "Tetris" };
  window.setFramerateLimit(144);
  while (window.isOpen()) {
    for (auto event = sf::Event{}; window.pollEvent(event); ) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      
    }
    
    window.clear();

    for (auto &i: g.getDisplay()) {
      window.draw(i);
    }
    // window.draw(square);

    window.display();
  }
}
