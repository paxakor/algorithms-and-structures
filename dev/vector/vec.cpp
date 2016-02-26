#include <cstdio>
#include "vector.hpp"

int main() {
  int n = 1000 * 1000 * 100;
  Vector<int> v(n, 3);
  for (int i = 0; i < n; ++i) {
    v.push_back(i * i);
  }
  v[3] = 55555;
  // for (int i = 0; i < n; i+=4) {
  //   v[i] = i;
  // }
  return 0;
}
