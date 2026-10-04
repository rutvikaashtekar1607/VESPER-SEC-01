#include <stddef.h>
#include <stdint.h>

void randombytes(uint8_t *out, size_t outlen)
{
    for (size_t i = 0; i < outlen; i++)
        out[i] = 0;
}
