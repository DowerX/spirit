#pragma once

#include <cstdint>
#include <cstring>
#include <initializer_list>
#include <stdexcept>
#include <string>

namespace Engine::Types {

const uint64_t primes[] = {73856093, 19349663, 83492791, 83492803, 83492807, 83492837, 83492863, 83492879, 83492881, 83492887, 83492917, 83493023};

template <size_t s, typename T>
class Vector {
 private:
  T values[s];
  uint64_t hash;

  uint64_t calc_hash() {
    hash = values[0] * primes[0];
    for (size_t i = 1; i < s; i++) {
      hash ^= *((uint64_t*)&values[i]) * primes[i];
    }
    return hash;
  }

 public:
  Vector(T values[s]) {
    std::memcpy(this->values, values, s * sizeof(T));
    calc_hash();
  }

  Vector(std::initializer_list<T> values) {
    size_t i = 0;
    for (const T& value : values) {
      this->values[i++] = value;
    }
    calc_hash();
  }

  T get(size_t i) const {
#ifdef DEBUG
    if (i >= s)
      throw std::out_of_range("vector index out of range: " + std::to_string(i));
#endif
    return values[i];
  }

  const T* get() const { return values; }

  uint64_t get_hash() const { return hash; }
};
} // namespace Engine::Types