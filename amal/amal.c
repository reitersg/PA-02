/*----------------------------------------------------------------------------
PA-02: Messaage Digest & Signature using Pipes

FILE:   amal.c

Written By: 
     1- Christian Okada
     2- Scott Reiter
     
Submitted on: 
----------------------------------------------------------------------------*/

#include "../myCrypto.h"
#include "../wrappers.h"
#define FILE_SIZE 51246445
int main ( int argc , char * argv[] )
{

    /* Initialise the crypto library */
    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();
    OPENSSL_config(NULL);
    uint8_t buffer[FILE_SIZE];
    int fd_ctrl, fd_data, fd_in;
    FILE *log;
    if( argc < 3 )
    {
        printf("Missing command-line arguments: %s <ctrlFD> <dataFD>\n" , argv[0]) ;
        exit(-1) ;
    }
    fd_ctrl = atoi( argv[1] ) ;
    fd_data = atoi( argv[2] ) ;
    
    log = fopen("amal/logAmal.txt" , "w" );

    if( ! log )
    {
        fprintf( stderr , "This is Amal. Could not create log file\n");
        exit(-1) ;
    }
    fprintf( log , "This is Amal. Will send digest to FD %d and file to FD %d\n" ,
                   fd_ctrl , fd_data );

    fd_in = open("amal/bunny.mp4" , O_RDONLY , S_IRUSR | S_IWUSR ) ;
    if( fd_in == -1 )
    {
        fprintf( stderr , "This is Amal. Could not open input file\n");
        exit(-1) ;
    }

    uint8_t *digest;   
    fprintf( log , "This is Amal. Starting to digest the input file\n");

    // ....
    // fileDigest(fd_in, digest, fd_ctrl);
    
    Read(fd_in, buffer, FILE_SIZE);
    Write(fd_data, buffer, FILE_SIZE);
    
    EVP_cleanup();
    ERR_free_strings();

    fclose( log ) ;  
    close(fd_data);
    return 0 ;
}

void RSAEncrypt(uint8_t *digest, uint8_t *output, int digest_len, unsigned char *key) {
	int padding = RSA_PKCS1_PADDING;
	RSA *rsa = getRSAfromFile("filename)", 1);
	RSA_public_encrypt(digest_len, digest, output, rsa, padding);
	
}
