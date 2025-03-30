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

bool is_safe_relaxed(const Report &report, Report &auxBuf) {
  for (int i = 0; i < report.size(); i++) {
    auxBuf.clear();

    for (int j = 0; j < report.size(); j++) {
      if (j == i) {
        continue;
      }
      auxBuf.push_back(report[j]);
    }

    if (is_safe(auxBuf)) {
      return true;
    }
  }

  return false;
}

int solve_p1(std::ifstream &f) {
  int total = 0;

  std::string line;
  line.reserve(50);

  Report report_buf;
  report_buf.reserve(20);

  while (std::getline(f, line)) {
    parse_report(line, report_buf);
    if (is_safe(report_buf)) {
      total += 1;
    }
  }

  return total;
}

int solve_p2(std::ifstream &f) {
  int total = 0;

  std::string line;
  line.reserve(50);

  Report report_buf;
  report_buf.reserve(20);

  Report aux_report_buf;
  aux_report_buf.reserve(19);

  while (std::getline(f, line)) {
    parse_report(line, report_buf);
    if (is_safe_relaxed(report_buf, aux_report_buf)) {
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

  f.clear();
  f.seekg(0);

  auto report2 = solve_p2(f);
  std::cout << "P2: " << report2 << "\n";
}
