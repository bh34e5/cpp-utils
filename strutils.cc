#include "strutils.hh"
#include "utils.hh"

#include <stdio.h>
#include <string.h>

#define DEFAULT_SCRATCH (MEGAS(4))
static Arena _scratch;

static Arena *getArena(Arena *arena) {
    Arena *res = arena;

    if (res == nullptr) {
        res = &_scratch;

        if (res->cap == 0) {
            *res = makeArena(DEFAULT_SCRATCH);
        }
    }

    return res;
}

StrSlice readFile(StrSlice filename, Arena *arena) {
    Arena *scratch = getArena(arena);

    auto marker = scratch->marker();

    char *filename_z =
        (char *)pushSize(scratch, filename.len + 1, PushFlags_None);

    memcpy((void *)filename_z, filename.ptr, filename.len);
    filename_z[filename.len] = 0;

    StrSlice res = {};

    FILE *f = fopen(filename_z, "r");
    if (f != nullptr) {
        fseek(f, 0, SEEK_END);
        size_t filelen = ftell(f);
        fseek(f, 0, SEEK_SET);

        char *contents = new char[filelen];
        if (contents != nullptr) {
            if (fread(contents, filelen, 1, f) == 1) {
                res.len = filelen;
                res.ptr = contents;
            } else {
                delete[] contents;
            }
        }

        fclose(f);
    }

    return res;
}
