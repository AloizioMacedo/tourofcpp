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
  MyBox() { val = nullptr; }

  // Constructor
  MyBox(int value) {
    val = new int;
    *val = value;
  }

  // Destructor
  ~MyBox() { delete val; }

  // Copy constructor
  MyBox(const MyBox &box) {
    val = new int;
    *val = *box.val;
  }
  // Copy assignment
  MyBox &operator=(const MyBox &box) {
    if (val != nullptr) {
      delete val;
    }

    val = new int;
    *val = *box.val;

    return *this;
  }

  // Move constructor
  MyBox(MyBox &&box) {
    val = box.val;
    box.val = nullptr;
  }
  // Move assignment
  MyBox &operator=(MyBox &&box) {
    val = box.val;
    box.val = nullptr;

    return *this;
  }

  int getValue() { return *val; }

private:
  int *val;
};

class User {
public:
  MyBox age;
  User(MyBox &&a) : age(std::move(a)) {};
};

void testing_destructors() {
  auto v = MyBox(30);
  std::cout << v.getValue() << "\n";

  User user1 = User(std::move(v));
  std::cout << user1.age.getValue() << "\n";
}

int main() {
  testing_destructors();
  testing_abstraction();
}
