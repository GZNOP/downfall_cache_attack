#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//gcc ./victim/victim.c ./victim/gather.S -o ./victim/a.out -g -O0
//taskset -c 1 ./a.out

extern uint8_t * source;
extern void gather_once();
char * str =
    "COUCOULATEAM<333"
    "COMMENTCAVA?????"
    "PERSOCAVABIEN!:D"
    "JADORE BEAUCOUP "
    "LES CHOCOLATINES"
    "JME REND COMPTE "
    "QUE JPEU METTRE "
    "DES ESPACES EN  "
    "FAIT, PAS BESOIN"
    "DE TOUT COLLER!!"
    "ALSO: FART HAHAH"
    "TROP DROLLE?! :3"
;

int main(int argc, char const* argv[]) {
    printf("getting data\n");
    fflush(stdout);

    memcpy((uint8_t *)&source, str, strlen(str));

    while (1) {
        gather_once();
    }

    return 0;
}
