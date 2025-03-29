#include <string>

class User {
public:
  User(std::string name, int age);
  bool is_underage() const;
  std::string name;
  int age;
};
