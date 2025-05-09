
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueVec : virtual public Queue<Data>,
  virtual protected Vector<Data> {

private:

protected:

  ulong head = 0;
  ulong tail = 0;

  using Vector<Data>::size;
  using Vector<Data>::Elements;

public:

  // Default constructor
  QueueVec() : Vector<Data>(4) {};

  /* ************************************************************************ */

  // Specific constructors
  QueueVec(const TraversableContainer<Data> &);
  QueueVec(MappableContainer<Data> && con);

  /* ************************************************************************ */

  // Copy constructor
  QueueVec(const QueueVec & que) : Vector<Data>(que), head(que.head), tail(que.tail) {};

  // Move constructor
  QueueVec(QueueVec &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~QueueVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  QueueVec & operator=(const QueueVec &);

  // Move assignment
  QueueVec & operator=(QueueVec &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueVec &) const noexcept;
  inline bool operator!=(const QueueVec &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  const Data & Head() const override;
  Data & Head() override;
  void Dequeue() override;
  Data HeadNDequeue() override;
  void Enqueue(const Data &) override;
  void Enqueue(Data &&) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  inline bool Empty() const noexcept override;

  inline ulong Size() const noexcept override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override;

protected:

  // Auxiliary member functions

  void Expand();
  void Reduce();

  void Resize(ulong, ulong);

};

/* ************************************************************************** */

}

#include "queuevec.cpp"

#endif
