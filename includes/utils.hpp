#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics.hpp>

sf::Color createColorFromString(const std::string& hexString) {
  // remove '#' character from the beginning of the string, if it exists
  std::string trimmedString = hexString;
  if (trimmedString[0] == '#') {
    trimmedString.erase(0, 1);
  }

  // parse the hexadecimal string to integers
  int red = std::stoi(trimmedString.substr(0, 2), nullptr, 16);
  int green = std::stoi(trimmedString.substr(2, 2), nullptr, 16);
  int blue = std::stoi(trimmedString.substr(4, 2), nullptr, 16);
  int alpha = 255; // default alpha is 255 (fully opaque)

  if (trimmedString.length() == 8) {
    alpha = std::stoi(trimmedString.substr(6, 2), nullptr, 16);
  }

  // return the resulting color
  return sf::Color(red, green, blue, alpha);
}

#endif