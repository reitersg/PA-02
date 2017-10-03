/*----------------------------------------------------------------------------
PA-02: Messaage Digest & Signature using Pipes

FILE:   myCrypto.c

Written By: 
     1- 
     2-
     
Submitted on: 
----------------------------------------------------------------------------*/

#include "myCrypto.h"

void handleErrors( char *msg)
{
    fprintf( stderr , "%s\n" , msg ) ;
    ERR_print_errors_fp(stderr);
    abort();
}

//-----------------------------------------------------------------------------
#define INPUT_CHUNK   16384

size_t fileDigest( int fd_in , uint8_t *digest , int fd_save )
// Read all the incoming data from 'fd_in' file descriptor
// Compute the SHA256 hash value of this incoming data into the array 'digest'
// If the file descriptor 'fd_save' is > 0, store a copy of the incoming data to 'fd_save'
// Returns actual size in bytes of the computed hash value
{
    unsigned int  mdLen ;
    uint8_t buffer[INPUT_CHUNK];
    EVP_MD_ctx *mdCtx;
    int nBytes;

    if ( !(mdCtx != EVP_MD_CTX_CREATE() )
        handleErrors("Can't create");
    if (1 != EVP_DigestInit(mdCtx, EVP_sha256() )
        handleErrors();

    while (1) {
        nBytes = read (fd_in, buffer, INPUT_CHUNK);
        if (nBytes < 0) {
            break;
        }
        
        if (1 != EVP_DigestUpdate(mdCtx, buffer, nBytes) )
                handleErrors();

       if (fd_save > 0) {
            write(fd_save, buffer, nBytes);

        }
    }
    
       EVP_DigestFinal(mdCtx, buffer, &mdLen);
    // ....
    write(fd_save, digest, mdLen);
    
    return mdLen ;
}

//-----------------------------------------------------------------------------
RSA * getRSAfromFile(char * filename, int public)
{
    FILE * fp = fopen(filename,"rb");
 
    if (fp == NULL)
    {
        printf("Unable to open RSA key file %s \n",filename);
        return NULL;    
    }

    RSA *rsa = RSA_new() ;
 
    if ( public )
        rsa = PEM_read_RSA_PUBKEY(fp, &rsa,NULL, NULL);
    else
        rsa = PEM_read_RSAPrivateKey(fp, &rsa,NULL, NULL);
 
    fclose( fp );
    return rsa;
}


