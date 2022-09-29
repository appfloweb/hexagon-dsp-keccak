/*==============================================================================
  Copyright (c) 2012-2020 Qualcomm Technologies, Inc.
  All rights reserved. Qualcomm Proprietary and Confidential.
==============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "HAP_farf.h"
#include "calculator.h"
#include "HAP_vtcm_mgr.h"

extern void keccak512_40();

extern void keccak512_40_96();

extern void keccak512_64();

extern void keccak256_96();

void *aligned_malloc_vtcm(size_t required_bytes, size_t alignment) {

    int offset = alignment - 1 + sizeof(void *);

    void *p1 = (void *) HAP_request_VTCM(required_bytes + offset, 1);

    if (p1 == NULL)

        return NULL;

    void **p2 = (void **) (((size_t) p1 + offset) & ~(alignment - 1));

    p2[-1] = p1;

    return p2;

}

void aligned_free_vtcm(void *p2) {

    void *p1 = ((void **) p2)[-1];

    HAP_release_VTCM(p1);

}

int calculator_open(const char *uri, remote_handle64 *handle) {
    void *tptr = NULL;
    tptr = (void *) aligned_malloc_vtcm(96 * 16 * 2, 128);
    *handle = (remote_handle64) tptr;
    assert(*handle);
    return 0;
}

/**
 * @param handle, the value returned by open
 * @retval, 0 for success, should always succeed
 */
int calculator_close(remote_handle64 handle) {
    if (handle)
        aligned_free_vtcm((void *) handle);
    return 0;
}

