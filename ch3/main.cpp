#include "User.h"
#include <iostream>

void warn(const User &user) {
  if (user.is_underage()) {
    std::cout << "The user is underage!!\n";
  }
}

int main() {
  std::string name = "John Doe";
  auto user = User(name, 17);

  warn(user);
}
