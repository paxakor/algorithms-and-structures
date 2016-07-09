#include <bits/stdc++.h>
#include "list/list.hpp"
using namespace std;

int main() {
  pkr::List<int> l;
  size_t n;
  cin >> n;
  for (size_t i = 0; i < n; ++i) {
    char cmd;
    cin >> cmd;
    if (cmd == 's') {
      cout << l.size() << endl;
    } else if (cmd == 'c') {
      l.clear();
    } else if (cmd == 'f') {
      int k;
      cin >> k;
      l.push_front(k);
    } else if (cmd == 'p') {
      const auto vec = l.to_vector();
      copy(vec.begin(), vec.end(),
        ostream_iterator<decltype(vec)::value_type>(cout, " "));
      cout << endl;
    } else if (cmd == 'b') {
      int k;
      cin >> k;
      l.push_back(k);
    } else if (cmd == 'r') {
      int k;
      cin >> k;
      l.remove(k);
    }
  }
}
