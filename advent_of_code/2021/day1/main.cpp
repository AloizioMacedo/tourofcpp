#include <fstream>
#include <iostream>

int solve_p1(std::ifstream &f) {
  std::string line;

  int total = 0;

  int previous = 0;

  int i = 0;
  while (std::getline(f, line)) {
    int n = std::stoi(line);

    if (i == 0) {
      previous = n;
      i++;

      continue;
    }

    if (n > previous) {
      total++;
    }

    previous = n;
    i++;
  }

  return total;
}

int solve_p2(std::ifstream &f) {
  std::string line;
  line.reserve(10);

  int total = 0;

  int previous = 0;

  int a = 0;
  int b = 0;
  int c = 0;

  int i = 0;
  while (std::getline(f, line)) {
    int n = std::stoi(line);

    if (i == 0) {
      c = n;
      i++;

      continue;
    } else if (i == 1) {
      b = c;
      c = n;

      i++;

      continue;
    } else if (i == 2) {
      a = b;
      b = c;
      c = n;
      i++;

      continue;
    }

    previous = a;
    a = b;
    b = c;
    c = n;

    if (a + b + c > previous + a + b) {
      total++;
    }

    i++;
  }

  return total;
}

int main() {
  std::ifstream f;
  f.open("input.txt");

  std::cout << "P1: " << solve_p1(f) << "\n";
  f.clear();
  f.seekg(0);
  std::cout << "P1: " << solve_p2(f) << "\n";
}
