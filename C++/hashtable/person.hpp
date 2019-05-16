#pragma once

#include <string>

class Person {
 private: 
  std::string key_;

  float gradePointAverage_;
 public:
  Person(std::string key, float gradePointAverage);

  std::string key(void);

  float gradePointAverage(void);
};
