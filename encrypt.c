#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "libs/utils.c"
#include "libs/arithmetic.c"

int loadPublicKey(mpz_t n, mpz_t e)
{
    FILE *publicKeyFile = fopen("publickey.txt", "r");
    if (publicKeyFile)
    {
        mpz_inp_str(n, publicKeyFile, 10);
        mpz_inp_str(e, publicKeyFile, 10);
        fclose(publicKeyFile);
        return 1;
    }
    else
    {
        printf("O arquivo que contém a chave pública não existe.\n");
        return 0;
    }
}

int loadAndProcessMessage(mpz_t n, mpz_t e)
{
    FILE *messageFile = fopen("mensagem.txt", "r");

    if (messageFile)
    {
        FILE *encryptedMessageFile = fopen("mensagem_encriptada.txt", "w");

        char c;
        mpz_t mappedChar, encryptedChar;
        mpz_inits(mappedChar, encryptedChar, NULL);
        while (fscanf(messageFile, "%c", &c) != EOF)
        {
            map_char_to_int(mappedChar, c);
            mod_exp(encryptedChar, mappedChar, e, n);
            gmp_fprintf(encryptedMessageFile, "%Zd ", encryptedChar);
        }
        mpz_clears(mappedChar, encryptedChar, NULL);

        fclose(messageFile);
        fclose(encryptedMessageFile);
        return 1;
    }
    else
    {
        printf("O arquivo contendo a mensagem não existe.\n");
        return 0;
    }
}

int main()
{
    mpz_t n, e;
    mpz_inits(n, e, NULL);

    if (!loadPublicKey(n, e))
    {
        exit(EXIT_FAILURE);
    }
    if (!loadAndProcessMessage(n, e))
    {
        exit(EXIT_FAILURE);
    }

    mpz_clears(n, e, NULL);
    exit(EXIT_SUCCESS);
}