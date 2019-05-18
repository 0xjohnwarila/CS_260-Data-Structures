#pragma once

#include <array>
#include <iostream>
#include <vector>

#include "linked_list.hpp"
#include "person.hpp"

template <class T>
class HashTable {
 private:
  int collisionCount_;
  int objectCount_;

  size_t size_;

  const float CRITICAL_LOAD_FACTOR = .7;

  bool linProbe;
  bool doubleHash;
  bool openIndex;

  std::vector<T> table;

  T nullObject;

  T* array(size_t inSize) const;
  size_t hash(const std::string& key, size_t size) const;
  bool loadFactorAtCritical(void) const;
  bool indexFull(size_t index, const T& inObject) const;
  void createTable(size_t size);
  void setCollision(const std::string& collisionHandler);
  void switchCollision(void);
  void rehashAll(void);
  void insert(size_t index, const T& inObject);

 public:
  // The constructor requires a size, a hashFunction to use, and a collsionHandler
  HashTable(size_t size, const std::string& collisionHandler);

  int collisionCount(void) const;
  int objectCount(void) const;

  size_t size(void) const;

  void add(const T& inObject);
  void remove(T& inObject);
  void get(std::string& key);
};

//
// CONSTRUCTOR
//

template <class T>
HashTable<T>::HashTable(size_t size, const std::string& collisionHandler) {
  createTable(size);
  setCollision(collisionHandler);
  collisionCount_ = 0;
  objectCount_ = 0;
  size_ = size;
}

//
// PUBLIC
// METHODS
//

template <class T>
int HashTable<T>::collisionCount(void) const {
  return collisionCount_;
}

template <class T>
int HashTable<T>::objectCount(void) const {
  return objectCount_;
}

template <class T>
size_t HashTable<T>::size(void) const {
  return size_;
}

template <class T>
void HashTable<T>::add(const T& inObject) {
  const std::string& key = inObject.key();
  size_t index = hash(key, size_);
  insert(index, inObject);

  if (loadFactorAtCritical() && openIndex)
    switchCollision();
}

//
// PRIVATE
// METHODS
//

template <class T>
void HashTable<T>::createTable(size_t size) {
  for (size_t i = 0; i < size; i++)
    table.push_back(T(true));
}

template <class T>
void HashTable<T>::insert(size_t index, const T& inObject) {
  if (indexFull(index, inObject))
    collision(index, inObject);
  else
    table[index] = inObject;
}

template <class T>
bool HashTable<T>::indexFull(size_t index, const T& inObject) const {
  if (!table.at(index).isNull() && table.at(index).key() != inObject.key())
    return true;
  else
    return false;
}

template <class T>
void collision(size_t index, T& inObject) {
}

template <class T>
void HashTable<T>::setCollision(const std::string& collisionHandler) {
  linProbe = (collisionHandler == "Linear Probing");
  doubleHash = (collisionHandler == "Double Hashing");
  openIndex = true;
}

template <class T>
void HashTable<T>::rehashAll(void) {
  std::vector<T> tempVector = table;
  table.empty();
  for (size_t i = 0; i < size_; i++)
    add(tempVector[i]);
}

template <class T>
T* HashTable<T>::array(size_t inSize) const {
  T* newArray = new (std::nothrow) T[inSize];
  if (newArray == nullptr)
    std::cerr << "Mem allocation error" << std::endl;
  return newArray;
}

template <class T>
void HashTable<T>::switchCollision(void) {
  openIndex = false;
  rehashAll();
}

template <class T>
size_t HashTable<T>::hash(const std::string& key, size_t size) const {
  size_t index = 0;

  for (auto&& i : key) {
    index += i;
  }

  return index % size_;
}

template <class T>
bool HashTable<T>::loadFactorAtCritical(void) const {
  float loadFactor = objectCount_ / size_;

  if (loadFactor > CRITICAL_LOAD_FACTOR)
    return true;

  return false;
}
