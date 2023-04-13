#include <stdio.h>
#include <gmp.h>

void _inverse(mpz_t mdc, mpz_t a, mpz_t m, int *cont, mpz_t s, mpz_t t)
{
    mpz_t mod, div, zero, um, neg_div, mult, sum;
    mpz_inits(mod, div, zero, neg_div, mult, sum, NULL);
    mpz_init_set_str(um, "1", 10);

    mpz_fdiv_qr(div, mod, a, m);
    mpz_neg(neg_div, div);

    if (mpz_cmp(mod, zero) == 0)
    {
        mpz_set(mdc, m);
        return;
    }

    _inverse(mdc, m, mod, cont, s, t);

    if (*cont == 1)
    {
        mpz_set(s, um);
        mpz_set(t, neg_div);
    }
    else if (*cont % 2 == 0)
    {
        mpz_mul(mult, t, neg_div);
        mpz_add(sum, mult, s);
        mpz_set(s, sum);
    }
    else
    {
        mpz_mul(mult, s, neg_div);
        mpz_add(sum, mult, t);
        mpz_set(t, sum);
    }

    (*cont)++;

    mpz_clears(mod, div, zero, um, neg_div, mult, sum, NULL);
}

void getInverse(mpz_t inv, mpz_t a, mpz_t m)
{
    mpz_t mdc, s, t, mult1, mult2, soma, aux, zero;
    int cont = 1, *c = &cont;
    mpz_inits(mdc, s, t, mult1, mult2, soma, aux, zero, NULL);

    mpz_init_set_str(s, "1", 10);

    _inverse(mdc, a, m, c, s, t);

    mpz_mul(mult1, s, a);
    mpz_mul(mult2, t, m);
    mpz_add(soma, mult1, mult2);

    if (!(mpz_cmp(soma, mdc) == 0))
    {
        mpz_set(aux, s);
        mpz_set(s, t);
        mpz_set(t, aux);
    }

    if (mpz_cmp(s, zero) < 0)
    {
        mpz_add(s, s, m);
    }

    mpz_set(inv, s);

    mpz_clears(mdc, s, t, mult1, mult2, soma, aux, zero, NULL);
}