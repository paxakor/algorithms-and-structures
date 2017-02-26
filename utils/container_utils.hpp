// Copyright 2017, Pavel Korozevtsev.

#pragma once

#include <algorithm>
#include <type_traits>
#include <vector>

namespace pkr {

template <typename Container>
auto to_vector(const Container& seq) {
  std::vector<std::decay_t<decltype(seq.front())>> res;
  std::copy(seq.begin(), seq.end(), std::back_inserter(res));
  return res;
}

template <typename Container, typename Type>
auto find_before(const Container& seq, const Type& val) {
  typename Container::ConstIterator prev = nullptr;
  for (auto it = seq.begin(); it != seq.end() && *it != val; ++it) {
    prev = it;
  }
  return prev;
}

template <typename Container, typename Type>
auto find_before(Container& seq, const Type& val) {
  typename Container::Iterator prev = nullptr;
  for (auto it = seq.begin(); it != seq.end() && *it != val; ++it) {
    prev = it;
  }
  return prev;
}

template <typename Container>
auto size(const Container& seq) {
  size_t sz = 0;
  for (const auto& v : seq) {
    ++sz;
  }
  return sz;
}

}  // namespace pkr
