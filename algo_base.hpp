#pragma once

template <typename Type>
Type min(const Type& a, const Type& b) {
  if (a < b)
    return a;
  return b;
}

template <typename Type>
Type max(const Type& a, const Type& b) {
  if (a > b)
    return a;
  return b;
}
