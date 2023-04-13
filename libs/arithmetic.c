#include <gmp.h>
#include "utils.c"

typedef mpz_t bigint;

void add(bigint result, bigint num1, bigint num2)
{
    mpz_add(result, num1, num2);
}

void sub(bigint result, bigint num1, bigint num2)
{
    mpz_sub(result, num1, num2);
}

void mult(bigint result, bigint num1, bigint num2)
{
    mpz_mul(result, num1, num2);
}

void div(bigint result, bigint num1, bigint num2)
{
    mpz_div(result, num1, num2);
}

void div_int(bigint result, bigint num1, int num2)
{
    mpz_div_ui(result, num1, num2);
}

void mod(bigint result, bigint num1, bigint num2)
{
    mpz_mod(result, num1, num2);
}

int mod_int(bigint num1, int num2)
{
    return mpz_fdiv_ui(num1, num2);
}

void mdc(bigint result, bigint num1, bigint num2)
{
    if(compare_int(num2, 0) == 0)
    {
        mpz_set(result, num1);
        return;
    }

    bigint resto;
    mpz_init(resto);
    mod(resto, num1, num2);
    mdc(result, num2, resto);
    mpz_clear(resto);
}

void mod_exp(bigint result, bigint base, bigint exp, bigint m){

    if(compare_int(m, 1) == 0){
        set_int(result, 0);
        return;
    }

    bigint temp_mult;
    mpz_init(temp_mult);

    bigint base_t;
    mpz_init(base_t);

    mod(base_t, base, m);
    set_int(result, 1);

    while (compare_int(exp, 0) > 0){
        if(mod_int(exp, 2) == 1){
            mult(temp_mult, result, base_t);
            mod(result, temp_mult, m);
        }

        mult(temp_mult, base_t, base_t);
        mod(base_t, temp_mult, m);

        div_int(exp, exp, 2);
    }

    mpz_clear(temp_mult);
    mpz_clear(base_t);
}