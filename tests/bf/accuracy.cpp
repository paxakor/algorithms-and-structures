#include <fstream>
#include <iostream>
#include <set>
#include <typeinfo>
#include "bloom_filters/bloom_filter.hpp"
#include "bloom_filters/scalable_bloom_filter.hpp"
#include "bloom_filters/stable_bloom_filter.hpp"
#include "utils/random.hpp"

using Type = size_t;

// count false-positive answers for given 'k', 'm' and 'n'
size_t test_fp(pkr::BloomFilterBase<Type>* const bf,
               const size_t n) {
  static pkr::Random<Type> ri;
  std::set<Type> st;
  size_t errors = 0;
  size_t hms = 0;
  for (size_t i = 0; i < n; ++i) {
    const auto x = ri.get();
    if (i % 2) {
      bf->insert(x);
      st.insert(x);
    } else {
      bool x_in_st = (st.find(x) != st.end());
      bool x_in_bf = bf->find(x);
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
      << " (in " << typeid(bf).name() << ")" << std::endl;
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
  constexpr size_t n = 100'000;
  for (size_t k = 2; k < 20; k += 2) {
    for (size_t m = 10'000; m < 80'000 * k; m *= 4) {
      for (size_t p = 1'000; p < 50'000; p *= 2) {
        pkr::BloomFilterBase<Type>* bf =
          new pkr::StableBloomFilter<Type>(k, m, p);
        const auto a = test_fp(bf, n);
        delete bf;
        if (need_save_to_file) {
          double r = double(a) * 100 / n;
          fout << k << " \t" << m << " \t"
            << p << " \t" << r << "%" << std::endl;
        }
      }
    }
    std::cout << "." << std::flush;
  }
  std::cout << std::endl;
  return 0;
}
