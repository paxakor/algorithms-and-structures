#pragma once

#include <cstdio>

template <typename Type>
class Node {
public:
    Node();
    Node(Type);
    // Node(const Type*);
    Node(Node<Type>&);
    // Node(Node<Type>*);
    ~Node();
    // Node<Type>& operator = (Type);
    // Node<Type>& operator = (Type&);
    Node<Type>& operator = (Node<Type>&);
    // Node<Type>& operator = (Node<Type>*);
    // Node<Type>& operator ++ ();
    Node<Type>* operator & ();
    void set(Type);
    // void set(const Type*);
    // void set_next(Node<Type>&);
    void set_next(Node<Type>*);
    Type value();
    Node<Type>* next();
protected:
    Type value_var;
    Node<Type>* next_var;
};

template <typename Type>
Node<Type>::Node() {
    this->next_var = nullptr;
}

template <typename Type>
Node<Type>::Node(Type val) {
    this->value_var = val;
    this->next_var = nullptr;
}

// template <typename Type>
// Node<Type>::Node(const Type* val) {
//     this->value_var = *val;
//     this->next_var = nullptr;
// }

template <typename Type>
Node<Type>::Node(Node<Type>& another_node) {
    this->value_var = another_node.value_var;
    this->next_var = another_node.next_var;
}

// template <typename Type>
// Node<Type>::Node(Node<Type>* another_node) {
//     this->value_var = another_node->value_var;
//     this->next_var = another_node->next_var;
// }

template <typename Type>
Node<Type>::~Node() {
    if (this->next_var != nullptr) {
        delete next_var;
    }
}

// template <typename Type>
// Node<Type>& Node<Type>::operator = (Type val) {
//     this->set(val);
//     return *this;
// }

// template <typename Type>
// Node<Type>& Node<Type>::operator = (Type& val) {
//     this->set(val);
//     return *this;
// }

template <typename Type>
Node<Type>& Node<Type>::operator = (Node<Type>& another_node) {
    this->value_var = another_node.value();
    this->next_var = another_node.next();
    return *this;
}

// template <typename Type>
// Node<Type>& Node<Type>::operator = (Node<Type>* another_node) {
//     this->value_var = another_node->value();
//     this->next_var = another_node->next();
//     return *this;
// }

// template <typename Type>
// Node<Type>& Node<Type>::operator ++ () {
//     if (this->next_var == nullptr) {
//         this->next_var = new Node<Type>;
//     }
//     *(this) = *(this->next_var);
//     return *this;
// }

template <typename Type>
Node<Type>* Node<Type>::operator & () {
    return this;
}

template <typename Type>
void Node<Type>::set(Type val) {
    this->value_var = val;
}

// template <typename Type>
// void Node<Type>::set(const Type* val) {
//     this->value_var = *val;
// }

// template <typename Type>
// void Node<Type>::set_next(Node<Type>& another_node) {
//     this->next_var = &another_node;
// }

template <typename Type>
void Node<Type>::set_next(Node<Type>* another_node) {
    this->next_var = another_node;
}

template <typename Type>
Type Node<Type>::value() {
    return this->value_var;
}

template <typename Type>
Node<Type>* Node<Type>::next() {
    return this->next_var;
}
