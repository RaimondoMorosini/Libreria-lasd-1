#include "util/test_utils.hpp"
#include "list/list.hpp"
#include "vector/vector.hpp"
#include "set/setlist.hpp"
#include "set/setVector.hpp"
#include "test.hpp"

void mytest()
{
  std::cout << "Running mytest...\n";
  //call main
  main();
  std::cout << "mytest completed.\n";
}
int main()
{

  std::cout << "Running Vector tests...\n";
  TestVector<int>();
  TestVector<std::string>();
  TestVector<MyObject>();
  TestSortableVectorInt();
  TestVectorString();

  std::cout << "\nRunning List tests...\n";
  RunListTests<int>();
  RunListTests<std::string>();
  RunListTests<MyObject>();

  std::cout << "\nRunning SetVec tests...\n";
  RunSetVecTests<int>();
  RunSetVecTests<std::string>();
  RunSetVecTests<MyObject>();

  std::cout << "\nRunning SetLst tests...\n";
  RunSetLstTests<int>();
  RunSetLstTests<std::string>();
  RunSetLstTests<MyObject>();

  std::cout << "\nAll tests passed.\n";
  return 0;
}
