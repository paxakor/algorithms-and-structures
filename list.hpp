#ifndef list_hpp
#define list_hpp

#include "node.hpp"

template <typename Type>
class List {
public:
    List();  // O(1)
    List(Node<Type>*, Node<Type>*);  // O(1)
    List(List<Type>&);  // O(n)
    List(const Type*, int);  // O(n)
    ~List();  // O(n)
    List<Type> operator = (List<Type>&);  // O(n)
    Node<Type>* begin() const;  // O(1)
    Node<Type>* end() const;  // O(1)
    Node<Type>* find(const Type&) const;  // O(n)
    Node<Type>* find_prev(const Type&) const;  // O(n)
    void append(const Type&);  // O(1)
    void insert(Node<Type>*, const Type&);  // O(1)
    void remove(Node<Type>*);  // O(1)
    void remove(const Type&);  // O(n)
protected:
    Node<Type>* begin_ptr;
    Node<Type>* end_ptr;
};

template <typename Type>
int size_of_list(const List<Type>& list) {
    int s = 0;
    for(auto ptr = list.begin(); ptr != list.end(); ptr = ptr->next()) {
        ++s;
    }
    return s;
}

template <typename Type>
List<Type>::List() {
    this->begin_ptr = new Node<Type>;
    this->end_ptr = this->begin_ptr;
    this->end_ptr->set_next(nullptr);
}

template <typename Type>
List<Type>::List(Node<Type>* first, Node<Type>* second) {
    this->begin_ptr = first;
    this->end_ptr = second;
    this->end_ptr->set_next(nullptr);
}

template <typename Type>
List<Type>::List(List<Type>& another_list) {
    this->begin_ptr = new Node<Type>;
    this->end_ptr = this->begin_ptr;
    Node<Type>* ptr = another_list.begin();
    while(ptr != another_list.end()) {
        end_ptr->set(ptr->value());
        end_ptr->set_next(new Node<Type>);
        ++end_ptr;
        ++ptr;
    }
    this->end_ptr->set_next(nullptr);
}

template <typename Type>
List<Type>::List(const Type* array, int length) {
    this->begin_ptr = new Node<Type>;
    this->end_ptr = begin_ptr;
    for(int i = 0; i < length; ++i) {
        this->end_ptr->set(array[i]);
        this->end_ptr->set_next(new Node<Type>);
        this->end_ptr = end_ptr->next();
    }
    this->end_ptr->set_next(nullptr);
    print_list(*this);
}

template <typename Type>
List<Type>::~List() {}

template <typename Type>
List<Type> List<Type>::operator = (List<Type>& another_list) {
    List<Type> new_list(another_list);
    this->begin_ptr = new_list.begin();
    this->end_ptr = new_list.end();
    return *this;
}

template <typename Type>
Node<Type>* List<Type>::begin() const {
    return this->begin_ptr;
}

template <typename Type>
Node<Type>* List<Type>::end() const {
    return this->end_ptr;
}

template <typename Type>
Node<Type>* List<Type>::find(const Type& val) const {
    Node<Type>* ptr = this->begin();
    while(ptr != this->end() && ptr->value() != val) {
        ++ptr;
    }
    return ptr;
}

template <typename Type>
Node<Type>* List<Type>::find_prev(const Type& val) const {
    Node<Type>* ptr = this->begin();
    while(ptr->next() != this->end()) {
        if(ptr->next()->value() == val) {
            break;
        }                
        ptr = ptr->next();
    }
    return ptr;
}

template <typename Type>
void List<Type>::append(const Type& val) {
    this->end()->set(val);
    this->end_ptr->set_next(new Node<Type>);
    this->end_ptr = this->end_ptr->next();
}

template <typename Type>
void List<Type>::insert(Node<Type>* ptr, const Type& val) {
    Node<Type>* new_node = new Node<Type>;
    new_node->set(val);
    new_node->set_next(ptr->next());
    ptr->set_next(new_node);
}

template <typename Type>
void List<Type>::remove(Node<Type>* ptr) {
    if(ptr == this->begin()) {
        this->begin_ptr = this->begin_ptr->next();
    }
    else {
        ptr->set_next(ptr->next()->next());
    }
}

template <typename Type>
void List<Type>::remove(const Type& val) {
    if (this->begin()->value() == val) {
        this->remove(this->begin());
    }
    else {        
        Node<Type>* ptr = this->find_prev(val);        
        if(ptr->next() != this->end()) {
            this->remove(ptr);
        }
    }
}

#endif /* list_hpp */
