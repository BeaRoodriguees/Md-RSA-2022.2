#include <stdio.h>
#include <gmp.h>

void inverse(mpz_t result, mpz_t a, mpz_t m, int *cont, mpz_t s, mpz_t t) {
    mpz_t mod, div, zero, um, neg_div, mult, sum;
    mpz_inits(mod, div, zero, neg_div, mult, sum, NULL);
    mpz_init_set_str(um, "1", 10);


    mpz_fdiv_qr(div, mod, a, m);
    mpz_neg(neg_div, div);
    
    gmp_printf("negdiv: %Zd ", neg_div);
    gmp_printf("A: %Zd M: %Zd div: %Zd mod: %Zd iteracoes: %d\n", a, m, div, mod, *cont);

    if(mpz_cmp(mod, zero) == 0) {
        mpz_set(result, m);
        return;
    }

    inverse(result, m, mod, cont, s, t);

    gmp_printf("s: %Zd t: %Zd\n", s, t);    
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

int main() {
    mpz_t result, a, m, s, t;
    int cont = 1, *c = &cont;
    mpz_inits(result, s, t, NULL);

    mpz_init_set_str(a, "144", 10);
    mpz_init_set_str(m, "233", 10);
    mpz_init_set_str(s, "1", 10);

    inverse(result, a, m, c, s, t);

    gmp_printf("\nresto: %Zd\ns: %Zd\ncont: %d\n", result, s, cont);

    return 0;
}