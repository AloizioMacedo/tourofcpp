#include <iostream>
#include <memory>
#include <vector>

template <typename T> class Node {
public:
  T val;
  std::unique_ptr<Node<T>> next;

  Node(T val) : val(std::move(val)) {}

  void push(T value) {
    if (!next) {
      auto next_node = std::make_unique<Node<T>>(std::move(value));
      next = std::move(next_node);
    } else {
      next.get()->push(value);
    }
  }

  template <typename Func> void iterate(Func f) {
    f(val);
    if (next) {
      next.get()->iterate(f);
    }
  }
};

int main() {
  auto x = Node(32);
  x.push(49);
  x.push(12);

  auto f1 = [](int x) { std::cout << x << "\n"; };
  x.iterate(f1);

  int total = 0;
  auto g1 = [&total](int x) { total += x; };
  x.iterate(g1);

  std::cout << "Total is: " << total << "\n";

  auto y = Node(std::vector<int>{3, 2});
  y.push(std::vector<int>{5, 5});
  y.push(std::vector<int>{10, 2});

  auto f2 = [](const std::vector<int> &values) {
    for (const auto &value : values) {
      std::cout << value << " ";
    };
    std::cout << "\n";
  };
  y.iterate(f2);

  std::vector<int> aggregation;
  auto g2 = [&aggregation](const std::vector<int> &values) {
    for (const auto &value : values) {
      aggregation.push_back(value);
    }
  };
  y.iterate(g2);

  std::cout << "Final vector is: ";
  for (const auto &value : aggregation) {
    std::cout << value << " ";
  };
  std::cout << "\n";
}
