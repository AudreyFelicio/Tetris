#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include <iostream>
#include <vector>
#include "piece.hpp"
#include "board.hpp"

auto main() -> int {
  // std::vector<Piece> pieces = {
  //   OShape(sf::Color::Blue, {100.0f, 100.0f}),
  //   LShape(sf::Color::Blue, {200.0f, 200.0f}),
  //   IShape(sf::Color::Blue, {300.0f, 300.0f}),
  //   JShape(sf::Color::Blue, {400.0f, 400.0f}),
  //   ZShape(sf::Color::Blue, {500.0f, 500.0f}),
  //   TShape(sf::Color::Blue, {600.0f, 600.0f}),
  //   SShape(sf::Color::Blue, {700.0f, 700.0f})
  // };
  // const float LENGTH = 10.0;
  // sf::Vector2f top_left(100.0f, 100.0f);
  // sf::RectangleShape square(sf::Vector2f(LENGTH, LENGTH));
  // square.setPosition(sf::Vector2f(top_left.x + LENGTH * 1, top_left.y + LENGTH * 1));
  // square.setFillColor(sf::Color::Blue);

  std::array<std::array<bool, WIDTH>, HEIGHT> grid = 
    {{ 
      {{0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}}, 
      {{0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}}, 
      {{0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}}, 
      {{0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}}, 
      {{0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}}, 
      {{0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}}, 
      {{0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}}, 
      {{0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}}, 
      {{0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}}, 
      {{0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}},
      {{0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}}, 
      {{0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}}, 
      {{0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}}, 
      {{0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}}, 
      {{0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}},
      {{0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}}, 
      {{0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}}, 
      {{0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}}, 
      {{0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}}, 
      {{0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}}
  }};
  Board board(grid, sf::Color::White, sf::Vector2f(500.0f, 100.0f));

  auto window = sf::RenderWindow{ { 1920u, 1080u }, "Tetris" };
  window.setFramerateLimit(144);

  sf::Clock clock;
  sf::Time total_elapsed = sf::milliseconds(0);
  while (window.isOpen()) {
    total_elapsed += clock.restart();
    if (total_elapsed >= sf::milliseconds(100)) {
      board.moveDown();
      total_elapsed = sf::milliseconds(0);
    }

    for (auto event = sf::Event{}; window.pollEvent(event); ) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } 
      else if (event.type == sf::Event::KeyPressed) {
        board.handleKeyboardInput(event.key.code);
      }
    }
    window.clear();
    board.draw(window);
    window.display();
  }
}
