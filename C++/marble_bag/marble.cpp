// Implementation of Marble class

#include "marble.hpp"

// Constructors

Marble::Marble(void) {
  // Empty constructor. Used for error handling
  marbleColor = "";
  marblePattern = "";
}

Marble::Marble(std::string color, std::string pattern) {
  // Constructor with color and pattern inputs. This is what should always be
  // used by the object, except for specific error handling reasons.
  marbleColor = color;
  marblePattern = pattern;
}

// Setters for Marble color and pattern

void Marble::setColor(std::string color) {
  marbleColor = color;
}

void Marble::setPattern(std::string pattern) {
  marblePattern = pattern;
}

// Getters for Marble color and pattern

std::string Marble::color(void) {
  return marbleColor;
}

std::string Marble::pattern(void) {
  return marblePattern;
}