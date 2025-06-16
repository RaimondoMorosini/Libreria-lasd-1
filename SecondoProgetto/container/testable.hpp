
#ifndef TESTABLE_HPP
#define TESTABLE_HPP
#include "container.hpp"

namespace lasd {

template <typename Data>
class TestableContainer : virtual public Container {
public:

  virtual ~TestableContainer() = default;   // Destructor

  TestableContainer & operator=(const TestableContainer &) = delete;// Copy assignment
  TestableContainer & operator=(TestableContainer &&) noexcept = delete;// Move assignment


  // Comparison operators
  bool operator==(const TestableContainer &) const noexcept = delete;
  bool operator!=(const TestableContainer &) const noexcept = delete;

  //functions required by the class diagram
  virtual bool Exists(const Data &) const noexcept = 0;

};


}

#endif
