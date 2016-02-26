#ifndef tree_hpp
#define tree_hpp


template <typename Type>
class TreeNode {
public:
  TreeNode();
  // TreeNode(const Type& val, TreeNode<Type>* p = nullptr,
  //   TreeNode<Type>* l = nullptr, TreeNode<Type>* r = nullptr);
  ~TreeNode();
  Type value;
  TreeNode<Type>* left;
  TreeNode<Type>* right;
  TreeNode<Type>* parent;
};

template <typename Type>
TreeNode<Type>::TreeNode() {
  this->value = Type();
  this->left = nullptr;
  this->right = nullptr;
  this->parent = nullptr;
}

// template <typename Type>
// TreeNode<Type>::TreeNode(const Type& val, TreeNode<Type>* p,
//   TreeNode<Type>* l, TreeNode<Type>* r) {
//   this->value = val;
//   this->left = l;
//   this->right = r;
//   this->parent = p;
// }

template <typename Type>
TreeNode<Type>::~TreeNode() {
  if (this->parent != nullptr &&
    (this->parent->left == this || this->parent->right == this)) {
    if (this->parent->left == this) {
      this->parent->left = nullptr;
    } else if (this->parent->right == this) {
      this->parent->right = nullptr;
    }
  }
  if (this->left != nullptr && this->left->parent == this) {
    delete this->left;
    this->left = nullptr;
  }
  if (this->right != nullptr && this->right->parent == this) {
    delete this->right;
    this->right = nullptr;
  }
}

#endif /* tree_hpp */
