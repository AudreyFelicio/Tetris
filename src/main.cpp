#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include <iostream>
#include <vector>
#include "piece.hpp"
#include "board.hpp"
#include "game.hpp"

auto main() -> int {
  Game game;

  auto window = sf::RenderWindow{ { SCREEN_WIDTH, SCREEN_HEIGHT }, "Tetris" };
  window.setFramerateLimit(144);

  sf::Clock clock;
  sf::Time total_elapsed = sf::milliseconds(0);
  while (window.isOpen()) {
    total_elapsed += clock.restart();
    if (total_elapsed >= sf::milliseconds(100)) {
      game.next();
      total_elapsed = sf::milliseconds(0);
    }

    for (auto event = sf::Event{}; window.pollEvent(event); ) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } 
      else if (event.type == sf::Event::KeyPressed) {
        game.handleKeyboardInput(event.key.code);
      }
    }
    window.clear();
    game.draw(window);
    window.display();
  }
}
