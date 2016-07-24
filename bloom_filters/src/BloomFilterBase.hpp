// Copyright 2016, Pavel Korozevtsev.

template <typename Type>
class BloomFilterBase {
public:
  virtual ~BloomFilterBase();
  virtual void insert(const Type&) = 0;
  virtual bool find(const Type&) = 0;
};
