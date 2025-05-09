
namespace lasd {

/* ************************************************************************** */

// Specific constructors

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(ulong newtablesize) : HashTableOpnAdr() {
  tablesize = newtablesize;
  table.Resize(tablesize);
  flagtable.Resize(tablesize);
}

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const TraversableContainer<Data> & con) : HashTableOpnAdr() {
  InsertAll(con);
}

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(ulong newtablesize, const TraversableContainer<Data> & con) : HashTableOpnAdr(newtablesize) {
  InsertAll(con);
}

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(MappableContainer<Data> && con) {
  InsertAll(std::move(con));
}

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(ulong newtablesize, MappableContainer<Data> && con) : HashTableOpnAdr(newtablesize) {
  InsertAll(std::move(con));
}

/* ************************************************************************** */

// Copy constructor
template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr<Data> & ht) : HashTable<Data>(ht) {
  ccoeff = ht.ccoeff;
  dcoeff = ht.dcoeff;
  table = ht.table;
  flagtable = ht.flagtable;
}

// Move constructor
template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr<Data> && ht) noexcept : HashTable<Data>(std::move(ht)) {
  std::swap(ccoeff, ht.ccoeff);
  std::swap(dcoeff, ht.dcoeff);
  std::swap(table, ht.table);
  std::swap(flagtable, ht.flagtable);
}

/* ************************************************************************** */

// Copy assignment
template<typename Data>
HashTableOpnAdr<Data> & HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr<Data> & ht) {
  HashTable<Data>::operator=(ht);
  ccoeff = ht.ccoeff;
  dcoeff = ht.dcoeff;
  table = ht.table;
  flagtable = ht.flagtable;
  return *this;
}

// Move assignment
template<typename Data>
HashTableOpnAdr<Data> & HashTableOpnAdr<Data>::operator=(HashTableOpnAdr<Data> && ht) noexcept {
  HashTable<Data>::operator=(std::move(ht));
  std::swap(ccoeff, ht.ccoeff);
  std::swap(dcoeff, ht.dcoeff);
  std::swap(table, ht.table);
  std::swap(flagtable, ht.flagtable);
  return *this;
}

/* ************************************************************************** */

// Comparison operators

template<typename Data>
inline bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr<Data> & ht) const noexcept {
  if (size == ht.Size()) {
    for (ulong i = 0; i < tablesize; ++i) {
      if (flagtable[i] > 1) {
        if (!ht.Exists(table[i])) {
          return false;
        }
      }
    }
    return true;
  }
  return false;
}

template<typename Data>
inline bool HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr<Data> & ht) const noexcept {
  return !(*this == ht);
}

/* ************************************************************************** */

// Specific member functions (inherited from DictionaryContainer)

template<typename Data>
bool HashTableOpnAdr<Data>::Insert(const Data & dat) {
  if (2 * size > tablesize) {
    Resize(2 * tablesize);
  }
  ulong idx = FindEmpty(dat, 0);
  if (idx < tablesize) {
    ulong pos = HashKey(dat, idx);
    if (flagtable[pos] > 1) {
      return false;
    } else {
      table[pos] = dat;
      flagtable[pos] = 2;
      ++size;
      return !Remove(dat, idx + 1);
    }
  } else {
    throw std::length_error("Unsuccessful Insertion.");
  }
}

template<typename Data>
bool HashTableOpnAdr<Data>::Insert(Data && dat) {
  if (2 * size > tablesize) {
    Resize(2 * tablesize);
  }
  ulong idx = FindEmpty(dat, 0);
  if (idx < tablesize) {
    ulong pos = HashKey(dat, idx);
    if (flagtable[pos] > 1) {
      return false;
    } else {
      table[pos] = std::move(dat);
      flagtable[pos] = 2;
      ++size;
      return !Remove(dat, idx + 1);
    }
  } else {
    throw std::length_error("Unsuccessful Insertion.");
  }
}

template<typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data & dat) {
  return Remove(dat, 0);
}

/* ************************************************************************** */

// Specific member functions (inherited from TestableContainer)

template<typename Data>
bool HashTableOpnAdr<Data>::Exists(const Data & dat) const noexcept {
  ulong idx = Find(dat, 0);
  if (idx < tablesize) {
    ulong pos = HashKey(dat, idx);
    if (flagtable[pos] != 0) {
      return true;
    }
  }
  return false;
};

/* ************************************************************************** */

// Specific member functions (inherited from HashTable)

template<typename Data>
void HashTableOpnAdr<Data>::Resize(ulong newtablesize) {
  newtablesize = (size < newtablesize) ? newtablesize : (size + 1);
  HashTableOpnAdr<Data> * tmpht = new HashTableOpnAdr<Data>(newtablesize);
  for (ulong i = 0; i < tablesize; ++i) {
    if (flagtable[i] > 1) {
      tmpht->Insert(std::move(table[i]));
    }
  }
  std::swap(*tmpht, *this);
  delete tmpht;
};

/* ************************************************************************** */

// Specific member functions (inherited from ClearableContainer)

template<typename Data>
void HashTableOpnAdr<Data>::Clear() {
  size = 0;
  tablesize = 128;
  table.Clear();
  table.Resize(tablesize);
  flagtable.Clear();
  flagtable.Resize(tablesize);
}

/* ************************************************************************** */

// Auxiliary member functions

template<typename Data>
ulong HashTableOpnAdr<Data>::HashKey(const Data & dat, ulong idx) const noexcept {
  ulong enckey = enchash(dat);
  return ((HashKey(enckey) + idx) % tablesize);
  // return ((HashKey(enckey) + (ccoeff * idx + dcoeff)) % tablesize);
  // return ((HashKey(enckey) + ((idx * idx + idx) / 2)) % tablesize);
  // return ((HashKey(enckey) + (HashIdx(enckey) * idx)) % tablesize);
}

template<typename Data>
ulong HashTableOpnAdr<Data>::HashIdx(ulong key) const noexcept {
  return (((ccoeff * key + dcoeff) % prime) % (tablesize - 1));
}

template<typename Data>
ulong HashTableOpnAdr<Data>::Find(const Data & dat, ulong idx) const noexcept {
  ulong pos = HashKey(dat, idx);
  while ((idx < tablesize) && (flagtable[pos] != 0)) {
    if ((flagtable[pos] != 1) && (table[pos] == dat)) {
      break;
    }
    pos = HashKey(dat, ++idx);
  }
  return idx;
};

template<typename Data>
ulong HashTableOpnAdr<Data>::FindEmpty(const Data & dat, ulong idx) const noexcept {
  ulong pos = HashKey(dat, idx);
  while ((idx < tablesize) && (flagtable[pos] > 1)) {
    if (table[pos] == dat) {
      break;
    }
    pos = HashKey(dat, ++idx);
  }
  return idx;
};

template<typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data & dat, ulong idx) {
  idx = Find(dat, idx);
  if (idx < tablesize) {
    ulong pos = HashKey(dat, idx);
    if (flagtable[pos] != 0) {
      flagtable[pos] = 1;
      --size;
      return true;
    }
  }
  return false;
}

/* ************************************************************************** */

}
