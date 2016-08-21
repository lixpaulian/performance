/*
 * xxtea.c
 *
 * (c) 2016 Lixco Microsystems <lix@paulian.net>
 *
 * Created on: Jul 24, 2016 (LNP)
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "timing.h"
#include "xxtea.h"


#define ENCRYPTED_AREA_LEN (64 * (1024 / 4))	/* in words */
#define SEED (0xDEADBABA)
#define CRYPT_BLOCK_LEN 64

uint32_t const keychain[] =
{
	1553853876u, 697942743u, 457962054u, 424309557u
};

uint32_t encrypted_area[ENCRYPTED_AREA_LEN];
uint32_t backup_area[ENCRYPTED_AREA_LEN];


static void fill_random_data(uint32_t *area, int len);
static void btea(uint32_t *v, int n, uint32_t const key[4]);


void encryption_test(int iterations)
{
	int blocks, i, j, result;
	uint32_t cnt;
	uint32_t random, encrypt, decrypt, compare;

	random = encrypt = decrypt = compare = 0;

	srand(SEED);

	for (j = 0; j < iterations; j++)
	{
		/* generate random data */
		cnt = getCounterValue();
		fill_random_data(encrypted_area, ENCRYPTED_AREA_LEN);
		random += getCounterValue() - cnt;

		/* backup random data */
		memcpy((void *) backup_area, (void *) encrypted_area, ENCRYPTED_AREA_LEN * 4);

		/* encrypt */
		cnt = getCounterValue();
		blocks = ENCRYPTED_AREA_LEN * 4 / CRYPT_BLOCK_LEN;
		for (i = 0; i < blocks; i++)
			btea(encrypted_area + (i * CRYPT_BLOCK_LEN / 4), CRYPT_BLOCK_LEN / 4, keychain);
		encrypt += getCounterValue() - cnt;

		/* decrypt */
		cnt = getCounterValue();
		for (i = 0; i < blocks; i++)
			btea(encrypted_area + (i * CRYPT_BLOCK_LEN / 4), -(CRYPT_BLOCK_LEN / 4), keychain);
		decrypt += getCounterValue() - cnt;

		/* compare with backup */
		cnt = getCounterValue();
		result = memcmp((void *) encrypted_area, (void *) backup_area, ENCRYPTED_AREA_LEN);
		compare += getCounterValue() - cnt;

		if (result)
		{
			printf("Compare failed\n");
			break;
		}
	}
	/* print results */
	printf("Results after %d iterations\n", iterations);
	printf("Generate random data: %lu us\n", random / iterations);
	printf("Encrypt data: %lu us\n", encrypt / iterations);
	printf("Decrypt data: %lu us\n", decrypt / iterations);
	printf("Compare data: %lu us\n", compare / iterations);
}



static void fill_random_data(uint32_t *area, int len)
{
	int i;

	for (i = 0; i < len; i++)
		*area++ = rand();
}


/* For encryption we use a "corrected block TEA" algorithm (XXTEA)
   as it should be sufficiently robust for this application.
   Reference: http://en.wikipedia.org/wiki/XXTEA */

#define DELTA 0x9e3779b9
#define MX (((z>>5^y<<2) + (y>>3^z<<4)) ^ ((sum^y) + (key[(p&3)^e] ^ z)))

static void btea(uint32_t *v, int n, uint32_t const key[4])
{
    uint32_t y, z, sum;
    unsigned p, rounds, e;

    if (n > 1)
    {	/* Coding Part */
        rounds = 6 + 52/n;
        sum = 0;
        z = v[n-1];
        do
        {
            sum += DELTA;
            e = (sum >> 2) & 3;
            for (p=0; (int)p<n-1; p++)
            {
                y = v[p+1];
                z = v[p] += MX;
            }
            y = v[0];
            z = v[n-1] += MX;
        } while (--rounds);
    }
    else if (n < -1)
    {	/* Decoding Part */
        n = -n;
        rounds = 6 + 52/n;
        sum = rounds*DELTA;
        y = v[0];
        do
        {
            e = (sum >> 2) & 3;
            for (p=n-1; p>0; p--)
            {
                z = v[p-1];
                y = v[p] -= MX;
            }
            z = v[n-1];
            y = v[0] -= MX;
        } while ((sum -= DELTA) != 0);
    }
}

