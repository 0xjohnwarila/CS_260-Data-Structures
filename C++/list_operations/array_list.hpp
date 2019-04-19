#pragma once

#include <iostream>
#include <new>

template <class T>
class ArrayList {
 private:
  T *arrList;
  int arrLength;
  bool empty(void);

 public:
  ArrayList(){};
  void add(T inVal, int inPos);
  void fill(T inArr[], int length);
  T remove(int pos);
  T get(int pos);
};

template <class T>
void ArrayList<T>::add(T inVal, int inPos) {
  if (inPos > arrLength) {
    // This is probably terribly inefficient, but its a start
    T *tempArr = new (std::nothrow) T[inPos + 1];
    if (tempArr == nullptr) {
      std::cout << "Mem allocation error" << std::endl;
      return;
    }
    for (int i = 0; i < arrLength + 1; i++) {
      tempArr[i] = arrList[i];
    }
    tempArr[inPos] = inVal;
    fill(tempArr, inPos + 1);
  } else {
    arrList[inPos] = inVal;
  }
}

template <class T>
void ArrayList<T>::fill(T inArr[], int length) {
  arrList = new (std::nothrow) T[length];
  if (arrList == nullptr) {
    std::cout << "Mem allocation error" << std::endl;
    return;
  }
  for (int i = 0; i < length; i++) {
    arrList[i] = inArr[i];
  }
}

template <class T>
T ArrayList<T>::get(int pos) {
  return arrList[pos];
}
