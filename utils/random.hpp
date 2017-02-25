// Copyright 2016, Pavel Korozevtsev.

#pragma once

#include <limits>
#include <random>

namespace pkr {

template <typename Integer>
class Random {
public:
  Random()
    : Random(std::numeric_limits<Integer>::min(),
             std::numeric_limits<Integer>::max()) {}

  Random(Integer min, Integer max)
    : rng(std::random_device{}())
    , uni(min, max) {}

  auto get() {
    return uni(rng);
  }

  auto operator()() {
    return get();
  }

private:
  std::mt19937_64 rng;
  std::uniform_int_distribution<Integer> uni;
};

}  // namespace pkr
