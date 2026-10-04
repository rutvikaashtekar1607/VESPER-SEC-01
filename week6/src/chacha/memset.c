#include <stddef.h>

void *memset(void *s, int c, size_t n)
{
    unsigned char *p = (unsigned char *)s;
    unsigned char value = (unsigned char)c;

    while (n != 0) {
        *p = value;
        p++;
        n--;
    }

    return s;
}