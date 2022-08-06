#include <chrono>
#include <iostream>

#define private public
#define protected public
#include "detail/bs_order_tree.hpp"
#include "detail/splay_order_tree.hpp"
#undef private
#undef protected

using namespace throttle::detail;

int main() {
  splay_order_tree<int, std::less<int>, int> t{};
  for (int i = 0; i < 25; i++) {
    t.insert(i);
  }

  for (const auto v: t) {
    std::cout << v << " ";
  }
  std::cout << "\n";

  for (int i = 0; i < 10; i++) {
    t.erase(i);
  }

  assert(t.size() == 15);
  t.erase(24);

  for (const auto v: t) {
    std::cout << v << " ";
  }
  std::cout << "\n";
}