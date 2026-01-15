/*
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *  Purpose: pointer list with value-based comparison (*ptr).
 *
 *  Ported: 2026/01/15
 *
 *  Notes:
 *   - Clean-room implementation for feelfem2.
 *   - includes()/getPosition() compare pointed-to objects: (*a == *b).
 *   - deleteAllPointedValues() deletes pointees, then clears the list.
 */

#pragma once
#ifndef FEM_CLASS_PTRLIST
#define FEM_CLASS_PTRLIST

#include "list.hpp"

template <class T>
class ptrList : public list<T>
{
public:
    // Compare pointed-to values (requires: T is pointer-like, *T supports operator==)
    int includes(T value) const override
    {
        for (const auto& p : this->data_) {
            if (p && value && (*value == *p)) return 1;
        }
        return 0;
    }

    int getPosition(T value) const override
    {
        int no = 1;
        for (const auto& p : this->data_) {
            if (p && value && (*value == *p)) return no;
            ++no;
        }
        return 0;
    }

    void deleteAllPointedValues()
    {
        for (auto& p : this->data_) {
            delete p;
            p = nullptr;
        }
        this->data_.clear();
    }
};

#endif

