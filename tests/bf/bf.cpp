#include <iostream>
#include <set>
#include "bloom_filters/bloom_filter.hpp"
#include "utils/random.hpp"

int main() {
  pkr::Random<int> ri(-10000, 10000);
  int k = 5, m = 400;
  int n = 1000;
  pkr::BloomFilter<int> bf(k, m);
  std::set<int> st;
  int errors = 0;
  int hms = 0;
  for (int i = 0; i < n; ++i) {
    auto x = ri.get();
    if (i % 2) {
      bf.insert(x);
      st.insert(x);
    } else {
      bool x_in_st = (st.find(x) != st.end());
      bool x_in_bf = bf.find(x);
      if (!x_in_bf && x_in_st) {
        // std::cout << "value in set, but not in BF" << std::endl;
        ++errors;
      }
      if (x_in_bf && !x_in_st) {
        // std::cout << "hm..." << std::endl;
        ++hms;
      }
    }
  }
  std::cout << "errors: " << errors << std::endl;
  std::cout << "hms: " << hms << std::endl;

  // check whether I know how to use virtual dtor
  /*
  for (int i = 0; i < 100000; ++i) {
    pkr::BloomFilterBase<int>* ptr = new pkr::BloomFilter<int>(500, 400);
    delete ptr;
  }
  */
  return 0;
}
