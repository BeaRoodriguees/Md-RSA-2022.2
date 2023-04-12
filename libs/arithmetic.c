#include <gmp.h>

typedef mpz_t bigint;

void add(bigint result, bigint num1, bigint num2)
{
    mpz_add(result, num1, num2);
}

void sub(bigint result, bigint num1, bigint num2)
{
    mpz_sub(result, num1, num2);
}

void mul(bigint result, bigint num1, bigint num2)
{
    mpz_mul(result, num1, num2);
}

void div(bigint result, bigint num1, bigint num2)
{
    mpz_div(result, num1, num2);
}

void mod(bigint result, bigint num1, bigint num2)
{
    mpz_mod(result, num1, num2);
}

void mdc(bigint result, bigint num1, bigint num2)
{
    if(mpz_cmp_si(num2, 0) == 0)
    {
        mpz_set(result, num1);
        return;
    }

    bigint temp;
    mpz_init(temp);
    mpz_mod(temp, num1, num2);
    mdc(result, num2, temp);
    mpz_clear(temp);
}


