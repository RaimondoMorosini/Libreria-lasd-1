#include <stdexcept>
#include <algorithm>

namespace lasd
{

    /* ************************************************************************** */

    // Copy constructor
    template <typename Data>
    SetVec<Data>::SetVec(const SetVec<Data> &other) : Vector<Data>(other.size)
    {
        head = 0;
        numeroDiElementi = other.numeroDiElementi;

        for (ulong i = 0; i < numeroDiElementi; ++i)
        {
            Elements[i] = other[i];
        }
    }

    // Move constructor
    template <typename Data>
    SetVec<Data>::SetVec(SetVec<Data> &&other) noexcept
    {
        std::swap(Elements, other.Elements);
        std::swap(size, other.size);
        std::swap(head, other.head);
        std::swap(numeroDiElementi, other.numeroDiElementi);
    }

    // Copy assignment
template<typename Data>
SetVec<Data>& SetVec<Data>::operator=(const SetVec<Data>& other) {
  SetVec<Data>* tmp = new SetVec<Data>(other);
  std::swap(*tmp, *this);
  delete tmp;
  return *this;
}

    // Move assignment
    template <typename Data>
    SetVec<Data> &SetVec<Data>::operator=(SetVec<Data> &&other) noexcept
    {
        if (this != &other)
        {
            std::swap(Elements, other.Elements);
            std::swap(size, other.size);
            std::swap(head, other.head);
            std::swap(numeroDiElementi, other.numeroDiElementi);
        }
        return *this;
    }

    /* ************************************************************************** */

    // Equality operator
    template <typename Data>
    bool SetVec<Data>::operator==(const SetVec<Data> &other) const noexcept
    {
        if (numeroDiElementi != other.numeroDiElementi)
        {
            return false;
        }

        for (ulong i = 0; i < numeroDiElementi; ++i)
        {
            if (Elements[RealIndex(i)] != other.Elements[other.RealIndex(i)])
            {
                return false;
            }
        }

        return true;
    }

    // Inequality operator
    template <typename Data>
    inline bool SetVec<Data>::operator!=(const SetVec<Data> &other) const noexcept
    {
        return !(*this == other);
    }

    /* ************************************************************************** */


/* ************************************************************************** */

// Costruttore da TraversableContainer (copia gli elementi, usa Insert)
template <typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data> &container) : Vector<Data>(container.Size() * 2)
{
    head = 0;
    numeroDiElementi = 0;

    container.Traverse([this](const Data &dat)
                       { this->Insert(dat); });
}

// Costruttore da MappableContainer (move)
template <typename Data>
SetVec<Data>::SetVec(MappableContainer<Data> &&container) : Vector<Data>(container.Size() * 2)
{
    head = 0;
    numeroDiElementi = 0;

    container.Map([this](Data &dat)
                  { this->Insert(std::move(dat)); });
}

/* ************************************************************************** */

// Operatore [] const
template <typename Data>
const Data &SetVec<Data>::operator[](ulong index) const
{
    if (index >= numeroDiElementi)
    {
        throw std::out_of_range("Index out of range");
    }
    return Elements[RealIndex(index)];
}

// Operatore [] non-const
template <typename Data>
Data &SetVec<Data>::operator[](ulong index)
{
    if (index >= numeroDiElementi)
    {
        throw std::out_of_range("Index out of range");
    }
    return Elements[RealIndex(index)];
}

/* ************************************************************************** */

/* ************************************************************************** */
// funzioni ausiliarie

// Converte indice logico in indice reale nel buffer circolare
template <typename Data>
ulong SetVec<Data>::RealIndex(ulong index) const
{
    return (head + index) % size;
}

// Ricerca binaria per trovare la posizione dove inserire o cercare un elemento
// Restituisce l'indice del primo elemento maggiore o uguale a dat
template <typename Data>
ulong SetVec<Data>::LowerBoundIndex(const Data &dat) const
{
    ulong left = 0;
    ulong right = numeroDiElementi;

    while (left < right)
    {
        ulong mid = (left + right) / 2;
        if (Elements[RealIndex(mid)] < dat)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }
    return left;
}

// Shift a destra da from a to (inclusi) → usato per fare spazio
template <typename Data>
void SetVec<Data>::ShiftRight(ulong from, ulong to)
{
    for (long i = to; i >= static_cast<long>(from); --i)
    {
        Elements[RealIndex(i + 1)] = std::move(Elements[RealIndex(i)]);
    }
}

// Shift a sinistra da from a to (inclusi) → usato per rimuovere
template <typename Data>
void SetVec<Data>::ShiftLeft(ulong from, ulong to)
{
    for (ulong i = from; i <= to; ++i)
    {
        Elements[RealIndex(i)] = std::move(Elements[RealIndex(i + 1)]);
    }
}
/* ************************************************************************** */

// Aumenta la capacità del vettore sottostante
template <typename Data>
void SetVec<Data>::Resize(ulong newCapacity)
{
    Data *newElements = new Data[newCapacity];

    for (ulong i = 0; i < numeroDiElementi; ++i)
    {
        newElements[i] = std::move(Elements[RealIndex(i)]);
    }

    std::swap(Elements, newElements);
    delete[] newElements;

    head = 0;
    size = newCapacity;
}

