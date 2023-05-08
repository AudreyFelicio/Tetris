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
#include <iomanip>
#include <sstream>

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
    if (input == sf::Keyboard::Escape) {
      is_paused = !is_paused;
    } else if (input == sf::Keyboard::Space) {
      board.next();
    }

    board.handleKeyboardInput(input);
  }

private:
  sf::Font font;
  sf::Text title;
  sf::Text score;
  sf::Text level;
  bool is_paused = false;
  int current_score = 0;
  int current_level = 1;
  Board board = Board::createNewBoard(BOARD_POSITION);

  auto initFont() -> void {
    font.loadFromFile("./resources/font/telelower.ttf");
  }

  auto initTitle() -> void {
    title.setString(TITLE);
    title.setFont(font);
    title.setCharacterSize(FONT_SIZE * 2);
    title.setPosition(TITLE_POSITION);
    title.setFillColor(ORANGE);
  }

  auto initScore() -> void {
    std::ostringstream oss;
    oss << SCORE << std::setw(4) << std::setfill(' ') << std::right << current_score;
    score.setString(oss.str());
    score.setFont(font);
    score.setCharacterSize(FONT_SIZE);
    score.setPosition(SCORE_POSITION);
    score.setFillColor(BEIGE);
  }

  auto updateScore() -> void {
    std::ostringstream oss;
    oss << SCORE << std::setw(4) << std::setfill(' ') << std::right << ++current_score;
    score.setString(oss.str());
  }
};

#endif
