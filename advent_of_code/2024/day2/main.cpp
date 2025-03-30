#include <charconv>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

using Report = std::vector<int>;

Report parse_report(const std::string_view &line) {
  int a = 0;
  int b = 0;

  Report values;
  values.reserve(20);
  while ((b = line.find(" ", a)) != std::string_view::npos) {
    auto n_str = line.substr(a, b);

    int n = 0;
    std::from_chars(n_str.begin(), n_str.end(), n);

    values.push_back(n);
    a = b + 1;
  }

  auto n_str = line.substr(a);

  int n = 0;
  std::from_chars(n_str.begin(), n_str.end(), n);

  values.push_back(n);

  return values;
}

std::vector<Report> parse_file(std::ifstream &f) {
  std::string line;

  std::vector<Report> reports;
  while (std::getline(f, line)) {
    Report report = parse_report(line);
    reports.push_back(std::move(report));
  }

  return reports;
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
  auto reports = parse_file(f);
  int total = 0;
  for (const auto &report : reports) {
    if (is_safe(report)) {
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
