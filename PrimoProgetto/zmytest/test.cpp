#include "util/test_utils.hpp"
#include "list/list.hpp"

int main() {

  std::cout << "\nRunning List tests...\n";
  RunListTests<int>();
  RunListTests<std::string>();
  RunListTests<MyObject>();

  std::cout << "\nAll tests passed.\n";
  return 0;
}
