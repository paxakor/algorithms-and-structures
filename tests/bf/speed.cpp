#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <typeinfo>
#include "bloom_filters/bloom_filter.hpp"
#include "bloom_filters/scalable_bloom_filter.hpp"
#include "utils/random.hpp"
#include "utils/stopwatch.hpp"

using Type = size_t;

struct TestResult {
  size_t k;
  size_t m;
  double time;
  double fp_rate;
};

std::vector<Type> gen_test(const size_t n) {
  static pkr::Random<Type> ri;
  std::vector<Type> res(n);
  for (auto& x : res) {
    x = ri.get();
  }
  return res;
}

std::vector<bool> run_std_set(const std::vector<Type>& test_data) {
  const auto n = test_data.size();
  std::set<Type> st;
  std::vector<bool> res(n / 2);
  pkr::StopwatchReal sw("std::set");
  for (size_t i = 0; i < n; ++i) {
    const auto x = test_data[i];
    if (i % 2) {
      res[i / 2] = (st.find(x) != st.end());
    } else {
      st.insert(x);
    }
  }
  return res;
}

template <typename BF>
TestResult run_bf(const size_t k,
                  const size_t m,
                  const std::vector<Type>& test_data,
                  const std::vector<bool>& truth) {
  BF bf(k, m, 0.1);
  size_t errors = 0;
  size_t hms = 0;
  const auto n = test_data.size();
  pkr::StopwatchImpl<false, true> sw("");
  for (size_t i = 0; i < n; ++i) {
    const auto x = test_data[i];
    if (i % 2) {
      bool x_in_st = truth[i / 2];
      bool x_in_bf = bf.find(x);
      if (!x_in_bf && x_in_st) {
        ++errors;
      }
      if (x_in_bf && !x_in_st) {
        ++hms;
      }
    } else {
      bf.insert(x);
    }
  }
  if (errors) {
    std::cerr << "ACHTUNG! errors: " << errors
      << " (in " << typeid(BF).name() << ")" << std::endl;
  }
  const double fp_rate = static_cast<double>(hms) / n;
  return {k, m, sw.get(), fp_rate};
}

int main(int argc, const char** argv) {
  constexpr size_t n = 1'000'000;
  const auto test_data = gen_test(n);
  const auto truth = run_std_set(test_data);
  std::vector<TestResult> results;
  for (size_t k = 2; k < 20; k += 2) {
    for (size_t m = 10'000; m < 80'000'000 * k; m *= 4) {
      const auto res =
        run_bf<pkr::ScalableBloomFilter<Type>>(k, m, test_data, truth);
      results.push_back(res);
    }
    std::cout << "." << std::flush;
  }
  std::cout << std::endl;

  std::sort(results.begin(), results.end(),
    [](const TestResult& a, const TestResult& b) {
      return (a.fp_rate < b.fp_rate) ||
             ((a.fp_rate == b.fp_rate) && (a.time < b.time));
    });

  std::ostream* out;
  if (argc > 1) {
    out = new std::ofstream(argv[1]);
  } else {
    out = &std::cout;
  }
  for (const auto& res : results) {
    *out << res.fp_rate << " " <<
            res.time    << " " <<
            res.k       << " " <<
            res.m       << std::endl;
  }
  return 0;
}
