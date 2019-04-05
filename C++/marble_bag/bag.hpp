// Definition of Bag class

#pragma once

#include <vector>
#include "marble.hpp"

class Bag {
 private:
  // Data stored: Integer representing max number of marbles
  //              Vector of marbles
  const long unsigned int maxLength = 64;

  std::vector<Marble> marbles;

  // Private Methods
  bool isFull(void);
  void shuffle(void);

 public:
  Marble getMarble(void);

  int marbleCount(void);

  void printAll(void);
  void addMarble(Marble newMarble);
};
