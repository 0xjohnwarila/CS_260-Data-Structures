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
  for (int i = 0; i < marbleNum; i++) {
    Marble newMarble = Marble();
    testBag.addMarble(newMarble);
  }
  return testBag.marbleCount() == marbleNum;
}

int main() {
  Marble testMarble = Marble("RED", "SWIRL");
  // The values here don't really matter. The console should output all 1's if
  // everything has gone correctly.
  std::cout << testMarbleColor("RED") << std::endl
            << testMarblePattern("SWIRL") << std::endl
            << testMarbleSetColor("RED") << std::endl
            << testMarbleSetPattern("SWIRL") << std::endl
            << testBagAddMarble(testMarble) << std::endl
            << testBagMarbleCount(64) << std::endl;
  return EXIT_SUCCESS;
}