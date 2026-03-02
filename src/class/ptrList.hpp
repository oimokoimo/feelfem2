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
 *   - Assumes list<T> provides protected:
 *         link<T>* ptrToFirstLink;
 *         void deleteAllValues();   // deletes link nodes only
 */

#pragma once

#include "list.hpp"
#include <type_traits>

template <class T>
class ptrList : public list<T>
{
    static_assert(std::is_pointer_v<T>,
                  "ptrList<T> requires T to be a pointer type.");

public:
    using base_type = list<T>;

    // ------------------------------------------------------------
    // includes : value-based comparison (*ptr)
    // ------------------------------------------------------------
    int includes(T value) const override
    {
        if (!value) return 0;

        for (link<T>* p = this->ptrToFirstLink;
             p != nullptr;
             p = p->ptrToNextLink)
        {
            if (p->value && (*value == *(p->value)))
                return 1;
        }
        return 0;
    }

    // ------------------------------------------------------------
    // getPosition : value-based comparison (*ptr)
    // ------------------------------------------------------------
    int getPosition(T value) const override
    {
        if (!value) return 0;

        int no = 1;
        for (link<T>* p = this->ptrToFirstLink;
             p != nullptr;
             p = p->ptrToNextLink, ++no)
        {
            if (p->value && (*value == *(p->value)))
                return no;
        }
        return 0;
    }

    // ------------------------------------------------------------
    // deleteAllPointedValues
    //   - delete pointees
    //   - then delete link nodes (base class)
    // ------------------------------------------------------------
    void deleteAllPointedValues()
    {
        for (link<T>* p = this->ptrToFirstLink;
             p != nullptr;
             p = p->ptrToNextLink)
        {
            delete p->value;
            p->value = nullptr;
        }

        // IMPORTANT: call base explicitly to avoid recursion
        base_type::deleteAllValues();
    }

    // ------------------------------------------------------------
    // deleteAllValues (override)
    //   - feelfem1互換:
    //       ptrList では deleteAllValues() ＝ pointeeも削除
    // ------------------------------------------------------------
    void deleteAllValues() override
    {
        deleteAllPointedValues();
    }
};
