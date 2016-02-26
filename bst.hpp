#ifndef bst_hpp
#define bst_hpp

#include <cstddef>
#include "tree.hpp"

// BST -- Binary Search Tree
template <typename Type>
class BST {
public:
  BST();
  ~BST();
  void add(const Type&);
  void del(const Type&);
  bool find(const Type&) const;
private:
  TreeNode<Type>* upper_bound(TreeNode<Type>*) const;
  void add(TreeNode<Type>*, const Type&);
  void del(TreeNode<Type>*);
  TreeNode<Type>* find(TreeNode<Type>*, const Type&) const;

  TreeNode<Type>* root;
  bool empty;
};

template <typename Type>
BST<Type>::BST() {
  this->root = new TreeNode<Type>;
  this->empty = true;
}

template <typename Type>
BST<Type>::~BST() {
  delete this->root;
}

template <typename Type>
void BST<Type>::add(const Type& val) {
  if (this->find(val)) {
    return;
  }
  if (this->empty) {
    this->root->value = val;
    this->empty = false;
  } else {
    this->add(this->root, val);  
  }
}

template <typename Type>
void BST<Type>::add(TreeNode<Type>* v, const Type& val) {
  if (val < v->value) {
    if (v->left != nullptr) {
      this->add(v->left, val);
    } else {
      v->left = new TreeNode<Type>;
      v->left->value = val;
      v->left->parent = v;
    }
  } else {
    if (v->right != nullptr) {
      this->add(v->right, val);
    } else {
      v->right = new TreeNode<Type>;
      v->right->value = val;
      v->right->parent = v;
    }
  }
}

template <typename Type>
void BST<Type>::del(const Type& val) {
  TreeNode<Type>* v = this->find(this->root, val);
  if (v == nullptr) {
    return;
  }
  this->del(v);
}

template <typename Type>
void BST<Type>::del(TreeNode<Type>* v) {
  if (v == nullptr) {
    return;
  }
  if (v->parent == nullptr) {
    if (v->left == nullptr && v->right == nullptr) {
      delete this->root;
      this->root = new TreeNode<Type>;
      this->empty = true;
    } else if (v->left == nullptr && v->right != nullptr) {
      v->right->parent = nullptr;
      this->root = v->right;
      delete v;
    } else if (v->left != nullptr && v->right == nullptr) {
      v->left->parent = nullptr;
      this->root = v->left;
      delete v;
    } else /*if (v->left != nullptr && v->right != nullptr)*/ {
      TreeNode<Type>* u = this->upper_bound(v);
      v->value = u->value;
      this->del(u);
    }
  } else {
    bool v_is_left_son = (v->parent->left == v);
    if (v->left == nullptr && v->right == nullptr) {
      if (v_is_left_son) {
        v->parent->left = nullptr;
      } else {
        v->parent->right = nullptr;
      }
      delete v;
    } else if (v->left == nullptr && v->right != nullptr) {
      v->right->parent = v->parent;
      if (v_is_left_son) {
        v->parent->left = v->right;
      } else {
        v->parent->right = v->right;
      }
      delete v;
    } else if (v->left != nullptr && v->right == nullptr) {
      v->left->parent = v->parent;
      if (v_is_left_son) {
        v->parent->left = v->left;
      } else {
        v->parent->right = v->left;
      }
      delete v;
    } else /*if (v->left != nullptr && v->right != nullptr)*/ {
      TreeNode<Type>* u = this->upper_bound(v);
      v->value = u->value;
      this->del(u);
    }
  }
}

template <typename Type>
bool BST<Type>::find(const Type& val) const {
  return (this->find(this->root, val) != nullptr);
}

template <typename Type>
TreeNode<Type>* BST<Type>::find(TreeNode<Type>* v, const Type& val) const {

  if (v == nullptr) {
    return nullptr;
  }
  if (v->value == val) {
    return v;
  }
  if (val < v->value) {
    return this->find(v->left, val);
  } else {
    return this->find(v->right, val);
  }
}

template <typename Type>
TreeNode<Type>* BST<Type>::upper_bound(TreeNode<Type>* v) const {
  if (v != nullptr && v->right != nullptr) {
    v = v->right;
    while (v->left != nullptr) {
      v = v->left;
    }
  }
  return v;
}

#endif /* bst_hpp */
