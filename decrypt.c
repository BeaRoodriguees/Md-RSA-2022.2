#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "libs/utils.c"
#include "libs/arithmetic.c"
#include "libs/inverse.c"

int loadPrivateKey(mpz_t e, mpz_t p, mpz_t q)
{
    FILE *privateKeyFile = fopen("pqekey.txt", "r");

    if(privateKeyFile)
    {
        mpz_inp_str(p, privateKeyFile, 10);
        mpz_inp_str(q, privateKeyFile, 10);
        mpz_inp_str(e, privateKeyFile, 10);
        fclose(privateKeyFile);
        return 1;
    }
    else
    {
        printf("O arquivo não exite.");
    }
}

int calculatePrivateKey(mpz_t d, mpz_t e, mpz_t p, mpz_t q){
    mpz_t totiente;
    mpz_init(totiente);

    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    
    mpz_mul(totiente, p, q);
    getInverse(d, e, totiente);

    mpz_add_ui(p, p, 1);
    mpz_add_ui(q, q, 1);

    mpz_clear(totiente);
}

int loadAndDecryptMessage(mpz_t d, mpz_t n)
{
    FILE *encryptedMessageFile = fopen("mensagem_encriptada.txt", "r");
    if(encryptedMessageFile)
    {
        FILE *decryptedMessageFile = fopen("mensagem_desencriptada.txt", "w");

        char c;
        mpz_t encryptedChar, decryptedChar;
        mpz_inits(encryptedChar, decryptedChar, NULL);

        while(gmp_fscanf(encryptedMessageFile, "%Zd", encryptedChar) != EOF)
        {
            mod_exp(decryptedChar, encryptedChar, d, n);
            map_int_to_char(&c, decryptedChar);

            gmp_fprintf(decryptedMessageFile, "%c", c);
        }

        mpz_clears(encryptedChar, decryptedChar, NULL);
        fclose(encryptedMessageFile);
        fclose(decryptedMessageFile);
        return 1;
    }
    else
    {
        printf("O arquivo contendo a mensagem não existe.\n");
        return 0;
    }

}

int main(){
    mpz_t n, p, q, d, e;
    mpz_inits(n, p, q, d, e, NULL);
    
    if(!loadPrivateKey(e, p, q))
    {
        exit(EXIT_FAILURE);
    }
    
    mpz_mul(n, p, q);
    calculatePrivateKey(d, e, p, q);

    if (!loadAndDecryptMessage(d, n))
    {
        exit(EXIT_FAILURE);
    }

    mpz_clears(n, p, q, d, e, NULL);
    printf("Sucesso ao salvar mensagem desencriptar em mensagem_desencriptada.txt");
    exit(EXIT_SUCCESS);
}

