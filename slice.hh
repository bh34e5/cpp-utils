#pragma once

#include <assert.h>
#include <limits.h>
#include <stddef.h>

template <typename T> struct Slice {
    size_t len;
    T *ptr;

    T &operator[](size_t idx) {
        assert(idx < this->len && "Out of bounds access");
        return this->ptr[idx];
    }
};

template<typename T>
static inline int sliceLen(Slice<T> s) {
    assert(s.len <= INT_MAX && "Slice length larger than max integer");
    return (int) s.len;
}
