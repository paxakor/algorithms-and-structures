// Copyright 2016, Pavel Korozevtsev.

#pragma once

#include <vector>

namespace pkr {

template <typename Type>
class Arena {
public:
  ~Arena() {
    for (auto ptr : _storage) {
      delete[] ptr;
    }
  }

  Type* get(size_t size) {
    Type* ptr = new Type[size];
    _storage.push_back(ptr);
    return ptr;
  }

private:
  std::vector<Type*> _storage;
};

}  // namespace pkr
