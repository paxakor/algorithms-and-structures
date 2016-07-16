#include <bits/stdc++.h>
#include "sparse_table_old.hpp"

int main(int argc, char const *argv[]) {
  int n;
  std::cin >> n;
  std::vector<int> numbers(n);
  for (auto& x : numbers) {
    std::cin >> x;
  }
  SparseTable<int> st(numbers.begin(), numbers.end());
  int m;
  std::cin >> m;
  for (int i = 0; i < m; ++i) {
    int l, r;
    std::cin >> l >> r;
    std::cout << l << " " << r << std::endl;
    std::cout << st.get(l, r + 1) << std::endl;
  }
  return 0;
}
