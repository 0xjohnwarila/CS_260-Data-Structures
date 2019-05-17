#pragma once

#include <array>
#include <iostream>

#include "person.hpp"

template <class T>
class HashTable {
 private:
  int collisionCount_;
  int objectCount_;

  size_t size_;

  static const float criticalLoadFactor;

  bool linProbe;
  bool doubleHash;
  bool openIndex;

  T *table;
  
  size_t hash(std::string& key, size_t size) const;
  bool loadFactorAtCritical(void) const;
  void createTable(const size_t size);
  void setCollision(const std::string& collisionHandler);
  void switchCollision(void);
  void rehashAll(void);
 public:
  // The constructor requires a size, a hashFunction to use, and a collsionHandler
  HashTable(size_t size, const std::string& collisionHandler);

  int collisionCount(void) const;
  int objectCount(void) const;
  
  size_t size(void) const;

  void add(T& inObject);
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
int HashTable<T>::collisionCount(void) const{
  return collisionCount_;
}

template <class T>
int HashTable<T>::objectCount(void) const{
  return objectCount_;
}

template <class T>
size_t  HashTable<T>::size(void) const {
  return size_;
}

template <class T>
void HashTable<T>::add(T& inObject) {
  std::string& key = inObject.key();
  size_t index = hash(key, size_);
  insert(index, inObject);
  
  if (loadFactorAtCritical())
    switchCollision();
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
  openIndex = true;
}

template <class T>
void HashTable<T>::switchCollision(void) {
  openIndex = false;
  rehashAll();
}

template <class T>
size_t HashTable<T>::hash(std::string& key, size_t size) const{

}

template <class T>
bool HashTable<T>::loadFactorAtCritical(void) const{
  float loadFactor = objectCount / size;

  if (loadFactor > criticalLoadFactor)
    return true;
  
  return false;
}
