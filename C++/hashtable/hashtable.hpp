#pragma once

#include <array>
#include <iostream>

#include "person.hpp"

template <class T>
class HashTable {
 private:
  int collisionCount_;
  int objectCount_;

  bool linProbe;
  bool doubleHash;
  bool chaining;

  T *table;

  void createTable(const size_t size);
  void setCollision(const std::string& collisionHandler);
 public:
  // The constructor requires a size, a hashFunction to use, and a collsionHandler
  HashTable(size_t size, const std::string& collisionHandler);

  int collisionCount(void) const;
  int objectCount(void) const;

  void add(T& inObject);
  void remove(T& inObject);
  void get(std::string& key);
};


template <class T>
HashTable<T>::HashTable(size_t size, const std::string& collisionHandler) {
  createTable(size);
  setCollision(collisionHandler);
  collisionCount_ = 0;
  objectCount_ = 0;
}


//
// PRIVATE
// METHODS
//

template <class T>
void HashTable<T>::createTable(const size_t size) {
  table = new (std::nothrow) T[size];
  if (table == nullptr)
    std::cerr << "Mem allocation error" << std::endl;
}

template <class T>
void HashTable<T>::setCollision(const std::string& collisionHandler) {
  linProbe = (collisionHandler == "Linear Probing");
  doubleHash = (collisionHandler == "Double Hashing");
  chaining = (collisionHandler == "Chaining");
}
