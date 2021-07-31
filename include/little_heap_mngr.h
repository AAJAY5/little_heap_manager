#ifndef __LITTLE_HEAP_MNGR_H__
#define __LITTLE_HEAP_MNGR_H__

#include <stdint.h>

#define LTL_SIZE_T              size_t
#define LTL_SIZEOF(x)           sizeof(x)
static LTL_SIZE_T __attribute__((__used__)) __ltl_heap_used = 0;

#define LTL_MALLOC(__block_size) (                                     \
    {                                                                  \
        void *__hptr = NULL;                                           \
        void *__mheap = malloc(__block_size + LTL_SIZEOF(LTL_SIZE_T)); \
        if (__mheap)                                                   \
        {                                                              \
            *((LTL_SIZE_T *)__mheap) = (__block_size);                 \
            __ltl_heap_used += __block_size;                           \
            __hptr = (__mheap + LTL_SIZEOF(LTL_SIZE_T));               \
        }                                                              \
        __hptr;                                                        \
    })

#define LTL_CALLOC(__block_count, __block_size) (                                           \
    {                                                                                       \
        void *__hptr = NULL;                                                                \
        void *__cheap = calloc(1, (__block_size * __block_count) + LTL_SIZEOF(LTL_SIZE_T)); \
        if (__cheap)                                                                        \
        {                                                                                   \
            *((LTL_SIZE_T *)__cheap) = (__block_size * __block_count);                      \
            __ltl_heap_used += (__block_size * __block_count);                              \
            __hptr = (__cheap + LTL_SIZEOF(LTL_SIZE_T));                                    \
        }                                                                                   \
        __hptr;                                                                             \
    })

#define LTL_FREE(__mem_ptr) (                                                              \
    {                                                                                      \
        if (__mem_ptr)                                                                     \
        {                                                                                  \
            LTL_SIZE_T __used_mem = *((LTL_SIZE_T *)(__mem_ptr - LTL_SIZEOF(LTL_SIZE_T))); \
            __ltl_heap_used -= __used_mem;                                                 \
            free(__mem_ptr - LTL_SIZEOF(LTL_SIZE_T));                                      \
        }                                                                                  \
    })

#define LTL_HEAP_USAGE() ({ __ltl_heap_used; })

#define LTL_ALLOCED_SIZE(__mem_ptr) (                                            \
    {                                                                            \
        LTL_SIZE_T __alloc_mem = 0;                                              \
        if (__mem_ptr)                                                           \
            __alloc_mem = *((LTL_SIZE_T *)(__mem_ptr - LTL_SIZEOF(LTL_SIZE_T))); \
        __alloc_mem;                                                             \
    })

#endif