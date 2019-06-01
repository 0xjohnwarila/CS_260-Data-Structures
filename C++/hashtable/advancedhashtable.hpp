// Advanced hashtable, fancy collision avoidance, chaining and good hash function.
// With perfect data, most of the primary methods (add, get, remove) would go from a O(n) to O(1)
// But in worse case, most methods are O(n). This is probably not going to be seen in real world use
// because the hashing function used is fairly decent, and the chains won't be too deep.

#pragma once

#include <array>
#include <iostream>
#include <vector>

#include "fnv.h"
#include "linked_list.hpp"
#include "person.hpp"

// Quick and dirty storage method for the index and depth an object is stored at
struct depthIndex {
  size_t index;
  size_t depth;
};

template <class T>
class AdvancedHashTable {
 private:
  int objectCount_;

  size_t size_;

  std::vector<std::vector<T>> table;

  size_t hash(const std::string key, size_t size) const;
  depthIndex find(const std::string key) const;
  bool indexFull(size_t index, const T& inObject) const;
  void createTable(size_t size);
  void insert(const size_t index, const T& inObject);
  void collision(const size_t index, const T& inObject);
  void setNull(depthIndex dIndex);

 public:
  // The constructor requires a size for the table
  AdvancedHashTable(size_t size);

  int objectCount(void) const;

  size_t size(void) const;

  void add(const T& inObject);
  void remove(std::string key);
  T get(std::string key);
};

//
// CONSTRUCTOR
//

// Constructor, put a size in
// O(n)
template <class T>
AdvancedHashTable<T>::AdvancedHashTable(size_t size) {
  createTable(size);
  objectCount_ = 0;
  size_ = size;
}

//
// PUBLIC
// METHODS
//

// Returns the number of objects in table
// O(1)
template <class T>
int AdvancedHashTable<T>::objectCount(void) const {
  return objectCount_;
}

// Returns size of table
// O(1)
template <class T>
size_t AdvancedHashTable<T>::size(void) const {
  return size_;
}

// ADD DOCUMENTATION HERE JOHN. BEFORE YOU TURN IT IN
// Takes T& inObject, generates an index from a hash of the key, then inserts it into the list
// O(n)
template <class T>
void AdvancedHashTable<T>::add(const T& inObject) {
  const std::string key = inObject.key();
  size_t index = hash(key, size_);
  insert(index, inObject);
}

// Takes a std::string key, then finds the index and depth of the object with the key and removes it
// O(n) <- because of find(key)
template <class T>
void AdvancedHashTable<T>::remove(std::string key) {
  // Find the index of the object to be removed
  // Replace it with nullObject
  depthIndex dIndex = find(key);
  if (dIndex.index != size_)
    setNull(dIndex);
}

// Takes a std::string key, finds the index and depth of the object with the key and returns it.
// If there is no matching object, it returns a nullobject.
// O(n) <- because of find(key);
template <class T>
T AdvancedHashTable<T>::get(std::string key) {
  // Find the index to get
  // Return it
  depthIndex dIndex = find(key);
  T returnPerson = T(true);
  if (dIndex.index != size_)
    returnPerson = table.at(dIndex.index).at(dIndex.depth);

  return returnPerson;
}

//
// PRIVATE
// METHODS
//

// Fills the table vector with vectors of size 1 with a nullobject in them
// O(n)
template <class T>
void AdvancedHashTable<T>::createTable(size_t size) {
  for (size_t i = 0; i < size; i++) {
    table.push_back(std::vector<T>());
    table.at(i).push_back(T(true));
  }
}

// Finds the object with the key provided.
// First it gets the index from hashing the key
// Then it walks down the index until it hits the object
// When it finds the object, it will return a struct of the index and depth
// If it does not find the object, it will return a struct with size_ as the index
// O(n)
template <class T>
depthIndex AdvancedHashTable<T>::find(const std::string key) const {
  size_t hashVal = hash(key, size_);
  size_t depth = 0;
  std::vector<T> currentList = table.at(hashVal);
  for (auto&& i : currentList) {
    if (i.key() == key)
      return {hashVal, depth};
    depth++;
  }
  return {size_, 0};
}

// Hashes the key with the hash function fnv1a.
// O(n)
template <class T>
size_t AdvancedHashTable<T>::hash(const std::string key, size_t size) const {
  uint32_t hashReturn = FNV::fnv1a(key);
  return hashReturn % size;
}

// Takes an index, and an T& inObject and places it at the appropriate depth at the index
// It will go to the index, and walk down it until it hits a nullObject or a copy
// If it finds nullObject, it will insert there and return
// If it finds a copy it will do nothing and return
// If it finds neither it will push the object to the end of the vector
// O(n)
template <class T>
void AdvancedHashTable<T>::insert(const size_t index, const T& inObject) {
  std::vector<T> currentList = table.at(index);
  size_t depth = 0;
  auto isCopy = [](const T& obj1, const T& obj2) { return (obj1.key() == obj2.key()); };
  for (auto&& i : currentList) {
    if (i.isNull()) {
      table.at(index).at(depth) = inObject;
      objectCount_++;
      return;
    }
    if (isCopy(i, inObject))
      return;
    depth++;
  }

  table.at(index).push_back(inObject);
  objectCount_++;
}

// Takes a depthIndex and sets the object there to null
// O(1)
template <class T>
void AdvancedHashTable<T>::setNull(depthIndex dIndex) {
  table.at(dIndex.index).at(dIndex.depth) = T(true);
}