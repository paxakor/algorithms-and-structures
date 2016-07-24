// Copyright 2016, Pavel Korozevtsev.

#pragma once

#include <vector>
#include "bloom_filter_base.hpp"

namespace pkr {

template <typename Type, class Hash = Hasher<Type>>
class BloomFilter : public BloomFilterBase<Type, Hash> {
public:
  BloomFilter(size_t, size_t);
  void insert(const Type&) override;
  bool find(const Type&) override;

private:
  size_t _k;
  size_t _m;
  std::vector< std::vector<bool> > _table;
  Hash _hasher;
};

template <typename Type, class Hash>
BloomFilter<Type, Hash>::BloomFilter(size_t k, size_t m)
  : _k(k)
  , _m(m)
  , _table(k)
  , _hasher(k) {
  for (auto& hash_line : _table) {
    hash_line.assign(_m, false);
  }
}

template <typename Type, class Hash>
void BloomFilter<Type, Hash>::insert(const Type& value) {
  for (size_t i = 0; i < _k; ++i) {
    const size_t hash_id = _hasher(value, i) % _m;
    _table[i][hash_id] = true;
  }
}

template <typename Type, class Hash>
bool BloomFilter<Type, Hash>::find(const Type& value) {
  for (size_t i = 0; i < _k; ++i) {
    const size_t hash_id = _hasher(value, i) % _m;
    if (_table[i][hash_id] == false) {
      return false;
    }
  }
  return true;
}

}  // namespace pkr
