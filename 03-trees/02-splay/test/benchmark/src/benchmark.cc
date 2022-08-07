#include <chrono>
#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
#include <numeric>

#include "splay_order_set.hpp"

using namespace throttle;

template class throttle::splay_order_set<int>;

template <typename T>
int set_range_query(const std::set<T>& p_set, T p_first, T p_second) {
  auto its = p_set.lower_bound(p_first);
  auto ite = p_set.upper_bound(p_second);
  return std::distance(its, ite);
}

template <typename T>
int my_set_range_query(throttle::splay_order_set<T> &p_set, T p_first, T p_second) {
  if (p_set.empty()) {
    return 0;
  }
  
  auto cl_left = p_set.closest_left(p_first);
  auto cl_right = p_set.closest_right(p_second);
  int rank_left = (cl_left == p_set.end() ? 0 : p_set.get_rank_of(*cl_left));
  int rank_right = (cl_right == p_set.end() ? p_set.size() + 1 : p_set.get_rank_of(*cl_right));
  return rank_right - rank_left - 1;
}

int main() {
  int n;
  if (!(std::cin >> n)) {
    std::abort();
  }

  std::vector<int> vec{};
  vec.reserve(n);

  for (int i = 0; i < n; ++i) {
    int temp;
    if (!(std::cin >> temp)) {
      std::abort();
    }
    vec.push_back(temp);
  }

  int m;
  if (!(std::cin >> m)) {
    std::abort();
  }

  std::vector<std::pair<int, int>> q_vec{};
  q_vec.reserve(m);

  for (int i = 0; i < m; ++i) {
    int temp1, temp2;
    if ((!(std::cin >> temp1 >> temp2)) || temp1 >= temp2) {
      std::abort();
    }
    q_vec.push_back({temp1, temp2});
  }

  auto my_set_start = std::chrono::high_resolution_clock::now();

  splay_order_set<int> t{};
  for (const auto v : vec) {
    t.insert(v);
  }

  for (const auto q : q_vec) {
    std::cout << my_set_range_query(t, q.first, q.second);
  }

  auto my_set_finish = std::chrono::high_resolution_clock::now();
  auto my_set_elapsed = std::chrono::duration<double, std::milli>(my_set_finish - my_set_start);
}