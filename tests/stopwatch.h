// Copyright 2016, Pavel Korozevtsev.

#pragma once

#include <ctime>
#include <iostream>
#include <string>

class Stopwatch {
public:
  explicit Stopwatch(const std::string& new_name)
  : _name(new_name)
  , _start(clock()) {
    std::cout << "Start " << _name << std::endl;
  }

  void end() {
    double secs = get();
    std::cout << _name << " ended in " << secs << " seconds" << std::endl;
    _ended = true;
  }

  double get() const {
    return (clock() - _start) / CLOCKS_PER_SEC;
  }

  ~Stopwatch() {
    if (!_ended) {
      end();
    }
  }

private:
  const std::string _name;
  double _start;
  bool _ended = false;
};
