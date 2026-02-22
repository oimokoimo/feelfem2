/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : matrix.hpp
 *  Date     : 2002/02/06
 *  Modified : 
 *  
 *  Purpose  :
 *
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *  
 */

#ifndef FEM_CLASS_MATRIX
#define FEM_CLASS_MATRIX

#include <cassert>
#include <cstddef>
#include <utility>

template <class T>
class matrix {
public:
  using size_type = std::size_t;

  matrix(size_type rows_ini, size_type columns_ini)
    : data_((rows_ini && columns_ini) ? new T[rows_ini * columns_ini] : nullptr),
      rows_(rows_ini), columns_(columns_ini)
  {
    assert(rows_ > 0);
    assert(columns_ > 0);
  }

  ~matrix() { delete[] data_; }

  matrix(const matrix&)            = delete;
  matrix& operator=(const matrix&) = delete;

  matrix(matrix&& other) noexcept
    : data_(other.data_), rows_(other.rows_), columns_(other.columns_)
  {
    other.data_ = nullptr;
    other.rows_ = other.columns_ = 0;
  }

  matrix& operator=(matrix&& other) noexcept {
    if (this != &other) {
      delete[] data_;
      data_ = other.data_;
      rows_ = other.rows_;
      columns_ = other.columns_;
      other.data_ = nullptr;
      other.rows_ = other.columns_ = 0;
    }
    return *this;
  }

  T& val(size_type i, size_type j) {
    assert(i < rows_);
    assert(j < columns_);
    return data_[i * columns_ + j];
  }

  const T& val(size_type i, size_type j) const {
    assert(i < rows_);
    assert(j < columns_);
    return data_[i * columns_ + j];
  }

  size_type rows() const noexcept { return rows_; }
  size_type columns() const noexcept { return columns_; }

  T* data() noexcept { return data_; }
  const T* data() const noexcept { return data_; }

private:
  T* data_{nullptr};
  size_type rows_{0}, columns_{0};
};

#endif
