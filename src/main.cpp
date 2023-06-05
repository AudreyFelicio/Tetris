#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include <iostream>
#include <vector>
#include "piece.hpp"
#include "board.hpp"
#include "game.hpp"
#include "utils.hpp"

auto main() -> int {
  Game game;

  auto window = sf::RenderWindow{ { SCREEN_WIDTH, SCREEN_HEIGHT }, "Tetris", sf::Style::Titlebar | sf::Style::Close};
  window.setFramerateLimit(144);

  sf::Texture background_texture;
  if (!background_texture.loadFromFile("./resources/image/Background/background.png")) {
    printf("Error in loading texture.\n");
  }
  background_texture.setSmooth(true);

  sf::Sprite background;
  background.setTexture(background_texture);
  background.setPosition(0, 0);
  background.setScale(0.93f, 0.76f);

  sf::Texture texture_brown;
  if (!texture_brown.loadFromFile("./resources/image/Blocks/brown.png")) {
    printf("Error in loading texture.\n");
  }
  texture_brown.setSmooth(true);

  blocks[0].setTexture(texture_brown);
  blocks[0].setPosition(10, 10);
  blocks[0].setScale(0.34f, 0.34f);

  sf::Texture texture_yellow;
  if (!texture_yellow.loadFromFile("./resources/image/Blocks/yellow.png")) {
    printf("Error in loading texture.\n");
  }
  texture_yellow.setSmooth(true);

 
  blocks[1].setTexture(texture_yellow);
  blocks[1].setPosition(10, 10);
  blocks[1].setScale(0.34f, 0.34f);

  sf::Texture texture_light_yellow;
  if (!texture_light_yellow.loadFromFile("./resources/image/Blocks/LIGHT_YELLOW.png")) {
    printf("Error in loading texture.\n");
  }
  texture_light_yellow.setSmooth(true);

  blocks[2].setTexture(texture_light_yellow);
  blocks[2].setPosition(10, 10);
  blocks[2].setScale(0.34f, 0.34f);

  sf::Texture texture_orange;
  if (!texture_orange.loadFromFile("./resources/image/Blocks/ORANGE.png")) {
    printf("Error in loading texture.\n");
  }
  texture_orange.setSmooth(true);

  blocks[3].setTexture(texture_orange);
  blocks[3].setPosition(10, 10);
  blocks[3].setScale(0.34f, 0.34f);

  sf::Texture texture_green;
  if (!texture_green.loadFromFile("./resources/image/Blocks/GREEN.png")) {
    printf("Error in loading texture.\n");
  }
  texture_green.setSmooth(true);

  blocks[4].setTexture(texture_green);
  blocks[4].setPosition(10, 10);
  blocks[4].setScale(0.34f, 0.34f);

  sf::Clock clock;
  sf::Time total_elapsed = sf::milliseconds(0);
  while (window.isOpen()) {
    total_elapsed += clock.restart();
    bool no_event = true;

    for (auto event = sf::Event{}; window.pollEvent(event); ) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::KeyPressed) {
        game.handleKeyboardInput(event.key.code);
      }
      no_event = false;
    }
    if (total_elapsed >= sf::milliseconds(500) && no_event) {
      game.next();
      total_elapsed = sf::milliseconds(0);
    }
    window.clear();
    window.draw(background); 
    game.draw(window);
    window.display();
  }
}
