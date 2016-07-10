// #include <bits/stdc++.h>
#include <iostream>
#include "tests/stopwatch.h"
#ifdef FLAG
#include <queue>
#else
#include "heap.hpp"
#endif
using namespace std;

int main() {
#ifdef FLAG
  priority_queue<int, std::vector<int>, std::greater<int>> h;
#else
  pkr::Heap<int> h(3);
#endif
  string cmd;
  int i = 0;
  // Stopwatch sw("Prog");
  while (getline(cin, cmd) && !cmd.empty()) {
    if (cmd[0] == 't') {
      cout << h.top() << endl;
    } else if (cmd[0] == 'i') {
      int k = stoi(cmd.substr(2));
      h.push(k);
    } else if (cmd[0] == 'e') {
      h.pop();
    }
    // cout << "pass: " << i++ << endl;
  }
}
