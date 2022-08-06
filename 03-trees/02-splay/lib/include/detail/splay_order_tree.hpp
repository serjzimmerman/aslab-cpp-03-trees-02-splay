/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <tsimmerman.ss@phystech.edu>, wrote this file.  As long as you
 * retain this notice you can do whatever you want with this stuff. If we meet
 * some day, and you think this stuff is worth it, you can buy us a beer in
 * return.
 * ----------------------------------------------------------------------------
 */

#pragma once

#include "bs_order_tree.hpp"
#include <stdexcept>

namespace throttle {
namespace detail {
template <typename t_value_type, typename t_comp, typename t_key_type>
class splay_order_tree : public bs_order_tree<t_value_type, t_comp, t_key_type> {
  using bs_order_tree_impl::base_ptr;
  using typename bs_order_tree<t_value_type, t_comp, t_key_type>::node_ptr;

protected:
  void splay_to_root(base_ptr p_node) {
    while (p_node->m_parent) {
      // Case 1. Zig
      if (!p_node->m_parent->m_parent) {
        this->rotate_to_parent(p_node);
      }

      // Case 2. Zig-zig
      else if (p_node->is_linear()) {
        this->rotate_to_parent(p_node->m_parent);
        this->rotate_to_parent(p_node);
      }

      // Case 3. Zig-zag
      else {
        this->rotate_to_parent(p_node);
        this->rotate_to_parent(p_node);
      }
    }
  }

  void join(base_ptr p_left, base_ptr p_right) {
    base_ptr max_left = p_left->maximum();
    splay_to_root(max_left);
    max_left->m_right = p_right;
    p_right->m_parent = max_left;
    this->m_root = max_left;
    max_left->m_size = max_left->m_left->m_size + max_left->m_right->m_size + 1;
  }

public:
  void insert(const t_value_type &p_val) {
    auto [inserted, prev] = this->bst_insert(p_val);
    if (!inserted) {
      splay_to_root(prev);
      throw std::out_of_range("Double insert");
    } else {
      splay_to_root(inserted);
    }
  }

  void erase(const t_key_type &p_key) {
    auto [to_erase, prev] = this->bst_lookup(p_key);

    if (!to_erase) {
      if (prev) splay_to_root(prev);
      throw std::out_of_range("Trying to erase element not present in the tree");
    }

    if (this->size() == 1) {
      this->m_root = this->m_leftmost = this->m_rightmost = nullptr;
      delete to_erase;
      return;
    }

    // Move the node to the root. Depending on the number of children of the new root we should modify leftmost and
    // rightmost pointers.
    splay_to_root(to_erase);

    if (!to_erase->m_left) {
      this->m_leftmost = to_erase->successor();
      this->m_root = to_erase->m_right;
      to_erase->m_right->m_parent = nullptr;
    } else if (!to_erase->m_right) {
      this->m_rightmost = to_erase->predecessor();
      this->m_root = to_erase->m_left;
      to_erase->m_left->m_parent = nullptr;
    } else {
      to_erase->m_right->m_parent = nullptr;
      to_erase->m_left->m_parent = nullptr;
      join(to_erase->m_left, to_erase->m_right);
    }

    delete to_erase;
  }

public:
};
} // namespace detail
} // namespace throttle
