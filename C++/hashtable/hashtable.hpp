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

  bool linProbe;
  bool doubleHash;
  bool openIndex;

  std::vector<T> table;

  const T& nullObject = T(true);

  T walk(std::string key, size_t index) const;
  size_t hash(const std::string key, size_t size) const;
  bool indexFull(size_t index, const T& inObject) const;
  bool isCorrectIndex(std::string key, size_t index) const;
  void createTable(size_t size);
  void setCollision(const std::string& collisionHandler);
  void insert(const size_t index, const T& inObject);
  void collision(const size_t index, const T& inObject);

 public:
  // The constructor requires a size, a hashFunction to use, and a collsionHandler
  HashTable(size_t size, const std::string& collisionHandler);

  int collisionCount(void) const;
  int objectCount(void) const;

  float loadFactor(void) const;

  size_t size(void) const;

  void add(const T& inObject);
  void remove(T& inObject);
  T get(std::string key) const;
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
  const std::string key = inObject.key();
  size_t index = hash(key, size_);
  insert(index, inObject);
}

template <class T>
T HashTable<T>::get(std::string key) const {
  size_t index = hash(key, size_);
  if (isCorrectIndex(key, index))
    return table.at(index);
  else
    return walk(key, index);
}

//
// PRIVATE
// METHODS
//

template <class T>
T HashTable<T>::walk(std::string key, size_t index) const {
  for (size_t i = index; i < size_; i++) {
    if (isCorrectIndex(key, index))
      return table.at(index);
  }

  for (int i = index; i >= 0; i--) {
    if (isCorrectIndex(key, index))
      return table.at(index);
  }

  std::cerr << "Key not found" << std::endl;
}

template <class T>
bool HashTable<T>::isCorrectIndex(std::string key, size_t index) const {
  return table.at(index).key() == key;
}

template <class T>
void HashTable<T>::createTable(size_t size) {
  for (size_t i = 0; i < size; i++)
    table.push_back(nullObject);
}

template <class T>
void HashTable<T>::insert(const size_t index, const T& inObject) {
  if (indexFull(index, inObject))
    collision(index, inObject);
  else
    table.at(index) = inObject;
}

template <class T>
bool HashTable<T>::indexFull(size_t index, const T& inObject) const {
  if ((!table.at(index).isNull()) && (table.at(index).key() != inObject.key()))
    return true;
  else
    return false;
}

template <class T>
void HashTable<T>::collision(const size_t index, const T& inObject) {
  for (size_t i = index; i < size_; i++) {
    if (table.at(i).isNull()) {
      table.at(i) = inObject;
      return;
    }
  }

  // No empty after the object, go to start of table
  for (size_t i = index; i >= 0; i--) {
    if (table.at(i).isNull()) {
      table.at(i) = inObject;
      return;
    }
  }

  std::cerr << "No room for object" << std::endl;
}

template <class T>
void HashTable<T>::setCollision(const std::string& collisionHandler) {
  linProbe = (collisionHandler == "Linear Probing");
  doubleHash = (collisionHandler == "Double Hashing");
  openIndex = true;
}

template <class T>
size_t HashTable<T>::hash(const std::string key, size_t size) const {
  size_t index = 0;

  for (auto&& i : key) {
    index += i;
  }

  return index % size_;
}