#include <algorithm>
#include <charconv>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>
#include <vector>

class Elf {
public:
  int calories = 0;

  Elf(int calories) : calories(calories) {};
};

Elf parse_elf(const std::string_view &block) {
  int total_cals = 0;

  int a = 0;
  int b = 0;

  while ((b = block.find("\n", a)) != std::string_view::npos) {
    auto cal = block.substr(a, b - a);

    int calories;
    std::from_chars(cal.begin(), cal.end(), calories);

    total_cals += calories;

    a = b + 1;
  }

  auto cal = block.substr(a);

  int calories = 0;
  std::from_chars(cal.begin(), cal.end(), calories);

  total_cals += calories;

  return Elf(total_cals);
}

std::vector<int> parse_calories(const std::string_view &contents) {
  std::vector<int> calories;

  int a = 0;
  int b = 0;

  while ((b = contents.find("\n\n", a)) != std::string_view::npos) {
    auto block = contents.substr(a, b - a);
    Elf elf = parse_elf(block);
    calories.push_back(elf.calories);

    a = b + 2;
  }

  auto block = contents.substr(a);
  Elf elf = parse_elf(block);
  calories.push_back(elf.calories);

  return calories;
}

int solve_p1(const std::string_view &contents) {
  auto calories = parse_calories(contents);
  auto max = std::max_element(calories.begin(), calories.end());

  return *max;
}

int solve_p2(const std::string_view &contents) {
  auto calories = parse_calories(contents);
  std::sort(calories.begin(), calories.end());

  auto n = calories.size();

  return calories[n - 1] + calories[n - 2] + calories[n - 3];
}

int main() {
  std::ifstream f;
  f.open("input.txt");
  std::stringstream ss;

  ss << f.rdbuf();
  auto contents = ss.str();

  auto result1 = solve_p1(contents);
  std::cout << "P1: " << result1 << "\n";

  auto result2 = solve_p2(contents);
  std::cout << "P2: " << result2 << "\n";
}
