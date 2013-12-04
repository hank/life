/* Creates a good random output using secure random generation and
   cryptographic hash functions. */
#include <stdio.h>
#include <stdlib.h>
#include <rdrand.h>
#include <openssl/sha.h>
int main()
{
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    uint32_t rnd[8];
    uint32_t times;
    int result;
    // Get 256 bits of random
    result = rdrand_get_n_32(8, rnd);   
    if(result != RDRAND_SUCCESS) {
        fprintf(stderr, "rdrand_get_n_32 returned %d, exiting...\n", result);
        return EXIT_FAILURE;
    }
    // Hash this a random number of times
    do {
        result = rdrand_32(&times, 5);   
        if(result != RDRAND_SUCCESS) {
            fprintf(stderr, "rdrand_32 returned %d, exiting...\n", result);
            return EXIT_FAILURE;
        }
    } while(times < (1<<22) || times > (1<<25));
    fprintf(stderr, "Hashing our random input %u times...\n", times);
    while(times-- > 0) {
        SHA256_Update(&sha256, (char*)rnd, sizeof(uint32_t)*8);       
    }
    SHA256_Final((unsigned char*)rnd, &sha256);
    printf("%08X%08X%08X%08X%08X%08X%08X%08X\n", 
            rnd[0], rnd[1], rnd[2], rnd[3], rnd[4], rnd[5], rnd[6], rnd[7]);
    
    return EXIT_SUCCESS;
}
