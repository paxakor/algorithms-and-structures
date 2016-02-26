#ifndef vector_hpp
#define vector_hpp

#include <cinttypes>
#define BASE_CAPACITY 2

template <typename Type>
class Vector {
public:
  Vector();
  Vector(size_t);
  Vector(size_t, const Type&);
  ~Vector();
  void push_back(const Type&);
  Type pop_back();
  bool empty() const;
  void clear();
  void resize(size_t);
  Type& operator[](size_t) const;
  Type at(size_t) const;
  Type front() const;
  Type back() const;
  void erase(size_t);
  void erase(size_t, size_t);
  size_t find(const Type&) const;
  size_t size() const;
  size_t capacity() const;
private:
  Type* data_old;
  Type* data_new;
  size_t size_var;
  size_t capacity_var;
};

template <typename Type>
Vector<Type>::Vector(size_t n) {
  this->capacity_var = n;
  this->data_old = new Type[this->capacity_var];
  this->data_new = new Type[this->capacity_var * 2];
  this->size_var = 0;
}

template <typename Type>
Vector<Type>::Vector() {
  *this = Vector(BASE_CAPACITY);
}

template <typename Type>
Vector<Type>::Vector(size_t n, const Type& val) {
  *this = Vector(n);
  for (size_t i = 0; i < n; ++i) {
    this->data_old[i] = val;
  }
}

template <typename Type>
Vector<Type>::~Vector() {
  delete[] this->data_old;
}

template <typename Type>
void Vector<Type>::push_back(const Type& val) {
  if (this->size_var + 1 < this->capacity_var) {
    this->data_old[this->size_var] = val;
    ++this->size_var;
  } else {
    this->resize(this->capacity_var * 2);
    this->push_back(val);
  }
}

template <typename Type>
bool Vector<Type>::empty() const {
  return this->size_var == 0;
}

template <typename Type>
void Vector<Type>::clear() {
  this->size_var = 0;
  delete[] this->data_old;
  this->Vector();
}

template <typename Type>
void Vector<Type>::resize(size_t new_capacity) {
  auto new_data = new Type[new_capacity];
  for (size_t i = 0; i < this->size_var && i < new_capacity; ++i) {
    new_data[i] = this->data_old[i];
  }
  delete[] this->data_old;
  this->data_old = new_data;
  this->capacity_var = new_capacity;
}

template <typename Type>
Type& Vector<Type>::operator[](size_t index) const {
  return this->data_old[index];
}

template <typename Type>
Type Vector<Type>::at(size_t index) const {
  return this->data_old[index];
}

template <typename Type>
Type Vector<Type>::front() const {
  return this->data_old[0];
}

template <typename Type>
Type Vector<Type>::back() const {
  // return this->data_old[this->size_var == 0 ? 0 : this->size_var - 1];
  return this->data_old[max(this->size_var - 1, 0)];
}

template <typename Type>
void Vector<Type>::erase(size_t index) {
  this->erase(index, index + 1);
}

template <typename Type>
void Vector<Type>::erase(size_t index_l, size_t index_r) {
  if (index_l == index_r) {
    return;
  } else if (index_r < index_l) {
    auto tmp = index_l;
    index_l = index_r;
    index_r = tmp;
  }
  index_r = index_r < this->capacity_var ? index_r : this->capacity_var - 1;
  size_t diff = index_r - index_l;
  for (size_t i = 0; index_r + i < this->capacity_var; ++i) {
    this->data_old[index_l + i] = this->data_old[index_r + i];
  }
}

template <typename Type>
size_t Vector<Type>::size() const {
  return this->size_var;
}

template <typename Type>
size_t Vector<Type>::capacity() const {
  return this->capacity_var;
}

template <typename Type>
size_t Vector<Type>::find(const Type& val) const {
  for (size_t i = 0; i < this->size_var; ++i) {
    if (this->data_old[i] == val) {
      return i;
    }
  }
  return this->size_var;
}

#endif /* vector_hpp */
