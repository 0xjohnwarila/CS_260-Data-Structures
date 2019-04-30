#pragma once

template <class T>
class AutoSortArray {
 private:
  T *arrList;
  int arrLength;

  int findPos(T inVal);

  void fill(T inArr[], int length);

 public:
  AutoSortArray() : arrLength(0){};

  void add(T inVal);

  T remove(int pos);
  T at(int pos);

  int length(void);
};

/*
Private method findPos(T inVal)

Finds the correct index for the new inputed value.

complexity O(n)
*/
template <class T>
int AutoSortArray<T>::findPos(T inVal) {
  T currentVal;
  for (int i = 0; i < arrLength; i++) {
    currentVal = arrList[i];
    if (currentVal > inVal)
      return i;
  }
  return arrLength;
}

/*
Private method fill(T inArrp[], int length)

Allocates and fills the array with another array.

complexity O(n)
*/
template <class T>
void AutoSortArray<T>::fill(T inArr[], int length) {
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
Public method add(T inVal)

Adds a new value to the list. The value will be placed in acsending order.

compelxity O(n)
*/
template <class T>
void AutoSortArray<T>::add(T inVal) {
  int pos = findPos(inVal);
  T *tempArr = new T[arrLength + 1];
  for (int i = 0; i < findPos(inVal); i++) {
    tempArr[i] = arrList[i];
  }
  tempArr[pos] = inVal;
  for (int i = pos; i < arrLength; i++) {
    tempArr[i + 1] = arrList[i];
  }
  fill(tempArr, arrLength + 1);
  delete tempArr;
}

/*
Public method at(int pos)

Returns the value at position pos

complexity O(1)
*/
template <class T>
T AutoSortArray<T>::at(int pos) {
  return arrList[pos];
}