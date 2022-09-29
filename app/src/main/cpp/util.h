//
// Created by Administrator on 2021/07/16.
//

#include <stdlib.h>
#include "rpcmem.h"
#include "remote.h"

#ifndef ETHM_UTIL_H
#define ETHM_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif
void *aligned_malloc(int heapid, size_t required_bytes, size_t alignment);

void aligned_free(void *p2);

#ifdef __cplusplus
}
#endif

#endif //ETHM_UTIL_H
