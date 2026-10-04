#include <stdint.h>
#include <stddef.h>
#include "../api.h"

#define DWT_CTRL (*(volatile uint32_t *)0xE0001000u)
#define DWT_CYCCNT (*(volatile uint32_t *)0xE0001004u)
#define DEMCR (*(volatile uint32_t *)0xE000EDFCu)

#define DEMCR_TRCENA (1u << 24)
#define DWT_CYCCNTENA (1u << 0)

volatile uint32_t result_keypair;
volatile uint32_t result_sign;
volatile uint32_t result_verify;
volatile uint32_t result_siglen;
volatile uint32_t result_stack;
volatile uint32_t result_valid;
volatile uint32_t result_done;

static void dwt_init(void)
{
    DEMCR |= DEMCR_TRCENA;
    DWT_CYCCNT = 0;
    DWT_CTRL |= DWT_CYCCNTENA;
}

static uint32_t dwt_start(void)
{
    DWT_CYCCNT = 0;
    return DWT_CYCCNT;
}

static uint32_t dwt_stop(uint32_t start)
{
    return DWT_CYCCNT - start;
}

static uint32_t measure_stack(void)
{
    volatile uint32_t *p = (uint32_t *)0x20000E00u;
    volatile uint32_t *end = (uint32_t *)0x2000F000u;

    while (p < end && *p == 0xA5A5A5A5u)
        p++;

    return (uint32_t)end - (uint32_t)p;
}

int main(void)
{
    static unsigned char pk[CRYPTO_PUBLICKEYBYTES];
    static unsigned char sk[CRYPTO_SECRETKEYBYTES];
    static unsigned char sig[CRYPTO_BYTES];
    static unsigned char message[32];
    static unsigned char seed[CRYPTO_SEEDBYTES];

    size_t siglen = 0;
    uint32_t start;
    uint32_t cycles_keypair;
    uint32_t cycles_sign;
    uint32_t cycles_verify;

    for (size_t i = 0; i < sizeof(seed); i++)
        seed[i] = (unsigned char)(i + 1);

    for (size_t i = 0; i < sizeof(message); i++)
        message[i] = (unsigned char)(0xA0u + i);

    dwt_init();

    start = dwt_start();
    if (crypto_sign_seed_keypair(pk, sk, seed) != 0)
        return 1;
    cycles_keypair = dwt_stop(start);

    start = dwt_start();
    if (crypto_sign_signature(sig, &siglen, message, sizeof(message), sk) != 0)
        return 2;
    cycles_sign = dwt_stop(start);

    start = dwt_start();
    if (crypto_sign_verify(sig, siglen, message, sizeof(message), pk) != 0)
        return 3;
    cycles_verify = dwt_stop(start);

    result_stack = measure_stack();

    result_keypair = cycles_keypair;
    result_sign = cycles_sign;
    result_verify = cycles_verify;
    result_siglen = (uint32_t)siglen;
    result_valid = 1;
    result_done = 1;

    (void)result_keypair;
    (void)result_sign;
    (void)result_verify;
    (void)result_siglen;
    (void)result_stack;
    (void)result_valid;
    (void)result_done;

    while (1) {
    }
}
