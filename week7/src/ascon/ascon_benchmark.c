#include <stdint.h>
#include "ascon-ref/api.h"
#include "ascon-ref/crypto_aead.h"

/* DWT cycle counter registers (Cortex-M4) */
#define DEMCR       (*(volatile uint32_t *)0xE000EDFC)
#define TRCENA      (1U << 24)
#define DWT_CTRL    (*(volatile uint32_t *)0xE0001000)
#define DWT_CYCCNT  (*(volatile uint32_t *)0xE0001004)
#define CYCCNTENA   (1U << 0)

/* Stack high-water measurement */
#define STACK_FILL_START 0x20000100U
#define STACK_TOP        0x2000F000U
#define STACK_PATTERN    0xA5A5A5A5U

/* Week 7 message sizes */
#define NUM_CASES 4
static const uint32_t message_lengths[NUM_CASES] = {
    16, 64, 256, 1024
};

/*
 * Large Week 7 benchmark buffers.
 * The linker places these above the stack region.
 */
#define MAX_MESSAGE_LEN 1024

static unsigned char plaintext[MAX_MESSAGE_LEN]
    __attribute__((section(".bench_buffers"), aligned(4)));

static unsigned char ciphertext[MAX_MESSAGE_LEN + CRYPTO_ABYTES]
    __attribute__((section(".bench_buffers"), aligned(4)));

/* Fixed test vectors for reproducibility */
static const unsigned char key[CRYPTO_KEYBYTES] = {
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
    0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F
};

static const unsigned char nonce[CRYPTO_NPUBBYTES] = {
    0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,
    0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F
};

/* Results readable from Renode */
volatile uint32_t result_cycles[NUM_CASES] = {0};
volatile uint32_t result_valid[NUM_CASES] = {0};
volatile uint32_t result_done = 0;
volatile uint32_t result_stack = 0;

/*
 * Scan upward from the beginning of the filled region.
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

int main(void)
{
    unsigned long long clen;
    int rc;

    /*
     * Prepare the largest plaintext before measurement.
     * Every byte has the same deterministic value.
     */
    for (uint32_t i = 0; i < MAX_MESSAGE_LEN; i++) {
        plaintext[i] = 0xAA;
    }

    /* Enable Cortex-M4 DWT cycle counter */
    DEMCR |= TRCENA;
    DWT_CTRL |= CYCCNTENA;

    /*
     * Run the same Ascon encryption with four message sizes.
     */
    for (uint32_t i = 0; i < NUM_CASES; i++) {

        DWT_CYCCNT = 0;

        rc = crypto_aead_encrypt(
            ciphertext,
            &clen,
            plaintext,
            message_lengths[i],
            0,
            0,
            0,
            nonce,
            key
        );

        /* Capture cycles immediately after encryption */
        result_cycles[i] = DWT_CYCCNT;

        /* Encryption returns 0 on success */
        result_valid[i] = (rc == 0 &&
                           clen == message_lengths[i] + CRYPTO_ABYTES);
    }

    /* Measure stack high-water mark after all cases */
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
