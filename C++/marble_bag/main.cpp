#include <iostream>

#include "bag.hpp"
#include "marble.hpp"

bool testMarbleColor(std::string testColor) {
  Marble testMarble = Marble(testColor, "");
  return testMarble.color() == testColor;
}

bool testMarblePattern(std::string testPattern) {
  Marble testMarble = Marble("", testPattern);
  return testMarble.pattern() == testPattern;
}

bool testMarbleSetColor(std::string testColor) {
  Marble testMarble = Marble();
  testMarble.setColor(testColor);
  return testMarble.color() == testColor;
}

bool testMarbleSetPattern(std::string testPattern) {
  Marble testMarble = Marble();
  testMarble.setPattern(testPattern);
  return testMarble.pattern() == testPattern;
}

bool testBagAddMarble(Marble testMarble) {
  Bag testBag = Bag();
  testBag.addMarble(testMarble);
  Marble returnedMarble = testBag.getMarble();
  return (testMarble.color() == returnedMarble.color()) && (testMarble.pattern() == returnedMarble.pattern());
}

bool testBagMarbleCount(int marbleNum) {
  Bag testBag = Bag();
  for (int i = 0; i < marbleNum + 1; i++) {
    Marble newMarble = Marble();
    testBag.addMarble(newMarble);
  }
  return testBag.marbleCount() == marbleNum;
}

int main() {
  return EXIT_SUCCESS;
}