static const uint64_t __attribute__((aligned(128))) RC[24 * 16] =
        {1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL,
         1ULL,
         0x8082ULL, 0x8082ULL, 0x8082ULL, 0x8082ULL, 0x8082ULL, 0x8082ULL, 0x8082ULL, 0x8082ULL,
         0x8082ULL, 0x8082ULL, 0x8082ULL, 0x8082ULL, 0x8082ULL, 0x8082ULL, 0x8082ULL, 0x8082ULL,
         0x800000000000808aULL, 0x800000000000808aULL, 0x800000000000808aULL, 0x800000000000808aULL,
         0x800000000000808aULL, 0x800000000000808aULL, 0x800000000000808aULL, 0x800000000000808aULL,
         0x800000000000808aULL, 0x800000000000808aULL, 0x800000000000808aULL, 0x800000000000808aULL,
         0x800000000000808aULL, 0x800000000000808aULL, 0x800000000000808aULL, 0x800000000000808aULL,
         0x8000000080008000ULL, 0x8000000080008000ULL, 0x8000000080008000ULL, 0x8000000080008000ULL,
         0x8000000080008000ULL, 0x8000000080008000ULL, 0x8000000080008000ULL, 0x8000000080008000ULL,
         0x8000000080008000ULL, 0x8000000080008000ULL, 0x8000000080008000ULL, 0x8000000080008000ULL,
         0x8000000080008000ULL, 0x8000000080008000ULL, 0x8000000080008000ULL, 0x8000000080008000ULL,
         0x808bULL, 0x808bULL, 0x808bULL, 0x808bULL, 0x808bULL, 0x808bULL, 0x808bULL, 0x808bULL,
         0x808bULL, 0x808bULL, 0x808bULL, 0x808bULL, 0x808bULL, 0x808bULL, 0x808bULL, 0x808bULL,
         0x80000001ULL, 0x80000001ULL, 0x80000001ULL, 0x80000001ULL, 0x80000001ULL, 0x80000001ULL,
         0x80000001ULL, 0x80000001ULL, 0x80000001ULL, 0x80000001ULL, 0x80000001ULL, 0x80000001ULL,
         0x80000001ULL, 0x80000001ULL, 0x80000001ULL, 0x80000001ULL,
         0x8000000080008081ULL, 0x8000000080008081ULL, 0x8000000080008081ULL, 0x8000000080008081ULL,
         0x8000000080008081ULL, 0x8000000080008081ULL, 0x8000000080008081ULL, 0x8000000080008081ULL,
         0x8000000080008081ULL, 0x8000000080008081ULL, 0x8000000080008081ULL, 0x8000000080008081ULL,
         0x8000000080008081ULL, 0x8000000080008081ULL, 0x8000000080008081ULL, 0x8000000080008081ULL,
         0x8000000000008009ULL, 0x8000000000008009ULL, 0x8000000000008009ULL, 0x8000000000008009ULL,
         0x8000000000008009ULL, 0x8000000000008009ULL, 0x8000000000008009ULL, 0x8000000000008009ULL,
         0x8000000000008009ULL, 0x8000000000008009ULL, 0x8000000000008009ULL, 0x8000000000008009ULL,
         0x8000000000008009ULL, 0x8000000000008009ULL, 0x8000000000008009ULL, 0x8000000000008009ULL,
         0x8aULL, 0x8aULL, 0x8aULL, 0x8aULL, 0x8aULL, 0x8aULL, 0x8aULL, 0x8aULL, 0x8aULL, 0x8aULL,
         0x8aULL, 0x8aULL, 0x8aULL, 0x8aULL, 0x8aULL, 0x8aULL,
         0x88ULL, 0x88ULL, 0x88ULL, 0x88ULL, 0x88ULL, 0x88ULL, 0x88ULL, 0x88ULL, 0x88ULL, 0x88ULL,
         0x88ULL, 0x88ULL, 0x88ULL, 0x88ULL, 0x88ULL, 0x88ULL,
         0x80008009ULL, 0x80008009ULL, 0x80008009ULL, 0x80008009ULL, 0x80008009ULL, 0x80008009ULL,
         0x80008009ULL, 0x80008009ULL, 0x80008009ULL, 0x80008009ULL, 0x80008009ULL, 0x80008009ULL,
         0x80008009ULL, 0x80008009ULL, 0x80008009ULL, 0x80008009ULL,
         0x8000000aULL, 0x8000000aULL, 0x8000000aULL, 0x8000000aULL, 0x8000000aULL, 0x8000000aULL,
         0x8000000aULL, 0x8000000aULL, 0x8000000aULL, 0x8000000aULL, 0x8000000aULL, 0x8000000aULL,
         0x8000000aULL, 0x8000000aULL, 0x8000000aULL, 0x8000000aULL,
         0x8000808bULL, 0x8000808bULL, 0x8000808bULL, 0x8000808bULL, 0x8000808bULL, 0x8000808bULL,
         0x8000808bULL, 0x8000808bULL, 0x8000808bULL, 0x8000808bULL, 0x8000808bULL, 0x8000808bULL,
         0x8000808bULL, 0x8000808bULL, 0x8000808bULL, 0x8000808bULL,
         0x800000000000008bULL, 0x800000000000008bULL, 0x800000000000008bULL, 0x800000000000008bULL,
         0x800000000000008bULL, 0x800000000000008bULL, 0x800000000000008bULL, 0x800000000000008bULL,
         0x800000000000008bULL, 0x800000000000008bULL, 0x800000000000008bULL, 0x800000000000008bULL,
         0x800000000000008bULL, 0x800000000000008bULL, 0x800000000000008bULL, 0x800000000000008bULL,
         0x8000000000008089ULL, 0x8000000000008089ULL, 0x8000000000008089ULL, 0x8000000000008089ULL,
         0x8000000000008089ULL, 0x8000000000008089ULL, 0x8000000000008089ULL, 0x8000000000008089ULL,
         0x8000000000008089ULL, 0x8000000000008089ULL, 0x8000000000008089ULL, 0x8000000000008089ULL,
         0x8000000000008089ULL, 0x8000000000008089ULL, 0x8000000000008089ULL, 0x8000000000008089ULL,
         0x8000000000008003ULL, 0x8000000000008003ULL, 0x8000000000008003ULL, 0x8000000000008003ULL,
         0x8000000000008003ULL, 0x8000000000008003ULL, 0x8000000000008003ULL, 0x8000000000008003ULL,
         0x8000000000008003ULL, 0x8000000000008003ULL, 0x8000000000008003ULL, 0x8000000000008003ULL,
         0x8000000000008003ULL, 0x8000000000008003ULL, 0x8000000000008003ULL, 0x8000000000008003ULL,
         0x8000000000008002ULL, 0x8000000000008002ULL, 0x8000000000008002ULL, 0x8000000000008002ULL,
         0x8000000000008002ULL, 0x8000000000008002ULL, 0x8000000000008002ULL, 0x8000000000008002ULL,
         0x8000000000008002ULL, 0x8000000000008002ULL, 0x8000000000008002ULL, 0x8000000000008002ULL,
         0x8000000000008002ULL, 0x8000000000008002ULL, 0x8000000000008002ULL, 0x8000000000008002ULL,
         0x8000000000000080ULL, 0x8000000000000080ULL, 0x8000000000000080ULL, 0x8000000000000080ULL,
         0x8000000000000080ULL, 0x8000000000000080ULL, 0x8000000000000080ULL, 0x8000000000000080ULL,
         0x8000000000000080ULL, 0x8000000000000080ULL, 0x8000000000000080ULL, 0x8000000000000080ULL,
         0x8000000000000080ULL, 0x8000000000000080ULL, 0x8000000000000080ULL, 0x8000000000000080ULL,
         0x800aULL, 0x800aULL, 0x800aULL, 0x800aULL, 0x800aULL, 0x800aULL, 0x800aULL, 0x800aULL,
         0x800aULL, 0x800aULL, 0x800aULL, 0x800aULL, 0x800aULL, 0x800aULL, 0x800aULL, 0x800aULL,
         0x800000008000000aULL, 0x800000008000000aULL, 0x800000008000000aULL, 0x800000008000000aULL,
         0x800000008000000aULL, 0x800000008000000aULL, 0x800000008000000aULL, 0x800000008000000aULL,
         0x800000008000000aULL, 0x800000008000000aULL, 0x800000008000000aULL, 0x800000008000000aULL,
         0x800000008000000aULL, 0x800000008000000aULL, 0x800000008000000aULL, 0x800000008000000aULL,
         0x8000000080008081ULL, 0x8000000080008081ULL, 0x8000000080008081ULL, 0x8000000080008081ULL,
         0x8000000080008081ULL, 0x8000000080008081ULL, 0x8000000080008081ULL, 0x8000000080008081ULL,
         0x8000000080008081ULL, 0x8000000080008081ULL, 0x8000000080008081ULL, 0x8000000080008081ULL,
         0x8000000080008081ULL, 0x8000000080008081ULL, 0x8000000080008081ULL, 0x8000000080008081ULL,
         0x8000000000008080ULL, 0x8000000000008080ULL, 0x8000000000008080ULL, 0x8000000000008080ULL,
         0x8000000000008080ULL, 0x8000000000008080ULL, 0x8000000000008080ULL, 0x8000000000008080ULL,
         0x8000000000008080ULL, 0x8000000000008080ULL, 0x8000000000008080ULL, 0x8000000000008080ULL,
         0x8000000000008080ULL, 0x8000000000008080ULL, 0x8000000000008080ULL, 0x8000000000008080ULL,
         0x80000001ULL, 0x80000001ULL, 0x80000001ULL, 0x80000001ULL, 0x80000001ULL, 0x80000001ULL,
         0x80000001ULL, 0x80000001ULL, 0x80000001ULL, 0x80000001ULL, 0x80000001ULL, 0x80000001ULL,
         0x80000001ULL, 0x80000001ULL, 0x80000001ULL, 0x80000001ULL,
         0x8000000080008008ULL, 0x8000000080008008ULL, 0x8000000080008008ULL, 0x8000000080008008ULL,
         0x8000000080008008ULL, 0x8000000080008008ULL, 0x8000000080008008ULL, 0x8000000080008008ULL,
         0x8000000080008008ULL, 0x8000000080008008ULL, 0x8000000080008008ULL, 0x8000000080008008ULL,
         0x8000000080008008ULL, 0x8000000080008008ULL, 0x8000000080008008ULL,
         0x8000000080008008ULL,};

