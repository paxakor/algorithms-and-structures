#include <iostream>
#include "bloom_filters/hasher.hpp"
#include "utils/random.hpp"

int main() {
  pkr::Hasher<int> hi(1);
  pkr::Random<int> ri(-10, 10);
  int n = pkr::Random<int>{1, 20}.get();
  for (int i = 0; i < n; ++i) {
    auto x = ri.get();
    auto x_h = hi(x, 0);
    std::cout << x << " -> " << x_h << std::endl;
  }
  return 0;
}
