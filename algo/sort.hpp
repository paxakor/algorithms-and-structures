// Copyright 2016, Pavel Korozevtsev.

#pragma once

#include <cinttypes>
#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
#include <type_traits>
#include <utility>
#include "heap.hpp"

namespace pkr {

template <typename ForwardIterator, class Compare>
void heap_sort(ForwardIterator begin, ForwardIterator end, Compare comp) {
  using Type = typename std::remove_reference<decltype(*begin)>::type;
  Heap<Type, Compare> heap(begin, end);
  while (begin != end) {
    *(begin++) = heap.top();
    heap.pop();
  }
}

template <typename ForwardIterator>
void heap_sort(ForwardIterator begin, ForwardIterator end) {
  using Type = typename std::remove_reference<decltype(*begin)>::type;
  heap_sort(begin, end, std::less<Type>{});
}

template <typename RandomAccessIterator>
void radix_sort(RandomAccessIterator begin, RandomAccessIterator end,
                const int bit_index = 0) {
  using UInt = typename std::remove_reference<decltype(*begin)>::type;
  const int64_t len = std::distance(begin, end);
  if (!(len > 0)) {
    return;
  }
  const UInt bit = static_cast<UInt>(1) << (sizeof(UInt) * 8 - 1 - bit_index);
  int64_t l = 0, r = len - 1;
  while (l < r) {
    while (l < r && !(begin[l] & bit)) {
      ++l;
    }
    while (l < r && (begin[r] & bit)) {
      --r;
    }
    if (l < r) {
      using std::swap;
      swap(begin[l], begin[r]);
      ++l;
    }
  }
  while (0 < l && (begin[l] & bit)) {
    --l;
  }
  while (r < len - 1 && !(begin[r] & bit)) {
    ++r;
  }
  if (bit >> 1) {
    if (0 < l) {
      radix_sort(begin, begin + l + 1, bit_index + 1);
    }
    if (r < len - 1) {
      radix_sort(begin + r, end, bit_index + 1);
    }
  }
}

template <typename RandomAccessIterator, class Compare>
void insertion_sort(RandomAccessIterator begin,
                    RandomAccessIterator end,
                    Compare comp) {
  if (begin >= end) {
    return;
  }
  for (auto iter = begin + 1; iter != end; ++iter) {
    for (auto jter = iter; comp(*jter, *(jter - 1)); --jter) {
      using std::swap;
      swap(*jter, *(jter - 1));
    }
  }
}

template <typename RandomAccessIterator>
void insertion_sort(RandomAccessIterator begin, RandomAccessIterator end) {
  using Type = typename std::remove_reference<decltype(*begin)>::type;
  insertion_sort(begin, end, std::less<Type>{});
}

template <typename RandomAccessIterator, class Compare>
void merge(RandomAccessIterator begin,
           RandomAccessIterator mid,
           RandomAccessIterator end,
           Compare comp) {
  using Type = typename std::remove_reference<decltype(*begin)>::type;
  int64_t len = std::distance(begin, end);
  auto fst = begin;
  auto snd = mid;
  Type* const merged_data = new Type[len];
  Type* ptr = merged_data;
  while (fst != mid && snd != end) {
    if (comp(*fst, *snd)) {
      *(ptr++) = *fst;
      ++fst;
    } else {
      *(ptr++) = *snd;
      ++snd;
    }
  }
  while (fst != mid) {
    *(ptr++) = *(fst++);
  }
  while (snd != end) {
    *(ptr++) = *(snd++);
  }
  for (int64_t i = 0; i < len; ++i) {
    begin[i] = merged_data[i];
  }
  delete[] merged_data;
}

template <typename RandomAccessIterator, class Compare>
void merge_sort(RandomAccessIterator begin,
                RandomAccessIterator end,
                Compare comp) {
  const int64_t len = std::distance(begin, end);
  if (len < 2) {
    return;
  }
  const auto mid = begin + len / 2;
  merge_sort(begin, mid, comp);
  merge_sort(mid, end, comp);
  merge(begin, mid, end, comp);
}

template <typename RandomAccessIterator>
void merge_sort(RandomAccessIterator begin, RandomAccessIterator end) {
  using Type = typename std::remove_reference<decltype(*begin)>::type;
  merge_sort(begin, end, std::less<Type>{});
}

template <typename ForwardIterator, class Compare>
void counting_sort(ForwardIterator begin,
                   ForwardIterator end,
                   Compare comp) {
  using Type = typename std::remove_reference<decltype(*begin)>::type;
  std::map<Type, size_t, Compare> counts;
  for (auto item = begin; item != end; ++item) {
    const auto ptr = counts.find(*item);
    if (ptr == counts.end()) {
      counts.emplace(*item, 1);
    } else {
      ++(ptr->second);
    }
  }
  for (const auto& pp : counts) {
    for (size_t i = 0; i < pp.second; ++i) {
      *(begin++) = pp.first;
    }
  }
}

template <typename ForwardIterator>
void counting_sort(ForwardIterator begin, ForwardIterator end) {
  using Type = typename std::remove_reference<decltype(*begin)>::type;
  counting_sort(begin, end, std::less<Type>{});
}

}  //  namespace pkr
