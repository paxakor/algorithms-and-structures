#pragma once

namespace pkr {

template <typename Type>
const Type& min(const Type& a, const Type& b) {
  if (a < b)
    return a;
  return b;
}

template <typename Type>
const Type& max(const Type& a, const Type& b) {
  if (a > b)
    return a;
  return b;
}

template <typename Type>
void swap(Type& a, Type& b) {
  const Type c = a;
  a = b;
  b = c;
}

// *binary_search <= value
// it doesn't works
template <typename Iter, typename Type>
const Iter binary_search(const Iter& begin, const Iter& end,
  const Type& value) {
  if (begin == end) {
    return begin;
  } else if (begin + 1 == end) {
    return (*begin <= value) ? begin : end;
  }
  const auto diff = (end - begin) / 2;
  const auto mid = begin + diff;
  if (value < *mid) {
    return binary_search(begin, mid, value);
  } else {
    return binary_search(mid, end, value);
  }
}

}
