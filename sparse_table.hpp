#pragma once

#include <cinttypes>
#include <cmath>
#include <vector>

template <typename Type, class Compare = std::less<Type> >
class SparseTable {
public:
  template <typename Iterator> SparseTable(Iterator begin, Iterator end);

  // find best in [left, right)
  inline Type get(size_t left, size_t right) const {
    const auto deg = _lower_deg2[right - left - 1];
    return best(_table[deg][left],
                _table[deg][right - (static_cast<size_t>(1) << deg)]);
  }

private:
  std::vector< std::vector<Type> > _table;

  // you can replace this vector with function,
  // but you need precalc for true O(1) for 'get'
  std::vector<size_t> _lower_deg2;

  // calculate values for _lower_deg2;
  void precalc(size_t size);

  inline const Type& best(const Type& a, const Type& b) const {
    return Compare()(a, b) ? a : b;
  }
};

template <typename Type, class Compare>
template <typename Iterator>
SparseTable<Type, Compare>::SparseTable(Iterator begin, Iterator end) {
  std::vector<Type> bottom(begin, end);
  const size_t size = bottom.size();
  _table.resize(llround(log2(size)) + 1);
  _table[0] = bottom;

  size_t iter = 1;
  for (size_t step = 2; step <= size; step *= 2) {
    const size_t new_size = (size + 1) - step;
    _table[iter].resize(new_size);
    for (size_t i = 0; i < new_size; ++i) {
      _table[iter][i] = best(_table[iter - 1][i],
                             _table[iter - 1][i + step / 2]);
    }
    ++iter;
  }
  precalc(size);
}

template <typename Type, class Compare>
void SparseTable<Type, Compare>::precalc(size_t size) {
  _lower_deg2.resize(size);
  size_t step = 0;
  size_t pow2 = 1;
  size_t iter = 1;
  _lower_deg2[0] = 0;
  while (iter < size) {
    for (size_t i = 0; i < pow2 && iter < size; ++i, ++iter) {
      _lower_deg2[iter] = step;
    }
    ++step;
    pow2 *= 2;
  }
}
