#include "rsa.h"

u64 calculer_n(u64 p, u64 q) {
    return p * q;
}

u64 calculer_phi(u64 p, u64 q) {
    return (p - 1) * (q - 1);
}

u64 pgcd(u64 a, u64 b) {
    while (b != 0) {
        u64 r = a % b;
        a = b;
        b = r;
    }
    return a;
}

/* Euclide etendu : renvoie l'inverse de e modulo phi, ou -1 si e n'est pas inversible */
long long inverse_mod(long long e, long long phi) {
    long long t = 0, new_t = 1;
    long long r = phi, new_r = e;

    while (new_r != 0) {
        long long q = r / new_r;
        long long tmp;

        tmp = t - q * new_t;
        t = new_t;
        new_t = tmp;

        tmp = r - q * new_r;
        r = new_r;
        new_r = tmp;
    }

    if (r > 1) return -1;      /* e et phi ne sont pas premiers entre eux */
    if (t < 0) t += phi;
    return t;
}

u64 choisir_e(u64 phi) {
    if (phi > 65537 && pgcd(65537, phi) == 1)
        return 65537;

    for (u64 e = 3; e < phi; e += 2) {
        if (pgcd(e, phi) == 1)
            return e;
    }
    return 0;
}

/* Exponentiation modulaire rapide (square-and-multiply) */
u64 puiss_mod(u64 base, u64 exp, u64 mod) {
    u64 res = 1;
    base %= mod;

    while (exp > 0) {
        if (exp & 1)
            res = (u64)((unsigned __int128)res * base % mod);
        base = (u64)((unsigned __int128)base * base % mod);
        exp >>= 1;
    }
    return res;
}

u64 rsa_chiffrer(u64 m, u64 e, u64 n) {
    return puiss_mod(m, e, n);
}

u64 rsa_dechiffrer(u64 c, u64 d, u64 n) {
    return puiss_mod(c, d, n);
}