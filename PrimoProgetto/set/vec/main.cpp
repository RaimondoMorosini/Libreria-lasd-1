#include <iostream>
#include "../../vector/vector.hpp"
#include "setvec.hpp"

using namespace lasd;

int main() {
  std::cout << "===== Creazione di un Vector<int> =====\n";
  Vector<int> v(5);
  for (ulong i = 0; i < 5; ++i) {
    v[i] = i + 1; // 1, 2, 3, 4, 5
  }

  std::cout << "===== Costruttore SetVec da TraversableContainer =====\n";
  SetVec<int> set1(v);
  std::cout << "Set1 Size: " << set1.Size() << "\n";
  for (int i = 1; i <= 5; ++i) {
    std::cout << "Set1.Exists(" << i << "): " << set1.Exists(i) << "\n";
  }

  std::cout << "\n===== Costruttore di copia =====\n";
  SetVec<int> set2(set1);
  std::cout << "Set2 Size: " << set2.Size() << "\n";
  std::cout << "Set2.Exists(3): " << set2.Exists(3) << "\n";

  std::cout << "\n===== Operatore di assegnazione (copia) =====\n";
  SetVec<int> set3;
  set3 = set2;
  std::cout << "Set3 Size: " << set3.Size() << "\n";
  std::cout << "Set3.Exists(4): " << set3.Exists(4) << "\n";

  std::cout << "\n===== Costruttore di move =====\n";
  SetVec<int> set4(std::move(set2));
  std::cout << "Set4 Size: " << set4.Size() << "\n";
  std::cout << "Set4.Exists(5): " << set4.Exists(5) << "\n";

  std::cout << "Set2 Size dopo il move: " << set2.Size() << "\n";

  std::cout << "\n===== Operatore di assegnazione (move) =====\n";
  SetVec<int> set5;
  set5 = std::move(set3);
  std::cout << "Set5 Size: " << set5.Size() << "\n";
  std::cout << "Set5.Exists(2): " << set5.Exists(2) << "\n";

  std::cout << "Set3 Size dopo il move: " << set3.Size() << "\n";

  std::cout << "\n===== Test Insert su Set5 =====\n";
  set5.Insert(42);
  std::cout << "Set5.Exists(42): " << set5.Exists(42) << "\n";
  std::cout << "Set5 Size: " << set5.Size() << "\n";

  return 0;
}
