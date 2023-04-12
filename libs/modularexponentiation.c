#include <gmp.h>
#include "arithmetic.c"

typedef mpz_t bigint;

void modExp(bigint result, bigint base, bigint exp, bigint m){

    if(mpz_cmp_ui (m, 1) == 0){
        mpz_set_si(result, 0);
        return;
    }

    bigint temp_mult;
    mpz_init(temp_mult);

    bigint temp_b;
    mpz_init(temp_b);
    mod(temp_b, base, m);
    mpz_set_si(result, 1);

    while (mpz_cmp_ui (exp, 0) > 0){
        if(mpz_fdiv_ui(exp, 2) == 1){
            mpz_mul(temp_mult, result, temp_b);
            mod(result, temp_mult, m);
        }

        mpz_mul(temp_mult, temp_b, temp_b);
        mod(temp_b, temp_mult, m);

        mpz_fdiv_q_ui(exp, exp, 2);
    }
    mpz_clear(temp_mult);
    mpz_clear(temp_b);
}

int main()
{
    bigint result, b, e, m;
    mpz_init(result);
    mpz_init(b);
    mpz_init(e);
    mpz_init(m);

    mpz_set_ui(b, 135);
    mpz_set_ui(e, 35415);
    mpz_set_ui(m, 1327);

    modExp(result, b, e, m);

    gmp_printf("%Zd", result);
}