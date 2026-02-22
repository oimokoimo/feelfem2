/*
 *  feelfem2 (modernized/ported)
 *  Safe fixed-size array template (legacy-compatible)
 *
 *  SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FEM_CLASS_VECTOR
#define FEM_CLASS_VECTOR

#include <cassert>
#include <cstddef>
#include <utility>
#include <algorithm> // std::fill_n

template <class T>
class vector {
public:
  using size_type = std::size_t;
  using value_type = T;

  // constructor: fixed-size allocation
  explicit vector(size_type numberOfElements)
    : data_(numberOfElements ? new T[numberOfElements] : nullptr),
      size_(numberOfElements)
  {}

  // destructor
  ~vector() { delete[] data_; }

  // ---- Rule of 5 ----
  // Copy is dangerous for owning raw pointer -> forbid (legacy code typically didn't copy intentionally)
  vector(const vector&)            = delete;
  vector& operator=(const vector&) = delete;

  // Move is OK
  vector(vector&& other) noexcept
    : data_(other.data_), size_(other.size_)
  {
    other.data_ = nullptr;
    other.size_ = 0;
  }

  vector& operator=(vector&& other) noexcept {
    if (this != &other) {
      delete[] data_;
      data_ = other.data_;
      size_ = other.size_;
      other.data_ = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  // element access
  T& operator[](size_type index) {
    assert(index < size_);
    return data_[index];
  }

  const T& operator[](size_type index) const {
    assert(index < size_);
    return data_[index];
  }

  // legacy API
  size_type length() const noexcept { return size_; }

  // optional helpers (便利なので)
  T* data() noexcept { return data_; }
  const T* data() const noexcept { return data_; }
  bool empty() const noexcept { return size_ == 0; }

  // fill all elements
  void fill(const T& v) {
    std::fill_n(data_, size_, v);
  }

private:
  T* data_{nullptr};
  size_type size_{0};
};

#endif // FEM_CLASS_VECTOR
