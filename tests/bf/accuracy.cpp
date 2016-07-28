#include <fstream>
#include <iostream>
#include <set>
#include <typeinfo>
#include "bloom_filters/bloom_filter.hpp"
#include "bloom_filters/scalable_bloom_filter.hpp"
#include "utils/random.hpp"

using Type = size_t;

// count false-positive answers for given 'k', 'm' and 'n'
template <typename BF>
size_t test_fp(const size_t k, const size_t m, const size_t n) {
  static pkr::Random<Type> ri;
  BF bf(k, m);
  std::set<Type> st;
  size_t errors = 0;
  size_t hms = 0;
  for (size_t i = 0; i < n; ++i) {
    const auto x = ri.get();
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
    std::cerr << "ACHTUNG! errors: " << errors
      << " (in " << typeid(BF).name() << ")" << std::endl;
  }
  return hms;
}

int main(int argc, const char** argv) {
  bool need_save_to_file = false;
  std::ofstream fout;
  if (argc > 1) {
    need_save_to_file = true;
    fout.open(argv[1]);
  }
  size_t wins = 0;
  size_t fails = 0;
  for (size_t k = 2; k < 100; k += 2) {
    for (size_t m = 10'000; m < 80'000'000 * k; m *= 4) {
      for (size_t n = 1'000; n < 50'000; n *= 2) {
        const auto a = test_fp<pkr::BloomFilter<Type>>(k, m, n);
        const auto b = test_fp<pkr::ScalableBloomFilter<Type>>(k, m, n);
        if (b > a) {
          ++wins;
        } else if (b < a) {
          ++fails;
        }
        if (need_save_to_file && (a || b)) {
          fout << k << " " << m << " " << n << " "
            << a << " " << b << std::endl;
        }
      }
    }
    std::cout << "." << std::flush;
  }
  std::cout << std::endl;
  std::cout << "wins: " << wins << std::endl;
  std::cout << "fails: " << fails << std::endl;
  return 0;
}
