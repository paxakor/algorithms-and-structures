#ifndef skip_list_hpp
#define skip_list_hpp

#include <cstdlib>
#include <ctime>
#include "list.hpp"
#include "pair.hpp"

bool dice(double p) {
    srand(time(NULL));
    return ((rand() % 10001) / 10000.0 < p);
}


template <typename Type>
class SkipList {
public:
    SkipList();
    SkipList(double);
    SkipList(const List<Type>&);
    SkipList(const List<Type>&, double);
    SkipList(const SkipList<Type>&);
    ~SkipList();

    Node<Type>* begin() const;
    Node<Type>* end() const;
    Node<Type>* find(const Type&) const;
    Type lower_bound(const Type&) const;
    void add(const Type&);
    void del(const Type&);

protected:
    List< List<Type> > data;
    List<Type> main_list;
    double probability;
};

template <typename Type>
SkipList<Type>::SkipList() {
    this->probability = 0.5;
}

template <typename Type>
SkipList<Type>::SkipList(double p) {
    this->probability = p;
}

template <typename Type>
SkipList<Type>::SkipList(const List<Type>& another_list) {
    this->probability = 0.5;
    this->main_list = another_list;

}

template <typename Type>
SkipList<Type>::SkipList(const List<Type>& arr, double p) {
    this->probability = p;

}

template <typename Type>
SkipList<Type>::SkipList(const SkipList<Type>& list) {
    this->probability = list.probability;
    this->data = list.data;
    this->main_list = list.main_list;
}

template <typename Type>
SkipList<Type>::~SkipList() {}


template <typename Type>
void SkipList<Type>::add(const Type&) {

}

template <typename Type>
void SkipList<Type>::del(const Type&) {

}

template <typename Type>
Type SkipList<Type>::lower_bound(const Type&) const{

}

#endif /* skip_list_hpp */
