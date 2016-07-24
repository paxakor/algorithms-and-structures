// Copyright 2016, Pavel Korozevtsev.

#pragma once

#include <functional>
#include <vector>
#include "utils/random.hpp"

namespace pkr {

template <typename Type, typename ResultType = size_t>
class Hasher {
public:
  explicit Hasher(size_t k)
    : _masks(k) {
    Random<ResultType> rnd;
    for (auto& m : _masks) {
      m = rnd.get();
    }
  }

  ResultType operator()(Type const& value, size_t k) const {
    return _std_hash(value) ^ _masks[k];
  }

private:
  // hash for standart types.
  // you should implement your own functor for other types.
  std::hash<Type> _std_hash;

  // array of random masks
  std::vector<ResultType> _masks;
};

}  // namespace pkr
