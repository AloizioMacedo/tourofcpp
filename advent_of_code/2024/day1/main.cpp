#include <algorithm>
#include <charconv>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

class Pair {
public:
  int x;
  int y;

  Pair(int x, int y) : x(x), y(y) {}
};

class PairOfVecs {
public:
  std::vector<int> vec1;
  std::vector<int> vec2;

  PairOfVecs(std::vector<int> vec1, std::vector<int> vec2)
      : vec1(std::move(vec1)), vec2(std::move(vec2)) {}
};

Pair parse_line(const std::string_view &line) {
  auto space_pos = line.find("   ");

  auto a = line.substr(0, space_pos);
  auto b = line.substr(space_pos + 3);

  int x;
  std::from_chars(a.begin(), a.end(), x);
  int y;
  std::from_chars(b.begin(), b.end(), y);

  return Pair(x, y);
}

PairOfVecs parse_contents(std::ifstream &f) {
  std::string line;

  // Since we know the input is 1000 lines long, this helps prevent
  // some unnecessary reallocations.
  // Note that this is _not_ a necessity to guarantee correct behavior,
  // just a microoptimization given that we know the input.
  std::vector<int> vec1;
  vec1.reserve(1000);
  std::vector<int> vec2;
  vec2.reserve(1000);

  while (std::getline(f, line)) {
    Pair pair = parse_line(line);

    vec1.push_back(pair.x);
    vec2.push_back(pair.y);
  }

  return PairOfVecs(std::move(vec1), std::move(vec2));
}

int solve_p1(std::ifstream &f) {
  PairOfVecs pairs = parse_contents(f);
  auto vec1 = std::move(pairs.vec1);
  auto vec2 = std::move(pairs.vec2);

  std::sort(vec1.begin(), vec1.end());
  std::sort(vec2.begin(), vec2.end());

  int total = 0;
  // Both vectors have the same size by construction.
  // See `parse_contents`.
  for (int i = 0; i < vec1.size(); i++) {
    total += std::abs(vec1[i] - vec2[i]);
  }

  return total;
}

int main() {
  std::ifstream f;
  f.open("input.txt");

  auto result1 = solve_p1(f);
  std::cout << "P1: " << result1 << "\n";
}
