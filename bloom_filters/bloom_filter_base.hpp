// Copyright 2016, Pavel Korozevtsev.

#pragma once

#include "hasher.hpp"

namespace pkr {

template <typename Type, class Hash = Hasher<Type>>
class BloomFilterBase {
public:
  virtual ~BloomFilterBase() {}
  virtual void insert(const Type&) = 0;
  virtual bool find(const Type&) = 0;
};

}  // namespace pkr
