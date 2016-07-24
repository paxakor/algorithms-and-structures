// Copyright 2016, Pavel Korozevtsev.

#pragma once

#include <cstddef>
#include <functional>
#include <vector>

namespace pkr {

template <typename Type, class Compare = std::less<Type> >
class Heap {
public:
  Heap() = default;
  Heap(const Heap&) = default;

  template <typename InputIterator>
  Heap(InputIterator, InputIterator, size_t = 2);

  Heap(size_t k)
    : _k(k) {}

  void push(const Type&);
  void pop();
  Type top() const {
    return _data.front();
  }
  size_t size() const {
    return _data.size();
  }
  bool empty() const {
    return size() == 0;
  }
  auto data() const {
    return _data;
  }
  void clear() {
    _data.clear();
  }

private:
  void sift_up(size_t);
  void sift_down(size_t);
  inline size_t parent(size_t) const;
  inline size_t child(size_t, size_t) const;

  const size_t _k = 2;
  std::vector<Type> _data;
};

template <typename Type, class Compare>
template <typename InputIterator>
Heap<Type, Compare>::Heap(InputIterator begin, InputIterator end, size_t k)
  : _k(k)
  , _data(begin, end) {
  for (size_t i = 0; i < _data.size(); ++i) {
    sift_up(i);
  }
}

template <typename Type, class Compare>
void Heap<Type, Compare>::push(const Type& val) {
  _data.push_back(val);
  sift_up(size() - 1);
}

template <typename Type, class Compare>
void Heap<Type, Compare>::pop() {
  if (empty()) {
    return;
  }
  _data.front() = _data.back();
  _data.pop_back();
  if (!empty()) {
    sift_down(0);
  }
}

template <typename Type, class Compare>
void Heap<Type, Compare>::sift_up(size_t iter) {
  auto& a = _data[iter];
  auto& b = _data[parent(iter)];
  if (Compare()(a, b)) {
    using std::swap;
    swap(a, b);
    sift_up(parent(iter));
  }
}

template <typename Type, class Compare>
void Heap<Type, Compare>::sift_down(size_t iter) {
  auto iter_min = iter;
  auto iter_child = child(iter, 0);
  for (size_t i = 0; i < _k && iter_child < size(); ++i) {
    if (Compare()(_data[iter_child], _data[iter_min])) {
      iter_min = iter_child;
    }
    ++iter_child;
  }
  if (iter_min == iter) {
    return;
  }
  using std::swap;
  swap(_data[iter_min], _data[iter]);
  sift_down(iter_min);
}

template <typename Type, class Compare>
size_t Heap<Type, Compare>::parent(size_t iter) const {
  return iter == 0 ? 0 : (iter - 1) / _k;
}

// number in [0, k-1].
template <typename Type, class Compare>
size_t Heap<Type, Compare>::child(size_t iter, size_t number) const {
  // const auto ans = iter * _k + number + 1;
  // return ans >= size() ? 0 : ans;
  return iter * _k + number + 1;
}

} // namespace pkr
