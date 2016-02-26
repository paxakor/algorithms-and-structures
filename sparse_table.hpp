#ifndef sparse_table_hpp
#define sparse_table_hpp

#include <cinttypes>
#include <cmath>
#include <vector>

template <typename Type>
class SparseTable {
public:
  SparseTable(const Type* const, const int64_t);
  Type get(int64_t, int64_t) const;
private:
  // usage: table[len][i], len = 2**k.
  std::vector< std::vector<Type> > table;
  int64_t* lower_deg2;
};

template <typename Type>
SparseTable<Type>::SparseTable(const Type* const array, const int64_t size) {

  this->table.resize(llround(log2(size)) + 1);
  
  this->table[0].resize(size);
  for (int64_t i = 0; i < size; ++i) {
    this->table[0][i] = array[i];
  }

  int64_t step = 2;
  int64_t iter = 1;
  while (step <= size) {
    auto new_size = size - step + 1;
    this->table[iter].resize(new_size);
    for (int64_t i = 0; i < new_size; ++i) {
      this->table[iter][i] = std::min(this->table[iter - 1][i],
        this->table[iter - 1][i + step / 2]);
    }
    step *= 2;
    ++iter;
  }

  this->lower_deg2 = new int64_t[size];
  step = 0;
  int64_t pow2 = 1;
  iter = 1;
  this->lower_deg2[0] = 0;
  while (iter < size) {
    for (int64_t i = 0; i < pow2 && iter < size; ++i, ++iter) {
      this->lower_deg2[iter] = step;
    }
    ++step;
    pow2 *= 2;
  }
}

template <typename Type>
Type SparseTable<Type>::get(int64_t left, int64_t right) const {
  auto deg = this->lower_deg2[right - left];
  auto first = this->table[deg][left];
  auto second = this->table[deg][right - (1 << deg) + 1];
  return std::min(first, second);
}

#endif /* sparse_table_hpp */