// Inserimento per copia
template <typename Data>
bool SetVec<Data>::Insert(const Data &dat)
{
    if (Exists(dat))
        return false;

    if (numeroDiElementi == size)
    {
        Resize(size * 2);
    }

    ulong idx = LowerBoundIndex(dat);

    if (idx < numeroDiElementi / 2)
    {
        // Shift a sinistra e aggiorna head
        head = (head == 0) ? (size - 1) : (head - 1);
        ShiftLeft(0, idx - 1);
    }
    else
    {
        // Shift a destra
        ShiftRight(idx, numeroDiElementi - 1);
    }

    Elements[RealIndex(idx)] = dat;
    ++numeroDiElementi;

    return true;
}

// Inserimento per move
template <typename Data>
bool SetVec<Data>::Insert(Data &&dat)
{
    if (Exists(dat))
        return false;

    if (numeroDiElementi == size)
    {
        Resize(size * 2);
    }

    ulong idx = LowerBoundIndex(dat);

    if (idx < numeroDiElementi / 2)
    {
        head = (head == 0) ? (size - 1) : (head - 1);
        ShiftLeft(0, idx - 1);
    }
    else
    {
        ShiftRight(idx, numeroDiElementi - 1);
    }

    Elements[RealIndex(idx)] = std::move(dat);
    ++numeroDiElementi;

    return true;
}

/* ************************************************************************** */

// Rimozione di un elemento (se presente)
template <typename Data>
bool SetVec<Data>::Remove(const Data &dat)
{
    ulong idx = LowerBoundIndex(dat);

    if (idx < numeroDiElementi && Elements[RealIndex(idx)] == dat)
    {
        if (idx < numeroDiElementi / 2)
        {
            ShiftRight(0, idx - 1);
            head = (head + 1) % size;
        }
        else
        {
            ShiftLeft(idx, numeroDiElementi - 1);
        }

        --numeroDiElementi;
        return true;
    }

    return false;
}

/* ************************************************************************** */

// Restituisce il minimo elemento (primo ordinato)
template <typename Data>
const Data& SetVec<Data>::Min() const {
  if (numeroDiElementi == 0) throw std::length_error("SetVec is empty");
  return (*this)[0];
}

// Rimuove e restituisce il minimo elemento
template <typename Data>
Data SetVec<Data>::MinNRemove() {
   Data tmp = Min();
  RemoveMin();
  return tmp;
}

// Rimuove il minimo elemento (prima posizione)
template <typename Data>
void SetVec<Data>::RemoveMin() {
  if (numeroDiElementi == 0) throw std::length_error("SetVec is empty");
  // Sposta head avanti di 1 (logica buffer circolare)
  head = (head + 1) % size;
  --numeroDiElementi;
}

// Restituisce il massimo elemento (ultimo ordinato)
template <typename Data>
const Data& SetVec<Data>::Max() const {
  if (numeroDiElementi == 0) throw std::length_error("SetVec is empty");
  return (*this)[numeroDiElementi - 1];
}

// Rimuove e restituisce il massimo elemento
template <typename Data>
Data SetVec<Data>::MaxNRemove() {
  Data tmp = Max();
  RemoveMax();
  return tmp;
}

// Rimuove il massimo elemento (ultima posizione)
template <typename Data>
void SetVec<Data>::RemoveMax() {
  if (numeroDiElementi == 0) throw std::length_error("SetVec is empty");
  --numeroDiElementi;
}

// Restituisce il predecessore (massimo elemento strettamente minore di dat)
template<typename Data>
const Data& SetVec<Data>::Predecessor(const Data& dat) const {
  ulong idx = LowerBoundIndex(dat);
  if (idx == 0) throw std::length_error("No predecessor found.");
  return Elements[RealIndex(idx - 1)];
}

template<typename Data>
Data SetVec<Data>::PredecessorNRemove(const Data& dat) {
  Data tmp = Predecessor(dat);
  Remove(tmp);
  return tmp;
}

template<typename Data>
void SetVec<Data>::RemovePredecessor(const Data& dat) {
  Remove(Predecessor(dat));
}

// Restituisce il successore (minimo elemento strettamente maggiore di dat)
template <typename Data>
const Data& SetVec<Data>::Successor(const Data& dat) const {
  if (numeroDiElementi == 0) throw std::length_error("SetVec is empty");

  ulong idx = LowerBoundIndex(dat);

  // Se dat è presente, il successore è idx+1, altrimenti è idx
  if (idx < numeroDiElementi && (*this)[idx] == dat) ++idx;

  if (idx >= numeroDiElementi) throw std::length_error("No successor exists");

  return (*this)[idx];
}

// Rimuove e restituisce il successore di dat
template <typename Data>
Data SetVec<Data>::SuccessorNRemove(const Data& dat) {
  const Data& succ = Successor(dat);
  Data succCopy = succ;
  RemoveSuccessor(dat);
  return succCopy;
}

// Rimuove il successore di dat
template <typename Data>
void SetVec<Data>::RemoveSuccessor(const Data& val) {
  Remove(Successor(val));
}



/* ************************************************************************** */

}
