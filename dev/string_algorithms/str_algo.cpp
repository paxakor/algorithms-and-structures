#include "str_algo.hpp"

std::vector<size_t> prefix_function(const std::string& str) {
  const size_t n = str.size();
  std::vector<size_t> prefix(n);
  prefix[0] = 0;
  for (size_t i = 1; i < n; ++i) {
    size_t k = prefix[i - 1];
    while (k > 0 && str[i] != str[k]) {
      k = prefix[k - 1];
    }
    if (str[k] == str[i]) {
      prefix[i] = k + 1;
    } else {
      prefix[i] = 0;
    }
  }
  return prefix;
}

std::vector<size_t> z_function(const std::string& str) {
  const size_t n = str.size();
  std::vector<size_t> z(n);
  z[0] = 0;
  size_t l = 0, r = 0;
  for (size_t i = 1; i < n; ++i) {
    if (i > r) {
      size_t j = 0;
      while (j + i < n && str[i + j] == str[j]) {
        ++j;
      }
      z[i] = j;
      l = i;
      r = i + j - 1;
    } else if (z[i - l] < r - i + 1) {
      z[i] = z[i - l];
    } else {
      while (r + 1 < n && str[r + 1] == str[r - i + 1]) {
        ++r;
      }
      z[i] = r - i + 1;
      l = i;
    }
  }
  return z;
}

std::vector<size_t> find(const std::string& pattern, const std::string& str) {
  const char null = 0x00;
  std::vector<size_t> res;
  std::vector<size_t> prefix = prefix_function(pattern + null + str);
  const size_t p = pattern.size();
  const size_t s = str.size();
  for (size_t i = p; i < s; i += (p - prefix[p + i + 1])) {
    if (prefix[p + i + 1] == p) {
      res.push_back(i - p + 1);
      ++i;
    }
  }
  return res;
}
