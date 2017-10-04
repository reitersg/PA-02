/*----------------------------------------------------------------------------
PA-02: Messaage Digest & Signature using Pipes

FILE:   amal.c

Written By: 
     1- Christian Okada
     2- Scott Reiter
     
Submitted on: 
----------------------------------------------------------------------------*/

#include "../myCrypto.h"

#define FILE_SIZE 51246445
int main ( int argc , char * argv[] )
{

    /* Initialise the crypto library */
    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();
    OPENSSL_config(NULL);
    uint8_t buffer[FILE_SIZE];

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
    fileDigest(fd_in, digest, fd_ctrl);
    
    read(
    write(fd_data,  
    
    EVP_cleanup();
    ERR_free_strings();

    fclose( log ) ;  

    return 0 ;
}

