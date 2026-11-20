#include <stdio.h>
#include "keys.h"

int main() {
    int p = 61, q = 53;
    int n, e, d;

    printf("=== Test du module KEYS ===\n");

    // Test 1 : est_premier
    printf("Test est_premier(61) : %s\n", est_premier(61) ? "OK" : "ECHEC");
    printf("Test est_premier(60) : %s\n", est_premier(60) == 0 ? "OK" : "ECHEC");

    // Test 2 : calculer_pgcd
    printf("Test pgcd(12,18) = %d : %s\n", calculer_pgcd(12, 18), calculer_pgcd(12, 18) == 6 ? "OK" : "ECHEC");

    // Test 3 : generer_cles
    if (generer_cles(&p, &q, &n, &e, &d) == 1) {
        printf("Test generer_cles : OK -> n=%d e=%d d=%d\n", n, e, d);
    } else {
        printf("Test generer_cles : ECHEC\n");
        return 0;
    }

    // Test 4 : verifier_cles
    if (verifier_cles(p, q, n, e, d) == 1) {
        printf("Test verifier_cles : OK - Cles VALIDEES !\n");
    } else {
        printf("Test verifier_cles : ECHEC\n");
    }

    // Test 5 : sauvegarder_cles
    if (sauvegarder_cles(n, e, d) == 1) {
        printf("Test sauvegarder_cles : OK - fichiers crees !\n");
    } else {
        printf("Test sauvegarder_cles : ECHEC\n");
    }

    printf("=== Fin du test ===\n");
    return 0;
}