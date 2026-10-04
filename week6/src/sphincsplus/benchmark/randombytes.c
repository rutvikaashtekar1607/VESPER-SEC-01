#include <stdint.h>
#include "../randombytes.h"

static uint32_t state = 0x6D2B79F5u;

void randombytes(unsigned char *x, unsigned long long xlen)
{
    while (xlen--) {
        state ^= state << 13;
        state ^= state >> 17;
        state ^= state << 5;
        *x++ = (unsigned char)(state >> 24);
    }
}
