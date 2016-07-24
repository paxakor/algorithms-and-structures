// Copyright 2016, Pavel Korozevtsev.

#pragma once

#include <functional>
#include <thread>
#include "sort.hpp"

namespace pkr {

template <typename RandomAccessIterator, class Compare>
void merge_sort_parallel(RandomAccessIterator begin,
                         RandomAccessIterator end,
                         Compare comp,
                         int lvl = 2) {
  const int64_t len = std::distance(begin, end);
  if (len < 2) {
    return;
  }
  const auto mid = begin + len / 2;
  if (lvl > 0) {
    std::thread th1(merge_sort_parallel<RandomAccessIterator, Compare>,
                    begin, mid, comp, lvl - 1);
    std::thread th2(merge_sort_parallel<RandomAccessIterator, Compare>,
                    mid, end, comp, lvl - 1);
    th1.join();
    th2.join();
  } else {
    merge_sort(begin, mid, comp);
    merge_sort(mid, end, comp);
  }
  merge(begin, mid, end, comp);
}

template <typename RandomAccessIterator>
void merge_sort_parallel(RandomAccessIterator begin,
                         RandomAccessIterator end,
                         int lvl = 2) {
  using Type = typename std::remove_reference<decltype(*begin)>::type;
  merge_sort_parallel(begin, end, std::less<Type>{}, lvl);
}

}  // namespace pkr
