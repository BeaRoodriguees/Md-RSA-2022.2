#include <gmp.h>
#include <stdio.h>

void mdc(mpz_t result, mpz_t num1, mpz_t num2)
{
    if(mpz_cmp_si(num2, 0) == 0)
    {
        mpz_set(result, num1);
        return;
    }

    mpz_t resto;
    mpz_init(resto);
    mpz_mod(resto, num1, num2);
    mdc(result, num2, resto);
    mpz_clear(resto);
}

void mod_exp(mpz_t result, mpz_t base, mpz_t exp, mpz_t m){

    if(mpz_cmp_si(m, 1) == 0){
        mpz_set_si(result, 0);
        return;
    }

    mpz_t mult_aux;
    mpz_init(mult_aux);

    mpz_t base_t;
    mpz_init(base_t);

    mpz_mod(base_t, base, m);
    mpz_set_si(result, 1);

    mpz_t rest_temp;
    mpz_init(rest_temp);

    while (mpz_cmp_si(exp, 0) > 0){
        if(mpz_fdiv_ui(exp, 2) == 1){
            mpz_mul(mult_aux, result, base_t);
            mpz_mod(result, mult_aux, m);
        }

        mpz_mul(mult_aux, base_t, base_t);
        mpz_mod(base_t, mult_aux, m);

        mpz_div_ui(exp, exp, 2);
    }

    mpz_clear(mult_aux);
    mpz_clear(base_t);
}