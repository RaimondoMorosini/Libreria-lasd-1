#ifndef SETLST_TPP
#define SETLST_TPP

#include <stdexcept>
#include <utility>
#include <vector>
#include <algorithm>

namespace lasd
{

  /* ************************************************************************** */

  // Costruttore da TraversableContainer
  template <typename Data>
  SetLst<Data>::SetLst(const TraversableContainer<Data> &con)
  {
    SortableVector<Data> tempVec(con); // Copia gli elementi
    tempVec.Sort();                    // Ordina il vettore

    for (ulong i = 0; i < tempVec.Size(); ++i)
    {
      if (i == 0 || !(tempVec[i] == tempVec[i - 1]))
      {
        InsertAtBack(tempVec[i]);
      }
    }
  }

  // Costruttore da MappableContainer (rvalue)
  template <typename Data>
  SetLst<Data>::SetLst(MappableContainer<Data> &&con)
  {
    SortableVector<Data> tempVec(std::move(con)); // Muove gli elementi
    tempVec.Sort();                               // Ordina il vettore

    for (ulong i = 0; i < tempVec.Size(); ++i)
    {
      if (i == 0 || !(tempVec[i] == tempVec[i - 1]))
      {
        InsertAtBack(std::move(tempVec[i]));
      }
    }
  }

  /* ************************************************************************** */

  // Copy constructor
  template <typename Data>
  SetLst<Data>::SetLst(const SetLst<Data> &other) : List<Data>(other) {}

  // Move constructor
  template <typename Data>
  SetLst<Data>::SetLst(SetLst<Data> &&other) noexcept : List<Data>(std::move(other)) {}

  // Copy assignment
  template <typename Data>
  SetLst<Data> &SetLst<Data>::operator=(const SetLst<Data> &other)
  {
    List<Data>::operator=(other);
    return *this;
  }

  // Move assignment
  template <typename Data>
  SetLst<Data> &SetLst<Data>::operator=(SetLst<Data> &&other) noexcept
  {
    List<Data>::operator=(std::move(other));
    return *this;
  }

  // Equality operator
  template <typename Data>
  bool SetLst<Data>::operator==(const SetLst<Data> &other) const noexcept
  {
    return List<Data>::operator==(other);
  }

  // Inequality operator
  template <typename Data>
  bool SetLst<Data>::operator!=(const SetLst<Data> &other) const noexcept
  {
    return !(*this == other);
  }

  /* ************************************************************************ */

  // Insert (copy)
  template <typename Data>
  bool SetLst<Data>::Insert(const Data &val)
  {
    typename List<Data>::Node *prev = nullptr;
    typename List<Data>::Node *curr = this->head;

    // Scorri fino a trovare posizione corretta o duplicato
    while (curr != nullptr && curr->element < val)
    {
      prev = curr;
      curr = curr->next;
    }

    // Se già presente, non inserire
    if (curr != nullptr && !(val < curr->element) && !(curr->element < val))
    {
      return false;
    }

    if (prev == nullptr)
    {
      // Inserimento in testa
      this->InsertAtFront(val);
    }
    else if (curr == nullptr)
    {
      // Inserimento in coda
      this->InsertAtBack(val);
    }
    else
    {
      // Inserimento in mezzo
      typename List<Data>::Node *newNode = new typename List<Data>::Node(val);
      newNode->next = curr;
      prev->next = newNode;
      ++(this->size);
    }

    return true;
  }

  // Insert (move)
  template <typename Data>
  bool SetLst<Data>::Insert(Data &&val)
  {
    typename List<Data>::Node *prev = nullptr;
    typename List<Data>::Node *curr = this->head;

    while (curr != nullptr && curr->element < val)
    {
      prev = curr;
      curr = curr->next;
    }

    if (curr != nullptr && !(val < curr->element) && !(curr->element < val))
    {
      return false;
    }

    if (prev == nullptr)
    {
      this->InsertAtFront(std::move(val));
    }
    else if (curr == nullptr)
    {
      this->InsertAtBack(std::move(val));
    }
    else
    {
      typename List<Data>::Node *newNode = new typename List<Data>::Node(std::move(val));
      newNode->next = curr;
      prev->next = newNode;
      ++(this->size);
    }

    return true;
  }

  template <typename Data>
  bool SetLst<Data>::Remove(const Data &val)
  {
    if (head == nullptr)
      return false; // lista vuota
    // Se il nodo da rimuovere è il primo
    if (head->element == val)
    {
      auto toDelete = head;
      head = head->next;
      toDelete->next = nullptr; // per evitare la cancellazione ricorsiva
      delete toDelete;
      --size;

      // Se la lista ora è vuota aggiorna tail
      if (head == nullptr)
      {
        tail = nullptr;
      }

      return true;
    }

    // Nodo precedente e corrente per scorrere
    auto prev = head;
    auto curr = head->next;

    // Scorri fino a trovare il nodo da rimuovere o la fine della lista
    while (curr != nullptr && curr->element < val)
    {
      prev = curr;
      curr = curr->next;
    }
    // Se il nodo corrente è quello da rimuovere
    if (curr != nullptr && curr->element == val)
    {
      prev->next = curr->next; // Salta il nodo corrente
      curr->next = nullptr;    // per evitare la cancellazione ricorsiva
      delete curr;
      --size;

      // Se il nodo rimosso era l'ultimo, aggiorna tail
      if (prev->next == nullptr)
      {
        tail = prev;
      }

      return true;
    }
    return false; // valore non trovato
  }

