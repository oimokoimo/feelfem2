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

#include "list.hpp"

template <class T>
class ptrList : public list<T>
{
public:
    using base_type = list<T>;

    int includes(T value) const override
    {
        if (!value) return 0;

        for (link<T>* p = this->ptrToFirstLink; p != nullptr; p = p->ptrToNextLink) {
            if (p->value && (*value == *(p->value))) return 1;
        }
        return 0;
    }

    int getPosition(T value) const override
    {
        if (!value) return 0;

        int no = 1;
        for (link<T>* p = this->ptrToFirstLink; p != nullptr; p = p->ptrToNextLink, ++no) {
            if (p->value && (*value == *(p->value))) return no;
        }
        return 0;
    }

    void deleteAllPointedValues()
    {
        for (link<T>* p = this->ptrToFirstLink; p != nullptr; p = p->ptrToNextLink) {
            delete p->value;
            p->value = nullptr;
        }
        this->deleteAllValues(); // delete links
    }

    void deleteAllValues() override
    {
        deleteAllPointedValues();
    }
};

