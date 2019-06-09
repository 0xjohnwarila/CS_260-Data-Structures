#pragma once

#include <algorithm>
#include <utility>
#include <vector>

template <class T>
std::pair<bool, int> findInVector(const std::vector<T>& inputVector, const T& element);