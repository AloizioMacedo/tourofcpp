#include <charconv>
#include <fstream>
#include <iostream>
#include <regex>
#include <string_view>
#include <vector>

class Mul {
public:
  int x;
  int y;

  Mul(int x, int y) : x(x), y(y) {}

  int apply() const { return x * y; }
};

class MulBlock {
private:
  std::string_view block;

public:
  MulBlock(std::string_view block) : block(block) {}

  Mul to_mul() {
    int open_parens_pos = block.find("(");
    int comma_pos = block.find(",");
    int close_parens_pos = block.find(")");

    auto first =
        block.substr(open_parens_pos + 1, comma_pos - (open_parens_pos + 1));
    auto second =
        block.substr(comma_pos + 1, close_parens_pos - (comma_pos + 1));

    int x = 0;
    std::from_chars(first.begin(), first.end(), x);
    int y = 0;
    std::from_chars(second.begin(), second.end(), y);

    return Mul(x, y);
  }
};

// Seems that regex_search does not work with `string_view`.
// Why is `string` really needed? Why is a string_view not enough??
std::vector<Mul> parse_muls(const std::string &contents) {
  std::regex pat(R"(mul\(\d+,\d+\))");

  std::sregex_iterator begin(contents.begin(), contents.end(), pat);
  std::sregex_iterator end;

  std::vector<Mul> muls;
  for (auto it = begin; it != end; it++) {
    auto block = MulBlock(it->str());
    muls.push_back(block.to_mul());
  }

  return muls;
}

int solve_p1(const std::string &contents) {
  std::vector<Mul> muls = parse_muls(contents);

  int total = 0;
  for (const auto &mul : muls) {
    total += mul.apply();
  }

  return total;
}

int main() {
  std::ifstream f;
  f.open("input.txt");

  std::stringstream buf;
  buf << f.rdbuf();

  std::string contents = buf.str();

  auto result1 = solve_p1(contents);
  std::cout << "P1: " << result1 << "\n";
}
