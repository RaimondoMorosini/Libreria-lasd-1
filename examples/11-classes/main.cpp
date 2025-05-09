
#include <iostream>

using namespace std;

// Example 1

class A {

protected:

  uint size = 0;

  char* str = nullptr;

public:

  A() = default;

  A(uint num) : size(num) {
    cout << "A new object is created" << endl;
    // size = num;
    str = new char[num]();
  }

  ~A() {
    cout << "The object containing " << (*this) << "is destructed" << endl;
    delete[] str;
  }

  char& operator[](const uint idx) {
    return str[idx];
    // if (idx < size)
    // {
    //   return str[idx];
    // }
    // else
    // {
    //   throw out_of_range("An unexpected access occurred!");
    // }
  }

  bool operator==(const A& obj) const noexcept {
    if (size == obj.size)
    {
      for (uint i = 0; i < size; i++)
      {
        if (str[i] != obj.str[i])
        {
          return false;
        }
      }
      return true;
    }
    return false;
  }

  friend ostream& operator<<(ostream&, const A&);

};

ostream& operator<<(ostream& outstr, const A& a) {
  for (uint i = 0; i < a.size; i++) { cout << i << ": '" << a.str[i] << "' "; }
  return outstr;
}

// // Example 2
//
// class A {
// private:
// // protected:
//   bool flag = false;
// public:
//   A() { cout << "A new base object is created" << endl; }
//   ~A() { cout << "The base object is destructed" << endl; }
// };
//
// class B: public A {
// public:
//   B() { cout << "A new derived object is created" << endl; flag = false; }
//   ~B() { cout << "The derived object is destructed" << endl; }
// };

// // Example 3
//
// class A {
// public:
//   A() { cout << "A new base object is created" << endl; }
//   ~A() { cout << "The base object is destructed" << endl; } // virtual
// };
//
// class B: public A {
// protected:
//   int* x = nullptr;
// public:
//   B() { cout << "A new derived object is created" << endl; x = new int { 0 }; }
//   ~B() { cout << "The derived object is destructed" << endl; delete x; }
// };

// // Example 4
//
// class A {
// protected:
//   uint size = 0;
// public:
//   A() { cout << "A new base object is created" << endl; }
//   ~A() { cout << "The base object is destructed" << endl; } // virtual
// };
//
// class B: public A { // virtual public A
// public:
//   B() { cout << "A new derived B object is created" << endl; size = 1; }
//   ~B() { cout << "The derived B object is destructed" << endl; }
// };
//
// class C: public A { // virtual public A
// public:
//   C() { cout << "A new derived C object is created" << endl; size = 2; }
//   ~C() { cout << "The derived C object is destructed" << endl; }
// };
//
// class D: public B, C  { // public C, B
// public:
//   D() { cout << "A new derived D object is created" << endl; }
//   ~D() { cout << "The derived D object is destructed" << endl; }
//   void PrintSize() { cout << size << endl; };
//   // void PrintSize() const noexcept { cout << B::size << " " << C::size << endl; };
// };

// // Example 5

// class A {
// protected:
//   uint val = 0;
// public:
//
//   A() { val++; std::cout << "A " << val << std::endl; }
//
//   A(const A& a) { val = a.val; val += 1000; std::cout << "Copy A " << val << std::endl; }
//
//   ~A() { std::cout << "Delete A " << val << std::endl; }
// };
//
// class B : public A { // virtual
// protected:
//   uint valx = 1;
// public:
//
//   B() { val += 20; std::cout << "B " << val << std::endl; } // Equivalently, you can add ": A()"
//
//   B(const B& b) : A(b) { valx = b.valx; val += 20000; std::cout << "Copy B " << val << std::endl; } // Remove ": A(b)"
//
//   ~B() { std::cout << "Delete B " << val << std::endl; }
// };
//
// class C : public B { // virtual
// public:
//
//   C() { val += 300; std::cout << "C " << val << std::endl; } // Equivalently, you can add ": B()".
//
//   C(const C& c) : B(c) { val += 300000; std::cout << "Copy C " << val << std::endl; } // Remove ": B(c)"; Add ": A(c)" when A is virtual in B
//
//   ~C() { std::cout << "Delete C " << val << std::endl; }
// };

