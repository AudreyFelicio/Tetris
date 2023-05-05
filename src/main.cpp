#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include <iostream>
#include "piece.hpp"

auto main() -> int {
  OShape sq(sf::Color::Blue, {100.0f, 100.0f});
  LShape l(sf::Color::Blue, {200.0f, 200.0f});
  const float LENGTH = 10.0;
  sf::Vector2f top_left(100.0f, 100.0f);
  sf::RectangleShape square(sf::Vector2f(LENGTH, LENGTH));
  square.setPosition(sf::Vector2f(top_left.x + LENGTH * 1, top_left.y + LENGTH * 1));
  square.setFillColor(sf::Color::Blue);

  auto window = sf::RenderWindow{ { 1920u, 1080u }, "Tetris" };
  window.setFramerateLimit(144);

  sf::Clock clock;
  sf::Time total_elapsed = sf::milliseconds(0);
  while (window.isOpen()) {
    total_elapsed += clock.restart();
    if (total_elapsed >= sf::milliseconds(1'000)) {
      sq.moveDown();
      l.moveDown();
      total_elapsed = sf::milliseconds(0);
    }

    for (auto event = sf::Event{}; window.pollEvent(event); ) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::KeyPressed) {
        sq.handleKeyboardInput(event.key.code);
        l.handleKeyboardInput(event.key.code);
      }
    }
    window.clear();
    sq.draw(window);
    l.draw(window);
    window.display();
  }
}
