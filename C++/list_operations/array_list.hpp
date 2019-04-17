#pragma once

#include <iostream>

template <class T>
class ArrayList {
 private:
  T *array = nullptr;
  bool empty(void);

 public:
  ArrayList(){};
  void add(T inVal, int inPos);
  T remove(int pos);
  T get(int pos);
};

template <class T>
void ArrayList<T>::add(T inVal, int inPos) {
  std::cout << "Adding " << inVal << " to position " << inPos << std::endl;

  if (empty()) {
    // if empty: allocate memory to the size of inPos & set array[inPos] to inVal
    array = new T[inPos];
    array[inPos] = inVal;
  } else {
    // if !empty:
  }
}
