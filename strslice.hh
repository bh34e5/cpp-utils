#pragma once

#include "slice.hh"
#include "utils.hh"

#include <string.h>

typedef Slice<char const> StrSlice;

#define STR_SLICE(s) (StrSlice{ARRAY_LEN((s)) - 1, (s)})
#define STR_ARGS(s) sliceLen((s)), (s).ptr

static bool eql(StrSlice a, StrSlice b) {
    if (a.len != b.len) {
        return false;
    }

    for (size_t i = 0; i < a.len; ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

static inline StrSlice strSlice(char const *str) {
    StrSlice res = {};

    if (str != nullptr) {
        size_t len = strlen(str);

        res.len = len;
        res.ptr = str;
    }

    return res;
}
