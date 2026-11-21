#include <stdio.h>
#include "rsa.h"

int main(void) {
    printf("=== Tests unitaires ===\n");
    printf("pgcd(48, 18)           = %llu   (attendu 6)\n", pgcd(48, 18));
    printf("inverse_mod(17, 3120)  = %lld  (attendu 2753)\n", inverse_mod(17, 3120));
    printf("inverse_mod(6, 9)      = %lld  (attendu -1)\n", inverse_mod(6, 9));
    printf("puiss_mod(65, 17, 3233)= %llu  (attendu 2790)\n", puiss_mod(65, 17, 3233));

    printf("\n=== Test RSA complet (p=61, q=53) ===\n");
    u64 p = 61, q = 53;
    u64 n = calculer_n(p, q);
    u64 phi = calculer_phi(p, q);
    u64 e = 17;
    long long d = inverse_mod((long long)e, (long long)phi);

    printf("n = %llu, phi = %llu, e = %llu, d = %lld\n", n, phi, e, d);

    int ok = 1;
    for (u64 m = 0; m < 256; m++) {          /* tous les octets possibles */
        u64 c = rsa_chiffrer(m, e, n);
        u64 r = rsa_dechiffrer(c, (u64)d, n);
        if (r != m) { ok = 0; printf("ERREUR pour m = %llu\n", m); }
    }
    printf("Chiffrement/dechiffrement des octets 0..255 : %s\n", ok ? "OK" : "ECHEC");

    printf("choisir_e(3120) = %llu\n", choisir_e(3120));
    return 0;
}