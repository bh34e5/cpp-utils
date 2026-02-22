#pragma once

#include "arena.hh"
#include "strslice.hh"

StrSlice readFile(StrSlice filename, Arena *arena = nullptr);
