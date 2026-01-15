/*
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *  Purpose: iterator
 *
 *  Notes:
 *        Replaces a legacy iterator interface that had non-commercial reproduction terms.
 *
 */

#pragma once

template <class T>
class iterator
{
public:
    virtual ~iterator() = default;
    virtual int  init() = 0;
    virtual int  operator !() = 0;     // has current?
    virtual T    operator ()() = 0;    // current
    virtual int  operator ++() = 0;    // next
    virtual void operator =(T) = 0;    // set current
};

