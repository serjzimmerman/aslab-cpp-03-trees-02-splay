#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <numeric>
#include <set>

#include "splay_order_set.hpp"

using namespace throttle;

template class throttle::splay_order_set<int>;

template <typename T> int set_range_query(const std::set<T> &p_set, T p_first, T p_second) {
  auto its = p_set.lower_bound(p_first);
  auto ite = p_set.upper_bound(p_second);
  return std::distance(its, ite);
}

template <typename T> int my_set_range_query(throttle::splay_order_set<T> &p_set, T p_first, T p_second) {
  if (p_set.empty()) {
    return 0;
  }

  auto its = p_set.lower_bound(p_first);
  auto ite = p_set.upper_bound(p_second);

  int rank_left = (its == p_set.end() ? 0 : p_set.get_rank_of(*its));
  int rank_right = (ite == p_set.end() ? p_set.size() + 1 : p_set.get_rank_of(*ite));

  return rank_right - rank_left;
}

int main() {
  int n;
  if (!(std::cin >> n)) {
    return 666;
  }

  std::vector<int> vec{};
  vec.reserve(n);

  for (int i = 0; i < n; ++i) {
    int temp;
    if (!(std::cin >> temp)) {
      return 666;
    }
    vec.push_back(temp);
  }

  int m;
  if (!(std::cin >> m)) {
    return 666;
  }

  std::vector<std::pair<int, int>> q_vec{};
  std::vector<int> my_set_ans{}, set_ans{};
  q_vec.reserve(m);
  my_set_ans.reserve(m);
  set_ans.reserve(m);

  for (int i = 0; i < m; ++i) {
    int temp1, temp2;
    if ((!(std::cin >> temp1 >> temp2)) || temp1 >= temp2) {
      return 666;
    }
    q_vec.push_back({temp1, temp2});
  }

  auto my_set_start = std::chrono::high_resolution_clock::now();

  splay_order_set<int> t{};
  for (const auto v : vec) {
    t.insert(v);
  }

  for (const auto q : q_vec) {
    my_set_ans.push_back(my_set_range_query(t, q.first, q.second));
  }

  auto my_set_finish = std::chrono::high_resolution_clock::now();
  auto my_set_elapsed = std::chrono::duration<double, std::milli>(my_set_finish - my_set_start);

  auto set_start = std::chrono::high_resolution_clock::now();

  std::set<int> s{};
  for (const auto v : vec) {
    s.insert(v);
  }

  for (const auto q : q_vec) {
    set_ans.push_back(set_range_query(s, q.first, q.second));
  }

  auto set_finish = std::chrono::high_resolution_clock::now();
  auto set_elapsed = std::chrono::duration<double, std::milli>(my_set_finish - my_set_start);

  if (my_set_ans != set_ans) {
    return 42;
  }

  for (const auto v: my_set_ans) {
    std::cout << v << " ";
  }
  std::cout << "\n";

  return 0;
}