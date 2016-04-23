#pragma once

#include <vector>

template <typename Type>
class Jump {
public:
  Type begin;
  Type end;
  Type third;
};

class Node {
public:
  Node() : ended(0) {}
  std::vector< Jump<size_t> > jumps;
  size_t ended;
};

class SuffixTree {
public:
  SuffixTree();
protected:
  std::vector<Node> nodes;
  std::string data;
};
