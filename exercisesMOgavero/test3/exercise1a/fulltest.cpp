
#include <iostream>

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/testable.hpp"
#include "../container/dictionary.hpp"
#include "../container/traversable.hpp"
#include "../container/mappable.hpp"
#include "../container/linear.hpp"

#include "../vector/vector.hpp"

#include "../list/list.hpp"

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

void testVectorInt(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector<int> Test:" << endl;
  try {
    {
      lasd::SortableVector<int> vec;
      Empty(loctestnum, loctesterr, vec, true);
      Size(loctestnum, loctesterr, vec, true, 0);

      GetFront(loctestnum, loctesterr, vec, false, 0);
      GetBack(loctestnum, loctesterr, vec, false, 0);
      SetAt(loctestnum, loctesterr, vec, false, 1, 0);
      GetAt(loctestnum, loctesterr, vec, false, 2, 0);

      Exists(loctestnum, loctesterr, vec, false, 0);

      Traverse(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);

      Fold(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 0);
      FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 0);
      FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 0);

      SetAt(loctestnum, loctesterr, vec, false, 1, 0);
      GetAt(loctestnum, loctesterr, vec, false, 2, 0);
    }
    {
      lasd::SortableVector<int> vec(6);
      Empty(loctestnum, loctesterr, vec, false);
      Size(loctestnum, loctesterr, vec, true, 6);

      SetAt(loctestnum, loctesterr, vec, true, 0, 4);
      SetAt(loctestnum, loctesterr, vec, true, 1, 3);
      SetAt(loctestnum, loctesterr, vec, true, 2, 1);
      SetAt(loctestnum, loctesterr, vec, true, 3, 0);
      SetAt(loctestnum, loctesterr, vec, true, 4, 2);
      SetAt(loctestnum, loctesterr, vec, true, 5, 5);
      SetAt(loctestnum, loctesterr, vec, false, 7, 0);

      GetFront(loctestnum, loctesterr, vec, true, 4);
      GetBack(loctestnum, loctesterr, vec, true, 5);

      SetFront(loctestnum, loctesterr, vec, true, 5);
      SetBack(loctestnum, loctesterr, vec, true, 4);

      GetFront(loctestnum, loctesterr, vec, true, 5);
      GetBack(loctestnum, loctesterr, vec, true, 4);

      Exists(loctestnum, loctesterr, vec, true, 0);

      Traverse(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      Fold(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 15);
      FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 15);
      FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<int>, 1, 0);

      vec.Resize(3);
      Fold(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 9);
      FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 9);
      FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<int>, 1, 15);

      vec.Resize(4);
      SetAt(loctestnum, loctesterr, vec, true, 3, 1);
      MapPreOrder(loctestnum, loctesterr, vec, true, &MapIncrement<int>);
      TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      MapPreOrder(loctestnum, loctesterr, vec, true, &MapDouble<int>);
      TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      GetAt(loctestnum, loctesterr, vec, true, 1, 8);

      lasd::SortableVector<int> copvec(vec);
      EqualVector(loctestnum, loctesterr, vec, copvec, true);
      EqualLinear(loctestnum, loctesterr, vec, copvec, true);
      TraversePreOrder(loctestnum, loctesterr, copvec, true, &TraversePrint<int>);
      MapPreOrder(loctestnum, loctesterr, vec, true, &MapIncrement<int>);
      NonEqualVector(loctestnum, loctesterr, vec, copvec, true);

      copvec = vec;
      EqualVector(loctestnum, loctesterr, vec, copvec, true);
      EqualLinear(loctestnum, loctesterr, vec, copvec, true);
      MapPreOrder(loctestnum, loctesterr, vec, true, &MapIncrement<int>);
      NonEqualVector(loctestnum, loctesterr, vec, copvec, true);
      NonEqualLinear(loctestnum, loctesterr, vec, copvec, true);

      FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 36);
      copvec = move(vec);
      FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 32);

      lasd::SortableVector<int> movvec(move(vec));
      FoldPreOrder(loctestnum, loctesterr, movvec, true, &FoldAdd<int>, 0, 32);
      SetAt(loctestnum, loctesterr, vec, false, 1, 0);

      movvec.Clear();
      Empty(loctestnum, loctesterr, movvec, true);
      Size(loctestnum, loctesterr, movvec, true, 0);
    }
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void testVectorDouble(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector<double> Test:" << endl;
  try {
    lasd::SortableVector<double> vec(4);
    Empty(loctestnum, loctesterr, vec, false);
    Size(loctestnum, loctesterr, vec, true, 4);

    SetAt(loctestnum, loctesterr, vec, true, 0, 5.5);
    SetAt(loctestnum, loctesterr, vec, true, 1, 3.3);
    SetAt(loctestnum, loctesterr, vec, true, 2, 1.1);
    SetAt(loctestnum, loctesterr, vec, true, 3, 0.5);

    GetFront(loctestnum, loctesterr, vec, true, 5.5);
    GetBack(loctestnum, loctesterr, vec, true, 0.5);

    Exists(loctestnum, loctesterr, vec, true, 1.1);

    TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<double>);
    TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<double>);
    FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<double>, 0.0, 10.4);
    FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<double>, 1.0, 9.9825);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void testVectorString(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector<string> Test:" << endl;
  try {
    lasd::SortableVector<string> vec(3);
    Empty(loctestnum, loctesterr, vec, false);
    Size(loctestnum, loctesterr, vec, true, 3);

    SetAt(loctestnum, loctesterr, vec, true, 0, string("This"));
    SetAt(loctestnum, loctesterr, vec, true, 1, string("is"));
    SetAt(loctestnum, loctesterr, vec, true, 2, string("correct!"));

    GetFront(loctestnum, loctesterr, vec, true, string("This"));
    GetBack(loctestnum, loctesterr, vec, true, string("correct!"));

    Exists(loctestnum, loctesterr, vec, true, string("is"));

    MapPreOrder(loctestnum, loctesterr, vec, true, [](string & str) { MapStringAppend(str, string(" ")); });
    TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<string>);
    FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldStringConcatenate, string("X"), string("XThis is correct! "));
    FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldStringConcatenate, string("X"), string("Xcorrect! is This "));

    Exists(loctestnum, loctesterr, vec, false, string("is"));

    lasd::SortableVector<string> copvec(vec);
    EqualVector(loctestnum, loctesterr, vec, copvec, true);
    EqualLinear(loctestnum, loctesterr, vec, copvec, true);
    MapPreOrder(loctestnum, loctesterr, vec, true, [](string & str) { MapStringAppend(str, string(" ")); });
    NonEqualVector(loctestnum, loctesterr, vec, copvec, true);

    copvec = vec;
    EqualVector(loctestnum, loctesterr, vec, copvec, true);
    EqualLinear(loctestnum, loctesterr, vec, copvec, true);
    MapPreOrder(loctestnum, loctesterr, vec, true, [](string & str) { MapStringAppend(str, string("X")); });
    NonEqualVector(loctestnum, loctesterr, vec, copvec, true);
    NonEqualLinear(loctestnum, loctesterr, vec, copvec, true);

    FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldStringConcatenate, string("?"), string("?This  Xis  Xcorrect!  X"));
    copvec = move(vec);
    FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldStringConcatenate, string("?"), string("?This  is  correct!  "));

    lasd::SortableVector<string> movvec(move(vec));
    FoldPreOrder(loctestnum, loctesterr, movvec, true, &FoldStringConcatenate, string("?"), string("?This  is  correct!  "));
    movvec.Sort();
    FoldPreOrder(loctestnum, loctesterr, movvec, true, &FoldStringConcatenate, string("?"), string("?This  correct!  is  "));
    SetAt(loctestnum, loctesterr, vec, false, 1, string(""));

    movvec.Clear();
    Empty(loctestnum, loctesterr, movvec, true);
    Size(loctestnum, loctesterr, movvec, true, 0);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void testVector(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  testVectorInt(loctestnum, loctesterr);
  testVectorDouble(loctestnum, loctesterr);
  testVectorString(loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
  cout << endl << "Exercise 1A - Vector (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void testListInt(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of List<int> Test:" << endl;
  try {
    lasd::List<int> lst;
    Empty(loctestnum, loctesterr, lst, true);
    Size(loctestnum, loctesterr, lst, true, 0);

    GetFront(loctestnum, loctesterr, lst, false, 0);
    GetBack(loctestnum, loctesterr, lst, false, 0);

    Exists(loctestnum, loctesterr, lst, false, 0);

    TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
    TraversePostOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);

    FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 0);
    FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 0);

    RemoveFromFront(loctestnum, loctesterr, lst, false);
    FrontNRemove(loctestnum, loctesterr, lst, false, 0);

    InsertAtFront(loctestnum, loctesterr, lst, true, 5);
    InsertAtFront(loctestnum, loctesterr, lst, true, 9);
    InsertAtFront(loctestnum, loctesterr, lst, true, 1);
    InsertAtFront(loctestnum, loctesterr, lst, true, 0);
    InsertAtFront(loctestnum, loctesterr, lst, true, 6);
    InsertAtBack(loctestnum, loctesterr, lst, true, 4);
    InsertAtBack(loctestnum, loctesterr, lst, true, 2);

    GetFront(loctestnum, loctesterr, lst, true, 6);
    GetBack(loctestnum, loctesterr, lst, true, 2);

    SetFront(loctestnum, loctesterr, lst, true, 2);
    SetBack(loctestnum, loctesterr, lst, true, 6);
    GetAt(loctestnum, loctesterr, lst, true, 3, 9);
    SetAt(loctestnum, loctesterr, lst, true, 3, 3);

    GetFront(loctestnum, loctesterr, lst, true, 2);
    GetBack(loctestnum, loctesterr, lst, true, 6);

    Exists(loctestnum, loctesterr, lst, true, 0);

    TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
    TraversePostOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
    FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 21);
    FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldMultiply<int>, 1, 0);

    RemoveFromFront(loctestnum, loctesterr, lst, true);
    FrontNRemove(loctestnum, loctesterr, lst, true, 0);
    FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldMultiply<int>, 1, 360);

    lasd::List<int> coplst(lst);
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    EqualLinear(loctestnum, loctesterr, lst, coplst, true);
    TraversePreOrder(loctestnum, loctesterr, coplst, true, &TraversePrint<int>);
    MapPreOrder(loctestnum, loctesterr, lst, true, &MapIncrement<int>);
    TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
    NonEqualList(loctestnum, loctesterr, lst, coplst, true);

    InsertAtFront(loctestnum, loctesterr, lst, true, 0);
    InsertAtBack(loctestnum, loctesterr, lst, true, 0);
    TraversePostOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
    TraversePostOrder(loctestnum, loctesterr, coplst, true, &TraversePrint<int>);
    coplst = lst;
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    EqualLinear(loctestnum, loctesterr, lst, coplst, true);
    MapPreOrder(loctestnum, loctesterr, lst, true, &MapIncrement<int>);
    NonEqualList(loctestnum, loctesterr, lst, coplst, true);
    FrontNRemove(loctestnum, loctesterr, lst, true, 1);
    FrontNRemove(loctestnum, loctesterr, lst, true, 3);
    TraversePostOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
    TraversePostOrder(loctestnum, loctesterr, coplst, true, &TraversePrint<int>);

    lasd::List<int> coplstz(coplst);
    coplstz.Clear();
    coplstz = lst;
    EqualList(loctestnum, loctesterr, lst, coplstz, true);

    coplstz = coplst;
    GetBack(loctestnum, loctesterr, coplstz, true, 0);
    SetBack(loctestnum, loctesterr, coplstz, true, 1);
    TraversePostOrder(loctestnum, loctesterr, coplstz, true, &TraversePrint<int>);

    FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 27);
    coplst = move(lst);
    FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 24);

    TraversePostOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
    TraversePostOrder(loctestnum, loctesterr, coplst, true, &TraversePrint<int>);
    lst = coplst;
    TraversePostOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);

    lasd::List<int> movlst(move(lst));
    FoldPreOrder(loctestnum, loctesterr, movlst, true, &FoldAdd<int>, 0, 27);
    FrontNRemove(loctestnum, loctesterr, movlst, true, 5);

    InsertAtBack(loctestnum, loctesterr, lst, true, 10);
    MapPreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);

    TraversePreOrder(loctestnum, loctesterr, movlst, true, &TraversePrint<int>);
    InsertC(loctestnum, loctesterr, movlst, true, 5);
    TraversePreOrder(loctestnum, loctesterr, movlst, true, &TraversePrint<int>);
    InsertC(loctestnum, loctesterr, movlst, false, 8);
    Remove(loctestnum, loctesterr, movlst, false, 9);
    Remove(loctestnum, loctesterr, movlst, true, 6);
    TraversePreOrder(loctestnum, loctesterr, movlst, true, &TraversePrint<int>);
    InsertC(loctestnum, loctesterr, movlst, true, 9);
    InsertC(loctestnum, loctesterr, movlst, false, 8);
    TraversePreOrder(loctestnum, loctesterr, movlst, true, &TraversePrint<int>);
    Remove(loctestnum, loctesterr, movlst, true, 8);
    Remove(loctestnum, loctesterr, movlst, true, 9);
    InsertC(loctestnum, loctesterr, movlst, false, 7);
    InsertC(loctestnum, loctesterr, movlst, true, 10);
    TraversePreOrder(loctestnum, loctesterr, movlst, true, &TraversePrint<int>);
    FoldPreOrder(loctestnum, loctesterr, movlst, true, &FoldAdd<int>, 1, 24);

    movlst.Clear();
    Empty(loctestnum, loctesterr, movlst, true);
    Size(loctestnum, loctesterr, movlst, true, 0);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of List<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void testListDouble(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of List<double> Test:" << endl;
  try {
    lasd::List<double> lst;
    Empty(loctestnum, loctesterr, lst, true);
    Size(loctestnum, loctesterr, lst, true, 0);

    InsertAtBack(loctestnum, loctesterr, lst, true, -2.5);
    InsertAtBack(loctestnum, loctesterr, lst, true, 2.5);

    lst.Clear();

    InsertAtFront(loctestnum, loctesterr, lst, true, 5.5);
    InsertAtFront(loctestnum, loctesterr, lst, true, 3.3);
    InsertAtBack(loctestnum, loctesterr, lst, true, 1.1);
    InsertAtBack(loctestnum, loctesterr, lst, true, 0.5);

    GetFront(loctestnum, loctesterr, lst, true, 3.3);
    GetBack(loctestnum, loctesterr, lst, true, 0.5);

    Exists(loctestnum, loctesterr, lst, true, 1.1);

    TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<double>);
    TraversePostOrder(loctestnum, loctesterr, lst, true, &TraversePrint<double>);
    FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<double>, 0.0, 10.4);
    FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldMultiply<double>, 1.0, 9.9825);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of List<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void testListString(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of List<string> Test:" << endl;
  try {
    lasd::List<string> lst;
    Empty(loctestnum, loctesterr, lst, true);
    Size(loctestnum, loctesterr, lst, true, 0);

    InsertAtFront(loctestnum, loctesterr, lst, true, string("is"));
    InsertAtFront(loctestnum, loctesterr, lst, true, string("This"));
    InsertAtBack(loctestnum, loctesterr, lst, true, string("correct!"));

    GetFront(loctestnum, loctesterr, lst, true, string("This"));
    GetBack(loctestnum, loctesterr, lst, true, string("correct!"));

    Exists(loctestnum, loctesterr, lst, true, string("is"));

    MapPreOrder(loctestnum, loctesterr, lst, true, [](string & str) { MapStringAppend(str, string(" ")); });
    TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<string>);
    FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldStringConcatenate, string("X"), string("XThis is correct! "));
    FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldStringConcatenate, string("X"), string("Xcorrect! is This "));

    Exists(loctestnum, loctesterr, lst, false, string("is"));

    lasd::List<string> coplst(lst);
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    EqualLinear(loctestnum, loctesterr, lst, coplst, true);
    MapPreOrder(loctestnum, loctesterr, lst, true, [](string & str) { MapStringAppend(str, string(" ")); });
    NonEqualList(loctestnum, loctesterr, lst, coplst, true);

    coplst = lst;
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    EqualLinear(loctestnum, loctesterr, lst, coplst, true);
    MapPreOrder(loctestnum, loctesterr, lst, true, [](string & str) { MapStringAppend(str, string("X")); });
    NonEqualList(loctestnum, loctesterr, lst, coplst, true);

    lst = coplst;
    coplst.Clear();
    coplst = lst;
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    EqualLinear(loctestnum, loctesterr, lst, coplst, true);
    MapPreOrder(loctestnum, loctesterr, lst, true, [](string & str) { MapStringAppend(str, string("X")); });
    NonEqualList(loctestnum, loctesterr, lst, coplst, true);

    FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldStringConcatenate, string("?"), string("?This  Xis  Xcorrect!  X"));
    coplst = move(lst);
    FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldStringConcatenate, string("?"), string("?This  is  correct!  "));

    lasd::List<string> movlst(move(lst));
    FoldPreOrder(loctestnum, loctesterr, movlst, true, &FoldStringConcatenate, string("?"), string("?This  is  correct!  "));
    GetFront(loctestnum, loctesterr, lst, false, string(""));

    movlst.Clear();
    Empty(loctestnum, loctesterr, movlst, true);
    Size(loctestnum, loctesterr, movlst, true, 0);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of List<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void testList(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  testListInt(loctestnum, loctesterr);
  testListDouble(loctestnum, loctesterr);
  testListString(loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
  cout << endl << "Exercise 1A - List (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void testVectorListInt(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector/List<int> Test:" << endl;
  try {
    lasd::SortableVector<int> vec(5);
    SetAt(loctestnum, loctesterr, vec, true, 0, 5);
    SetAt(loctestnum, loctesterr, vec, true, 1, -15);
    SetAt(loctestnum, loctesterr, vec, true, 2, 10);
    SetAt(loctestnum, loctesterr, vec, true, 3, -5);
    SetAt(loctestnum, loctesterr, vec, true, 4, 0);

    lasd::List<int> lst;
    InsertAtBack(loctestnum, loctesterr, lst, true, 10);
    InsertAtFront(loctestnum, loctesterr, lst, true, -15);
    InsertAtFront(loctestnum, loctesterr, lst, true, 5);
    InsertAtBack(loctestnum, loctesterr, lst, true, -5);
    InsertAtBack(loctestnum, loctesterr, lst, true, 0);

    EqualLinear(loctestnum, loctesterr, vec, lst, true);

    lasd::SortableVector<int> copvec(lst);
    EqualVector(loctestnum, loctesterr, vec, copvec, true);
    lasd::SortableVector<int> copvecx(vec);
    EqualVector(loctestnum, loctesterr, copvecx, copvec, true);

    copvecx.Resize(6);
    Size(loctestnum, loctesterr, copvecx, true, 6);
    SetAt(loctestnum, loctesterr, copvecx, true, 5, 0);
    NonEqualVector(loctestnum, loctesterr, copvecx, copvec, true);
    copvec.Resize(4);
    copvecx.Resize(4);
    EqualVector(loctestnum, loctesterr, copvecx, copvec, true);

    lasd::List<int> coplst(vec);
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    lasd::List<int> coplstx(lst);
    EqualList(loctestnum, loctesterr, coplstx, coplst, true);

    RemoveFromFront(loctestnum, loctesterr, coplstx, true);
    NonEqualList(loctestnum, loctesterr, coplstx, coplst, true);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector/List<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void testVectorListDouble(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector/List<double> Test:" << endl;
  try {
    lasd::SortableVector<double> vec(5);
    SetAt(loctestnum, loctesterr, vec, true, 0, 5.25);
    SetAt(loctestnum, loctesterr, vec, true, 1, -15.75);
    SetAt(loctestnum, loctesterr, vec, true, 2, 10.5);
    SetAt(loctestnum, loctesterr, vec, true, 3, -10.0);
    SetAt(loctestnum, loctesterr, vec, true, 4, -0.5);

    lasd::List<double> lst;
    InsertAtFront(loctestnum, loctesterr, lst, true, -15.75);
    InsertAtBack(loctestnum, loctesterr, lst, true, 10.5);
    InsertAtFront(loctestnum, loctesterr, lst, true, 5.25);
    InsertAtBack(loctestnum, loctesterr, lst, true, -10.0);
    InsertAtBack(loctestnum, loctesterr, lst, true, -0.5);

    EqualLinear(loctestnum, loctesterr, vec, lst, true);

    lasd::SortableVector<double> copvec(lst);
    EqualVector(loctestnum, loctesterr, vec, copvec, true);
    lasd::SortableVector<double> copvecx(vec);
    EqualVector(loctestnum, loctesterr, copvecx, copvec, true);

    copvecx.Resize(6);
    Size(loctestnum, loctesterr, copvecx, true, 6);
    SetAt(loctestnum, loctesterr, copvecx, true, 5, 15.5);
    NonEqualVector(loctestnum, loctesterr, copvecx, copvec, true);
    copvec.Resize(4);
    copvecx.Resize(4);
    EqualVector(loctestnum, loctesterr, copvecx, copvec, true);

    lasd::List<double> coplst(vec);
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    lasd::List<double> coplstx(lst);
    EqualList(loctestnum, loctesterr, coplstx, coplst, true);

    RemoveFromFront(loctestnum, loctesterr, coplstx, true);
    NonEqualList(loctestnum, loctesterr, coplstx, coplst, true);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector/List<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void testVectorListString(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector/List<string> Test:" << endl;
  try {
    lasd::SortableVector<string> vec(5);
    SetAt(loctestnum, loctesterr, vec, true, 0, string("This"));
    SetAt(loctestnum, loctesterr, vec, true, 1, string("is"));
    SetAt(loctestnum, loctesterr, vec, true, 2, string("correct!"));
    SetAt(loctestnum, loctesterr, vec, true, 3, string("Who"));
    SetAt(loctestnum, loctesterr, vec, true, 4, string("knows."));

    lasd::List<string> lst;
    InsertAtFront(loctestnum, loctesterr, lst, true, string("correct!"));
    InsertAtBack(loctestnum, loctesterr, lst, true, string("Who"));
    InsertAtFront(loctestnum, loctesterr, lst, true, string("is"));
    InsertAtFront(loctestnum, loctesterr, lst, true, string("This"));
    InsertAtBack(loctestnum, loctesterr, lst, true, string("knows."));

    EqualLinear(loctestnum, loctesterr, vec, lst, true);

    lasd::SortableVector<string> copvec(lst);
    EqualVector(loctestnum, loctesterr, vec, copvec, true);
    lasd::SortableVector<string> copvecx(vec);
    EqualVector(loctestnum, loctesterr, copvecx, copvec, true);

    copvecx.Resize(3);
    Size(loctestnum, loctesterr, copvecx, true, 3);
    NonEqualVector(loctestnum, loctesterr, copvecx, copvec, true);
    copvec.Resize(4);
    copvecx.Resize(4);
    SetAt(loctestnum, loctesterr, copvecx, true, 3, string("Who"));
    EqualVector(loctestnum, loctesterr, copvecx, copvec, true);

    lasd::List<string> coplst(vec);
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    lasd::List<string> coplstx(lst);
    EqualList(loctestnum, loctesterr, coplstx, coplst, true);

    copvec = vec;

    Size(loctestnum, loctesterr, vec, true, 5);
    TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<string>);
    Size(loctestnum, loctesterr, copvec, true, 5);
    TraversePreOrder(loctestnum, loctesterr, copvec, true, &TraversePrint<string>);

    lasd::List<string> coplsty(move(vec));
    EqualList(loctestnum, loctesterr, coplst, coplsty, true);
    Size(loctestnum, loctesterr, vec, true, 5);
    TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<string>);
    TraversePreOrder(loctestnum, loctesterr, copvec, true, &TraversePrint<string>);
    EqualVector(loctestnum, loctesterr, vec, copvec, false);

    Size(loctestnum, loctesterr, lst, true, 5);
    TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<string>);
    Size(loctestnum, loctesterr, coplst, true, 5);
    TraversePreOrder(loctestnum, loctesterr, coplst, true, &TraversePrint<string>);

    lasd::SortableVector<string> copvecy(move(lst));
    EqualVector(loctestnum, loctesterr, copvec, copvecy, true);
    Size(loctestnum, loctesterr, lst, true, 5);
    TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<string>);
    TraversePreOrder(loctestnum, loctesterr, coplst, true, &TraversePrint<string>);
    EqualList(loctestnum, loctesterr, lst, coplst, false);

    RemoveFromFront(loctestnum, loctesterr, coplstx, true);
    NonEqualList(loctestnum, loctesterr, coplstx, coplst, true);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector/List<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void testVectorList(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  testVectorListInt(loctestnum, loctesterr);
  testVectorListDouble(loctestnum, loctesterr);
  testVectorListString(loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
  cout << endl << "Exercise 1A - Vector/List (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void testFullExercise1A(uint & testnum, uint & testerr) {
  testVector(testnum, testerr);
  testList(testnum, testerr);
  testVectorList(testnum, testerr);
  cout << endl << "Exercise 1A (Full Test) (Errors/Tests: " << testerr << "/" << testnum << ")" << endl;
}
