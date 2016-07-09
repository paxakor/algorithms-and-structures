// Copyright 2016, Pavel Korozevtsev.

#include "BloomFilterBase.hpp"

template <typename Type>
class BloomFilter : public BloomFilterBase {
public:
  BloomFilter();
  virtual ~BloomFilter();
  virtual void insert(const Type&);
  virtual bool find(const Type&);
};
