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
  ArrayList();
  void add(T inVal, int inPos);
  void fill(T inArr[], int length);
  T remove(int pos);
  T get(int pos);
  T take(int pos);
};

template <class T>
ArrayList<T>::ArrayList() {
  arrList = new (std::nothrow) T[0];
  if (arrList == nullptr) {
    std::cout << "Mem allocation error" << std::endl;
  }
}

template <class T>
void ArrayList<T>::add(T inVal, int inPos) {
  if (inPos > arrLength) {
    T *tempArr = new (std::nothrow) T[inPos + 1];
    if (tempArr == nullptr) {
      std::cout << "Mem allocation error" << std::endl;
      return;
    }
    for (int i = 0; i < arrLength + 1; i++) {
      tempArr[i] = arrList[i];
    }
    tempArr[inPos] = inVal;
    delete arrList;
    arrList = tempArr;
    delete tempArr;
  } else if (inPos == arrLength - 1) {
    T *tempArr = new (std::nothrow) T[inPos + 1];
  } else {
    arrList[inPos] = inVal;
  }
}

template <class T>
void ArrayList<T>::fill(T inArr[], int length) {
  arrList = new (std::nothrow) T[length];
  arrLength = length;
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

template <class T>
T ArrayList<T>::take(int pos) {
  T temp = arrList[pos];
  arrList[pos] = 0;
  return temp;
}