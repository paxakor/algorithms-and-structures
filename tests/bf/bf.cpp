#include <iostream>
#include <set>
#include "bloom_filters/bloom_filter.hpp"
#include "utils/random.hpp"

using Type = int;

int main() {
  pkr::Random<Type> ri;
  size_t k = 50, m = 400'000;
  size_t n = 50'000;
  pkr::BloomFilter<Type> bf(k, m);
  std::set<Type> st;
  size_t errors = 0;
  size_t hms = 0;
  for (size_t i = 0; i < n; ++i) {
    auto x = ri.get();
    if (i % 2) {
      bf.insert(x);
      st.insert(x);
    } else {
      bool x_in_st = (st.find(x) != st.end());
      bool x_in_bf = bf.find(x);
      if (!x_in_bf && x_in_st) {
        ++errors;
      }
      if (x_in_bf && !x_in_st) {
        ++hms;
      }
    }
  }
  if (errors) {
    std::cout << "ACHTUNG! errors: " << errors << std::endl;
  }
  std::cout << "hms: " << hms
    << " (" << 2 * 100 * float(hms) / n << "%)" << std::endl;

  // check whether I know how to use virtual dtor
  /*
  for (size_t i = 0; i < 100000; ++i) {
    pkr::BloomFilterBase<Type>* ptr = new pkr::BloomFilter<Type>(500, 400);
    delete ptr;
  }
  */
  return 0;
}
