#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <cstddef>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

constexpr float UNIT_SQUARE_LENGTH = 20.0;
constexpr size_t LARGE_SIZE = 4;
constexpr size_t MEDIUM_SIZE = 3;
constexpr size_t SMALL_SIZE = 2;
constexpr size_t BOARD_WIDTH = 8;
constexpr size_t BOARD_HEIGHT = 8;
constexpr int SCREEN_WIDTH = 590;
constexpr int SCREEN_HEIGHT= 960;
constexpr int FONT_SIZE = 23;

const sf::Color ORANGE(240, 168, 48, 255);
const sf::Color BEIGE(252, 235, 182, 255);

const std::string TITLE = "TETRIS";
const std::string SCORE = "SCORE";

const sf::Vector2f BOARD_POSITION(100.0f, 150.0f);
const sf::Vector2f SCORE_POSITION(447.0f, 95.0f);
const sf::Vector2f TITLE_POSITION(200.0f, 12.5f);

#endif