static const uint64_t __attribute__((aligned(128))) RFill_40[4 * 16] =
        {1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL,
         1ULL,
         0x8000000000000000ULL, 0x8000000000000000ULL, 0x8000000000000000ULL, 0x8000000000000000ULL,
         0x8000000000000000ULL, 0x8000000000000000ULL, 0x8000000000000000ULL, 0x8000000000000000ULL,
         0x8000000000000000ULL, 0x8000000000000000ULL, 0x8000000000000000ULL, 0x8000000000000000ULL,
         0x8000000000000000ULL, 0x8000000000000000ULL, 0x8000000000000000ULL, 0x8000000000000000ULL
                //输入转置
                , 0x400000000ULL, 0x2c00000028ULL, 0x5400000050ULL, 0x7c00000078ULL,
         0xa4000000a0ULL, 0xcc000000c8ULL, 0xf4000000f0ULL, 0x11c00000118ULL, 0x14400000140ULL,
         0x16c00000168ULL, 0x19400000190ULL, 0x1bc000001b8ULL, 0x1e4000001e0ULL, 0x20c00000208ULL,
         0x23400000230ULL, 0x25c00000258ULL
                //输出转置
                , 0x400000000ULL, 0x4400000040ULL, 0x8400000080ULL, 0xc4000000c0ULL,
         0x10400000100ULL, 0x14400000140ULL, 0x18400000180ULL, 0x1c4000001c0ULL, 0x20400000200ULL,
         0x24400000240ULL, 0x28400000280ULL, 0x2c4000002c0ULL, 0x30400000300ULL, 0x34400000340ULL,
         0x38400000380ULL, 0x3c4000003c0ULL};

