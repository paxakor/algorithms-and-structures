#include <stdio.h>
#include <string>
#include "trie.hpp"

int main () {
  Trie tr;
  tr.add("abacaba");
  tr.add("bacaba");
  tr.add("acaba");
  tr.add("caba");
  tr.add("aba");
  tr.add("ba");
  tr.add("a");
  auto a = tr.find("ab");
  auto b = tr.find("aba");
  printf("%d %d\n", a, b);
  return 0;
}
