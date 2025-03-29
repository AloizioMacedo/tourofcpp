#include "User.h"

User::User(std::string name, int age) {
  this->name = name;
  this->age = age;
}

bool User::is_underage() const { return age < 18; }
