// Copyright 2016, Pavel Korozevtsev.

#pragma once

#include <ctime>
#include <chrono>
#include <iostream>
#include <string>

namespace pkr {

template <bool need_real_time>
class StopwatchImpl {
public:
  explicit StopwatchImpl(const std::string& new_name)
  : _name(new_name)
  , _start_cpu(clock())
  , _start_real(std::chrono::system_clock::now()) {
    std::cout << "Start " << _name << std::endl;
  }

  void end() {
    std::cout << _name << " ended in " << get() << " seconds" << std::endl;
    _ended = true;
  }

  double get() const {
    if (need_real_time) {
      return get_real();
    } else {
      return get_cpu();
    }
  }

  ~StopwatchImpl() {
    if (!_ended) {
      end();
    }
  }

private:
  double get_cpu() const {
    return (clock() - _start_cpu) / CLOCKS_PER_SEC;
  }

  double get_real() const {
    std::chrono::duration<double> diff =
      std::chrono::system_clock::now() - _start_real;
    return diff.count();
  }

  const std::string _name;
  double _start_cpu;
  std::chrono::time_point<std::chrono::system_clock> _start_real;
  bool _ended = false;
};

using Stopwatch = StopwatchImpl<false>;
using StopwatchReal = StopwatchImpl<true>;

}  // namespace pkr
