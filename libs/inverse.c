#include <stdio.h>
#include <gmp.h>

void _inverse(mpz_t mdc, mpz_t a, mpz_t m, int *cont, mpz_t s, mpz_t t)
{
    mpz_t mod, div, neg_div, mult, sum;
    mpz_inits(mod, div, neg_div, mult, sum, NULL);

    mpz_fdiv_qr(div, mod, a, m);
    mpz_neg(neg_div, div);

    if (mpz_cmp_si(mod, 0) == 0)
    {
        mpz_set(mdc, m);
        return;
    }

    _inverse(mdc, m, mod, cont, s, t);

    if (*cont == 1)
    {
        mpz_set_si(s, 1);
        mpz_set(t, neg_div);
    }
    else if (*cont % 2 == 0)
    {
        // s = s + t * (-div)
        mpz_mul(mult, t, neg_div);
        mpz_add(sum, mult, s);
        mpz_set(s, sum);
    }
    else
    {
        // t = t + s * (-div)
        mpz_mul(mult, s, neg_div);
        mpz_add(sum, mult, t);
        mpz_set(t, sum);
    }

    (*cont)++;

    mpz_clears(mod, div, neg_div, mult, sum, NULL);
}

/*
 * Calcula o inverso de a mod m utilizando o algoritmo de Euclides extentido.
 *
 * @param inv bigint (mpz_t) no qual será armazenado o inverso.
 * @param a   bigint(mpz_t) que representa o primeiro valor do módulo.
 * @param m   bigint(mpz_t) m que representa o valor do módulo.
 * @return void (variável inv é setada).
 *
 * @author Gabriel
 * @author Arthur
 */
void getInverse(mpz_t inv, mpz_t a, mpz_t m)
{
    mpz_t mdc, s, t, mult1, mult2, soma, aux;
    int cont = 1, *c = &cont;
    mpz_inits(mdc, s, t, mult1, mult2, soma, aux, NULL);

    _inverse(mdc, a, m, c, s, t);

    // soma = s * a + t * m
    mpz_mul(mult1, s, a);
    mpz_mul(mult2, t, m);
    mpz_add(soma, mult1, mult2);

    if (!(mpz_cmp(soma, mdc) == 0))
    {
        mpz_set(aux, s);
        mpz_set(s, t);
        mpz_set(t, aux);
    }

    if (mpz_cmp_si(s, 0) < 0)
    {
        mpz_add(s, s, m);
    }

    mpz_set(inv, s);

    mpz_clears(mdc, s, t, mult1, mult2, soma, aux, NULL);
}