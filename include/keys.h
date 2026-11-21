#ifndef KEYS_H
#define KEYS_H

// Vérifier si un nombre est premier
int est_premier(int n);

// Calculer le PGCD de deux nombres
int calculer_pgcd(int a, int b);

// Générer les clés RSA
int generer_cles(int *p, int *q, int *n, int *e, int *d);

// Sauvegarder les clés dans des fichiers
int sauvegarder_cles(int n, int e, int d);

// Vérifier si les clés sont valides
int verifier_cles(int p, int q, int n, int e, int d);

#endif