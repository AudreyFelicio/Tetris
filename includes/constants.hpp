#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <cstddef>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

constexpr float UNIT_SQUARE_LENGTH = 39;
constexpr size_t LARGE_SIZE = 4;
constexpr size_t MEDIUM_SIZE = 3;
constexpr size_t SMALL_SIZE = 2;
constexpr size_t BOARD_WIDTH = 7;
constexpr size_t BOARD_HEIGHT = 12;
constexpr size_t NEXT_BLOCK_X = 440;
constexpr size_t NEXT_BLOCK_Y = 160;
constexpr int SCREEN_WIDTH = 400;
constexpr int SCREEN_HEIGHT= 530;
constexpr int FONT_SIZE = 12;

const sf::Color ORANGE(240, 168, 48, 255);
const sf::Color BEIGE(252, 235, 182, 255);

const std::string TITLE = "TETRIS";
const std::string SCORE = "SCORE";

const sf::Vector2f BOARD_POSITION(12.5f, 53.5f);
const sf::Vector2f SCORE_POSITION(300.0f, 53.75f);
const sf::Vector2f TITLE_POSITION(147.5f, 10.0f);

constexpr int NO_OF_BLOCK_TYPES = 5;
sf::Sprite BLOCK_BROWN, BLOCK_GREEN, BLOCK_LIGHT_YELLOW, BLOCK_ORANGE, BLOCK_YELLOW; 
sf::Sprite blocks[] = {BLOCK_BROWN, BLOCK_GREEN, BLOCK_LIGHT_YELLOW, BLOCK_ORANGE, BLOCK_YELLOW};

#endif
