/*
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *
 *  Purpose: stack adapter (push/pop) built on feelfem2 list<T>.
 *
 *  Notes:
 *   - Keeps feelfem1-style API (push/pop) with minimal modernization.
 *   - Does NOT touch list<T>::ptrToFirstLink directly; uses list<T> APIs.
 */

#pragma once

#include <cassert>
#include <utility>   // std::move
#include "list.hpp"

template <class T>
class stack : public list<T>
{
public:
    using base_type = list<T>;

    stack() noexcept = default;
    stack(const stack&) = default;
    stack& operator=(const stack&) = default;
    ~stack() override = default;

    // legacy API: pop top element (asserts non-empty like feelfem1)
    T pop()
    {
        assert(!this->isEmpty());

        // Note: list<T>::firstElement() returns by value (legacy style),
        // so std::move here is mostly harmless but keeps intent clear.
        T ret = std::move(this->firstElement());
        this->removeFirst();
        return ret;
    }

    // convenience
    int isEmptyStack() const noexcept { return this->isEmpty(); }

    // push (legacy signature kept, plus overloads)
    void push(const T& value)
    {
        this->add(value);   // add() inserts at head => stack push
    }

    void push(T&& value)
    {
        // list<T>::add takes by value, so we move into that parameter
        this->add(std::move(value));
    }

    // optional: peek top (asserts non-empty)
    T top() const
    {
        assert(!this->isEmpty());
        return this->firstElement();
    }
};

