/*
 * test1.cc: Example of global object construction and destruction.
 * Output:
 *   Test object instantiated
 *   Main ends
 *   Test object destroyed
 */

#include <iostream>

class Test {
 public:
  Test();
  ~Test();
};

Test::Test() {
  std::cout << "Test object instantiated\n";
}

Test::~Test() {
  std::cout << "Test object destroyed\n";
}

Test t;
int main() {
  std::cout << "Main ends\n";
  return 0;
}
