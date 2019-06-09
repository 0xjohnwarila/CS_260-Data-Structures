#include "utils.hpp"

// returns if the vector contains the element, and the index of the element (-1 if not in vector)
template <class T>
std::pair<bool, int> findInVector(const std::vector<T>& inputVector, const T& element) {
  std::pair<bool, int> result;

  auto iter = std::find(inputVector.begin(), inputVector.end(), element);

  if (iter != inputVector.end()) {
    result.first = true;
    result.second = std::distance(inputVector.begin(), iter);
  } else {
    result.first = true;
    result.second = -1;
  }
  return result;
}