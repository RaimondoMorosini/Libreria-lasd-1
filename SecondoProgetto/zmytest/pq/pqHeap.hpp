#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include "../../pq/heap/pqheap.hpp"
#include "../util/test_utils.hpp"
#include "../../vector/vector.hpp"

using namespace lasd;

template <typename T>
void TestPQHeap() {
  std::cout << "\n=== Testing PQHeap<" << typeid(T).name() << "> ===\n";

  // 1. Default constructor
  {
    PQHeap<T> pq;
    ASSERT_TRUE(pq.Empty());
    ASSERT_EQ(pq.Size(), 0);
  }

  // 2. Costruttore da TraversableContainer
  {
    Vector<T> vec(5);
    vec[0] = MakeValue<T>(3);
    vec[1] = MakeValue<T>(1);
    vec[2] = MakeValue<T>(4);
    vec[3] = MakeValue<T>(1);
    vec[4] = MakeValue<T>(5);

    PQHeap<T> pq(vec);
    ASSERT_EQ(pq.Size(), 5);
    ASSERT_EQ(pq.Tip(), MakeValue<T>(5));
  }

  // 3. Costruttore da MappableContainer (move)
  {
    Vector<T> vec(3);
    vec[0] = MakeValue<T>(7);
    vec[1] = MakeValue<T>(2);
    vec[2] = MakeValue<T>(6);

    PQHeap<T> pq(std::move(vec));
    ASSERT_EQ(pq.Size(), 3);
    ASSERT_TRUE(pq.Exists(MakeValue<T>(7)));
    ASSERT_TRUE(pq.Exists(MakeValue<T>(2)));
    ASSERT_TRUE(pq.Exists(MakeValue<T>(6)));
    ASSERT_EQ(pq.Tip(), MakeValue<T>(7));

    pq.Clear(); // Clear the priority queue
    ASSERT_TRUE(pq.Empty());


  }

  // 4. Copy constructor
  {
    Vector<T> vec(3);
    vec[0] = MakeValue<T>(9);
    vec[1] = MakeValue<T>(8);
    vec[2] = MakeValue<T>(7);

    PQHeap<T> pq1(vec);
    PQHeap<T> pq2(pq1);

    ASSERT_EQ(pq1.Size(), pq2.Size());
    ASSERT_EQ(pq1.Tip(), pq2.Tip());
    //verifica se hanno tutti gli elementi
    ASSERT_TRUE(pq1.Exists(MakeValue<T>(9)));
    ASSERT_TRUE(pq1.Exists(MakeValue<T>(8)));
    ASSERT_TRUE(pq1.Exists(MakeValue<T>(7)));
    ASSERT_TRUE(pq2.Exists(MakeValue<T>(9)));
    ASSERT_TRUE(pq2.Exists(MakeValue<T>(8)));
    ASSERT_TRUE(pq2.Exists(MakeValue<T>(7)));

}

  // 5. Move constructor
  {
    Vector<T> vec(2);
    vec[0] = MakeValue<T>(1);
    vec[1] = MakeValue<T>(2);

    PQHeap<T> pq1(vec);
    PQHeap<T> pq2(std::move(pq1));

    ASSERT_EQ(pq2.Size(), 2);
    ASSERT_EQ(pq2.Tip(), MakeValue<T>(2));

    std::vector<T> emptyCheck;
    pq1.Traverse([&](const T &v) { emptyCheck.push_back(v); });
    ASSERT_EQ(emptyCheck.size(), 0);
  }

  // 6. Copy assignment
  {
    Vector<T> vec(3);
    vec[0] = MakeValue<T>(3);
    vec[1] = MakeValue<T>(4);
    vec[2] = MakeValue<T>(5);

    PQHeap<T> pq1(vec);
    PQHeap<T> pq2;
    pq2 = pq1;

    ASSERT_EQ(pq2.Tip(), MakeValue<T>(5));
    ASSERT_EQ(pq2.Size(), 3);
    ASSERT_TRUE(pq2.Exists(MakeValue<T>(3)));
    ASSERT_TRUE(pq2.Exists(MakeValue<T>(4)));
    ASSERT_TRUE(pq2.Exists(MakeValue<T>(5)));

  }

  // 7. Move assignment con pq vuoto
  {
    Vector<T> vec(3);
    vec[0] = MakeValue<T>(7);
    vec[1] = MakeValue<T>(6);
    vec[2] = MakeValue<T>(8);

    PQHeap<T> pq1(vec);
    PQHeap<T> pq2;
    pq2 = std::move(pq1);

    ASSERT_EQ(pq2.Tip(), MakeValue<T>(8));
    ASSERT_EQ(pq2.Size(), 3);

    std::vector<T> movedOut;
    pq1.Traverse([&](const T &v) { movedOut.push_back(v); });
    ASSERT_EQ(movedOut.size(), 0);
    ASSERT_EQ(pq1.Size(), 0);
  }
  //7.1 Move assignment con pq non vuoto
  {
    Vector<T> vec1(3);
    vec1[0] = MakeValue<T>(10);
    vec1[1] = MakeValue<T>(20);
    vec1[2] = MakeValue<T>(30);
    PQHeap<T> pq1(vec1);

    // Creiamo un altro heap con 4 elementi: {1, 15, 25,35}
    Vector<T> vec2(4);
    vec2[0] = MakeValue<T>(1);
    vec2[1] = MakeValue<T>(15);
    vec2[2] = MakeValue<T>(25);
    vec2[3] = MakeValue<T>(35);
    PQHeap<T> pq2(vec2);
    pq2 = std::move(pq1);

    ASSERT_EQ(pq2.Tip(), MakeValue<T>(30));
    ASSERT_EQ(pq2.Size(), 3);
    ASSERT_TRUE(pq2.Exists(MakeValue<T>(10)));
    ASSERT_TRUE(pq2.Exists(MakeValue<T>(20)));

    // pq1 ora deve contenere gli elementi di pq2
    ASSERT_EQ(pq1.Size(), 4);
    //inserisci un un vettore ed ordina std 

    ASSERT_EQ(pq1.Tip(), MakeValue<T>(35));
    ASSERT_TRUE(pq1.Exists(MakeValue<T>(1)));
    ASSERT_TRUE(pq1.Exists(MakeValue<T>(15)));
    ASSERT_TRUE(pq1.Exists(MakeValue<T>(25)));
    ASSERT_TRUE(pq1.Exists(MakeValue<T>(35)));

    std::vector<T> movedOut;
    pq1.Traverse([&](const T &v) { movedOut.push_back(v); });
    ASSERT_EQ(movedOut.size(), 4);
    ASSERT_EQ(pq1.Size(), 4);
  }

  // 8. Insert e Tip/TipNRemove/RemoveTip
  {
    PQHeap<T> pq;
    pq.Insert(MakeValue<T>(10));
    pq.Insert(MakeValue<T>(20));
    pq.Insert(MakeValue<T>(1));

    ASSERT_EQ(pq.Tip(), MakeValue<T>(20));
    T removed = pq.TipNRemove();
    ASSERT_EQ(removed, MakeValue<T>(20));
    ASSERT_EQ(pq.Tip(), MakeValue<T>(10));

    pq.RemoveTip();
    ASSERT_EQ(pq.Tip(), MakeValue<T>(1));
  }

  // 9. Change (by index)
  {
    Vector<T> vec(4);
    vec[0] = MakeValue<T>(10);
    vec[1] = MakeValue<T>(30);
    vec[2] = MakeValue<T>(20);
    vec[3] = MakeValue<T>(40);

    PQHeap<T> pq(vec);
    ASSERT_EQ(pq.Tip(), MakeValue<T>(40));

    pq.Change(1, MakeValue<T>(50));  // index 1, arbitrary but legal
    ASSERT_EQ(pq.Tip(), MakeValue<T>(50));
  }
  // 9.1 casi limite per Change
  {
    PQHeap<T> pq;
    pq.Insert(MakeValue<T>(100));
    ASSERT_EQ(pq.Tip(), MakeValue<T>(100));

    // Cambiamo il valore in root
    pq.Change(0, MakeValue<T>(200));
    ASSERT_EQ(pq.Tip(), MakeValue<T>(200));

    pq.Insert(MakeValue<T>(150));
    ASSERT_EQ(pq.Tip(), MakeValue<T>(200));  // 200 è ancora il massimo
    pq.Insert(MakeValue<T>(250));
    ASSERT_EQ(pq.Tip(), MakeValue<T>(250));  // 250 è il nuovo massimo
    //rimuoviamo il massimo
    pq.RemoveTip();
    ASSERT_EQ(pq.Tip(), MakeValue<T>(200));  // 200 è il nuovo massimo


    // Cambiamo un indice non valido
    bool caught = false;
    try {
      pq.Change(4, MakeValue<T>(300));  // index out of bounds
    } catch (const std::out_of_range &) {
      caught = true;
    }
    ASSERT_TRUE(caught);
  } 

  // 10. Eccezioni Tip/RemoveTip/TipNRemove su PQ vuota
  {
    PQHeap<T> pq;
    bool caught = false;
    try {
      pq.Tip();
    } catch (const std::length_error &) {
      caught = true;
    }
    ASSERT_TRUE(caught);

    caught = false;
    try {
      pq.RemoveTip();
    } catch (const std::length_error &) {
      caught = true;
    }
    ASSERT_TRUE(caught);

    caught = false;
    try {
      pq.TipNRemove();
    } catch (const std::length_error &) {
      caught = true;
    }
    ASSERT_TRUE(caught);
  }

  // 11. Costruzioni e assegnazioni tra HeapVec e PQHeap
{
  // Creiamo un HeapVec con alcuni valori
  Vector<T> vec(5);
  vec[0] = MakeValue<T>(10);
  vec[1] = MakeValue<T>(20);
  vec[2] = MakeValue<T>(30);
  vec[3] = MakeValue<T>(40);
  vec[4] = MakeValue<T>(50);

  HeapVec<T> hv(vec);
  ASSERT_TRUE(hv.IsHeap());
  ASSERT_EQ(hv.Size(), 5);

  // Costruzione PQHeap da HeapVec (da TraversableContainer)
  PQHeap<T> pq1(hv);
  ASSERT_EQ(pq1.Size(), hv.Size());
  ASSERT_EQ(pq1.TipNRemove(), MakeValue<T>(50));
    ASSERT_EQ(pq1.Size(), 4); // Dopo TipNRemove, la size deve essere diminuita
  ASSERT_EQ(pq1.TipNRemove(), MakeValue<T>(40));
  ASSERT_EQ(pq1.Size(), 3); // Dopo TipNRemove, la size deve essere diminuita
  ASSERT_EQ(pq1.TipNRemove(), MakeValue<T>(30));
    ASSERT_EQ(pq1.Size(), 2); // Dopo TipNRemove, la size deve essere diminuita
    ASSERT_EQ(pq1.TipNRemove(), MakeValue<T>(20));
    ASSERT_EQ(pq1.Size(), 1); // Dopo TipNRemove, la size deve essere diminuita
    ASSERT_EQ(pq1.TipNRemove(), MakeValue<T>(10));
    ASSERT_EQ(pq1.Size(), 0); // Dopo TipNRemove, la size deve essere diminuita
std::cout << "PQHeap created from HeapVec with size: " << pq1.Size() << "\n";

  // Copy constructor PQHeap da pq1
  PQHeap<T> pq2(pq1);
  ASSERT_EQ(pq2.Size(), pq1.Size());
ASSERT_EQ(pq2.Size(), 0); // pq1 è vuoto, quindi anche pq2 deve essere vuoto

  // Copy assignment PQHeap

  PQHeap<T> pq3 = hv; // Assegnazione da HeapVec a PQHeap
    ASSERT_EQ(pq3.Size(), hv.Size());
    ASSERT_EQ(pq3.Tip(), MakeValue<T>(50)); // Il massimo deve essere 50

    ASSERT_TRUE(pq3.Exists(MakeValue<T>(10)));
    ASSERT_TRUE(pq3.Exists(MakeValue<T>(20)));
    ASSERT_TRUE(pq3.Exists(MakeValue<T>(30)));
    ASSERT_TRUE(pq3.Exists(MakeValue<T>(40)));

  // Move constructor PQHeap da pq3
  PQHeap<T> pq4(std::move(pq3));
  ASSERT_EQ(pq4.Size(), hv.Size());
  ASSERT_EQ(pq3.Size(), 0); // pq3 deve essere vuoto

  // Move assignment PQHeap da pq4
  PQHeap<T> pq5;
  pq5 = std::move(pq4);
  ASSERT_EQ(pq5.Size(), hv.Size());
  ASSERT_EQ(pq5.Tip(), MakeValue<T>(50)); // Il massimo deve essere 50
  ASSERT_EQ(pq4.Size(), 0);

  // Copy constructor HeapVec da hv
  HeapVec<T> hv2(hv);
  ASSERT_EQ(hv2.Size(), hv.Size());


}



  

  std::cout << "All tests passed for PQHeap<" << typeid(T).name() << ">.\n";
}
