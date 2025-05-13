
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector : virtual public ResizableContainer, virtual public MutableLinearContainer<Data> {

protected:

  using Container::size;

  Data * Elements = nullptr;

public:

  // Default constructor
  Vector() = default;

  /* ************************************************************************ */

  // Specific constructors

  Vector(const ulong);

  Vector(const TraversableContainer<Data> &);
  Vector(MappableContainer<Data> &&);

  /* ************************************************************************ */

  // Copy constructor
  Vector(const Vector &);

  // Move constructor
  Vector(Vector &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~Vector();

  /* ************************************************************************ */

  // Copy assignment
  Vector & operator=(const Vector &);

  // Move assignment
  Vector & operator=(Vector &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Vector &) const noexcept;
  inline bool operator!=(const Vector &) const noexcept;

    /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

  Data & operator[](const ulong) override; //(must throw std::out_of_range when out of range)
  Data & Front() override; //(must throw std::length_error when empty)//(must throw std::length_error when empty)
  Data & Back() override; //(must throw std::length_error when empty)


    /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)
    const Data & operator[](const ulong) const override; //(must throw std::out_of_range when out of range)
  const Data & Front() const override; //(must throw std::length_error when empty)
  const Data & Back() const override; //(must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)

  void Resize(const ulong) override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override;



};

/* ************************************************************************** */

template <typename Data>
class SortableVector : virtual public Vector<Data>,
  virtual public SortableLinearContainer<Data> {

private:

protected:

public:

  // Default constructor
  SortableVector() = default;

  /* ************************************************************************ */

  // Specific constructors

  SortableVector(const ulong);

  SortableVector(const TraversableContainer<Data> &);
  SortableVector(MappableContainer<Data> &&);

  /* ************************************************************************ */

  // Copy constructor
  SortableVector(const SortableVector &);

  // Move constructor
  SortableVector(SortableVector &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~SortableVector() = default;

  /* ************************************************************************ */

  // Copy assignment
  SortableVector & operator=(const SortableVector &);

  // Move assignment
  SortableVector & operator=(SortableVector &&) noexcept;

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
