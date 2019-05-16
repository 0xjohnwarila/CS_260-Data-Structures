#pragma once

#include <array>
#include <iostream>

#include "person.hpp"

template <class T>
class HashTable {
 private:
  const std::string SHA3_256_ = "SHA3-256";
  const std::string MD5_ = "MD5";
  const std::string NAIVE_ = "Naive";
  int collisionCount_;
  int objectCount_;

  T *table;
 public:
  // The constructor requires a size, a hashFunction to use, and a collsionHandler
  HashTable(size_t size, const std::string &hashFunction, const std::string &collisionHandler);

  int collisionCount(void) const;
  int objectCount(void) const;

  void add(T inObject);
  void remove(T inObject);
  void get(std::string key);
};


template <class T>
HashTable<T>::HashTable(size_t size, const std::string &hashFunction, const std::string &collisionHandler) {
  std::cout << "Making a Hash Table of size " << size << " using Hash Function " << hashFunction << " and Collision Handler " << collisionHandler << "." << std::endl;

  table = new (std::nothrow) T[size];
  if(table == nullptr) {
    std::cerr << "Mem allocation error" << std::endl;
  }
}
