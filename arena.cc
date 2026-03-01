#include "arena.hh"

#include <stdlib.h>

Arena makeArena(size_t initial_cap) {
    Arena res = {};

    void *data = calloc(1, initial_cap);
    assert(data != nullptr && "Out of memory");

    res.data = data;
    res.cap = initial_cap;
    res.len = 0;

    return res;
}

Arena subArena(Arena *arena, size_t initial_cap) {
    Arena res = {};

    if (initial_cap == 0) {
        initial_cap = arena->cap - arena->len;
    }

    void *data = pushSize(arena, initial_cap);

    res.data = data;
    res.cap = initial_cap;
    res.len = 0;

    return res;
}

void *pushSize(Arena *arena, size_t size, PushFlags flags) {
    assert(arena->cap >= size && arena->len <= arena->cap - size &&
           "Arena out of memory");

    void *res = (char *)arena->data + arena->len;
    arena->len += size;

    if (flags & PushFlags_Zero) {
        memset(res, 0, size);
    }

    return res;
}
