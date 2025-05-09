
#ifndef CONTAINER_HPP
#define CONTAINER_HPP
namespace lasd {

using ulong = unsigned long; // Definizione di ulong 

class Container {
protected:

  ulong size = 0;
  Container() = default;   // Default constructor

public:

  virtual ~Container() = default;   // Destructor

  Container & operator=(const Container &) = delete;   // Copy assignment
  Container & operator=(Container &&) noexcept = delete; // Move assignment

  // Comparison operators
  bool operator==(const Container &) const noexcept = delete;
  bool operator!=(const Container &) const noexcept = delete;


  // Functions required by the class diagram
  inline virtual bool Empty() const noexcept {
    return (size == 0);
  }

  inline virtual ulong Size() const noexcept {
    return size;
  }

};


class ClearableContainer : virtual public Container {
public:

  virtual ~ClearableContainer() = default; // Destructor

  ClearableContainer & operator=(const ClearableContainer &) = delete; // Copy assignment

  ClearableContainer & operator=(ClearableContainer &&) noexcept = delete; // Move assignment

  // Comparison operators
  bool operator==(const ClearableContainer &) const noexcept = delete;
  bool operator!=(const ClearableContainer &) const noexcept = delete;

  // functions required by the class diagram
  virtual void Clear() = 0;

};


class ResizableContainer : virtual public ClearableContainer {
public:

  virtual ~ResizableContainer() = default; // Destructor

  ResizableContainer & operator=(const ResizableContainer &) = delete; // Copy assignment
  ResizableContainer & operator=(ResizableContainer &&) noexcept = delete; // Move assignment

  // Comparison operators
  bool operator==(const ResizableContainer &) const noexcept = delete;
  bool operator!=(const ResizableContainer &) const noexcept = delete;

  // functions required by the class diagram
  virtual void Resize(ulong) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  inline void Clear() override {
    Resize(0);
  }

};


}// namespace lasd

#endif
