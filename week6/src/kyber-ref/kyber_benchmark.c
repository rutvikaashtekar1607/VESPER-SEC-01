#include <stdint.h>
#include "params.h"
#include "kem.h"

volatile uint32_t result_keypair_cycles = 0;
volatile uint32_t result_enc_cycles = 0;
volatile uint32_t result_dec_cycles = 0;
volatile uint32_t result_done = 0;
volatile uint32_t result_valid = 0;
volatile uint32_t result_stack = 0;

static uint8_t pk[KYBER_PUBLICKEYBYTES];
static uint8_t sk[KYBER_SECRETKEYBYTES];
static uint8_t ct[KYBER_CIPHERTEXTBYTES];
static uint8_t ss_enc[KYBER_SSBYTES];
static uint8_t ss_dec[KYBER_SSBYTES];

static const uint8_t keypair_coins[2 * KYBER_SYMBYTES] = {
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
    0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
    0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,
    0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
    0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,
    0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
    0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,
    0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F
};

static const uint8_t enc_coins[KYBER_SYMBYTES] = {
    0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,
    0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
    0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,
    0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF
};

static uint32_t compare_secret(const uint8_t *a, const uint8_t *b)
{
    uint8_t diff = 0;

    for (uint32_t i = 0; i < KYBER_SSBYTES; i++)
        diff |= (uint8_t)(a[i] ^ b[i]);

    return diff == 0;
}

static void dwt_enable(void)
{
    volatile uint32_t *DEMCR = (uint32_t *)0xE000EDFC;
    volatile uint32_t *DWT_CTRL = (uint32_t *)0xE0001000;
    volatile uint32_t *DWT_CYCCNT = (uint32_t *)0xE0001004;

    *DEMCR |= (1u << 24);
    *DWT_CTRL |= 1u;
    *DWT_CYCCNT = 0;
}

static uint32_t dwt_cycles(void)
{
    volatile uint32_t *DWT_CYCCNT = (uint32_t *)0xE0001004;
    return *DWT_CYCCNT;
}

void main(void)
{
    uint32_t start;

    dwt_enable();

    start = dwt_cycles();
    crypto_kem_keypair_derand(pk, sk, keypair_coins);
    result_keypair_cycles = dwt_cycles() - start;

    start = dwt_cycles();
    crypto_kem_enc_derand(ct, ss_enc, pk, enc_coins);
    result_enc_cycles = dwt_cycles() - start;

    start = dwt_cycles();
    crypto_kem_dec(ss_dec, ct, sk);
    result_dec_cycles = dwt_cycles() - start;

    result_valid = compare_secret(ss_enc, ss_dec);

    /* Measure stack high-water mark. */
    {
        volatile uint32_t *p = (uint32_t *)0x20000E00;
        volatile uint32_t *stack_top = (uint32_t *)0x2000F000;

        while (p < stack_top && *p == 0xA5A5A5A5)
            p++;

        result_stack = 0x2000F000 - (uint32_t)p;
    }

    result_done = 1;

    while (1) {
    }
}