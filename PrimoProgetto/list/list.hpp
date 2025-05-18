
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"
#include "../container/container.hpp"


namespace lasd {

template <typename Data>
class List: virtual public ClearableContainer,
            virtual public MutableLinearContainer<Data>{
protected:

  using Container::size;

  struct Node {

    Data element;
    Node* next = nullptr;

    // Specific constructors
    inline Node() = default;
    inline Node(const Data& dat) : element(dat) {};
    inline Node(Data&& dat) noexcept : element(std::move(dat)) {};

    /* ********************************************************************** */

    // Copy constructor
    inline Node(const Node& nod) : element(nod.element) {};

    // Move constructor
    inline Node(Node&& nod) noexcept : element(std::move(nod.element)), next(nod.next) {
      nod.next = nullptr; // Avoid dangling pointer
    }

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() {
      delete next; // Recursively delete the next nodes
    }

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const Node&) const noexcept;
    inline bool operator!=(const Node& nod) const noexcept;

    /* ********************************************************************** */

    // Specific member functions

    // ...TODO CHIEDERE AD COllEGA 

  };

    Node* head = nullptr;
    Node* tail = nullptr;

public:

  // Default constructor
   List() = default;

  /* ************************************************************************ */

  // Specific constructor
  // List(argument) specifiers; // A list obtained from a TraversableContainer
  List(const TraversableContainer<Data>& );
  // List(argument) specifiers; // A list obtained from a MappableContainer
    List(MappableContainer<Data>&& );

  /* ************************************************************************ */

  // Copy constructor
   List(const List &);

  // Move constructor
  List(List &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~List();

  /* ************************************************************************ */

  // Copy assignment
  List & operator=(const List &);

  // Move assignment
  List & operator=(List &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const List &) const noexcept;
  inline bool operator!=(const List &) const noexcept;
  /* ************************************************************************ */

  // functions required by the class diagram

  virtual void InsertAtFront(const Data &); // Copy of the value
  virtual void InsertAtFront(Data &&); // Move of the value
  void  RemoveFromFront(); // (must throw std::length_error when empty)
  Data FrontNRemove(); // (must throw std::length_error when empty)

  virtual void InsertAtBack(const Data &); // Copy of the value
  virtual void InsertAtBack(Data &&); // Move of the value
  void RemoveFromBack(); // (must throw std::length_error when empty)
  Data BackNRemove(); // (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

  Data & operator[](const ulong) override; // Override MutableLinearContainer member (must throw std::out_of_range when out of range)

  Data & Front() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

  Data & Back() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

  
  

  
  
  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data & operator[](const ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  const Data & Front() const override; // Override LinearContainer member (must throw std::length_error when empty)

  const Data & Back() const override; // Override LinearContainer member (must throw std::length_error when empty)


  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  void Map(MapFun) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  void PreOrderMap(MapFun) override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  void PostOrderMap(MapFun) override; // Override PostOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  void Traverse(TraverseFun) const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}
#include "list.tpp"

#endif
