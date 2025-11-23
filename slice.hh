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

    T *begin() { return this->ptr; }
    T *end() { return this->ptr + this->len; }

    T const *cbegin() { return this->ptr; }
    T const *cend() { return this->ptr + this->len; }
};

template<typename T>
static inline int sliceLen(Slice<T> s) {
    assert(s.len <= INT_MAX && "Slice length larger than max integer");
    return (int) s.len;
}

#define SLICE(Type, arr) (Slice<Type>{ARRAY_LEN(arr), arr})