// // Example 6

// class A {
// protected:
//   uint size = 0;
// public:
//   A() { cout << "A new base object is created" << endl; }
//   ~A() { cout << "The base object is destructed" << endl; } // virtual
//   void f() { cout << "Class A specific method!" << endl; }
//   // virtual void f() = 0;
//   // virtual void f() { cout << "Class A specific method!" << endl; }
// };

// class B: public A { // virtual public A
// public:
//   B() { cout << "A new derived B object is created" << endl; size = 1; }
//   ~B() { cout << "The derived B object is destructed" << endl; }
//   void f() = delete;
//   void g() { cout << "Class B specific method!" << endl; A::f(); }
//   // virtual void f() = delete;
//   // virtual void f() override = delete;
// };

// // Example 7
//
// class A {
// public:
//   A() { cout << "A new base object is created" << endl; }
//   ~A() { cout << "The base object is destructed" << endl; } // virtual
//   void f() {
//     cout << endl << "Non virtual specific method calling a private virtual method: " << endl;
//     g();
//     cout << endl;
//   }
// private:
//   virtual void g() {
//     cout << "Class A private virtual method!" << endl;
//   }
// };
//
// class B: public A {
// public:
//   B() { cout << "A new derived B object is created" << endl; }
//   ~B() { cout << "The derived B object is destructed" << endl; }
// private:
//   virtual void g() {
//     cout << "Class B private virtual method!" << endl;
//   }
// };

// // // Example 8
// //
// class A {
// };
//
// class B {
//   A & ref;
// public:
//   B (A & newref) : ref(newref) {}
// };

int main() {

  // Example 1

  // A* ptr = new A();
  // delete ptr;

  A var1(3); // 0, {}
  A var2(3);

  cout << "var1: " << var1 << endl;
  cout << "var2: " << var2 << endl;

  cout << "var1 ?= var2: " << (var1 == var2) << endl;

  var1[0] = 'x';

  cout << "var1: " << var1 << endl;
  cout << "var2: " << var2 << endl;

  cout << "var1 ?= var2: " << (var1 == var2) << endl;

  var2[1] = 'y';

  cout << "var1: " << var1 << endl;
  cout << "var2: " << var2 << endl;

  cout << "var1 ?= var2: " << (var1 == var2) << endl;

  var1[1] = 'y';
  var2[0] = 'x';

  cout << "var1: " << var1 << endl;
  cout << "var2: " << var2 << endl;

  cout << "var1 ?= var2: " << (var1 == var2) << endl;

  var1[2] = '1';
  var2[2] = '2';

  cout << "var1 ?= var2: " << (var1 == var2) << endl;

  // // Example 2
  //
  // B* b = new B();
  // delete b;
  // return 0;

  // // Example 3
  //
  // A* a = new B();
  // delete a;
  // return 0;

  // // Example 4
  //
  // D d;
  // d.PrintSize();

  // // Example 5
  //
  // std::cout << std::endl;
  // C x;
  // std::cout << std::endl;
  // C y(x);
  // std::cout << std::endl;

  // // Example 6
  //
  // B* b = new B();
  // A* a = b;
  // a->f();
  // // b->f();
  // // b->g();
  // delete b;
  // // delete a;

  // // Example 7
  //
  // A* a = new A();
  // a->f();
  // delete a;
  // B* b = new B();
  // a = b;
  // a->f();
  // b->f();
  // delete b;

  // // Example 8
  //
  // A a;
  // B b(a);
  // std::cout << "Size of class A: " << sizeof(A) << std::endl;
  // std::cout << "Size of class B: " << sizeof(B) << std::endl;

  return 0;
}
