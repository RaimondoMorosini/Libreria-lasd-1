
#ifndef QUEUELST_HPP
#define QUEUELST_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueLst : virtual public Queue<Data>,
  virtual protected List<Data> {

private:

protected:

public:

  // Default constructor
  inline QueueLst() = default;

  /* ************************************************************************ */

  // Specific constructors
  QueueLst(const TraversableContainer<Data> & con) : List<Data>(con) {};
  QueueLst(MappableContainer<Data> && con) : List<Data>(std::move(con)) {};

  /* ************************************************************************ */

  // Copy constructor
  inline QueueLst(const QueueLst & que) : List<Data>(que) {};

  // Move constructor
  inline QueueLst(QueueLst && que) noexcept : List<Data>(std::move(que)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~QueueLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline QueueLst & operator=(const QueueLst &);

  // Move assignment
  inline QueueLst & operator=(QueueLst &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const QueueLst &) const noexcept;
  inline bool operator!=(const QueueLst &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  inline const Data & Head() const override;
  inline Data & Head() override;
  inline void Dequeue() override;
  inline Data HeadNDequeue() override;
  inline void Enqueue(const Data &) override;
  inline void Enqueue(Data &&) override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  using List<Data>::Clear;

};

/* ************************************************************************** */

}

#include "queuelst.cpp"

#endif
