#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "aes128ni.h"

//gcc -o victime victime_aes.c -maes -lssl -lcrypto pour compiler

int main()
{
    // Générer une clé aléatoire
    uint8_t key[AES128_KEYLEN];
    if (RAND_bytes(key, AES128_KEYLEN) != 1) {
        fprintf(stderr, "Erreur lors de la génération de la clé aléatoire\n");
        return 1;
    }

    // Initialiser le contexte AES
    struct aes128 ctx;
    aes128_init(&ctx, key);

    // Données à chiffrer
    uint8_t plaintext[AES128_BLOCKLEN] = "Hello hehe!";
    uint8_t ciphertext[AES128_BLOCKLEN];
    uint8_t decrypted_text[AES128_BLOCKLEN];


    printf("clé : ");
    for (size_t i = 0; i < AES128_KEYLEN; i++) {
        printf("%02x", key[i]);
    }
    printf("\n");
    

    while(1){
        // Chiffrer les données
        aes128_encrypt(&ctx, ciphertext, plaintext);
        // Afficher le texte chiffré
        //printf("Texte chiffré : ");
        //for (size_t i = 0; i < AES128_BLOCKLEN; i++) {
        //    printf("%02x", ciphertext[i]);
        //}
        //printf("\n");
        // Déchiffrer les données
        aes128_decrypt(&ctx, decrypted_text, ciphertext);
        // Afficher le texte déchiffré
        //printf("Texte déchiffré : %s\n", decrypted_text);
    }
    return 0;
}
