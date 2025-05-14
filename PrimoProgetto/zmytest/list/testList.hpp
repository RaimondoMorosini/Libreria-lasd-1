#include <gtest/gtest.h>
#include "../../list/list.hpp" 
#include <string>
#include <stdexcept>

using namespace lasd;

// Fixture di test parametrica
template <typename T>
class ListTest : public ::testing::Test {
protected:
  List<T> list;

  void SetUp() override {
    // TODO Popola con valori iniziali?
  }

  void TearDown() override {
    list.Clear();
  }
};

using MyTypes = ::testing::Types<int, std::string>;
TYPED_TEST_SUITE(ListTest, MyTypes);

TYPED_TEST(ListTest, InsertAtFrontAndBack) {
  this->list.InsertAtFront(TypeParam(10));
  this->list.InsertAtBack(TypeParam(20));
  EXPECT_EQ(this->list.Front(), TypeParam(10));
  EXPECT_EQ(this->list.Back(), TypeParam(20));
  EXPECT_EQ(this->list[0], TypeParam(10));
  EXPECT_EQ(this->list[1], TypeParam(20));
}

TYPED_TEST(ListTest, RemoveFromFront) {
  this->list.InsertAtFront(TypeParam(30));
  this->list.InsertAtFront(TypeParam(40));
  EXPECT_EQ(this->list.Front(), TypeParam(40));
  this->list.RemoveFromFront();
  EXPECT_EQ(this->list.Front(), TypeParam(30));
  this->list.RemoveFromFront();
  EXPECT_THROW(this->list.RemoveFromFront(), std::length_error);
}

TYPED_TEST(ListTest, RemoveFromBack) {
  this->list.InsertAtBack(TypeParam(50));
  this->list.InsertAtBack(TypeParam(60));
  EXPECT_EQ(this->list.Back(), TypeParam(60));
  this->list.RemoveFromBack();
  EXPECT_EQ(this->list.Back(), TypeParam(50));
  this->list.RemoveFromBack();
  EXPECT_THROW(this->list.RemoveFromBack(), std::length_error);
}

TYPED_TEST(ListTest, FrontNRemove) {
  this->list.InsertAtBack(TypeParam(70));
  TypeParam val = this->list.FrontNRemove();
  EXPECT_EQ(val, TypeParam(70));
  EXPECT_THROW(this->list.FrontNRemove(), std::length_error);
}

TYPED_TEST(ListTest, BackNRemove) {
  this->list.InsertAtFront(TypeParam(80));
  TypeParam val = this->list.BackNRemove();
  EXPECT_EQ(val, TypeParam(80));
  EXPECT_THROW(this->list.BackNRemove(), std::length_error);
}

TYPED_TEST(ListTest, IndexAccessOutOfBounds) {
  EXPECT_THROW(this->list[0], std::out_of_range);
  this->list.InsertAtBack(TypeParam(90));
  EXPECT_NO_THROW(this->list[0]);
  EXPECT_THROW(this->list[1], std::out_of_range);
}

TYPED_TEST(ListTest, CopyConstructor) {
  this->list.InsertAtBack(TypeParam(100));
  this->list.InsertAtBack(TypeParam(200));
  List<TypeParam> copiedList(this->list);
  EXPECT_EQ(copiedList[0], this->list[0]);
  EXPECT_EQ(copiedList[1], this->list[1]);
}

TYPED_TEST(ListTest, MoveConstructor) {
  this->list.InsertAtBack(TypeParam(300));
  List<TypeParam> movedList(std::move(this->list));
  EXPECT_EQ(movedList[0], TypeParam(300));
  EXPECT_EQ(movedList.Front(), TypeParam(300));
  EXPECT_EQ(movedList.Back(), TypeParam(300));
  EXPECT_EQ(movedList.Size(), 1);
}

TYPED_TEST(ListTest, ComparisonOperators) {
  this->list.InsertAtBack(TypeParam(1));
  this->list.InsertAtBack(TypeParam(2));
  List<TypeParam> sameList(this->list);
  EXPECT_TRUE(this->list == sameList);
  sameList.InsertAtBack(TypeParam(3));
  EXPECT_TRUE(this->list != sameList);
}

TYPED_TEST(ListTest, ClearFunction) {
  this->list.InsertAtBack(TypeParam(123));
  EXPECT_FALSE(this->list.Empty());
  this->list.Clear();
  EXPECT_TRUE(this->list.Empty());
  EXPECT_EQ(this->list.Size(), 0);
}

/* Map & Traverse test */
TYPED_TEST(ListTest, TraverseAndMap) {
  for (int i = 0; i < 5; ++i) this->list.InsertAtBack(TypeParam(i));

  int sum = 0;
  this->list.Traverse([&](const TypeParam& val) {
    sum += static_cast<int>(val);
  });
  EXPECT_EQ(sum, 0 + 1 + 2 + 3 + 4);

  this->list.Map([](TypeParam& val) {
    val = static_cast<TypeParam>(static_cast<int>(val) * 2);
  });

  EXPECT_EQ(static_cast<int>(this->list[0]), 0);
  EXPECT_EQ(static_cast<int>(this->list[1]), 2);
  EXPECT_EQ(static_cast<int>(this->list[4]), 8);
}
