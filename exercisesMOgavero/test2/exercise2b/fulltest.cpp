
#include <iostream>

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/testable.hpp"
#include "../container/dictionary.hpp"
#include "../container/traversable.hpp"
#include "../container/mappable.hpp"
#include "../container/linear.hpp"

#include "../iterator/iterator.hpp"

#include "../vector/vector.hpp"

#include "../list/list.hpp"

#include "../binarytree/binarytree.hpp"

#include "../bst/bst.hpp"

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

void testBSTInt(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of BST<int> Test" << endl;
  try {
    lasd::BST<int> bst;

    Empty(loctestnum, loctesterr, bst, true);
    Size(loctestnum, loctesterr, bst, true, 0);

    Min(loctestnum, loctesterr, bst, false, 0);
    Max(loctestnum, loctesterr, bst, false, 0);

    TraversePreOrder(loctestnum, loctesterr, bst, true, &TraversePrint<int>);
    TraverseInOrder(loctestnum, loctesterr, bst, true, &TraversePrint<int>);
    TraversePostOrder(loctestnum, loctesterr, bst, true, &TraversePrint<int>);
    TraverseBreadth(loctestnum, loctesterr, bst, true, &TraversePrint<int>);

    InsertC(loctestnum, loctesterr, bst, true, 10);
    InsertC(loctestnum, loctesterr, bst, true, 5);
    InsertC(loctestnum, loctesterr, bst, true, 15);
    InsertC(loctestnum, loctesterr, bst, true, 8);
    InsertC(loctestnum, loctesterr, bst, true, 12);
    InsertC(loctestnum, loctesterr, bst, true, 2);
    InsertC(loctestnum, loctesterr, bst, true, 18);
    InsertC(loctestnum, loctesterr, bst, true, 3);
    InsertC(loctestnum, loctesterr, bst, true, 4);
    InsertC(loctestnum, loctesterr, bst, true, 17);
    InsertC(loctestnum, loctesterr, bst, true, 16);
    InsertC(loctestnum, loctesterr, bst, true, 9);
    InsertC(loctestnum, loctesterr, bst, true, 11);
    InsertC(loctestnum, loctesterr, bst, true, 13);
    InsertC(loctestnum, loctesterr, bst, true, 7);
    InsertC(loctestnum, loctesterr, bst, true, 0);
    InsertC(loctestnum, loctesterr, bst, true, 20);
    InsertC(loctestnum, loctesterr, bst, true, 19);
    InsertC(loctestnum, loctesterr, bst, true, 1);

    Empty(loctestnum, loctesterr, bst, false);
    Size(loctestnum, loctesterr, bst, true, 19);

    TraversePreOrder(loctestnum, loctesterr, bst, true, &TraversePrint<int>);
    TraverseInOrder(loctestnum, loctesterr, bst, true, &TraversePrint<int>);
    TraversePostOrder(loctestnum, loctesterr, bst, true, &TraversePrint<int>);
    TraverseBreadth(loctestnum, loctesterr, bst, true, &TraversePrint<int>);

    Min(loctestnum, loctesterr, bst, true, 0);
    Max(loctestnum, loctesterr, bst, true, 20);

    Root(loctestnum, loctesterr, bst, true, 10);

    RemoveMin(loctestnum, loctesterr, bst, true);
    MinNRemove(loctestnum, loctesterr, bst, true, 1);

    InsertC(loctestnum, loctesterr, bst, true, -1);
    InsertC(loctestnum, loctesterr, bst, true, 1);
    InsertC(loctestnum, loctesterr, bst, true, 0);

    Size(loctestnum, loctesterr, bst, true, 20);

    Min(loctestnum, loctesterr, bst, true, -1);
    MaxNRemove(loctestnum, loctesterr, bst, true, 20);
    Size(loctestnum, loctesterr, bst, true, 19);

    InsertC(loctestnum, loctesterr, bst, false, 19);

    Size(loctestnum, loctesterr, bst, true, 19);

    Max(loctestnum, loctesterr, bst, true, 19);

    InsertC(loctestnum, loctesterr, bst, true, 20);

    Size(loctestnum, loctesterr, bst, true, 20);

    Exists(loctestnum, loctesterr, bst, false, 6);
    Exists(loctestnum, loctesterr, bst, false, 14);

    InsertC(loctestnum, loctesterr, bst, true, 14);
    InsertC(loctestnum, loctesterr, bst, true, 6);

    Size(loctestnum, loctesterr, bst, true, 22);

    Exists(loctestnum, loctesterr, bst, true, 6);
    Exists(loctestnum, loctesterr, bst, true, 14);

    Exists(loctestnum, loctesterr, bst, true, 3);
    Exists(loctestnum, loctesterr, bst, true, 10);
    Exists(loctestnum, loctesterr, bst, true, 17);

    Remove(loctestnum, loctesterr, bst, true, 3);
    Remove(loctestnum, loctesterr, bst, true, 10);
    Remove(loctestnum, loctesterr, bst, true, 17);
    Remove(loctestnum, loctesterr, bst, false, 10);

    Exists(loctestnum, loctesterr, bst, false, 3);
    Exists(loctestnum, loctesterr, bst, false, 10);
    Exists(loctestnum, loctesterr, bst, false, 17);

    Size(loctestnum, loctesterr, bst, true, 19);

    InsertC(loctestnum, loctesterr, bst, true, 3);
    InsertC(loctestnum, loctesterr, bst, true, 10);
    Remove(loctestnum, loctesterr, bst, false, 17);
    InsertC(loctestnum, loctesterr, bst, true, 17);

    Max(loctestnum, loctesterr, bst, true, 20);
    RemoveMax(loctestnum, loctesterr, bst, true);
    Max(loctestnum, loctesterr, bst, true, 19);

    InsertC(loctestnum, loctesterr, bst, true, 20);

    Size(loctestnum, loctesterr, bst, true, 22);

    TraversePreOrder(loctestnum, loctesterr, bst, true, &TraversePrint<int>);
    TraverseInOrder(loctestnum, loctesterr, bst, true, &TraversePrint<int>);
    TraversePostOrder(loctestnum, loctesterr, bst, true, &TraversePrint<int>);
    TraverseBreadth(loctestnum, loctesterr, bst, true, &TraversePrint<int>);

    Predecessor(loctestnum, loctesterr, bst, true, 9, 8);
    Predecessor(loctestnum, loctesterr, bst, true, 15, 14);
    Predecessor(loctestnum, loctesterr, bst, true, 20, 19);
    Predecessor(loctestnum, loctesterr, bst, true, 10, 9);
    Predecessor(loctestnum, loctesterr, bst, true, 6, 5);

    Successor(loctestnum, loctesterr, bst, true, 8, 9);
    Successor(loctestnum, loctesterr, bst, true, 9, 10);

    PredecessorNRemove(loctestnum, loctesterr, bst, true, 18, 17);
    SuccessorNRemove(loctestnum, loctesterr, bst, true, 13, 14);
    RemoveSuccessor(loctestnum, loctesterr, bst, true, 13);
    Predecessor(loctestnum, loctesterr, bst, true, 16, 13);
    RemovePredecessor(loctestnum, loctesterr, bst, true, 16);
    Predecessor(loctestnum, loctesterr, bst, true, 16, 12);

    FoldPreOrder(loctestnum, loctesterr, bst, true, &FoldAdd<int>, 0, 150);
    FoldInOrder(loctestnum, loctesterr, bst, true, &FoldAdd<int>, 0, 150);
    FoldPostOrder(loctestnum, loctesterr, bst, true, &FoldAdd<int>, 0, 150);
    FoldBreadth(loctestnum, loctesterr, bst, true, &FoldAdd<int>, 0, 150);

    lasd::BST<int> bst1(bst);

    EqualBST(loctestnum, loctesterr, bst, bst1);

    FoldPreOrder(loctestnum, loctesterr, bst1, true, &FoldAdd<int>, 0, 150);
    FoldInOrder(loctestnum, loctesterr, bst1, true, &FoldAdd<int>, 0, 150);
    FoldPostOrder(loctestnum, loctesterr, bst1, true, &FoldAdd<int>, 0, 150);
    FoldBreadth(loctestnum, loctesterr, bst1, true, &FoldAdd<int>, 0, 150);

    TraverseBreadth(loctestnum, loctesterr, bst1, true, &TraversePrint<int>);

    Remove(loctestnum, loctesterr, bst1, true, 5);

    NonEqualBST(loctestnum, loctesterr, bst, bst1);

    InsertC(loctestnum, loctesterr, bst1, true, 5);

    EqualBST(loctestnum, loctesterr, bst, bst1);

    lasd::BST<int> bst2 = bst1;

    EqualBST(loctestnum, loctesterr, bst1, bst2);

    RemovePredecessor(loctestnum, loctesterr, bst1, true, 9);

    NonEqualBST(loctestnum, loctesterr, bst1, bst2);

    lasd::BST<int> bst3(move(bst2));

    Empty(loctestnum, loctesterr, bst2, true);
    Size(loctestnum, loctesterr, bst2, true, 0);

    Empty(loctestnum, loctesterr, bst3, false);
    Size(loctestnum, loctesterr, bst3, true, 18);

    bst2 = move(bst1);

    Empty(loctestnum, loctesterr, bst1, true);
    Size(loctestnum, loctesterr, bst1, true, 0);

    Empty(loctestnum, loctesterr, bst2, false);
    Size(loctestnum, loctesterr, bst2, true, 17);

    NonEqualBST(loctestnum, loctesterr, bst3, bst2);

    InsertC(loctestnum, loctesterr, bst2, true, 8);

    EqualBST(loctestnum, loctesterr, bst3, bst2);

    TraversePreOrder(loctestnum, loctesterr, bst2, true, &TraversePrint<int>);
    TraversePreOrder(loctestnum, loctesterr, bst3, true, &TraversePrint<int>);
    TraversePostOrder(loctestnum, loctesterr, bst2, true, &TraversePrint<int>);
    TraversePostOrder(loctestnum, loctesterr, bst3, true, &TraversePrint<int>);
    TraverseBreadth(loctestnum, loctesterr, bst2, true, &TraversePrint<int>);
    TraverseBreadth(loctestnum, loctesterr, bst3, true, &TraversePrint<int>);
    TraverseInOrder(loctestnum, loctesterr, bst2, true, &TraversePrint<int>);
    TraverseInOrder(loctestnum, loctesterr, bst3, true, &TraversePrint<int>);

    MinNRemove(loctestnum, loctesterr, bst2, true, -1);
    MaxNRemove(loctestnum, loctesterr, bst3, true, 20);

    NonEqualBST(loctestnum, loctesterr, bst3, bst2);

    RemovePredecessor(loctestnum, loctesterr, bst2, false, 0);
    PredecessorNRemove(loctestnum, loctesterr, bst3, true, 0, -1);
    SuccessorNRemove(loctestnum, loctesterr, bst2, true, 19, 20);
    RemoveSuccessor(loctestnum, loctesterr, bst3, false, 19);

    EqualBST(loctestnum, loctesterr, bst3, bst2);

    bst.Clear();

    Empty(loctestnum, loctesterr, bst, true);
    Size(loctestnum, loctesterr, bst, true, 0);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of BST<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void testBSTFloat(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of BST<double> Test" << endl;
  try {
    lasd::List<double> lst;
    InsertAtFront(loctestnum, loctesterr, lst, true, 0.0);
    InsertAtBack(loctestnum, loctesterr, lst, true, 9.1);
    InsertAtFront(loctestnum, loctesterr, lst, true, 1.9);
    InsertAtBack(loctestnum, loctesterr, lst, true, 8.2);
    InsertAtFront(loctestnum, loctesterr, lst, true, 2.8);
    InsertAtBack(loctestnum, loctesterr, lst, true, 7.3);
    InsertAtFront(loctestnum, loctesterr, lst, true, 3.7);
    InsertAtBack(loctestnum, loctesterr, lst, true, 6.4);
    InsertAtFront(loctestnum, loctesterr, lst, true, 4.6);
    InsertAtBack(loctestnum, loctesterr, lst, true, 5.5);
    InsertAtBack(loctestnum, loctesterr, lst, true, -9.1);
    InsertAtFront(loctestnum, loctesterr, lst, true, -1.9);
    InsertAtBack(loctestnum, loctesterr, lst, true, -8.2);
    InsertAtFront(loctestnum, loctesterr, lst, true, -2.8);
    InsertAtBack(loctestnum, loctesterr, lst, true, -7.3);
    InsertAtFront(loctestnum, loctesterr, lst, true, -3.7);
    InsertAtBack(loctestnum, loctesterr, lst, true, -6.4);
    InsertAtFront(loctestnum, loctesterr, lst, true, -4.6);
    InsertAtBack(loctestnum, loctesterr, lst, true, -5.5);

    TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<double>);

    lasd::BST<double> bst1(lst);

    Empty(loctestnum, loctesterr, bst1, false);
    Size(loctestnum, loctesterr, bst1, true, 19);

    TraversePreOrder(loctestnum, loctesterr, bst1, true, &TraversePrint<double>);
    TraverseInOrder(loctestnum, loctesterr, bst1, true, &TraversePrint<double>);
    TraversePostOrder(loctestnum, loctesterr, bst1, true, &TraversePrint<double>);
    TraverseBreadth(loctestnum, loctesterr, bst1, true, &TraversePrint<double>);

    Min(loctestnum, loctesterr, bst1, true, -9.1);
    Max(loctestnum, loctesterr, bst1, true, 9.1);

    Root(loctestnum, loctesterr, bst1, true, -4.6);

    lasd::BST<double> bst2;

    InsertC(loctestnum, loctesterr, bst2, true, 0.0);
    InsertC(loctestnum, loctesterr, bst2, true, -5.5);
    InsertC(loctestnum, loctesterr, bst2, true, -8.2);
    InsertC(loctestnum, loctesterr, bst2, true, -2.8);
    InsertC(loctestnum, loctesterr, bst2, true, -7.3);
    InsertC(loctestnum, loctesterr, bst2, true, -3.7);
    InsertC(loctestnum, loctesterr, bst2, true, -9.1);
    InsertC(loctestnum, loctesterr, bst2, true, -1.9);
    InsertC(loctestnum, loctesterr, bst2, true, -6.4);
    InsertC(loctestnum, loctesterr, bst2, true, -4.6);
    InsertC(loctestnum, loctesterr, bst2, true, 5.5);
    InsertC(loctestnum, loctesterr, bst2, true, 8.2);
    InsertC(loctestnum, loctesterr, bst2, true, 2.8);
    InsertC(loctestnum, loctesterr, bst2, true, 7.3);
    InsertC(loctestnum, loctesterr, bst2, true, 3.7);
    InsertC(loctestnum, loctesterr, bst2, true, 9.1);
    InsertC(loctestnum, loctesterr, bst2, true, 1.9);
    InsertC(loctestnum, loctesterr, bst2, true, 6.4);
    InsertC(loctestnum, loctesterr, bst2, true, 4.6);

    Min(loctestnum, loctesterr, bst2, true, -9.1);
    Max(loctestnum, loctesterr, bst2, true, 9.1);

    Root(loctestnum, loctesterr, bst2, true, 0.0);

    EqualBST(loctestnum, loctesterr, bst1, bst2);

    NonEqualBT(loctestnum, loctesterr, bst1, bst2);

    MinNRemove(loctestnum, loctesterr, bst1, true, -9.1);
    MaxNRemove(loctestnum, loctesterr, bst2, true, 9.1);

    NonEqualBST(loctestnum, loctesterr, bst1, bst2);

    RemovePredecessor(loctestnum, loctesterr, bst1, false, -9.0);
    PredecessorNRemove(loctestnum, loctesterr, bst2, true, -9.0, -9.1);
    SuccessorNRemove(loctestnum, loctesterr, bst1, true, 9.0, 9.1);
    RemoveSuccessor(loctestnum, loctesterr, bst2, false, 9.0);

    EqualBST(loctestnum, loctesterr, bst1, bst1);
    NonEqualBT(loctestnum, loctesterr, bst1, bst2);

    TraverseBreadth(loctestnum, loctesterr, bst1, true, &TraversePrint<double>);
    TraverseBreadth(loctestnum, loctesterr, bst2, true, &TraversePrint<double>);

    PredecessorNRemove(loctestnum, loctesterr, bst2, true, 1.5, 0.0);

    NonEqualBST(loctestnum, loctesterr, bst1, bst2);

    SuccessorNRemove(loctestnum, loctesterr, bst1, true, -1.5, 0.0);

    EqualBST(loctestnum, loctesterr, bst2, bst1);

    RemoveSuccessor(loctestnum, loctesterr, bst2, true, 5.0);

    bst1.Clear();
    bst2.Clear();

    Empty(loctestnum, loctesterr, bst1, true);
    Size(loctestnum, loctesterr, bst1, true, 0);
    Empty(loctestnum, loctesterr, bst2, true);
    Size(loctestnum, loctesterr, bst2, true, 0);
    EqualBT(loctestnum, loctesterr, bst1, bst2);
    EqualBST(loctestnum, loctesterr, bst1, bst2);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of BST<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void testBSTString(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of BST<string> Test" << endl;
  try {
    lasd::Vector<string> vec(25);
    SetAt(loctestnum, loctesterr, vec, true, 0, string("J"));
    SetAt(loctestnum, loctesterr, vec, true, 1, string("F"));
    SetAt(loctestnum, loctesterr, vec, true, 2, string("Q"));
    SetAt(loctestnum, loctesterr, vec, true, 3, string("D"));
    SetAt(loctestnum, loctesterr, vec, true, 4, string("E"));
    SetAt(loctestnum, loctesterr, vec, true, 5, string("B"));
    SetAt(loctestnum, loctesterr, vec, true, 6, string("H"));
    SetAt(loctestnum, loctesterr, vec, true, 7, string("G"));
    SetAt(loctestnum, loctesterr, vec, true, 8, string("I"));
    SetAt(loctestnum, loctesterr, vec, true, 9, string("A"));
    SetAt(loctestnum, loctesterr, vec, true, 10, string("L"));
    SetAt(loctestnum, loctesterr, vec, true, 11, string("S"));
    SetAt(loctestnum, loctesterr, vec, true, 12, string("M"));
    SetAt(loctestnum, loctesterr, vec, true, 13, string("K"));
    SetAt(loctestnum, loctesterr, vec, true, 14, string("N"));
    SetAt(loctestnum, loctesterr, vec, true, 15, string("C"));
    SetAt(loctestnum, loctesterr, vec, true, 16, string("R"));
    SetAt(loctestnum, loctesterr, vec, true, 17, string("T"));
    SetAt(loctestnum, loctesterr, vec, true, 18, string("O"));
    SetAt(loctestnum, loctesterr, vec, true, 19, string("P"));
    SetAt(loctestnum, loctesterr, vec, true, 20, string("D"));
    SetAt(loctestnum, loctesterr, vec, true, 21, string("N"));
    SetAt(loctestnum, loctesterr, vec, true, 22, string("I"));
    SetAt(loctestnum, loctesterr, vec, true, 23, string("N"));
    SetAt(loctestnum, loctesterr, vec, true, 24, string("H"));

    lasd::BST<string> bst(vec);
    Size(loctestnum, loctesterr, bst, true, 20);

    TraverseInOrder(loctestnum, loctesterr, bst, true, &TraversePrint<string>);

    lasd::BTInOrderIterator<string> itr4(bst);
    GetItrValue(loctestnum, loctesterr, itr4, true, string("A"));
    ++itr4;++itr4;++itr4;++itr4;
    GetItrValue(loctestnum, loctesterr, itr4, true, string("E"));
    ++itr4;++itr4;
    GetItrValue(loctestnum, loctesterr, itr4, true, string("G"));
    ++itr4;++itr4;
    GetItrValue(loctestnum, loctesterr, itr4, true, string("I"));
    ++itr4;++itr4;++itr4;++itr4;
    GetItrValue(loctestnum, loctesterr, itr4, true, string("M"));
    ++itr4;++itr4;++itr4;
    GetItrValue(loctestnum, loctesterr, itr4, true, string("P"));
    ++itr4;++itr4;
    GetItrValue(loctestnum, loctesterr, itr4, true, string("R"));
    ++itr4;++itr4;
    GetItrValue(loctestnum, loctesterr, itr4, true, string("T"));
    Terminated(loctestnum, loctesterr, itr4, false);
    ++itr4;
    Terminated(loctestnum, loctesterr, itr4, true);

    FoldInOrder(loctestnum, loctesterr, bst, true, &FoldStringConcatenate, string("?"), string("?ABCDEFGHIJKLMNOPQRST"));
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of BST<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void testFullExercise2B(uint & testnum, uint & testerr) {
  testBSTInt(testnum, testerr);
  testBSTFloat(testnum, testerr);
  testBSTString(testnum, testerr);
  cout << endl << "Exercise 2B (Full Test) (Errors/Tests: " << testerr << "/" << testnum << ")" << endl;
}
