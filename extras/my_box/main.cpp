#include <utility>
#include <vector>
template <typename T> class Box {

public:
  Box(T &&value) {
    val = new T;
    *val = std::move(value);
  }
  ~Box() { delete val; }

  Box(const Box &box) {
    val = new T;
    *val = *box.val;
  }
  Box &operator=(const Box &box) {
    delete val;

    val = new T;
    *val = box.val;
  }

  Box(Box &&box) {
    val = box.val;
    box.val = nullptr;
  }
  Box &operator=(Box &&box) {
    delete val;

    val = box.val;
    box.val = nullptr;
  }

  T &getValue() const { return *val; }

private:
  T *val;
};

int main() {
  auto x = Box(3);

  std::vector<int> values{3};
  auto y = Box(std::move(values));

  auto a = x.getValue();
  const auto &b = y.getValue();
  const auto &c = y.getValue();
  const auto &d = y.getValue();

  return 0;
}
