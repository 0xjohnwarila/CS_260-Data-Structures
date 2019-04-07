#include "bag.hpp"
#include <algorithm>
#include <iostream>

void Bag::addMarble(Marble newMarble) {
  // Add a marble to the bag
  if (isFull())
    std::cout << "The bag is full" << std::endl;
  else
    marbles.push_back(newMarble);
}

void Bag::shuffle(void) {
  // Shuffle the marbles in the bag
  std::random_shuffle(marbles.begin(), marbles.end());
}

void Bag::printAll(void) {
  if (marbleCount() > 0) {
    // For each marble in marbles, print the marble's data
    for (auto currentMarble : marbles) {
      std::cout << "Marble color " << currentMarble.color() << ". "
                << "Marble pattern " << currentMarble.pattern() << "." << std::endl;
    }
  } else {
    std::cout << "The bag is empty." << std::endl;
  }
}

bool Bag::isFull(void) {
  // Check if the bag size is less than the maxLength
  if (marbles.size() < maxLength)
    return false;
  else
    return true;
}

int Bag::marbleCount(void) {
  // Get the size of marbles
  return marbles.size();
}

Marble Bag::getMarble(void) {
  // Get a random marble out of the bag. If there are no marbles in the bag, return
  // an empty marble.
  Marble returnMarble;
  if (marbles.empty()) {
    returnMarble = Marble();
  } else {
    shuffle();
    returnMarble = marbles.back();
    marbles.pop_back();
  }
  return returnMarble;
}