#include <algorithm>
#include <charconv>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
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
  auto &vec1 = pairs.vec1;
  auto &vec2 = pairs.vec2;

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

template <typename T>
std::unordered_map<T, int> get_count(const std::vector<T> &values) {
  std::unordered_map<T, int> count;
  count.reserve(700);

  for (const auto &value : values) {
    if (count.find(value) == count.end()) {
      count[value] = 1;
    } else {
      count[value] += 1;
    }
  }

  return count;
}

int solve_p2(std::ifstream &f) {
  PairOfVecs pairs = parse_contents(f);

  auto &vec1 = pairs.vec1;
  auto &vec2 = pairs.vec2;

  auto count = get_count(vec2);

  int total = 0;
  for (const auto &value : vec1) {
    if (count.find(value) != count.end()) {
      total += value * count[value];
    }
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