static const uint64_t __attribute__((aligned(128))) RFill_40_96[4 * 16] =
        {1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL,
         1ULL,
         0x8000000000000000ULL, 0x8000000000000000ULL, 0x8000000000000000ULL, 0x8000000000000000ULL,
         0x8000000000000000ULL, 0x8000000000000000ULL, 0x8000000000000000ULL, 0x8000000000000000ULL,
         0x8000000000000000ULL, 0x8000000000000000ULL, 0x8000000000000000ULL, 0x8000000000000000ULL,
         0x8000000000000000ULL, 0x8000000000000000ULL, 0x8000000000000000ULL, 0x8000000000000000ULL
                //输入转置
                , 0x400000000ULL, 0x2c00000028ULL, 0x5400000050ULL, 0x7c00000078ULL,
         0xa4000000a0ULL, 0xcc000000c8ULL, 0xf4000000f0ULL, 0x11c00000118ULL, 0x14400000140ULL,
         0x16c00000168ULL, 0x19400000190ULL, 0x1bc000001b8ULL, 0x1e4000001e0ULL, 0x20c00000208ULL,
         0x23400000230ULL, 0x25c00000258ULL
                //输出转置
                , 0x400000000ULL, 0x6400000060ULL, 0xc4000000c0ULL, 0x12400000120ULL,
         0x18400000180ULL, 0x1e4000001e0ULL, 0x24400000240ULL, 0x2a4000002a0ULL, 0x30400000300ULL,
         0x36400000360ULL, 0x3c4000003c0ULL, 0x42400000420ULL, 0x48400000480ULL, 0x4e4000004e0ULL,
         0x54400000540ULL, 0x5a4000005a0ULL};


static const uint64_t __attribute__((aligned(128))) RFill_96[4 * 16] =
        {1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL, 1ULL,
         1ULL,
         0x8000000000000000ULL, 0x8000000000000000ULL, 0x8000000000000000ULL, 0x8000000000000000ULL,
         0x8000000000000000ULL, 0x8000000000000000ULL, 0x8000000000000000ULL, 0x8000000000000000ULL,
         0x8000000000000000ULL, 0x8000000000000000ULL, 0x8000000000000000ULL, 0x8000000000000000ULL,
         0x8000000000000000ULL, 0x8000000000000000ULL, 0x8000000000000000ULL, 0x8000000000000000ULL
                //输入转置
                , 0x400000000ULL, 0x6400000060ULL, 0xc4000000c0ULL, 0x12400000120ULL,
         0x18400000180ULL, 0x1e4000001e0ULL, 0x24400000240ULL, 0x2a4000002a0ULL, 0x30400000300ULL,
         0x36400000360ULL, 0x3c4000003c0ULL, 0x42400000420ULL, 0x48400000480ULL, 0x4e4000004e0ULL,
         0x54400000540ULL, 0x5a4000005a0ULL
                //输出转置
                , 0x400000000ULL, 0x2400000020ULL, 0x4400000040ULL, 0x6400000060ULL,
         0x8400000080ULL, 0xa4000000a0ULL, 0xc4000000c0ULL, 0xe4000000e0ULL, 0x10400000100ULL,
         0x12400000120ULL, 0x14400000140ULL, 0x16400000160ULL, 0x18400000180ULL, 0x1a4000001a0ULL,
         0x1c4000001c0ULL, 0x1e4000001e0ULL};

static const uint64_t __attribute__((aligned(128))) RFill_64[16 * 2] =
        {
                0x8000000000000001ULL, 0x8000000000000001ULL, 0x8000000000000001ULL,
                0x8000000000000001ULL, 0x8000000000000001ULL, 0x8000000000000001ULL,
                0x8000000000000001ULL, 0x8000000000000001ULL, 0x8000000000000001ULL,
                0x8000000000000001ULL, 0x8000000000000001ULL, 0x8000000000000001ULL,
                0x8000000000000001ULL, 0x8000000000000001ULL, 0x8000000000000001ULL,
                0x8000000000000001ULL
                //输入输出转置
                , 0x400000000ULL, 0x4400000040ULL, 0x8400000080ULL, 0xc4000000c0ULL,
                0x10400000100ULL, 0x14400000140ULL, 0x18400000180ULL, 0x1c4000001c0ULL,
                0x20400000200ULL, 0x24400000240ULL, 0x28400000280ULL, 0x2c4000002c0ULL,
                0x30400000300ULL, 0x34400000340ULL, 0x38400000380ULL, 0x3c4000003c0ULL
        };

int calculator_keccak512_40_64(remote_handle64 h, const uint8_t *in, int loadLen, uint8_t *out,
                               int writeLen) {
    keccak512_40(&RC, &RFill_40, in, out, h);
    return 0;
}

int calculator_keccak512_40_96(remote_handle64 h, const uint8_t *in, int loadLen, uint8_t *out,
                               int writeLen) {
    keccak512_40_96(&RC, &RFill_40_96, in, out, h);
    return 0;
}

int calculator_keccak512_64_64(remote_handle64 h, const uint8_t *in, int loadLen, uint8_t *out,
                               int writeLen) {
    keccak512_64(&RC, &RFill_64, in, out, h);
    return 0;
}

int calculator_keccak256_96_32(remote_handle64 h, const uint8_t *in, int loadLen, uint8_t *out,
                               int writeLen) {
    keccak256_96(&RC, &RFill_96, in, out, h);
    return 0;
}