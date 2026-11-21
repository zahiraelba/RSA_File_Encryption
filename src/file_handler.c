#include <stdio.h>
#include "file_handler.h"
#include "rsa.h"

int chiffrer_fichier(const char *source, const char *destination, unsigned long long e, unsigned long long n) {
    FILE *src = fopen(source, "rb"); // 'r' = lire, 'b' = binaire
    if (src == NULL) {
        printf("Erreur : impossible d'ouvrir %s\n", source);
        return 0;
    }
    
    FILE *dest = fopen(destination, "wb"); // 'w' = écrire, 'b' = binaire
    if (dest == NULL) {
        printf("Erreur : impossible de creer %s\n", destination);
        fclose(src);
        return 0;
    }

    unsigned char octet;
    
    // On lit le fichier octet par octet
    while (fread(&octet, 1, 1, src) == 1) {
        // On chiffre l'octet
        unsigned long long chiffre = rsa_chiffrer(octet, e, n);
        // On écrit le résultat dans le fichier destination
        fwrite(&chiffre, sizeof(unsigned long long), 1, dest);
    }

    fclose(src);
    fclose(dest);
    printf("Fichier %s chiffre avec succes.\n", source);
    return 1;
}

int dechiffrer_fichier (const char *source, const char *destination, unsigned long long d, unsigned long long n) {
    FILE *src = fopen(source, "rb");
    if (src == NULL) {
        printf("Erreur : impossible d'ouvrir %s\n", source);
        return 0;
    }
    
    FILE *dest = fopen(destination, "wb");
    if (dest == NULL) {
        printf("Erreur : impossible de creer %s\n", destination);
        fclose(src);
        return 0;
    }

    unsigned long long chiffre;
    
    // On lit les blocs de 8 octets (la taille d'un unsigned long long)
    while (fread(&chiffre, sizeof(unsigned long long), 1, src) == 1) {
        // On déchiffre
        unsigned long long clair = rsa_dechiffrer(chiffre, d, n);
        
        // On le remet sous forme d'octet normal
        unsigned char octet = (unsigned char)clair;
        
        // On écrit l'octet dans le fichier final
        fwrite(&octet, 1, 1, dest);
    }

    fclose(src);
    fclose(dest);
    printf("Fichier %s dechiffre avec succes.\n", source);
    return 1;
}