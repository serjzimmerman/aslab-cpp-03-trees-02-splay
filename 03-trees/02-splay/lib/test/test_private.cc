#include <cstddef>
#include <cstdlib>
#include <functional>
#include <gtest/gtest.h>
#include <set>
#include <string>

#define private public
#define protected public

#undef private
#undef protected

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}