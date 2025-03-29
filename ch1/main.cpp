#include <iostream>
#include <vector>

double square(double x) { return x * x; }

int sum_values(const std::vector<int> &values) {
  int total = 0;

  for (auto &v : values) {
    total += v;
  }

  return total;
}

int main() {
  std::cout << "Hello, world!\n";

  std::vector<int> values{1, 4, 2};

  std::cout << square(3.5) << "\n";
  std::cout << "First value is: " << values[0] << "\n";

  // Testing if it is really avoiding allocating new things
  // by checking with valgrind;
  std::cout << "Sum is: " << sum_values(values) << "\n";
  std::cout << "Sum is: " << sum_values(values) << "\n";
  std::cout << "Sum is: " << sum_values(values) << "\n";
  std::cout << "Sum is: " << sum_values(values) << "\n";

  return 0;
}
