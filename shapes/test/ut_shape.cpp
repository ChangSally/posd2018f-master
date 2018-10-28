#include <gtest/gtest.h>
#include "../src/shape.h"
#include "../src/circle.h"
#include "../src/rectangle.h"
#include <algorithm>

int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST (ShapeTest, first)
{
  ASSERT_TRUE(true);
}

TEST (ShapeTest, Circle)
{
  Circle c(10.0);
  ASSERT_NEAR(314.159, c.area(), 0.001);
  ASSERT_NEAR(62.831, c.perimeter(), 0.001);
}

TEST (ShapeTest, Rectangle)
{
  Rectangle r(3, 4);
  ASSERT_NEAR(12, r.area(), 0.001);
  ASSERT_NEAR(14, r.perimeter(), 0.001);
}

TEST(ShapeTest, Sorting)
{
  Shape* test_array[4] = {new Circle(1.0), new Circle(0.5), new Rectangle(5, 6), new Rectangle(0.5, 1.5)};

  std::sort(test_array, test_array+4, [](Shape * a, Shape *b) {
    return a->area() < b->area();
  });
  ASSERT_NEAR(0.75, test_array[0]->area(), 0.001);
  ASSERT_NEAR(0.25*3.1415, test_array[1]->area(), 0.001);
  ASSERT_NEAR(3.1415, test_array[2]->area(), 0.001);
  ASSERT_NEAR(30, test_array[3]->area(), 0.001);



}
