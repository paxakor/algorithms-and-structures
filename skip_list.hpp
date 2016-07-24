#pragma once

#include <random>
#include "list.hpp"
#include "pair.hpp"

namespace pkr {

class Random {
public:
  Random(double p)
    : _rd()
    , _gen(rd())
    , _dis(p) {}
  bool get() const {
    return _dis(_gen);
  }

private:
  std::random_device _rd;
  std::mt19937 _gen;
  std::bernoulli_distribution _dis;
};

template <typename Type>
class SkipListNode {
public:
  SkipListNode();
  ~SkipListNode();
  
};

template <typename Type>
class SkipList {
public:
  SkipList(double = 0.5);
  void add(const Type&);
  void del(const Type&);
  bool find(const Type&) const;

private:
  List< List<Type> > data;
  static const Random rnd;
};

template <typename Type>
SkipList<Type>::SkipList(double p)
  : rnd(p) {}

template <typename Type>
void SkipList<Type>::add(const Type& val) {

}

template <typename Type>
void SkipList<Type>::del(const Type& val) {

}

template <typename Type>
void SkipList<Type>::find(const Type& val) const {

}
