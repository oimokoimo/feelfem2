/*
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *  Purpose: pointer list with value-based comparison (*ptr).
 *
 *  Ported: 2026-01-15
 *
 *  Notes:
 *   - Clean-room implementation for feelfem2.
 *   - includes()/getPosition() compare pointed-to objects: (*a == *b).
 *   - deleteAllPointedValues() deletes pointees, then clears the list.
 *   - Assumes list<T> provides protected: std::vector<T> data_;
 */

#pragma once

#ifndef FEELFEM2_CLASS_PTRLIST_HPP
#define FEELFEM2_CLASS_PTRLIST_HPP

#include <cstddef>   // std::nullptr_t
#include "list.hpp"

template <class T>
class ptrList : public list<T>
{
public:
    using base_type = list<T>;

    // Compare pointed-to values (requires: T is pointer-like; *T supports operator==)
    int includes(T value) const override
    {
        // legacy semantics: return 1 if included, else 0
        if (!value) return 0;

        for (const auto& p : this->data_) {
            if (p && (*value == *p)) return 1;
        }
        return 0;
    }

    int getPosition(T value) const override
    {
        // legacy semantics: position starts at 1; return 0 if not found
        if (!value) return 0;

        int no = 1;
        for (const auto& p : this->data_) {
            if (p && (*value == *p)) return no;
            ++no;
        }
        return 0;
    }

    // Delete the pointees (T must be a raw pointer type or deletable pointer-like)
    void deleteAllPointedValues()
    {
        for (auto& p : this->data_) {
            delete p;
            p = nullptr;
        }
        this->data_.clear();
    }

    // Safety: if someone calls base deleteAllValues() on a ptrList by mistake,
    // do NOT leak pointees silently. We choose to delete pointees too.
    void deleteAllValues() override
    {
        deleteAllPointedValues();
    }
};

#endif // FEELFEM2_CLASS_PTRLIST_HPP

