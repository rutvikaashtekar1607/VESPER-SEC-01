#ifndef PRINTSTATE_H_
#define PRINTSTATE_H_

/* Stubbed for bare-metal benchmarking: no console/printf available,
   and debug output is irrelevant to cycle timing. Real cryptographic
   computation (P12/P8 permutations) is untouched — only debug prints
   are removed. */
#define print(...) ((void)0)
#define printbytes(...) ((void)0)
#define printstate(...) ((void)0)

#endif