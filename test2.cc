/*
 * test2.cc: Example of global object construction and destruction.
 * Output:
 *   Main starts
 *   Func starts
 *   Test object instantiated
 *   Func ends
 *   Test object destroyed
 *   Main ends
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

void func() {
  std::cout << "Func starts\n";
  Test t;
  std::cout << "Func ends\n";
}

int main() {
  std::cout << "Main starts\n";
  func();
  std::cout << "Main ends\n";
  return 0;
}
