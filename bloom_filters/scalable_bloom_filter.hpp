// Copyright 2016, Pavel Korozevtsev.

#pragma once

#include <vector>
#include "bloom_filter_base.hpp"
#include "bloom_filter.hpp"

namespace pkr {

template <typename Type, class Hash = Hasher<Type>>
class ScalableBloomFilter : public BloomFilterBase<Type, Hash> {
public:
  ScalableBloomFilter(size_t, size_t, double = 0.5);
  void insert(const Type&) override;
  bool find(const Type&) const override;

private:
  inline void add_filter();
  void check_fill_ratio();

  const size_t _k;
  size_t _m;
  const double _max_fill_ratio;
  std::vector< BloomFilter<Type, Hash> > _table;
  static constexpr size_t _check_frequency = 16;
};

template <typename Type, class Hash>
ScalableBloomFilter<Type, Hash>
::ScalableBloomFilter(size_t k, size_t m, double r)
  : _k(k)
  , _m(m)
  , _max_fill_ratio(r) {
  add_filter();
  }

template <typename Type, class Hash>
void ScalableBloomFilter<Type, Hash>::insert(const Type& value) {
  _table.back().insert(value);
  check_fill_ratio();
}

template <typename Type, class Hash>
bool ScalableBloomFilter<Type, Hash>::find(const Type& value) const {
  for (const auto& filter : _table) {
    if (filter.find(value)) {
      return true;
    }
  }
  return false;
}

template <typename Type, class Hash>
inline void ScalableBloomFilter<Type, Hash>::add_filter() {
  _table.emplace_back(_k, _m);
  _m *= 2;
}

template <typename Type, class Hash>
void ScalableBloomFilter<Type, Hash>::check_fill_ratio() {
  const double last_ratio = _table.back().get_fill_ratio();
  if (last_ratio >= _max_fill_ratio) {
    add_filter();
  }
}

}  // namespace pkr
