// Copyright 2016, Pavel Korozevtsev.

#pragma once

#include <limits>
#include <random>

namespace pkr {

template <typename Integer>
class Random {
public:
  Random(Integer min = std::numeric_limits<Integer>::min(),
         Integer max = std::numeric_limits<Integer>::max())
    : rng(std::random_device{}())
    , uni(min, max) {};

  inline Integer get() {
    return uni(rng);
  }

private:
  std::mt19937_64 rng;
  std::uniform_int_distribution<Integer> uni;
};

} // namespace pkr
