#include "util/test_utils.hpp"
#include "list/list.hpp"
#include "vector/vector.hpp"
#include "set/setlist.hpp"
#include "set/setVector.hpp"
#include "heap/heapVector.hpp"
#include "pq/pqHeap.hpp"
#include "test.hpp"

void mytest()
{
   std::cout << "Running mytest...\n";
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

  std::cout << "\nRunning HeapVec tests...\n";
  TestHeapVec<int>();
    TestHeapVec<std::string>();
    TestHeapVec<MyObject>();
  
  std::cout << "\nRunning PQHeap tests...\n";
  TestPQHeap<int>();
  TestPQHeap<std::string>();
  TestPQHeap<MyObject>();



  std::cout << "\nAll tests passed.\n";
  std::cout << "mytest completed.\n";
}

