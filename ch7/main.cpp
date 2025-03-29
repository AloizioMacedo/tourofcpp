#include <iostream>
#include <regex>
#include <string>

class User {
  std::string name;
  int age;

public:
  User(std::string &&name, int age) : name(std::move(name)), age(age) {}

  std::string generate_greeting() const { return "Hello, " + name + "!"; }
};

void get_pair_of_digits(const std::string &name) {
  std::regex pat(R"(\d+\s\d+)");

  std::smatch matches;
  std::regex_search(name, matches, pat);
  for (auto v : matches) {
    std::cout << v.str() << "\n";
  }
}

int main() {
  auto user = User("Aloizio", 31);

  std::cout << user.generate_greeting() + "\n";

  get_pair_of_digits("   12 3");
  return 0;
}
