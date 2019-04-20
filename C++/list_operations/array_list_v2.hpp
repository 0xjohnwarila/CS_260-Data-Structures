#pragma once

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
  T take(int pos);
};

template <class T>
ArrayList<T>::ArrayList() {
}