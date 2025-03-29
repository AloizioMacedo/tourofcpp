#include <fstream>
#include <iostream>
#include <sstream>

int main() {
  std::ifstream f;
  f.open("input.txt");

  std::string s;
  std::ostringstream buffer;
  buffer << f.rdbuf();

  std::cout << buffer.str() << "\n";

  return 0;
}