  // Exists
  template <typename Data>
  bool SetLst<Data>::Exists(const Data &val) const noexcept
  {
    auto curr = head;
    while (curr != nullptr)
    {
      if (curr->element == val)
        return true;
      if (val < curr->element)
        return false;
      curr = curr->next;
    }
    return false;
  }

  // Clear
  template <typename Data>
  void SetLst<Data>::Clear()
  {
    List<Data>::Clear();
  }

  // operator[] const
  template <typename Data>
  const Data &SetLst<Data>::operator[](ulong index) const
  {
    return List<Data>::operator[](index);
  }

  // specific member functions (inherited from List)
  template <typename Data>
  void SetLst<Data>::InsertAtFront(const Data &dat)
  {
    if (this->Empty() || dat <= this->Front())
    {
      List<Data>::InsertAtFront(dat);
    }
    else
    {
      throw std::runtime_error("Order violation: you cannot insert this element at the front.");
    }
  }

  template <typename Data>
  void SetLst<Data>::InsertAtFront(Data &&dat)
  {
    if (!Exists(dat))
    {
      if (this->Empty() || dat <= this->Front())
      {
        List<Data>::InsertAtFront(std::move(dat));
      }
      else
      {
        throw std::runtime_error("Order violation: you cannot insert this element at the front.");
      }
    }
  }

  template <typename Data>
  void SetLst<Data>::InsertAtBack(const Data &dat)
  {
    if (this->Empty() || dat > this->Back())
    {
      List<Data>::InsertAtBack(dat);
    }
    else
    {
      throw std::runtime_error("Order violation: you cannot insert this element at the back.");
    }
  }

  template <typename Data>
  void SetLst<Data>::InsertAtBack(Data &&dat)
  {
    if (this->Empty() || dat > this->Back())
    {
      List<Data>::InsertAtBack(std::move(dat));
    }
    else
    {
      throw std::runtime_error("Order violation: you cannot insert this element at the back.");
    }
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

  // override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  template <typename Data>
  const Data &SetLst<Data>::Min() const
  {
    return List<Data>::Front();
  }

  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  template <typename Data>
  Data SetLst<Data>::MinNRemove()
  {
    return List<Data>::FrontNRemove();
  }

  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  template <typename Data>
  void SetLst<Data>::RemoveMin()
  {
    List<Data>::RemoveFromFront();
  }
  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  template <typename Data>
const Data& SetLst<Data>::Max() const {
  return List<Data>::Back();
}
  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  template <typename Data>
  Data SetLst<Data>::MaxNRemove()
  {
    return List<Data>::BackNRemove();
  }
  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  template <typename Data>
  void SetLst<Data>::RemoveMax()
  {
    List<Data>::RemoveFromBack();
  }

  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  template <typename Data>
  const Data &SetLst<Data>::Predecessor(const Data &val) const
  {
    if (size == 0)
      throw std::length_error("List is empty");
    Node *pred = FindPredecessorNode(val);
    if (pred == nullptr)
      throw std::length_error("No predecessor found");
    return pred->element;
  }
  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  template <typename Data>
  Data SetLst<Data>::PredecessorNRemove(const Data &val)
  {
    Data tmp = Predecessor(val);
    Remove(tmp);
    return tmp;
  }
  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  template <typename Data>
  void SetLst<Data>::RemovePredecessor(const Data &val)
  {
    Remove(Predecessor(val));
  }

  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  template <typename Data>
  const Data SetLst<Data>::Successor(const Data &val) const
  {
    if (size == 0)
      throw std::length_error("List is empty");
    Node *succ = FindSuccessorNode(val);
    if (succ == nullptr)
      throw std::length_error("No successor found");
    return succ->element;
  }
  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  template <typename Data>
  Data SetLst<Data>::SuccessorNRemove(const Data &val)
  {
    Data tmp = Successor(val);
    Remove(tmp);
    return tmp;
  }
  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  template <typename Data>
  void SetLst<Data>::RemoveSuccessor(const Data &val)
  {
    Remove(Successor(val));
  }
  /* ************************************************************************ */
  /// funzioni ausiliarie
  template <typename Data>
  typename SetLst<Data>::Node *SetLst<Data>::FindPredecessorNode(const Data &val) const
  {
    Node *curr = head;
    Node *prev = nullptr;

    while (curr != nullptr && curr->element < val)
    {
      prev = curr;
      curr = curr->next;
    }

    return prev; // può essere nullptr se non c'è predecessore
  }

  template <typename Data>
  typename SetLst<Data>::Node *SetLst<Data>::FindSuccessorNode(const Data &val) const
  {
    Node *curr = head;

    while (curr != nullptr && curr->element <= val)
    {
      curr = curr->next;
    }

    return curr; // può essere nullptr se non c'è successore
  }

} // namespace lasd

#endif // SETLST_TPP
