#pragma once

#include <cstddef>
#include <vector>
#include <string>

std::vector<size_t> prefix_function(const std::string&);
std::vector<size_t> z_function(const std::string&);

// Knuth–Morris–Pratt string searching algorithm
std::vector<size_t> find(const std::string&, const std::string&);
