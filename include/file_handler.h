#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

// Fonctions pour chiffrer et déchiffrer un fichier entier
int chiffrer_fichier(const char *source, const char *destination, unsigned long long e, unsigned long long n);
int dechiffrer_fichier(const char *source, const char *destination, unsigned long long d, unsigned long long n);

#endif