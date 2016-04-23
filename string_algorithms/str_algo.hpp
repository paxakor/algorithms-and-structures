#pragma once

#include <cstddef>
#include <vector>
#include <string>

using std::vector;
using std::string;

vector<size_t> prefix_function(const string&);
vector<size_t> z_function(const string&);

// Knuth–Morris–Pratt string searching algorithm
vector<size_t> find(const string&, const string&);

// vector<size_t> counting_sort(const string&);
vector<size_t> suff_mas(const string&);
