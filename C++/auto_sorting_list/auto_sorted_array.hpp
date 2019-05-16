/*
Everything is O(n). Keeps stuff in order. You can take things out. You can put things in.
*/
#pragma once

template <class T>
class AutoSortArray {
 private:
  T *arrList;
  size_t arrLength;

  size_t findPos(T inVal);

  void fill(T inArr[], int length);

 public:
  AutoSortArray() : arrLength(0){};

  void add(T inVal);

  T remove(size_t pos);
  T at(size_t pos);

  int length(void);
};

/*
Private method findPos(T inVal)

Finds the correct index for the new inputed value.

complexity O(n)
*/
template <class T>
size_t AutoSortArray<T>::findPos(T inVal) {
  T currentVal;
  for (size_t i = 0; i < arrLength; i++) {
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
  size_t pos = findPos(inVal);
  T *tempArr = new T[arrLength + 1];
  for (size_t i = 0; i < pos; i++) {
    tempArr[i] = arrList[i];
  }
  tempArr[pos] = inVal;
  for (size_t i = pos; i < arrLength; i++) {
    tempArr[i + 1] = arrList[i];
  }
  fill(tempArr, arrLength + 1);
  delete tempArr;
}

/*
Public method at(size_t pos)

Returns the value at index pos

complexity O(1)
*/
template <class T>
T AutoSortArray<T>::at(size_t pos) {
  return arrList[pos];
}

/*
Public method remove(size_t pos)

Removes a value from the array at index pos, then returns value.
If pos is beyond the array, it returns 0.

complexity O(n)
*/
template <class T>
T AutoSortArray<T>::remove(size_t pos) {
  if (pos >= arrLength)
    return 0;
  T returnData = arrList[pos];

  T *tempArr = new T[arrLength - 1];
  for (size_t i = 0; i < pos; i++) {
    tempArr[i] = arrList[i];
  }

  for (size_t i = pos + 1; i < arrLength; i++) {
    tempArr[i - 1] = arrList[i];
  }
  fill(tempArr, arrLength - 1);
  delete tempArr;
  return returnData;
}