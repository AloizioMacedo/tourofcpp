#include <iostream>

enum class Either { Left, Right };

void sayMyName(const Either &e) {
  switch (e) {
  case (Either::Left):
    std::cout << "I am left!\n";
    break;
  case (Either::Right):
    std::cout << "I am right!\n";
    break;
  }
}

int main() {
  sayMyName(Either::Right);
  sayMyName(Either::Left);

  return 0;
}
