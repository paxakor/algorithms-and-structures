// Copyright 2016, Pavel Korozevtsev.

#pragma once

#include <cmath>
#include <vector>
#include "bloom_filter_base.hpp"
#include "hasher.hpp"

namespace pkr {

template <typename Type, class Hash = Hasher<Type>>
class BloomFilter : public BloomFilterBase<Type, Hash> {
public:
  BloomFilter(size_t, size_t);
  void insert(const Type&) override;
  bool find(const Type&) const override;
  double get_fill_ratio() const;

private:
  const size_t _k;
  const size_t _m;
  const Hash _hasher;
  std::vector<bool> _line;
  size_t _inserted = 0;
};

template <typename Type, class Hash>
BloomFilter<Type, Hash>::BloomFilter(size_t k, size_t m)
  : _k(k)
  , _m(m)
  , _hasher(k)
  , _line(m, false) {}

template <typename Type, class Hash>
void BloomFilter<Type, Hash>::insert(const Type& value) {
  for (size_t i = 0; i < _k; ++i) {
    const size_t hash_id = _hasher(value, i) % _m;
    _line[hash_id] = true;
  }
  ++_inserted;
}

template <typename Type, class Hash>
bool BloomFilter<Type, Hash>::find(const Type& value) const {
  for (size_t i = 0; i < _k; ++i) {
    const size_t hash_id = _hasher(value, i) % _m;
    if (!_line[hash_id]) {
      return false;
    }
  }
  return true;
}

template <typename Type, class Hash>
double BloomFilter<Type, Hash>::get_fill_ratio() const {
  // return (static_cast<double>(_k) * _inserted) / _m;
  return 1.0 - exp(-static_cast<double>(_inserted) / _m);
}

}  // namespace pkr
