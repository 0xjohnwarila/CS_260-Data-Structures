// Definition of Marble class

#pragma once

#include <string>

class Marble {
 private:
  // Data stored: Color and pattern as strings.
  std::string marbleColor;
  std::string marblePattern;

 public:
  Marble(void);
  Marble(std::string color, std::string pattern);

  std::string color(void);
  std::string pattern(void);

  void setColor(std::string color);
  void setPattern(std::string pattern);
};
