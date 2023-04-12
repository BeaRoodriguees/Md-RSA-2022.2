#include <gmp.h>

typedef mpz_t bigint;

void map_char_to_int(bigint result, char c){
    int num_char = c - '0';
    if(num_char >= 65 && num_char <= 90){
        mpz_set_si(result, num_char-63);
    }else if(num_char >= 97 && num_char <= 122){
        mpz_set_si(result, num_char-95);
    }else if(num_char == 32){
        mpz_set_si(result, num_char-4);
    }
}

void map_int_to_char(char *c, bigint num){
    int num_int = mpz_get_si(num);
    if(num_int >= 1 && num_int <= 26){
        *c = num_int + 64;
    }else if(num_int >= 27 && num_int <= 52){
        *c = num_int + 96;
    }else if(num_int == 53){
        *c = num_int + 4;
    }
}