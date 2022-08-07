/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <tsimmerman.ss@phystech.edu>, wrote this file.  As long as you
 * retain this notice you can do whatever you want with this stuff. If we meet
 * some day, and you think this stuff is worth it, you can buy us a beer in
 * return.
 * ----------------------------------------------------------------------------
 */

#include <functional>
#include <initializer_list>

#include "detail/splay_order_tree.hpp"

namespace throttle {
template <typename T, typename t_comp = std::less<T>> class splay_order_set {
private:
  detail::splay_order_tree<T, t_comp, T> m_tree_impl;

public:
  using value_type = T;
  using reference = const T &;
  using size_type = typename detail::splay_order_tree<T, t_comp, T>::size_type;
  using key_type = T;

  class iterator {
    friend class splay_order_set<T, t_comp>;
  private:
    typename detail::splay_order_tree<T, t_comp, T>::iterator m_it_impl;

    iterator(typename detail::splay_order_tree<T, t_comp, T>::iterator p_wrapped) : m_it_impl{p_wrapped} {}

  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = typename detail::splay_order_tree<T, t_comp, T>::iterator::difference_type;
    using value_type = T;
    using pointer = const T *;
    using reference = const T &;

    iterator() : m_it_impl{} {}

    reference operator*() const {
      return *m_it_impl;
    }

    pointer operator->() {
      return m_it_impl.get();
    }

    iterator &operator++() {
      ++m_it_impl;
      return *this;
    }

    iterator operator++(int) {
      iterator temp{*this};
      ++(*this);
      return temp;
    }

    iterator &operator--() {
      --m_it_impl;
      return *this;
    }

    iterator operator--(int) {
      iterator temp{*this};
      --(*this);
      return temp;
    }

    bool operator==(const iterator &p_rhs) const {
      return m_it_impl == p_rhs.m_it_impl;
    }

    bool operator!=(const iterator &p_rhs) const {
      return m_it_impl != p_rhs.m_it_impl;
    }
  };

  using difference_type = typename iterator::difference_type;
  using const_iterator = iterator;

  splay_order_set() : m_tree_impl{} {}

  splay_order_set(std::initializer_list<T> p_list) : splay_order_set{} {
    m_tree_impl.insert_range(p_list.begin(), p_list.end());
  }

  bool empty() const {
    return m_tree_impl.empty();
  }

  size_type size() const {
    return m_tree_impl.size();
  }

  void clear() {
    m_tree_impl.clear();
  }

  iterator begin() const {
    return iterator{m_tree_impl.begin()};
  }

  iterator end() const {
    return iterator{m_tree_impl.end()};
  }

  const_iterator cbegin() const {
    return iterator{m_tree_impl.begin()};
  }

  const_iterator cend() const {
    return iterator{m_tree_impl.end()};
  }

  iterator min() const {
    return begin();
  }

  iterator max() const {
    return std::prev(end());
  }

  iterator closest_left(const key_type &p_key) {
    return iterator{m_tree_impl.closest_left(p_key)};
  }

  iterator closest_right(const key_type &p_key) {
    return iterator{m_tree_impl.closest_right(p_key)};
  }

  iterator find(const key_type &p_key) {
    return iterator{m_tree_impl.find(p_key)};
  }

  iterator select_rank(size_type p_rank) {
    return iterator{m_tree_impl.select_rank(p_rank)};
  }

  size_type get_rank_of(const key_type &p_key) {
    return m_tree_impl.get_rank_of(p_key);
  }

  void insert(const value_type &p_val) {
    m_tree_impl.insert(p_val);
  }

  void erase(const key_type &p_key) {
    m_tree_impl.erase(p_key);
  }

  bool contains(const key_type &p_key) {
    return (find(p_key) != end());
  }
};
} // namespace throttle