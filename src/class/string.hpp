/*
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *  Purpose: legacy-compatible string wrapper for feelfem2.
 *
 *  Notes:
 *   - Clean-room implementation using std::string internally.
 *   - Keeps legacy behavior of contain(): returns 1-based index if found, else 0.
 */

#pragma once

#include <string>
#include <istream>
#include <ostream>
#include <cctype>

int CstringLength(const char *);

class string
{
private:
    std::string s_;

public:
    // constructors
    string() = default;
    string(char c) : s_(1, c) {}
    explicit string(int reserve_size) { if (reserve_size > 0) s_.reserve(static_cast<size_t>(reserve_size)); }
    string(const char* p) : s_(p ? p : "") {}
    string(const string&) = default;
    string& operator=(const string&) = default;
    ~string() = default;

    // legacy: read a line into this string
    std::istream& getline(std::istream& in)
    {
        std::getline(in, s_);
        return in;
    }

    // comparisons (keep int-return style if your code expects int)
    friend int operator<(const string& a, const string& b) { return a.s_ < b.s_; }
    friend int operator==(const string& a, const string& b) { return a.s_ == b.s_; }
    friend int operator==(const string& a, const char* b)    { return a.s_ == (b ? b : ""); }
    friend int operator!=(const string& a, const char* b)    { return !(a == b); }

    // indexing
    char& operator[](unsigned int i)             { return s_.at(static_cast<size_t>(i)); }
    const char& operator[](unsigned int i) const { return s_.at(static_cast<size_t>(i)); }

    // lower-case (ASCII-ish; safe for tokens)
    void lower()
    {
        for (char& c : s_) {
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }
    }

    // convert
    operator const char*() const { return s_.c_str(); }

    // size
    unsigned int length() const { return static_cast<unsigned int>(s_.size()); }

    // legacy behavior: 1-based index if found, else 0
    int contain(const char* sub) const
    {
        if (!sub) return 0;

        // legacy: empty substring => found at position 1
        if (*sub == '\0') return 1;

        const auto pos = s_.find(sub);
        return (pos == std::string::npos) ? 0 : static_cast<int>(pos) + 1;
    }

    // stream I/O
    friend std::ostream& operator<<(std::ostream& os, const string& v) { return os << v.s_; }
    friend std::istream& operator>>(std::istream& is, string& v)       { return is >> v.s_; }
};

