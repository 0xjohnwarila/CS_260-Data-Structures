// I think everything works, if you try to put more than the max number of
// marbles it will tell you that you can't. If you try to get from an empty
// bag it will give you an empty marble.
// NOTE:
//       I am using empty marbles to signify a NULL value. I was not sure how
//       to gracefuly handle returning no value from a method that returns
//       a custom type.
//
// The design of this program is intended to allow for the different classes
// to be used seperatly. This is most easy to do with the marble class, as
// it is completely unaware of the bag class.
//
// The bag class would need some work to accept different objects put into
// it. Maybe I will rewrite it with templating. Although some methods that
// use marble specific methods would be difficult to handle.

#include <iostream>

#include "bag.hpp"
#include "marble.hpp"

// Testing functions. Most of these just make sure that the basic methods
// do what they are supposed to. I don't think they really deserve much
// comment.
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
  // Fill the bag with marbles to test if the count works.
  for (int i = 0; i < marbleNum; i++) {
    Marble newMarble = Marble("RED", "SWIRL");
    testBag.addMarble(newMarble);
  }
  std::cout << testBag.marbleCount() << std::endl;
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
            << testBagMarbleCount(65) << std::endl;

  Bag testBag = Bag();

  // Just some manual testing here...
  testBag.addMarble(testMarble);
  testBag.printAll();
  Marble returnedMarble = testBag.getMarble();
  testBag.printAll();
  std::cout << testBag.marbleCount() << std::endl;
  std::cout << returnedMarble.color() << std::endl;
  Marble emptyMarble = testBag.getMarble();
  std::cout << emptyMarble.color() << std::endl;

  // NOTE: I use EXIT_SUCCESS rather than 0. This comes from habits built
  //       after working through a textbook on high performance computing
  //       in C++ and Fortran. If you don't like it, I will write a script
  //       that replaces it before I submit in the future. Just let me know.
  return EXIT_SUCCESS;
}