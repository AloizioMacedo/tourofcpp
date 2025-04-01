#include <fstream>
#include <iostream>
#include <string_view>

int get_number(const std::string_view &s) {
  int first_digit = -1;
  int last_digit = -1;

  for (const auto &c : s) {
    if (c >= '0' && c <= '9') {
      if (first_digit == -1) {
        first_digit = c - '0';
      }
      last_digit = c - '0';
    }
  }

  return 10 * first_digit + last_digit;
}

int solve_p1(std::ifstream &f) {
  std::string line;

  int total = 0;
  while (std::getline(f, line)) {
    total += get_number(line);
  }

  return total;
}

const char *NAMES[]{"zero", "one", "two",   "three", "four",
                    "five", "six", "seven", "eight", "nine"};

int get_number_p2(const std::string_view &s) {
  int first_digit = -1;
  int last_digit = -1;

  for (int i = 0; i < s.length(); i++) {
    for (int j = 0; j < 10; j++) {
      if (s.substr(i).rfind(NAMES[j], 0) == 0) {
        if (first_digit == -1) {
          first_digit = j;
        }
        last_digit = j;

        break;
      }
    }

    if (s[i] >= '0' && s[i] <= '9') {
      if (first_digit == -1) {
        first_digit = s[i] - '0';
      }
      last_digit = s[i] - '0';
    }
  }

  return 10 * first_digit + last_digit;
}

int solve_p2(std::ifstream &f) {
  std::string line;

  int total = 0;
  while (std::getline(f, line)) {
    total += get_number_p2(line);
  }

  return total;
}

int main() {
  std::ifstream f;
  f.open("input.txt");

  std::cout << "P1: " << solve_p1(f) << "\n";
  f.clear();
  f.seekg(0);
  std::cout << "P2: " << solve_p2(f) << "\n";
}
