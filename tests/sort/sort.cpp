#include <algorithm>
#include <iostream>
#include "list.hpp"
#include "algo/sort.hpp"
#include "algo/sort_parallel.hpp"
#include "utils/random.hpp"
#include "utils/stopwatch.hpp"

using UInt = uint16_t;

#define TEST(sort_algo)                                     \
{                                                           \
  auto t = v;                                               \
  pkr::StopwatchReal sw(#sort_algo);                        \
  sort_algo(t.begin(), t.end());                            \
  sw.end();                                                 \
  if (print) {                                              \
    std::copy(t.begin(), t.end(),                           \
              std::ostream_iterator<UInt>(std::cout, " ")); \
    std::cout << std::endl;                                 \
  }                                                         \
  std::cout << (t == u ? "success" : "fail") << std::endl;  \
}

int main() {
  size_t n;
  std::cin >> n;
  const bool print = n < 20;
  pkr::Random<UInt> rnd(0, 1000);
  std::vector<UInt> v(n);
  for (auto& x : v) {
    x = rnd.get();
  }
  auto u = v;
  sort(u.begin(), u.end());
  TEST(std::sort);
  TEST(std::stable_sort);
  TEST(pkr::radix_sort);
  TEST(pkr::counting_sort);
  TEST(pkr::merge_sort);
  TEST(pkr::heap_sort);
  TEST(pkr::merge_sort_parallel);
  if (n < 20000) {
    TEST(pkr::insertion_sort);
  }
  return 0;
}
