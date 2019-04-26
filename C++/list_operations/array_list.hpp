/*
Array Based List
*/
#pragma once

#include <iostream>
#include <new>

template <class T>
class ArrayList {
 private:
  T *arrList;
  int arrLength;

 public:
  ArrayList();
  void add(T inVal, int inPos);
  void fill(T inArr[], int length);
  T remove(int pos);
  T at(int pos);
};

/*
Constructor: makes a new array of type T and size 0;

I am using std::nothrow so that I can manage erros myself
*/
template <class T>
ArrayList<T>::ArrayList() {
  arrList = new (std::nothrow) T[0];
  if (arrList == nullptr) {
    std::cout << "Mem allocation error" << std::endl;
  }
}

/*
Add: puts a value into the list at position inPos. This will overwrite the current value at inPos.
If the list is too small, it will generate a new array and fill it with the old array's data. Then
it saves the new array as the primary array.
*/
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
  } else {
    arrList[inPos] = inVal;
  }
}
/*
Fill: fills the list with some input array
*/
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

/*
At:returns the value at pos
*/
template <class T>
T ArrayList<T>::at(int pos) {
  return arrList[pos];
}

/*
Remove: returns the value at pos and removes it from the list. If the list is longer than the pos, it
places 0 in pos after getting the value. If the pos is the end of the list, the list will shrink
by one.
*/
template <class T>
T ArrayList<T>::remove(int pos) {
  T temp = arrList[pos];
  if (pos == arrLength - 1) {
    T *tempArr = new (std::nothrow) T[pos + 1];
    if (tempArr == nullptr) {
      std::cout << "Mem allocation error" << std::endl;
    }
    for (int i = 0; i < arrLength + 1; i++) {
      tempArr[i] = arrList[i];
    }
    delete arrList;
    arrList = tempArr;
    delete tempArr;
  } else {
    arrList[pos] = 0;
  }

  return temp;
}