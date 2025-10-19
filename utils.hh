#pragma once

#include <stddef.h>

#define OFFSET_OF(Struct, Field) ((size_t)(&((Struct *)0)->Field))
#define PARENT_OF_FIELD(Struct, Field, ptr)                                    \
    ((Struct *)((char *)ptr - OFFSET_OF(Struct, Field)))

#define ARRAY_LEN(a) (sizeof((a)) / sizeof(*(a)))

#define LOG_DEBUG(msg, ...) fprintf(stderr, "DEBUG: " msg, __VA_ARGS__)

#define SLL_PUSH(item, list) SLL_PUSH_NAMED(item, list, next)
#define SLL_PUSH_NAMED(item, list, next)                                       \
    do {                                                                       \
        (item)->next = (list);                                                 \
        (list) = (item);                                                       \
    } while (0)

#define SLL_DROP(list) SLL_DROP_NAMED(list, next)
#define SLL_DROP_NAMED(list, next)                                             \
    do {                                                                       \
        assert((list) != nullptr && "List empty");                             \
        (list) = (list)->next;                                                 \
    } while (0)

#define SLL_POP(list, res) SLL_POP_NAMED(list, res, next)
#define SLL_POP_NAMED(list, res, next)                                         \
    do {                                                                       \
        assert((list) != nullptr && "List empty");                             \
        res = (list);                                                          \
        (list) = (list)->next;                                                 \
    } while (0)
