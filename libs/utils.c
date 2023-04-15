#include <gmp.h>

typedef mpz_t bigint;

void map_char_to_int(bigint result, char c){
    if(c >= 65 && c <= 90){
        mpz_set_si(result, c-63);
    }else if(c >= 97 && c <= 122){
        mpz_set_si(result, c-95);
    }else if(c == 32){
        mpz_set_si(result, c-4);
    }
}

void map_int_to_char(char *c, bigint num){
    int num_int = mpz_get_si(num);
    if(num_int >= 2 && num_int <= 27){
        *c = num_int + 63;
    }if(num_int==28){
        *c = 32;
    }
}
