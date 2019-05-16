#pragma once

#include <string>

/* Person Class
 *
 * Stores a key (usually the person's name) and a GPA
 *
*/
class Person {
 private: 
  std::string key_;

  float gradePointAverage_;
 public:
  Person();
  Person(std::string key, float gradePointAverage);

  std::string key(void);

  float gradePointAverage(void);
};
