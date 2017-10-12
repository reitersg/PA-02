/*----------------------------------------------------------------------------
PA-02: Messaage Digest & Signature using Pipes

FILE:   basim.c

Written By: 
     1- Christian Okada
     2- Scott Reiter
     
Submitted on: 
----------------------------------------------------------------------------*/


#include "../myCrypto.h"
#define FILE_SIZE 51246445

void RSADecrypt(uint8_t *digest, uint8_t *output, int digest_len);

int main ( int argc , char * argv[] )
{
    
    /* Initialise the crypto library */
    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();
    OPENSSL_config(NULL);
    uint8_t buffer[32];
    uint8_t buffer_1[600];
    uint8_t decrypted[600];
    uint8_t digest[600];
    int fd_ctrl, fd_data, fd_out, fd_save;
    FILE *log;

    if( argc < 3 )
    {
        printf("Missing command-line arguments: %s <ctrlFD> <dataFD>\n" , argv[0]) ;
        exit(-1) ;
    }
    fd_ctrl = atoi( argv[1] ) ;
    fd_data = atoi( argv[2] ) ;

    log = fopen("basim/logBasim.txt" , "w" );

    if( ! log )
    {
        fprintf( stderr , "This is Basim. Could not create log file\n");
        exit(-1) ;
    }
    fprintf( log , "This is Basim. Will receive digest from FD %d and file from FD %d\n" ,
                   fd_ctrl , fd_data );

    fd_out = open("basim/bunny.mp4" , O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR ) ;
    if( fd_out == -1 )
    {
        fprintf( stderr , "This is Basim. Could not open output file\n");
        exit(-1) ;
    }
    fd_save = open("basim/fd_data.txt",O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR ) ;
	if (fd_save == -1) 
	{
	    fprintf(stderr, "This is Basim, could not open a file to save digest");
	exit(-1);
	}
    fprintf( log , "This is Basim. Starting to receive incoming file and compute its digest\n");
    size_t hash_size = fileDigest(fd_data, digest, fd_save);
    read(fd_ctrl, buffer_1, hash_size); 
    RSADecrypt(decrypted, buffer_1, hash_size);
    // ....
    //read(fd_ctrl, decrypted, hash);
    //RSADecrypt(decrypted, output, hash);
   
   /* if (!memcmp(output, buffer, sizeof(output) == 0) {
	
    } */
    EVP_cleanup();
    ERR_free_strings();

    fclose( log ) ;  
    close( fd_ctrl ) ;
    close( fd_data ) ;


    return 0 ;
}

void RSADecrypt(uint8_t *digest, uint8_t *output, int digest_len) {
	int padding = RSA_PKCS1_PADDING;
	RSA *rsa = getRSAfromFile("amal_pubKey.pem", 1);
	RSA_public_decrypt(digest_len, digest, output, rsa, padding);
	
}
