#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

int to_priority(char c) {
  if (c >= 'a' && c <= 'z') {
    return c - 'a' + 1;
  } else {
    return c - 'A' + 27;
  }
}

class Rucksack {
public:
  std::string_view part1;
  std::string_view part2;

  Rucksack(std::string_view part1, std::string_view part2)
      : part1(part1), part2(part2) {}

  char get_intersection() {
    for (const auto &v : part1) {
      if (part2.find(v) != std::string_view::npos) {
        return v;
      }
    }

    return -1;
  }

  int get_priority() { return to_priority(get_intersection()); }
};

Rucksack build_rucksack_from_line(const std::string_view &line) {
  auto n = line.size();

  auto part1 = line.substr(0, n / 2);
  auto part2 = line.substr(n / 2);

  return Rucksack(part1, part2);
}

int solve_p1(std::ifstream &f) {
  std::string line;
  line.reserve(50);

  int total = 0;
  while (std::getline(f, line)) {
    auto rucksack = build_rucksack_from_line(line);

    total += rucksack.get_priority();
  }

  return total;
}

class ElfGroup {
public:
  std::string_view sack1;
  std::string_view sack2;
  std::string_view sack3;

  ElfGroup(std::string_view sack1, std::string_view sack2,
           std::string_view sack3)
      : sack1(sack1), sack2(sack2), sack3(sack3) {}

  char get_badge() {
    for (const auto &v : sack1) {
      if (sack2.find(v) != std::string_view::npos &&
          sack3.find(v) != std::string_view::npos) {
        return v;
      }
    }

    return -1;
  }

  int get_priority() { return to_priority(get_badge()); }
};

int solve_p2(std::ifstream &f) {
  std::string line0;
  line0.reserve(50);
  std::string line1;
  line1.reserve(50);
  std::string line2;
  line2.reserve(50);

  int total = 0;
  int line_mod = 0;
  while (true) {
    if (line_mod == 0) {
      if (!std::getline(f, line0)) {
        break;
      };
    } else if (line_mod == 1) {
      if (!std::getline(f, line1)) {
        break;
      };
    } else {
      if (!std::getline(f, line2)) {
        break;
      };
      auto elf = ElfGroup(line0, line1, line2);
      total += elf.get_priority();
    }

    line_mod = (line_mod + 1) % 3;
  }

  return total;
}

int main() {
  std::ifstream f;
  f.open("input.txt");

  auto result1 = solve_p1(f);
  std::cout << "P1: " << result1 << "\n";

  f.clear();
  f.seekg(0);

  auto result2 = solve_p2(f);
  std::cout << "P2: " << result2 << "\n";
}
