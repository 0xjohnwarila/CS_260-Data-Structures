#include <iostream>

#include "bag.hpp"
#include "marble.hpp"

bool strEqual(std::string input1, std::string input2) {
  if (input1 == input2)
    return true;
  else
    return false;
}

bool testMarbleColor(std::string testColor) {
  Marble testMarble = Marble(testColor, "");
  return (strEqual(testMarble.color(), testColor));
}

bool testMarblePattern(std::string testPattern) {
  Marble testMarble = Marble("", testPattern);
  return (strEqual(testMarble.pattern(), testPattern));
}

bool testMarbleSetColor(std::string testColor) {
  Marble testMarble = Marble();
  testMarble.setColor(testColor);
  return (strEqual(testMarble.color(), testColor));
}

bool testMarbleSetPattern(std::string testPattern) {
  Marble testMarble = Marble();
  testMarble.setPattern(testPattern);
  return (strEqual(testMarble.pattern(), testPattern));
}

bool testBagAddMarble(Marble testMarble) {
  Bag testBag = Bag();
  testBag.addMarble(testMarble);
  Marble returnedMarble = testBag.getMarble();
  return (strEqual(testMarble.color(), returnedMarble.color()) && strEqual(testMarble.pattern(), returnedMarble.pattern()));
}

bool testBagMarbleCount(int marbleNum) {
  Bag testBag = Bag();
  for (int i = 0; i < marbleNum + 1; i++) {
    Marble newMarble = Marble();
    testBag.addMarble(newMarble);
  }
  if (testBag.marbleCount() == marbleNum)
    return true;
  else
    return false;
}

int main() {
  return EXIT_SUCCESS;
}