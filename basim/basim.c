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

size_t RSADecrypt(uint8_t *digest, uint8_t *output, int digest_len);

int main ( int argc , char * argv[] )
{
    
    /* Initialise the crypto library */
    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();
    OPENSSL_config(NULL);
    uint8_t buffer[100000];
    uint8_t buffer_1[600];
    uint8_t decrypted[600];
    uint8_t digest[600];
    BIO *bio_stdout;
    int fd_ctrl, fd_data, fd_out, fd_save;
    FILE *log;

    if( argc < 3 )
    {
        printf("Missing command-line arguments: %s <ctrlFD> <dataFD>\n" , argv[0]) ;
        exit(-1) ;
    }
    fd_ctrl = atoi( argv[1] ) ;
    fd_data = atoi( argv[2] ) ;

    log  = fopen("basim/logBasim.txt" , "w" );
    bio_stdout = BIO_new_fp(log, BIO_NOCLOSE);
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
    fd_save = open("fd_data.txt",O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR ) ;
	if (fd_save == -1) 
	{
	    fprintf(stderr, "This is Basim, could not open a file to save digest");
	exit(-1);
	}
    fprintf( log , "This is Basim. Starting to receive incoming file and compute its digest\n");
  	
   size_t read_val;
    while ((read_val = read(fd_data, buffer, 100000)) > 0) {
	    write(fd_out, buffer, read_val);
    }
    size_t hash_size = fileDigest(fd_data, digest, fd_save);
    read(fd_ctrl, buffer_1, hash_size); 
    size_t decrypt_len = RSADecrypt(buffer_1, decrypted, hash_size);
    fprintf(log, "This is the hash_size : %zu \n", hash_size);
    BIO_dump(bio_stdout, (const char *)decrypted, decrypt_len);
    if (memcmp(decrypted, digest, hash_size) == 0) {
	fprintf(log, "This is Basim, the signature from Amal is valid!\n");	
    } 
    fprintf(log, "Signatures don't match\n");
    EVP_cleanup();
    ERR_free_strings();

    fclose( log ) ;  
    close( fd_ctrl ) ;
    close( fd_data ) ;
    close(fd_save);
    close( fd_out );

    return 0 ;
}

size_t RSADecrypt(uint8_t *digest, uint8_t *output, int digest_len) {
	int padding = RSA_PKCS1_PADDING;
	RSA *rsa = getRSAfromFile("basim/amal_pubKey.pem", 1);
	return RSA_public_decrypt(digest_len, digest, output, rsa, padding);	
}
