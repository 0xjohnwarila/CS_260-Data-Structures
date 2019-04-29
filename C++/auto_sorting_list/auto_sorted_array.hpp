#pragma once

template <class T>
class AutoSortArray {
 private:
  T *arrList;
  int arrLength;

  int findPos(T inVal) {
    T currentVal;
    for (int i = 0; i < arrLength; i++) {
      currentVal = arrList[i];
      if (currentVal > inVal)
        return i;
    }
    return arrLength;
  }

 public:
  AutoSortArray() : arrLength(0){};
  void add(T inVal, int inPos);
  void add(T inVal);
  void fill(T inArr[], int length);
  T remove(int pos);
  T at(int pos);
};

template <class T>
void AutoSortArray<T>::add(T inVal, int inPos) {
  if (inPos > arrLength) {
    T *tempArr = new T[inPos + 1];
    for (int i = 0; i < arrLength; i++) {
      tempArr[i] = arrList[i];
    }
    tempArr[inPos] = inVal;
    delete arrList;
    fill(tempArr, inPos + 1);
    delete tempArr;
  } else {
    arrList[inPos] = inVal;
  }
}

/*
Fill: fills the list with some input array
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
At:returns the value at pos
*/
template <class T>
T AutoSortArray<T>::at(int pos) {
  return arrList[pos];
}