#include <stdint.h>
#include "ascon-ref/api.h"
#include "ascon-ref/crypto_aead.h"

/* DWT cycle counter registers (Cortex-M4) */
#define DEMCR       (*(volatile uint32_t *)0xE000EDFC)
#define TRCENA      (1U << 24)
#define DWT_CTRL    (*(volatile uint32_t *)0xE0001000)
#define DWT_CYCCNT  (*(volatile uint32_t *)0xE0001004)
#define CYCCNTENA   (1U << 0)

/*
 * Stack high-water measurement.
 *
 * Cortex-M4 stack grows downward.
 * Initial SP = 0x20010000.
 *
 * The region below the static result variables is not touched.
 * The measurement region is filled up to the initial stack top.
 */
#define STACK_FILL_START 0x20000100U
#define STACK_TOP        0x2000F000U
#define STACK_PATTERN    0xA5A5A5A5U

/*
 * Scan upward from the beginning of the filled region.
 *
 * The first changed word marks the lowest point reached
 * by the downward-growing stack.
 */
static uint32_t measure_stack_usage(void)
{
    volatile uint32_t *p =
        (volatile uint32_t *)STACK_FILL_START;

    while ((uintptr_t)p < STACK_TOP &&
           *p == STACK_PATTERN) {
        p++;
    }

    return STACK_TOP - (uint32_t)(uintptr_t)p;
}

/* Fixed test vectors for reproducibility */
static const unsigned char key[CRYPTO_KEYBYTES] = {
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
    0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F
};

static const unsigned char nonce[CRYPTO_NPUBBYTES] = {
    0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,
    0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F
};

static const unsigned char plaintext[16] = {
    0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
    0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA
};

static unsigned char ciphertext[16 + CRYPTO_ABYTES];

/* Results readable from Renode */
volatile uint32_t result_cycles = 0;
volatile uint32_t result_done   = 0;
volatile uint32_t result_stack  = 0;

int main(void)
{
    unsigned long long clen;

    /*
     * Fill the complete measurement region.
     * This routine does not use the stack.
     */

    /* Enable Cortex-M4 DWT cycle counter */
    DEMCR |= TRCENA;
    DWT_CYCCNT = 0;
    DWT_CTRL |= CYCCNTENA;

    /* Measured Ascon operation */
    crypto_aead_encrypt(
        ciphertext,
        &clen,
        plaintext,
        16,
        0,
        0,
        0,
        nonce,
        key
    );

    /* Record cycle count immediately after crypto */
    result_cycles = DWT_CYCCNT;

    /* Measure stack high-water mark */
    result_stack = measure_stack_usage();

    /* Freeze DWT */
    DWT_CTRL &= ~CYCCNTENA;

    /* Signal successful completion */
    result_done = 1;

    while (1) {
        __asm("bkpt");
    }

    return 0;
}