#ifndef GAME_HPP
#define GAME_HPP

#include <array>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <random>
#include "piece.hpp"
#include "board.hpp"
#include "constants.hpp"

class Game {
public:
  Game() {
    initFont();
    initTitle();
    initScore();
  }

  auto next() -> void {
    if (is_paused) {
      return;
    }

    board.next();
    if (board.getHasEnded()) {
      resetGame();
    }
    updateScore();
  }

  auto draw(sf::RenderWindow& window) -> void {
    window.draw(title);
    window.draw(score);
    board.draw(window);
  }

  auto resetGame() -> void {
    current_score = 0;
    board = Board::createNewBoard(BOARD_POSITION);
  }

  auto handleKeyboardInput(sf::Keyboard::Key input) -> void {
    if (input == sf::Keyboard::Space) {
      is_paused = !is_paused;
    }

    board.handleKeyboardInput(input);
  }

protected:
  sf::Font font;
  sf::Text title;
  sf::Text score;
  bool is_paused = false;
  int current_score = 0;
  Board board = Board::createNewBoard(BOARD_POSITION);

  auto initFont() -> void {
    font.loadFromFile("./Roboto-Black.ttf");
  }

  auto initTitle() -> void {
    title.setString(TITLE);
    title.setFont(font);
    title.setCharacterSize(FONT_SIZE);
    title.setPosition(TITLE_POSITION);
    title.setFillColor(sf::Color::Red);
  }

  auto initScore() -> void {
    score.setString(SCORE + " " + std::to_string(current_score));
    score.setFont(font);
    score.setCharacterSize(FONT_SIZE);
    score.setPosition(SCORE_POSITION);
    score.setFillColor(sf::Color::Red);
  }

  auto updateScore() -> void {
    score.setString(SCORE + " " + std::to_string(++current_score));
  }
};

#endif
