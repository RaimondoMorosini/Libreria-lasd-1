#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include "../../heap/vec/heapvec.hpp"
#include "../util/test_utils.hpp"  // Contiene la definizione di ASSERT_EQ, ASSERT_TRUE, ASSERT_FALSE, MakeValue, ecc.
#include "../../vector/vector.hpp" // Per poter costruire un Vector<T> come Traversable/Mappable

using namespace lasd;

template <typename T>
void TestHeapVec() {
  std::cout << "\n=== Testing HeapVec<" << typeid(T).name() << "> ===\n";

  // 1. Default constructor
  {
    HeapVec<T> emptyHeap;
    // Un heap appena costruito deve essere vuoto e rispettare IsHeap()
    ASSERT_TRUE(emptyHeap.IsHeap());

    // Verifichiamo che non ci siano elementi tramite Traverse
    std::vector<T> elems;
    emptyHeap.Traverse([&](const T &v) { elems.push_back(v); });
    ASSERT_EQ(elems.size(), 0);
  }

  // 2. Costruttore da TraversableContainer (Vector<T>)
  {
    // Prepariamo un Vector<T> di 8 elementi: {3, 1, 4, 1, 5, 9, 2, 6}
    Vector<T> sourceVec(8);
    T raw[8] = {
      MakeValue<T>(3),
      MakeValue<T>(1),
      MakeValue<T>(4),
      MakeValue<T>(1),
      MakeValue<T>(5),
      MakeValue<T>(9),
      MakeValue<T>(2),
      MakeValue<T>(6)
    };
    for (unsigned i = 0; i < 8; ++i) {
      sourceVec[i] = raw[i];
    }

    // Costruiamo l'heap a partire da sourceVec
    HeapVec<T> heapFromTraversable(sourceVec);

    // 2.1 Verifichiamo che IsHeap() sia true
    ASSERT_TRUE(heapFromTraversable.IsHeap());

    // 2.2 Usiamo Traverse per raccogliere tutti gli elementi interni
    std::vector<T> collected;
    heapFromTraversable.Traverse([&](const T &v) { collected.push_back(v); });

    // Il massimo valore nella lista originale era raw[5] == 9
    ASSERT_EQ(collected.front(), MakeValue<T>(9));
    ASSERT_EQ(collected.size(), 8);
  }

  // 3. Costruttore da MappableContainer (move di Vector<T>)
  {
    // Creiamo un Vector<T> di 5 elementi: {10, 20, 15, 30, 25}
    Vector<T> tempVec(5);
    tempVec[0] = MakeValue<T>(10);
    tempVec[1] = MakeValue<T>(20);
    tempVec[2] = MakeValue<T>(15);
    tempVec[3] = MakeValue<T>(30);
    tempVec[4] = MakeValue<T>(25);

    // Muoviamo tempVec dentro HeapVec
    HeapVec<T> heapFromMappable(std::move(tempVec));

    //verifichiamo che la size sia corretta
    ASSERT_EQ(heapFromMappable.Size(), 5);
    
    // verifichiamo che esistono tutti gli elementi
    ASSERT_TRUE(heapFromMappable.Exists(MakeValue<T>(10)));
    ASSERT_TRUE(heapFromMappable.Exists(MakeValue<T>(20)));
    ASSERT_TRUE(heapFromMappable.Exists(MakeValue<T>(15)));
    ASSERT_TRUE(heapFromMappable.Exists(MakeValue<T>(30)));
    ASSERT_TRUE(heapFromMappable.Exists(MakeValue<T>(25)));

    // Dopo il move, l'heap deve essere valido
    ASSERT_TRUE(heapFromMappable.IsHeap());

    // E tempVec deve risultare “vuoto” (size = 0)
    //stampiamo gli elementi di tempVec per verificare che sia vuoto
    std::cout << "Elements in tempVec after move: ";
    tempVec.Traverse([](const T &v) { std::cout << v << " "; });
    std::vector<T> afterMove;
    tempVec.Traverse([&](const T &v) { afterMove.push_back(v); });
    ASSERT_EQ(afterMove.size(), 0);
  }

  // 4. Copy constructor
  {
    // Partiamo da un Vector<T> di 4 elementi: {2, 8, 5, 1}
    Vector<T> baseVec(4);
    baseVec[0] = MakeValue<T>(2);
    baseVec[1] = MakeValue<T>(8);
    baseVec[2] = MakeValue<T>(5);
    baseVec[3] = MakeValue<T>(1);

    HeapVec<T> originalHeap(baseVec);
    ASSERT_TRUE(originalHeap.IsHeap());

    // Copia profonda
    HeapVec<T> copyHeap(originalHeap);
    ASSERT_TRUE(copyHeap.IsHeap());
    ASSERT_TRUE(copyHeap == originalHeap);

    // Se modifico originalHeap via Sort, la copia non cambia
    originalHeap.Sort();
    ASSERT_FALSE(originalHeap == copyHeap);
  }

  // 5. Move constructor
  {
    // Vector<T> di 3 elementi: {7, 3, 5}
    Vector<T> src(3);
    src[0] = MakeValue<T>(7);
    src[1] = MakeValue<T>(3);
    src[2] = MakeValue<T>(5);
    HeapVec<T> toMove(src);
    ASSERT_TRUE(toMove.IsHeap());

    // Muoviamo in un nuovo oggetto
    HeapVec<T> movedHeap(std::move(toMove));
    ASSERT_TRUE(movedHeap.IsHeap());

    // toMove ora deve essere vuoto
    std::vector<T> emptyCheck;
    toMove.Traverse([&](const T &v) { emptyCheck.push_back(v); });
    ASSERT_EQ(emptyCheck.size(), 0);
  }

  // 6. Copy assignment
  {
    // Vector<T> di 3 elementi: {11, 22, 33}
    Vector<T> v1(3);
    v1[0] = MakeValue<T>(11);
    v1[1] = MakeValue<T>(22);
    v1[2] = MakeValue<T>(33);
    HeapVec<T> heapA(v1);

    HeapVec<T> heapB;
    heapB = heapA;  // copy assignment

    ASSERT_TRUE(heapB.IsHeap());
    ASSERT_TRUE(heapB == heapA);

    // Self-assignment non deve cambiare nulla
    heapB = heapB;
    ASSERT_TRUE(heapB == heapA);

    // Modifico heapA via Sort: ora non sono più uguali
    heapA.Sort();
    ASSERT_FALSE(heapB == heapA);
  }

  // 7. Move assignment
  {
    // Vector<T> di 4 elementi: {4, 1, 6, 2}
    Vector<T> v2(4);
    v2[0] = MakeValue<T>(4);
    v2[1] = MakeValue<T>(1);
    v2[2] = MakeValue<T>(6);
    v2[3] = MakeValue<T>(2);
    HeapVec<T> heapC(v2);

    HeapVec<T> heapD;
    heapD = std::move(heapC);  // move assignment

    ASSERT_TRUE(heapD.IsHeap());

    // heapC ora deve essere vuoto
    std::vector<T> movedOut;
    heapC.Traverse([&](const T &v) { movedOut.push_back(v); });
    ASSERT_EQ(movedOut.size(), 0);
  }

  // 8. operator== e operator!=
  {
    // Vector<T> di 5 elementi: {9, 7, 3, 8, 6}
    Vector<T> v3(5);
    v3[0] = MakeValue<T>(9);
    v3[1] = MakeValue<T>(7);
    v3[2] = MakeValue<T>(3);
    v3[3] = MakeValue<T>(8);
    v3[4] = MakeValue<T>(6);

    HeapVec<T> h1(v3);
    HeapVec<T> h2(v3);

    // Due heap costruiti dallo stesso vettore devono essere uguali
    ASSERT_TRUE(h1 == h2);
    ASSERT_FALSE(h1 != h2);

    // Se ordino h2 con Sort, non saranno più uguali
    h2.Sort();
    ASSERT_FALSE(h1 == h2);
    ASSERT_TRUE(h1 != h2);
  }

  // 9. IsHeap() su casi limite
  {
    // 9.1 Heap vuoto
    HeapVec<T> hEmpty;
    ASSERT_TRUE(hEmpty.IsHeap());

    // 9.2 Heap di un solo elemento
    Vector<T> singleVec(1);
    singleVec[0] = MakeValue<T>(42);
    HeapVec<T> hSingle(singleVec);
    ASSERT_TRUE(hSingle.IsHeap());
  }

  // 10. Sort() e verifica ordinamento
  {
    // Prepariamo un Vector<T> di 6 elementi: {5, 2, 9, 1, 7, 3}
    Vector<T> unsortedVec(6);
    unsortedVec[0] = MakeValue<T>(5);
    unsortedVec[1] = MakeValue<T>(2);
    unsortedVec[2] = MakeValue<T>(9);
    unsortedVec[3] = MakeValue<T>(1);
    unsortedVec[4] = MakeValue<T>(7);
    unsortedVec[5] = MakeValue<T>(3);

    HeapVec<T> hSort(unsortedVec);
    ASSERT_TRUE(hSort.IsHeap());

    // Raccogliamo i valori prima di Sort (non necessariamente ordinati)
    std::vector<T> beforeSort;
    hSort.Traverse([&](const T &v) { beforeSort.push_back(v); });
    ASSERT_EQ(beforeSort.size(), 6);

    // Chiamiamo Sort()
    hSort.Sort();

    // Dopo Sort, l'invariante di heap NON deve più valere
    ASSERT_FALSE(hSort.IsHeap());

    // Raccogliamo i valori dopo Sort: devono essere in ordine crescente
    std::vector<T> afterSort;
    hSort.Traverse([&](const T &v) { afterSort.push_back(v); });
    ASSERT_EQ(afterSort.size(), 6);
    ASSERT_TRUE(std::is_sorted(afterSort.begin(), afterSort.end()));
  }

  // 11. Integrazione con Traverse e Map, poi Heapify()
  {
    // Vector<T> di 5 elementi: {2, 4, 6, 8, 10}
    Vector<T> base2(5);
    base2[0] = MakeValue<T>(2);
    base2[1] = MakeValue<T>(4);
    base2[2] = MakeValue<T>(6);
    base2[3] = MakeValue<T>(8);
    base2[4] = MakeValue<T>(10);

    HeapVec<T> hIM(base2);
    ASSERT_TRUE(hIM.IsHeap());

    // 11.1 Traverse deve raccogliere esattamente 5 valori
    std::vector<T> col;
    hIM.Traverse([&](const T &v) { col.push_back(v); });
    ASSERT_EQ(col.size(), 5);

    // 11.2 Map: raddoppiamo ogni elemento
    hIM.Map([](T &val) { val = val * 2; });

    // Dopo Map, l'invariante di heap NON è più garantita
    ASSERT_FALSE(hIM.IsHeap());

    // Chiamiamo Heapify() per ripristinare la proprietà di heap
    hIM.Heapify();
    ASSERT_TRUE(hIM.IsHeap());

    // Verifichiamo che il nuovo massimo (originariamente 10) sia diventato 20 e sia in root
    std::vector<T> postMap;
    hIM.Traverse([&](const T &v) { postMap.push_back(v); });
    ASSERT_EQ(postMap.front(), MakeValue<T>(20));
  }

  std::cout << "All tests passed for HeapVec<" << typeid(T).name() << ">.\n";
}
