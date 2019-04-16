#pragma once

#include <iostream>

template <class T>
class ArrayList {
 private:
  T *array = nullptr;

 public:
  ArrayList(){};
  void add(T inVal, int inPos);
  T remove(int pos);
  T get(int pos);
};

template <class T>
void ArrayList<T>::add(T inVal, int inPos) {
  std::cout << "Adding " << inVal << " to position " << inPos << std::endl;
}
