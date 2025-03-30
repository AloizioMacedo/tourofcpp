#include <charconv>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

using Report = std::vector<int>;

void parse_report(const std::string_view &line, Report &report_buf) {
  int a = 0;
  int b = 0;

  report_buf.clear();
  report_buf.reserve(20);
  while ((b = line.find(" ", a)) != std::string_view::npos) {
    auto n_str = line.substr(a, b);

    int n = 0;
    std::from_chars(n_str.begin(), n_str.end(), n);

    report_buf.push_back(n);
    a = b + 1;
  }

  auto n_str = line.substr(a);

  int n = 0;
  std::from_chars(n_str.begin(), n_str.end(), n);

  report_buf.push_back(n);
}

bool is_ascending(const Report &report) {
  for (int i = 1; i < report.size(); i++) {
    if (report[i] <= report[i - 1]) {
      return false;
    }
  }

  return true;
}

bool is_descending(const Report &report) {
  for (int i = 1; i < report.size(); i++) {
    if (report[i] >= report[i - 1]) {
      return false;
    }
  }

  return true;
}

bool is_within_bounds(const Report &report) {
  for (int i = 1; i < report.size(); i++) {
    auto abs_diff = std::abs(report[i] - report[i - 1]);
    if (abs_diff > 3 || abs_diff < 1) {
      return false;
    }
  }

  return true;
}

bool is_safe(const Report &report) {
  return (is_ascending(report) || is_descending(report)) &&
         is_within_bounds(report);
}

int solve_p1(std::ifstream &f) {
  int total = 0;

  Report report_buf;
  std::string line;
  line.reserve(50);

  while (std::getline(f, line)) {
    parse_report(line, report_buf);
    if (is_safe(report_buf)) {
      total += 1;
    }
  }

  return total;
}

int main() {
  std::ifstream f;
  f.open("input.txt");

  auto report1 = solve_p1(f);
  std::cout << "P1: " << report1 << "\n";
}
