#ifndef RSA_H
#define RSA_H

/* Type commun a tout le projet : entier non signe 64 bits */
typedef unsigned long long u64;

/* Calculs de base */
u64       calculer_n(u64 p, u64 q);          /* n = p * q */
u64       calculer_phi(u64 p, u64 q);        /* phi(n) = (p-1)(q-1) */
u64       pgcd(u64 a, u64 b);                /* PGCD (Euclide) */
long long inverse_mod(long long e, long long phi); /* d tel que e*d = 1 mod phi, -1 si impossible */
u64       choisir_e(u64 phi);                /* trouve un e premier avec phi, 0 si introuvable */

/* Exponentiation modulaire rapide : (base^exp) mod mod */
u64       puiss_mod(u64 base, u64 exp, u64 mod);

/* Chiffrement / dechiffrement d'un entier (il faut m < n) */
u64       rsa_chiffrer(u64 m, u64 e, u64 n);   /* c = m^e mod n */
u64       rsa_dechiffrer(u64 c, u64 d, u64 n); /* m = c^d mod n */

#endif