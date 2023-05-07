#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <cstddef>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

constexpr float UNIT_SQUARE_LENGTH = 10.0;
constexpr size_t BASE_SIZE = 4;
constexpr size_t BOARD_WIDTH = 15;
constexpr size_t BOARD_HEIGHT = 25;
constexpr int SCREEN_WIDTH = 590;
constexpr int SCREEN_HEIGHT= 960;
constexpr int FONT_SIZE = 23;

sf::Color ORANGE(240,168,48,255);
sf::Color BEIGE(252, 235, 182, 255);

std::string TITLE = "TETRIS";
std::string SCORE = "SCORE";

sf::Vector2f BOARD_POSITION(100.0f, 150.0f);
sf::Vector2f SCORE_POSITION(447.0f, 95.0f);
sf::Vector2f TITLE_POSITION(200.0f, 12.5f);

#endif
