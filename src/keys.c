#include <stdio.h>
#include <stdlib.h>
#include "keys.h"

// 1. Vérifier si un nombre est premier
int est_premier(int nombre) {

if (nombre < 2)
    return 0;
for (int i = 2; i < nombre; i++) {
    if (nombre % i == 0)
        return 0;
}
return 1;

}

// 2. Calculer le PGCD de deux nombres
int calculer_pgcd(int a, int b) {

while (b != 0) {
    int reste = a % b;
    a = b;
    b = reste;
}
return a;

}

// 3. Générer les clés RSA
int generer_cles(int *p, int *q, int *n, int *e, int *d) {

int phi;
// Vérifier les pointeurs
if (p == NULL || q == NULL || n == NULL ||
    e == NULL || d == NULL) {
    return 0;
}
// Générer le premier nombre premier p
do {
    *p = 11 + rand() % 10;
} while (est_premier(*p) == 0);
// Générer le deuxième nombre premier q
do {
    *q = 11 + rand() % 10;
} while (est_premier(*q) == 0 || *p == *q);
// Calculer n = p * q
*n = (*p) * (*q);
// Calculer phi(n)
phi = (*p - 1) * (*q - 1);
// Choisir e
*e = 3;
while (calculer_pgcd(*e, phi) != 1) {
    *e = *e + 2;
}
// Calculer d
*d = 1;
while (((*e) * (*d)) % phi != 1) {
    (*d)++;
}
printf("Les cles RSA ont ete generees.\n");
return 1;

}

// 4. Sauvegarder les clés dans des fichiers
int sauvegarder_cles(int n, int e, int d) {

FILE *fichier;
// Sauvegarder la clé publique
fichier = fopen("public.key", "w");
if (fichier == NULL)
    return 0;
fprintf(fichier, "%d %d\n", n, e);
fclose(fichier);
// Sauvegarder la clé privée
fichier = fopen("private.key", "w");
if (fichier == NULL)
    return 0;
fprintf(fichier, "%d %d\n", n, d);
fclose(fichier);
printf("Les cles ont ete sauvegardees.\n");
return 1;

}

// 5. Vérifier la validité des clés
int verifier_cles(int p, int q, int n, int e, int d) {

int phi;
// Vérifier que p et q sont premiers
if (est_premier(p) == 0 || est_premier(q) == 0)
    return 0;
// Vérifier que p et q sont différents
if (p == q)
    return 0;
// Vérifier que n = p * q
if (n != p * q)
    return 0;
// Calculer phi
phi = (p - 1) * (q - 1);
// Vérifier les valeurs de e et d
if (e <= 1 || e >= phi || d <= 0)
    return 0;
// Vérifier le PGCD
if (calculer_pgcd(e, phi) != 1)
    return 0;
// Vérifier la relation entre e et d
if ((e * d) % phi != 1)
    return 0;
return 1;

}