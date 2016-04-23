#pragma once

#include <thread>
#include "sort.hpp"
using std::thread;

template <typename Type>
void merge_sort_parallel(Type* begin, Type* end, int lvl) {
  auto length = end - begin;
  if (length < 16) {
    insertion_sort(begin, end);
  } else {
    auto mid = begin + (end - begin) / 2;
    auto length_1 = mid - begin;
    auto arr_1 = new Type[length_1];
    auto length_2 = end - mid;
    auto arr_2 = new Type[length_2];

    copy(begin, mid, arr_1);
    copy(mid, end, arr_2);

    if (lvl > 0) {
      thread th1(merge_sort_parallel<Type>, arr_1, arr_1 + length_1, lvl - 1);
      thread th2(merge_sort_parallel<Type>, arr_2, arr_2 + length_2, lvl - 1);
      th1.join();
      th2.join();
    } else {
      merge_sort(arr_1, arr_1 + length_1);
      merge_sort(arr_2, arr_2 + length_2);
    }

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