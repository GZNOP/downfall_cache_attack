#include <openssl/aes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Création de la clé AES
    unsigned char key[AES_BLOCK_SIZE];
    if (!RAND_bytes(key, AES_BLOCK_SIZE)) {
        fprintf(stderr, "Erreur lors de la génération de la clé AES\n");
        return 1;
    }
    printf("Key: ");
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        printf("%02x ", key[i]);
    }
    printf("\n");

    // Texte à chiffrer/déchiffrer
    unsigned char plaintext[] = "Hello hehe!";
    unsigned char ciphertext[sizeof(plaintext)];
    unsigned char decryptedtext[sizeof(plaintext)];

    // Boucle de chiffrement/déchiffrement
    while (1) {
        // Chiffrement du texte en clair
        AES_KEY encrypt_key;
        AES_set_encrypt_key(key, 128, &encrypt_key);
        AES_encrypt(plaintext, ciphertext, &encrypt_key);

        // Affichage du texte chiffré
        printf("Texte chiffré : ");
        for (int i = 0; i < sizeof(ciphertext); i++) {
            printf("%02x ", ciphertext[i]);
        }
        printf("\n");
        // Déchiffrement du texte chiffré
        AES_KEY decrypt_key;
        AES_set_decrypt_key(key, 128, &decrypt_key);
        AES_decrypt(ciphertext, decryptedtext, &decrypt_key);

        // Affichage du texte déchiffré
        printf("Texte déchiffré : %s\n", decryptedtext);
        sleep(1);
    }

    return 0;
}
