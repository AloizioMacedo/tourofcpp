#include <iostream>
#include <vector>

class Detector {
public:
  virtual bool detect(int n, const std::vector<int> &values) const = 0;
};

bool is_it_there(const Detector &detector, int n,
                 const std::vector<int> &values) {
  return detector.detect(n, values);
}

class MyDetector : public Detector {
public:
  MyDetector() {};

  bool detect(int n, const std::vector<int> &values) const override {
    for (auto v : values) {
      if (n == v) {
        return true;
      }
    }

    return false;
  }
};

void testing_abstraction() {
  auto myDetector = MyDetector();

  std::vector<int> values{5, 1, 2};

  std::cout << "Type a number!\n";

  int x = 1;

  if (is_it_there(myDetector, x, values)) {
    std::cout << "Yes, it is!\n";
  } else {
    std::cout << "No, it is not!\n";
  }
}

class MyBox {
public:
  MyBox(int value) {
    x = new int;
    *x = value;
  }
  ~MyBox() { delete x; }

  int getValue() { return *x; }

private:
  int *x;
};

void testing_destructors() {
  auto v = MyBox(30);
  std::cout << v.getValue() << "\n";
}

int main() {
  testing_destructors();
  testing_abstraction();
}
