#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "libs/arithmetic.c"

int exportPublicKey(const mpz_t n, const mpz_t e)
{
    FILE *publicKey = fopen("publickey.txt", "w");
    if (publicKey)
    {
        gmp_fprintf(publicKey, "%Zd %Zd", n, e);
        fclose(publicKey);
        return 1;
    }
    else
    {
        printf("Não foi possível gerar a chave pública.\n");
        return 0;
    }
}

int generate_public_key(mpz_t p, mpz_t q, mpz_t e, mpz_t n)
{
    mpz_t p_minus_1, q_minus_1, phi_n, mdc_res;
    mpz_inits(p_minus_1, q_minus_1, phi_n, mdc_res, NULL);

    // n = p * q
    mpz_mul(n, p, q);

    // phi_n = (p - 1) * (q - 1)
    mpz_sub_ui(p_minus_1, p, 1);
    mpz_sub_ui(q_minus_1, q, 1);
    mpz_mul(phi_n, p_minus_1, q_minus_1);

    mdc(mdc_res, e, phi_n);

    if (mpz_cmp_si(mdc_res, 1) == 0)
    {
        // liberar Memória
        mpz_clears(p_minus_1, q_minus_1, phi_n, mdc_res, NULL);
        return exportPublicKey(n, e);
    }
    else
    {
        // liberar Memória
        mpz_clears(p_minus_1, q_minus_1, phi_n, mdc_res, NULL);
        printf("O valor de e não é coprimo a (p - 1)*(q - 1)!\n");
        return 0;
    }
}

int main()
{
    mpz_t p, q, e, n;
    mpz_inits(p, q, e, n, NULL);

    FILE *pqeKey = fopen("pqekey.txt", "r");
    if (pqeKey)
    {
        mpz_inp_str(p, pqeKey, 10);
        mpz_inp_str(q, pqeKey, 10);
        mpz_inp_str(e, pqeKey, 10);
        fclose(pqeKey);
        if (!(is_prime(p) && is_prime(q)))
        {
            printf("Tanto p, quando q devem ser primos!\n");
            return 0;
        }

        if (generate_public_key(p, q, e, n))
        {
            printf("Chave pública salva com sucesso em publickey.txt\n");
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        printf("O arquivo que contém os números primos (p, q, e) não existe.\n");
        return 0;
    }
}
