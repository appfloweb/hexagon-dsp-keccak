//
// Created by Administrator on 2021/07/16.
//
#include "util.h"

void *aligned_malloc(int heapid, size_t required_bytes, size_t alignment) {

    int offset = alignment - 1 + sizeof(void *);

    void *p1 = (void *) rpcmem_alloc(heapid, RPCMEM_DEFAULT_FLAGS, required_bytes + offset);

    if (p1 == NULL)

        return NULL;

    void **p2 = (void **) (((size_t) p1 + offset) & ~(alignment - 1));

    p2[-1] = p1;

    return p2;

}
 void aligned_free(void *p2) {

    void *p1 = ((void **) p2)[-1];

    rpcmem_free(p1);

}
