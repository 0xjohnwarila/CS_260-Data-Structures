// Advanced hashtable, fancy collision avoidance, chaining and good hash function.

#pragma once

#include <array>
#include <iostream>
#include <vector>

#include "fnv.h"
#include "linked_list.hpp"
#include "person.hpp"

struct depthIndex {
  size_t index;
  size_t depth;
};

template <class T>
class AdvancedHashTable {
 private:
  int collisionCount_;
  int objectCount_;

  size_t size_;

  std::vector<LinkedList<T>> table;

  size_t hash(const std::string key, size_t size) const;
  depthIndex find(const std::string key) const;
  bool indexFull(size_t index, const T& inObject) const;
  bool isCorrectIndex(std::string key, size_t index) const;
  void createTable(size_t size);
  void insert(const size_t index, const T& inObject);
  void collision(const size_t index, const T& inObject);
  void removeFromTable(size_t index);

 public:
  // The constructor requires a size for the table
  AdvancedHashTable(size_t size);

  int collisionCount(void) const;
  int objectCount(void) const;

  float loadFactor(void) const;

  size_t size(void) const;

  void add(const T& inObject);
  void remove(std::string key);
  T get(std::string key) const;
};

//
// CONSTRUCTOR
//

template <class T>
AdvancedHashTable<T>::AdvancedHashTable(size_t size) {
  createTable(size);
  collisionCount_ = 0;
  objectCount_ = 0;
  size_ = size;
}

//
// PUBLIC
// METHODS
//

// Returns the number of collisions O(1)
template <class T>
int AdvancedHashTable<T>::collisionCount(void) const {
  return collisionCount_;
}

// Returns the number of objects in table O(1)
template <class T>
int AdvancedHashTable<T>::objectCount(void) const {
  return objectCount_;
}

// Returns size of table O(1)
template <class T>
size_t AdvancedHashTable<T>::size(void) const {
  return size_;
}

// Returns load factor of table O(1)
template <class T>
float AdvancedHashTable<T>::loadFactor(void) const {
  return (objectCount_ / size_);
}

// ADD DOCUMENTATION HERE JOHN. BEFORE YOU TURN IT IN
template <class T>
void AdvancedHashTable<T>::add(const T& inObject) {
  const std::string key = inObject.key();
  size_t index = hash(key, size_);
  insert(index, inObject);
}

template <class T>
void AdvancedHashTable<T>::remove(std::string key) {
  // Find the index of the object to be removed
  // Replace it with nullObject
}

template <class T>
T AdvancedHashTable<T>::get(std::string key) const {
  // Find the index to get
  // Return it
  depthIndex dIndex = find(key);
  if (dIndex.index != size_)
    return table.at(dIndex.index).get(dIndex.depth);
}

//
// PRIVATE
// METHODS
//

template <class T>
depthIndex AdvancedHashTable<T>::find(const std::string key) const {
  size_t hashVal = hash(key);
  LinkedList& currentList = table.at(hashVal);

  for (size_t depth = 0; depth < currentList.size(); depth++) {
    if (currentList.get(depth).key() == key) {
      return {hashVal, depth};
    }
  }
}

template <class T>
size_t AdvancedHashTable<T>::hash(const std::string key, size_t size) const {
  uint32_t hashReturn = FNV::fnv1a(key);
  return hashReturn % size;
}

template <class T>
void AdvancedHashTable<T>::insert(const size_t index, const T& inObject) {
  auto isCopy = [](T& obj1, T& obj2) { return (obj1.key() == obj2.key()); };
  T currentObject;
  for (size_t depth = 0; depth < table.at(index).size(); depth++) {
    currentObject = table.at(index).get(depth);
    if (currentObject.isNull()) {
      table.at(index).remove(depth);
      table.at(index).insert(inObject, depth);
      return;
    }
    if (isCopy(currentObject, inObject))
      return;
  }
}