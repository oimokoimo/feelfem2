/*
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *  Purpose: stack adaptor (push/pop) over feelfem2 list<T>.
 *
 *  Notes:
 *   - Requires list<T> provides protected: std::vector<T> data_;
 */

#pragma once
#ifndef FEELFEM2_CLASS_STACK_HPP
#define FEELFEM2_CLASS_STACK_HPP

#include <cassert>
#include "list.hpp"

template <class T>
class stack : public list<T>
{
public:
    // pop from top (front)
    T pop()
    {
        assert(!this->data_.empty());
        T ret = this->data_.front();
        this->data_.erase(this->data_.begin());
        return ret;
    }

    void push(const T& value)
    {
        // push to top (front)
        this->data_.insert(this->data_.begin(), value);
    }

    int isEmpty() const
    {
        return this->data_.empty() ? 1 : 0; // legacy int semantics
    }
};

#endif // FEELFEM2_CLASS_STACK_HPP

