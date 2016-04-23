#pragma once

#include <cinttypes>
#include <queue>
#include <unordered_map>
#include <vector>
#include "algo_base.hpp"

using std::pair;
using std::string;
using std::vector;

template <typename UInt>
vector<size_t> radix_sort_permutation(const vector<UInt>& vec) {
  const auto n = vec.size();
  vector<UInt> res_vec(vec);
  vector<size_t> permutation(n);
  for (size_t i = 0; i < n; ++i) {
    permutation[i] = i;
  }
  std::queue< pair< pair<size_t, size_t>, UInt > > borders;
  const UInt max_bit = static_cast<UInt>(1) << (sizeof(UInt) * 8 - 1);
  // change max_bit to 1 and `>>` to `<<` in order to change bit sort order
  borders.push({{0, n - 1}, max_bit});
  while (!borders.empty()) {
    const auto& pp = borders.front();
    auto bit = pp.second;
    const auto& lr = pp.first;
    borders.pop();
    const auto& left = lr.first, right = lr.second;
    auto l = left, r = right;
    while (l < r) {
      while (l < r && !(res_vec[l] & bit)) {
        ++l;
      }
      while (l < r && (res_vec[r] & bit)) {
        --r;
      }
      if (l < r) {
        std::swap(res_vec[l], res_vec[r]);
        std::swap(permutation[l], permutation[r]);
        ++l;
      }
    }
    while (l > 0 && (res_vec[l] & bit)) {
      --l;
    }
    while (r < n - 1 && !(res_vec[r] & bit)) {
      ++r;
    }
    bit = bit >> 1;
    if (left < l && (bit != 0)) {
      borders.push({{left, l}, bit});
    }
    if (r < right && (bit != 0)) {
      borders.push({{r, right}, bit});
    }
  }
  return permutation;
}

template <typename Iter>
void insertion_sort(const Iter begin, const Iter end) {
  if (begin >= end) {
    return;
  }
  for (auto iter = begin + 1; iter != end; ++iter) {
    for (auto jter = iter; *(jter - 1) > *jter; --jter) {
      pkr::swap(*jter, *(jter - 1));
    }
  }
}

// stupid function. only for legacy merge_sort. TODO.
template <typename Type>
void copy(Type* begin, Type* end, Type* arr) {
  for (auto ptr = begin; ptr != end; ++ptr) {
    *arr = *ptr;
    ++arr;
  }
}

template <typename Type>
void merge_sort(Type* begin, Type* end) {
  auto length = end - begin;
  if (length < 8) {
    insertion_sort(begin, end);
  } else {
    auto mid = begin + (end - begin) / 2;
    auto length_1 = mid - begin;
    auto arr_1 = new Type[length_1];
    auto length_2 = end - mid;
    auto arr_2 = new Type[length_2];

    copy(begin, mid, arr_1);
    copy(mid, end, arr_2);

    merge_sort(arr_1, arr_1 + length_1);
    merge_sort(arr_2, arr_2 + length_2);

    auto first = arr_1;
    auto second = arr_2;
    auto ptr = begin;
    while (!(first == arr_1 + length_1 && second == arr_2 + length_2)) {
      while (first != arr_1 + length_1 && \
        (second == arr_2 + length_2 || *first <= *second)) {
        *ptr = *first;
        ++first;
        ++ptr;
      }
      while (second != arr_2 + length_2 && \
        (first == arr_1 + length_1 || *second <= *first)) {
        *ptr = *second;
        ++second;
        ++ptr;
      }
    }

    delete[] arr_1;
    delete[] arr_2;
  }
}

template <typename Iter, typename Type>
void counting_sort(const Iter& begin, const Iter& end) {
  std::unordered_map<Type, size_t> counts;
  for (Iter item = begin; item != end; ++item) {
    auto ptr = counts.find(*item);
    if (ptr == counts.end()) {
      counts.insert({*item, 1});
    } else {
      ++(ptr->second);
    }
  }
  std::vector<Type> unique_items;
  for (const auto& pair : counts) {
    unique_items.push_back(pair.first);
  }
  merge_sort(unique_items.begin(), unique_items.end());
  for (const auto& item : unique_items) {
    
  }
}
