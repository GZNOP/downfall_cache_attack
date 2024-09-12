#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "bib.h"

#define _GNU_SOURCE
#define THRESHOLD 80

int probe(char *adrs)
{
    volatile unsigned long time;

    asm __volatile__(
        "mfence \n" //
        "lfence \n" // Evite la parallelisation d'instruction (assure la sequentialité)
        "rdtsc \n"  // enregistre le tmeps
        "lfence \n"
        "movl %%eax, %%esi \n" // on met la mesure de temps dans esi
        "movl (%1), %%eax\n"   // on prend l'adresse de adrs, on load (cache ou pas cache ???)
        "lfence \n"
        "rdtsc \n"             // 2e mesure de temps
        "subl %%esi, %%eax \n" // on soustrait pour avoir le delta t
        "clflush 0(%1) \n"     // on flush
        : "=a"(time)
        : "c"(adrs)
        : "%esi", "%edx");


    printf("time : %ld\n", time);
    return time < THRESHOLD;
}

int main(void)
{
    probe((char *)foo);
    while (!probe((char *)foo));

    printf("flush & reload worked\n");
}