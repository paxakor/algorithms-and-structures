#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include "str_algo.hpp"
#include "../sort.hpp"

using std::pair;
using std::string;
using std::vector;

vector<size_t> counting_sort(const string& str) {
  const size_t CHAR_COUNT = 0x100;
  const size_t n = str.size();
  vector< vector<size_t> > counts(CHAR_COUNT);
  for (size_t i = 0; i < n; ++i) {
    counts[static_cast<size_t>(str[i])].push_back(i);
  }
  vector<size_t> res;
  for (size_t i = 0; i < CHAR_COUNT; ++i) {
    res.insert(res.end(), counts[i].begin(), counts[i].end());
  }
  return res;
}

vector<size_t> suff_mas(const string& str) {
  const auto n = str.size();
  auto permutation = counting_sort(str);
  vector< pair<size_t, size_t> > classes(n);
  for (size_t i = 0; i < n; ++i) {
    classes[i] = {str[i], 0};
  }
  for (size_t LEN = 1; LEN < n; LEN *= 2) {
    vector<size_t> colours(n);
    size_t clr = 0;
    auto ch = classes[permutation[0]];
    for (size_t i = 0; i < n; ++i) {
      auto j = permutation[i];
      if (classes[j] != ch) {
        ++clr;
        ch = classes[j];
      }
      colours[j] = clr;
    }

    vector< pair< pair<size_t, size_t>, size_t > > new_classes;
    for (size_t i = 0; i < n; ++i) {
      new_classes.push_back({{colours[i], colours[(i + LEN) % n]}, i});
    }
    std::sort(new_classes.begin(), new_classes.end());
    for (size_t i = 0; i < n; ++i) {
      const auto& pp = new_classes[i];
      permutation[i] = pp.second;
      classes[permutation[i]] = pp.first;
    }
  }
  return permutation;
}

vector<size_t> suff_mas_old(const string& str) {
  const auto n = str.size();
  auto permutation = counting_sort(str);
  vector< pair<size_t, size_t> > classes(n);
  for (size_t i = 0; i < n; ++i) {
    classes[i] = {str[i], 0};
  }
  for (size_t LEN = 1; LEN < n; LEN *= 2) {
    vector<size_t> colours(n);
    size_t clr = 0;
    auto ch = classes[permutation[0]];
    for (size_t i = 0; i < n; ++i) {
      auto j = permutation[i];
      if (classes[j] != ch) {
        ++clr;
        ch = classes[j];
      }
      colours[j] = clr;
    }

    vector< pair< pair<size_t, size_t>, size_t > > new_classes;
    for (size_t i = 0; i < n; ++i) {
      new_classes.push_back({{colours[i], colours[(i + LEN) % n]}, i});
    }
    std::sort(new_classes.begin(), new_classes.end());
    for (size_t i = 0; i < n; ++i) {
      const auto& pp = new_classes[i];
      permutation[i] = pp.second;
      classes[permutation[i]] = pp.first;
    }
  }
  return permutation;
}
