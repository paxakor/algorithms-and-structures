#pragma once

namespace pkr {

template <typename TypeA, typename TypeB>
class Pair {
public:
  Pair() = default;
  Pair(const Pair&) = default;
  Pair(const TypeA&, const TypeB&);
  const Pair& operator=(const Pair&) = default;
  TypeA first;
  TypeB second;
};

template <typename TypeA, typename TypeB>
Pair<TypeA, TypeB>::Pair(const TypeA& a, const TypeB& b)
  : first(a)
  , second(b) {}

}
