#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <cstddef>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

constexpr float UNIT_SQUARE_LENGTH = 40.0;
constexpr size_t LARGE_SIZE = 4;
constexpr size_t MEDIUM_SIZE = 3;
constexpr size_t SMALL_SIZE = 2;
constexpr size_t BOARD_WIDTH = 10;
constexpr size_t BOARD_HEIGHT = 21;
constexpr size_t NEXT_BLOCK_X = 440;
constexpr size_t NEXT_BLOCK_Y = 160;
constexpr int SCREEN_WIDTH = 590;
constexpr int SCREEN_HEIGHT= 960;
constexpr int FONT_SIZE = 23;

const sf::Color ORANGE(240, 168, 48, 255);
const sf::Color BEIGE(252, 235, 182, 255);

const std::string TITLE = "TETRIS";
const std::string SCORE = "SCORE";

const sf::Vector2f BOARD_POSITION(18.0f, 100.0f);
const sf::Vector2f SCORE_POSITION(447.0f, 95.0f);
const sf::Vector2f TITLE_POSITION(200.0f, 12.5f);

constexpr int NO_OF_BLOCK_TYPES = 5;
sf::Sprite BLOCK_BROWN, BLOCK_GREEN, BLOCK_LIGHT_YELLOW, BLOCK_ORANGE, BLOCK_YELLOW; 
sf::Sprite blocks[] = {BLOCK_BROWN, BLOCK_GREEN, BLOCK_LIGHT_YELLOW, BLOCK_ORANGE, BLOCK_YELLOW};

#endif
