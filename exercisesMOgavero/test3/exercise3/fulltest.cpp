
#include <iostream>
#include <cmath>

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/testable.hpp"
#include "../container/dictionary.hpp"
#include "../container/linear.hpp"

#include "../vector/vector.hpp"

#include "../list/list.hpp"

#include "../hashtable/hashtable.hpp"
#include "../../hashtable/clsadr/htclsadr.hpp"
#include "../../hashtable/opnadr/htopnadr.hpp"

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

void testHashTableInt(lasd::HashTable<int> & ht, const lasd::LinearContainer<int> & con, uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  try {
    lasd::Vector<int> vec(2000);
    for (int i = 0; i < 2000; ++i) {
      vec[i] = i - 1000;
    }
    Size(loctestnum, loctesterr, ht, true, 972);
    for (int i = 0; i < 1029; i += 53) {
      Exists(loctestnum, loctesterr, ht, true, con[i]);
    }
    for (int i = 0; i < 1029; i += 40) {
      Remove(loctestnum, loctesterr, ht, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, 946);
    for (int i = 0; i < 1029; i += 40) {
      Exists(loctestnum, loctesterr, ht, false, con[i]);
    }
    CountHT(loctestnum, loctesterr, ht, vec, 76);
    for (int i = 0; i < 1029; i += 20) {
      InsertC(loctestnum, loctesterr, ht, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, 972);
    for (int i = 0; i < 1029; i += 20) {
      Exists(loctestnum, loctesterr, ht, true, con[i]);
    }
    CountHT(loctestnum, loctesterr, ht, vec, 85);
    for (int i = 0; i < 1029; i += 41) {
      Remove(loctestnum, loctesterr, ht, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, 947);
    for (int i = 0; i < 1029; i += 41) {
      Exists(loctestnum, loctesterr, ht, false, con[i]);
    }
    CountHT(loctestnum, loctesterr, ht, vec, 82);
    for (int i = 0; i < 1029; i += 11) {
      InsertC(loctestnum, loctesterr, ht, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, 951);
    for (int i = 0; i < 1029; i += 11) {
      Exists(loctestnum, loctesterr, ht, true, con[i]);
    }
    CountHT(loctestnum, loctesterr, ht, vec, 83);
    ht.Resize(2003);
    for (int i = 0; i < 1029; i += 41) {
      InsertC(loctestnum, loctesterr, ht, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, 972);
    CountHT(loctestnum, loctesterr, ht, vec, 85);
    ht.Resize(4001);
    Size(loctestnum, loctesterr, ht, true, 972);
    CountHT(loctestnum, loctesterr, ht, vec, 85);
    ht.Resize(211);
    Size(loctestnum, loctesterr, ht, true, 972);
    CountHT(loctestnum, loctesterr, ht, vec, 85);
    Empty(loctestnum, loctesterr, ht, false);
    ht.Clear();
    Empty(loctestnum, loctesterr, ht, true);
    Size(loctestnum, loctesterr, ht, true, 0);
    InsertC(loctestnum, loctesterr, ht, con);
    Empty(loctestnum, loctesterr, ht, false);
    Size(loctestnum, loctesterr, ht, true, 972);
    CountHT(loctestnum, loctesterr, ht, vec, 85);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of HashTable<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void testHashTableInt(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of HashTable<int> Test" << endl;
  try {
    lasd::Vector<int> vec(1029);
    for (uint i = 0; i < 1029; i++) {
      vec[i] = pow(-2, i % 24) * ((127 * i + 31) % 1029);
    }

    lasd::HashTableClsAdr<int> htclsadr(343, vec);
    cout << endl << "Begin of HashTableClsAdr<int> Test:" << endl;
    testHashTableInt(htclsadr, vec, loctestnum, loctesterr);
    lasd::HashTableOpnAdr<int> htopnadr(343, vec);
    cout << endl << "Begin of HashTableOpnAdr<int> Test:" << endl;
    testHashTableInt(htopnadr, vec, loctestnum, loctesterr);
    cout << "\n";

    lasd::HashTableClsAdr<int> cophtclsadr(htclsadr);
    Size(loctestnum, loctesterr, htclsadr, true, 972);
    Size(loctestnum, loctesterr, cophtclsadr, true, 972);
    EqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    htclsadr.Clear();
    Empty(loctestnum, loctesterr, htclsadr, true);
    Size(loctestnum, loctesterr, htclsadr, true, 0);
    NonEqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    htclsadr = std::move(cophtclsadr);
    NonEqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    Empty(loctestnum, loctesterr, htclsadr, false);
    Size(loctestnum, loctesterr, htclsadr, true, 972);
    Empty(loctestnum, loctesterr, cophtclsadr, true);
    Size(loctestnum, loctesterr, cophtclsadr, true, 0);
    cophtclsadr = htclsadr;
    EqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    Empty(loctestnum, loctesterr, cophtclsadr, false);
    Size(loctestnum, loctesterr, cophtclsadr, true, 972);

    lasd::HashTableOpnAdr<int> cophtopnadr(htopnadr);
    Size(loctestnum, loctesterr, htopnadr, true, 972);
    Size(loctestnum, loctesterr, cophtopnadr, true, 972);
    EqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    htopnadr.Clear();
    Empty(loctestnum, loctesterr, htopnadr, true);
    Size(loctestnum, loctesterr, htopnadr, true, 0);
    NonEqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    htopnadr = std::move(cophtopnadr);
    NonEqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    Empty(loctestnum, loctesterr, htopnadr, false);
    Size(loctestnum, loctesterr, htopnadr, true, 972);
    Empty(loctestnum, loctesterr, cophtopnadr, true);
    Size(loctestnum, loctesterr, cophtopnadr, true, 0);
    cophtopnadr = htopnadr;
    EqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    Empty(loctestnum, loctesterr, cophtopnadr, false);
    Size(loctestnum, loctesterr, cophtopnadr, true, 972);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of HashTable<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void testHashTableFloat(lasd::HashTable<double> & ht, const lasd::LinearContainer<double> & con, uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  try {
    Size(loctestnum, loctesterr, ht, true, 1023);
    for (int i = 0; i < 1029; i += 23) {
      Exists(loctestnum, loctesterr, ht, true, con[i]);
    }
    for (int i = 0; i < 1029; i += 23) {
      Remove(loctestnum, loctesterr, ht, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, 978);
    for (int i = 0; i < 1029; i += 23) {
      Exists(loctestnum, loctesterr, ht, false, con[i]);
    }
    for (int i = 0; i < 1029; i += 22) {
      Remove(loctestnum, loctesterr, ht, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, 934);
    for (int i = 0; i < 1029; i += 22) {
      Exists(loctestnum, loctesterr, ht, false, con[i]);
    }
    for (int i = 0; i < 1029; i += 23) {
      InsertC(loctestnum, loctesterr, ht, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, 979);
    for (int i = 0; i < 1029; i += 23) {
      Exists(loctestnum, loctesterr, ht, true, con[i]);
    }
    ht.Resize(4001);
    Size(loctestnum, loctesterr, ht, true, 979);
    ht.Resize(211);
    Size(loctestnum, loctesterr, ht, true, 979);
    for (int i = 0; i < 1029; i += 22) {
      InsertC(loctestnum, loctesterr, ht, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, 1023);
    for (int i = 0; i < 1029; i += 22) {
      Exists(loctestnum, loctesterr, ht, true, con[i]);
    }
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of HashTable<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void testHashTableFloat(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of HashTable<double> Test" << endl;
  try {
    lasd::List<double> lst;
    for (uint i = 0; i < 1029; i++) {
      lst.InsertAtFront((pow(-2, i % 24) * ((127 * i + 31) % 1029)) / (343 * pow(-3, i % 7)));
    }

    lasd::HashTableClsAdr<double> htclsadr(343, lst);
    cout << endl << "Begin of HashTableClsAdr<double> Test:" << endl;
    testHashTableFloat(htclsadr, lst, loctestnum, loctesterr);
    lasd::HashTableOpnAdr<double> htopnadr(343, lst);
    cout << endl << "Begin of HashTableOpnAdr<double> Test:" << endl;
    testHashTableFloat(htopnadr, lst, loctestnum, loctesterr);
    cout << "\n";

    lasd::HashTableClsAdr<double> cophtclsadr(htclsadr);
    Size(loctestnum, loctesterr, htclsadr, true, 1023);
    Size(loctestnum, loctesterr, cophtclsadr, true, 1023);
    EqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    htclsadr.Clear();
    Empty(loctestnum, loctesterr, htclsadr, true);
    Size(loctestnum, loctesterr, htclsadr, true, 0);
    NonEqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    htclsadr = std::move(cophtclsadr);
    NonEqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    Empty(loctestnum, loctesterr, htclsadr, false);
    Size(loctestnum, loctesterr, htclsadr, true, 1023);
    Empty(loctestnum, loctesterr, cophtclsadr, true);
    Size(loctestnum, loctesterr, cophtclsadr, true, 0);
    cophtclsadr = htclsadr;
    EqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    Empty(loctestnum, loctesterr, cophtclsadr, false);
    Size(loctestnum, loctesterr, cophtclsadr, true, 1023);

    lasd::HashTableOpnAdr<double> cophtopnadr(htopnadr);
    Size(loctestnum, loctesterr, htopnadr, true, 1023);
    Size(loctestnum, loctesterr, cophtopnadr, true, 1023);
    EqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    htopnadr.Clear();
    Empty(loctestnum, loctesterr, htopnadr, true);
    Size(loctestnum, loctesterr, htopnadr, true, 0);
    NonEqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    htopnadr = std::move(cophtopnadr);
    NonEqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    Empty(loctestnum, loctesterr, htopnadr, false);
    Size(loctestnum, loctesterr, htopnadr, true, 1023);
    Empty(loctestnum, loctesterr, cophtopnadr, true);
    Size(loctestnum, loctesterr, cophtopnadr, true, 0);
    cophtopnadr = htopnadr;
    EqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    Empty(loctestnum, loctesterr, cophtopnadr, false);
    Size(loctestnum, loctesterr, cophtopnadr, true, 1023);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of HashTable<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void testHashTableString(lasd::HashTable<string> & ht, const lasd::LinearContainer<string> & con, uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  try {
    Size(loctestnum, loctesterr, ht, true, 1029);
    for (int i = 0; i < 1029; i += 21) {
      Exists(loctestnum, loctesterr, ht, true, con[i]);
    }
    for (int i = 0; i < 1029; i += 21) {
      Remove(loctestnum, loctesterr, ht, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, 980);
    for (int i = 0; i < 1029; i += 21) {
      Exists(loctestnum, loctesterr, ht, false, con[i]);
    }
    for (int i = 0; i < 1029; i += 31) {
      Remove(loctestnum, loctesterr, ht, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, 948);
    for (int i = 0; i < 1029; i += 31) {
      Exists(loctestnum, loctesterr, ht, false, con[i]);
    }
    for (int i = 0; i < 1029; i += 21) {
      InsertC(loctestnum, loctesterr, ht, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, 997);
    for (int i = 0; i < 1029; i += 21) {
      Exists(loctestnum, loctesterr, ht, true, con[i]);
    }
    ht.Resize(3631);
    Size(loctestnum, loctesterr, ht, true, 997);
    ht.Resize(797);
    Size(loctestnum, loctesterr, ht, true, 997);
    for (int i = 0; i < 1029; i += 31) {
      InsertC(loctestnum, loctesterr, ht, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, 1029);
    for (int i = 0; i < 1029; i += 31) {
      Exists(loctestnum, loctesterr, ht, true, con[i]);
    }
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of HashTable<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void testHashTableString(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of HashTable<string> Test" << endl;
  try {
    lasd::Vector<string> vec(1029);
    vec[0] = "@";
    for (uint i = 1; i < 49; i++) {
      vec[i] = vec[i - 1] + static_cast<char>(32 + ((127 * i + 31) % 95));
    }
    for (uint i = 49; i < 1029; i++) {
      vec[i] = vec[i - 1];
      vec[i][i % 49] = static_cast<char>(32 + ((127 * i + 31) % 95));
    }

    lasd::HashTableClsAdr<string> htclsadr(523, vec);
    cout << endl << "Begin of HashTableClsAdr<string> Test:" << endl;
    testHashTableString(htclsadr, vec, loctestnum, loctesterr);
    lasd::HashTableOpnAdr<string> htopnadr(523, vec);
    cout << endl << "Begin of HashTableOpnAdr<string> Test:" << endl;
    testHashTableString(htopnadr, vec, loctestnum, loctesterr);
    cout << "\n";

    lasd::HashTableClsAdr<string> cophtclsadr(htclsadr);
    Size(loctestnum, loctesterr, htclsadr, true, 1029);
    Size(loctestnum, loctesterr, cophtclsadr, true, 1029);
    EqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    htclsadr.Clear();
    Empty(loctestnum, loctesterr, htclsadr, true);
    Size(loctestnum, loctesterr, htclsadr, true, 0);
    NonEqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    htclsadr = std::move(cophtclsadr);
    NonEqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    Empty(loctestnum, loctesterr, htclsadr, false);
    Size(loctestnum, loctesterr, htclsadr, true, 1029);
    Empty(loctestnum, loctesterr, cophtclsadr, true);
    Size(loctestnum, loctesterr, cophtclsadr, true, 0);
    cophtclsadr = htclsadr;
    EqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    Empty(loctestnum, loctesterr, cophtclsadr, false);
    Size(loctestnum, loctesterr, cophtclsadr, true, 1029);

    lasd::HashTableOpnAdr<string> cophtopnadr(htopnadr);
    Size(loctestnum, loctesterr, htopnadr, true, 1029);
    Size(loctestnum, loctesterr, cophtopnadr, true, 1029);
    EqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    htopnadr.Clear();
    Empty(loctestnum, loctesterr, htopnadr, true);
    Size(loctestnum, loctesterr, htopnadr, true, 0);
    NonEqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    htopnadr = std::move(cophtopnadr);
    NonEqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    Empty(loctestnum, loctesterr, htopnadr, false);
    Size(loctestnum, loctesterr, htopnadr, true, 1029);
    Empty(loctestnum, loctesterr, cophtopnadr, true);
    Size(loctestnum, loctesterr, cophtopnadr, true, 0);
    cophtopnadr = htopnadr;
    EqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    Empty(loctestnum, loctesterr, cophtopnadr, false);
    Size(loctestnum, loctesterr, cophtopnadr, true, 1029);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of HashTable<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void testFullExercise3(uint & testnum, uint & testerr) {
  testHashTableInt(testnum, testerr);
  testHashTableFloat(testnum, testerr);
  testHashTableString(testnum, testerr);
  cout << endl << "Exercise 3 (Full Test) (Errors/Tests: " << testerr << "/" << testnum << ")" << endl;
}
