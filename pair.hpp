#ifndef pair_hpp
#define pair_hpp

template <typename TypeA, typename TypeB>
class Pair {
public:
  Pair();
  Pair(const TypeA&, const TypeB&);
  ~Pair();
  TypeA first;
  TypeB second;
};

template <typename TypeA, typename TypeB>
Pair<TypeA, TypeB>::Pair() {}

template <typename TypeA, typename TypeB>
Pair<TypeA, TypeB>::Pair(const TypeA& a, const TypeB& b) {
  this->first = a;
  this->second = b;
}

template <typename TypeA, typename TypeB>
Pair<TypeA, TypeB>::~Pair() {}

#endif /* pair_hpp */
