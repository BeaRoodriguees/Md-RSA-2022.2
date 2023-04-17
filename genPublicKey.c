#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>



int exportPublicKey(const mpz_t n, const mpz_t e)
{
    FILE *publicKey = fopen("publickey.txt", "w");
    if (publicKey)
    {
        gmp_fprintf(publicKey, "%Zd %Zd",n,e);
        fclose(publicKey);
        return 1;
    }
    else
    {
        printf("Não foi possível gerar a chave pública.\n");
        return 0;
    }
}

void generate_public_key(const mpz_t p, const mpz_t q, const mpz_t e, mpz_t n, mpz_t d) {
    mpz_t p_minus_1, q_minus_1, phi_n, gcd;
    mpz_inits(p_minus_1, q_minus_1, phi_n, gcd, NULL);

    // n = p * q
    mpz_mul(n, p, q);

    // phi_n = (p - 1) * (q - 1)
    mpz_sub_ui(p_minus_1, p, 1);
    mpz_sub_ui(q_minus_1, q, 1);
    mpz_mul(phi_n, p_minus_1, q_minus_1);

    // d = e^-1 mod phi_n
    mpz_invert(d, e, phi_n);

    // liberar Memória
    mpz_clears(p_minus_1, q_minus_1, phi_n, gcd, NULL);
    exportPublicKey(n, e);
}

int loadPqeKey()
{
    mpz_t p, q, e, n, d;
    mpz_inits(p, q, e, n, d, NULL);

    FILE *pqeKey = fopen("pqekey.txt", "r");
    if (pqeKey)
    {
        mpz_inp_str(p, pqeKey, 10);
        mpz_inp_str(q, pqeKey, 10);
        mpz_inp_str(e, pqeKey, 10);
        fclose(pqeKey);
        generate_public_key(p, q, e, n, d);
        return 1;
    }
    else
    {
        printf("O arquivo que contém a chave pública não existe.\n");
        return 0;
    }
}
