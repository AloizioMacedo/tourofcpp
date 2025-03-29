#include <iostream>
#include <vector>

template <typename T> class MyBox {
private:
  T *val;

public:
  MyBox(T &&value) {
    val = new T;
    *val = std::move(value);
  }

  ~MyBox() { delete val; }

  MyBox(const MyBox &a) {
    val = new T;
    *val = *a.val;
  }

  MyBox &operator=(const MyBox &a) { *val = *a.val; }

  MyBox(MyBox &&a) {
    val = a.val;
    a.val = nullptr;
  }

  MyBox &operator=(MyBox &&a) {
    val = a.val;
    a.val = nullptr;
  }

  T getValue() { return *val; }
};

int main() {
  MyBox<int> a = MyBox<int>(239);
  std::cout << a.getValue() << "\n";

  std::vector<int> values{1, 5, 2, 9};
  auto b = MyBox(std::move(values));

  std::cout << b.getValue()[2] << "\n";
}
