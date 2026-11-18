
#include <stdio.h>
#include <openssl/evp.h>
#include <openssl/pem.h>

int generate_rsa_keys() {

    EVP_PKEY_CTX *ctx;
    EVP_PKEY *pkey = NULL;

    // 1. Creer le contexte RSA
    ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);

    if (ctx == NULL) {
        printf("Erreur de creation du contexte RSA\n");
        return 0;
    }

    // 2. Initialiser la generation
    if (EVP_PKEY_keygen_init(ctx) <= 0) {
        printf("Erreur d'initialisation\n");
        EVP_PKEY_CTX_free(ctx);
        return 0;
    }

    // 3. Definir la taille de la cle : 2048 bits
    if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048) <= 0) {
        printf("Erreur de configuration RSA\n");
        EVP_PKEY_CTX_free(ctx);
        return 0;
    }

    // 4. Generer les cles
    if (EVP_PKEY_keygen(ctx, &pkey) <= 0) {
        printf("Erreur de generation des cles\n");
        EVP_PKEY_CTX_free(ctx);
        return 0;
    }

    // 5. Sauvegarder la cle privee
    FILE *private_file = fopen("keys/private.pem", "wb");

    if (private_file == NULL ||
        PEM_write_PrivateKey(private_file, pkey, NULL, NULL, 0, NULL, NULL) != 1) {
        printf("Erreur de sauvegarde de la cle privee\n");
        if (private_file != NULL) fclose(private_file);
        EVP_PKEY_free(pkey);
        EVP_PKEY_CTX_free(ctx);
        return 0;
    }

    fclose(private_file);

    // 6. Sauvegarder la cle publique
    FILE *public_file = fopen("keys/public.pem", "wb");

    if (public_file == NULL ||
        PEM_write_PUBKEY(public_file, pkey) != 1) {
        printf("Erreur de sauvegarde de la cle publique\n");
        if (public_file != NULL) fclose(public_file);
        EVP_PKEY_free(pkey);
        EVP_PKEY_CTX_free(ctx);
        return 0;
    }

    fclose(public_file);

    // Liberer la memoire
    EVP_PKEY_free(pkey);
    EVP_PKEY_CTX_free(ctx);

    printf("Cles RSA generees avec succes !\n");

    return 1;
}
