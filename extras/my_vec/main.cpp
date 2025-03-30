#include <new>
#include <utility>

template <typename T> class Vector {

public:
  Vector() {
    siz = 0;
    cap = 8;

    elems = (T *)operator new[](cap * sizeof(T));
  }
  ~Vector() {
    for (int i = 0; i < siz; i++) {
      elems[i].~T();
    }

    operator delete[](elems);
  }

  const T &operator[](int i) const { return elems[i]; }

  // Copy constructor
  Vector(const Vector &v) {
    elems = new T[v.siz];
    for (int i = 0; i < v.siz; i++) {
      elems[i] = v[i];
    }

    siz = v.siz;
    cap = v.cap;
  }
  // Copy assignment
  Vector &operator=(const Vector &v) {
    operator delete[](elems);
    elems = new T[v.cap];
    for (int i = 0; i < v.siz; i++) {
      elems[i] = v[i];
    }

    siz = v.siz;
    cap = v.cap;

    return *this;
  }

  // Move constructor
  Vector(Vector &&v) {
    elems = v.elems;

    v.elems = nullptr;
    siz = v.siz;
    cap = v.cap;
  }
  // Move assignment
  Vector &operator=(Vector &&v) {
    if (this != &v) {
      operator delete[](elems);
      elems = v.elems;

      v.elems = nullptr;
      siz = v.siz;
      cap = v.cap;
    }

    return *this;
  }

  int size() { return siz; }

  void push_back(T &&value) {
    if (siz >= cap) {
      cap = 2 * cap;
      auto newElems = (T *)operator new[](cap * sizeof(T));

      for (int i = 0; i < siz; i++) {
        new (newElems + i) T(std::move(elems[i]));
        elems[i].~T();
      }

      operator delete[](elems);
      elems = newElems;
    }

    new (elems + siz) T(std::move(value));
    siz++;
  }

private:
  T *elems;
  int siz;
  int cap;
};

int main() {
  Vector<int> v;
  for (int i = 0; i < 15; i++) {
    v.push_back(std::move(i));
  }

  Vector<Vector<int>> w;
  for (int i = 0; i < 15; i++) {
    Vector<int> a;
    w.push_back(std::move(a));
  }
}
