#pragma once

#include <assert.h>
#include <stddef.h>
#include <string.h>

#define KILOS(n) ((n) << 10)
#define MEGAS(n) ((n) << 20)

struct Arena {
    void *data;
    size_t len;
    size_t cap;

    struct Marker {
        Arena &arena;
        size_t len;

        Marker(Arena &arena) : arena(arena), len(arena.len) {}
        ~Marker() {
            this->arena.reset(this->len);
        }
    };

    inline void reset(size_t marker) {
        assert(marker <= this->len && "Invalid marker");
        this->len = marker;
    }

    Marker marker() {
        return Marker{*this};
    }
};

enum PushFlags {
    PushFlags_None,
    PushFlags_Zero = 1,
};

static inline PushFlags defaultPushFlags() {
    PushFlags flags = PushFlags_Zero;
    return flags;
}

#define PUSH_STRUCT(Struct, arena) ((Struct *)pushSize((arena), sizeof(Struct)))
#define PUSH_STRUCT_NO_CLEAR(Struct, arena) \
    ((Struct *)pushSize((arena), sizeof(Struct), PushFlags_None))

#define PUSH_LIST(Struct, arena, count) \
    ((Struct *)pushSize((arena), (count) * sizeof(Struct)))
#define PUSH_LIST_NO_CLEAR(Struct, arena, count) \
    ((Struct *)pushSize((arena), (count) * sizeof(Struct), PushFlags_None))

Arena makeArena(size_t initial_cap);
Arena subArena(Arena *arena, size_t initial_cap);
void *pushSize(Arena *arena, size_t size, PushFlags flags = defaultPushFlags());
