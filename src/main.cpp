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

  auto window = sf::RenderWindow{ { SCREEN_WIDTH, SCREEN_HEIGHT }, "Tetris", sf::Style::Titlebar | sf::Style::Close};
  window.setFramerateLimit(144);

  sf::Texture background_texture;
  if (!background_texture.loadFromFile("./resources/image/Background/background_smooth_no_text.png")) {
    printf("Error in loading texture.\n");
  }
  background_texture.setSmooth(true);

  sf::Sprite background;
  background.setTexture(background_texture);
  background.setPosition(0, 0);
  background.setScale(0.5f, 0.5f);

  sf::Clock clock;
  sf::Time total_elapsed = sf::milliseconds(0);
  while (window.isOpen()) {
    total_elapsed += clock.restart();
    if (total_elapsed >= sf::milliseconds(500)) {
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
    window.draw(background); 
    game.draw(window);
    window.display();
  }
}
