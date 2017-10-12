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

size_t RSAEncrypt(uint8_t *digest, uint8_t *output, int digest_len);

int main ( int argc , char * argv[] )
{
    /* Initialise the crypto library */
    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();
    OPENSSL_config(NULL);
    uint8_t buffer[100000];
    int fd_ctrl, fd_data, fd_in, fd_save;
    BIO *bio_stdout;
    FILE *log;
    if( argc < 3 )
    {
        printf("Missing command-line arguments: %s <ctrlFD> <dataFD>\n" , argv[0]) ;
        exit(-1) ;
    }
    fd_ctrl = atoi( argv[1] ) ;
    fd_data = atoi( argv[2] ) ;
    log = fopen("amal/logAmal.txt" , "w" );
    bio_stdout = BIO_new_fp(log, BIO_NOCLOSE);

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
    fd_save = open("amal/digest.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd_save == -1 )
    {
	fprintf(stderr, "This is amal, could not open digest.txt\n");
	exit(-1);
    }
    uint8_t digest[600];
    uint8_t output[600];
    size_t read_val;
    fprintf(log, "This is Amal. Starting to write to fd_data now\n");
    while (read_val = read(fd_in, buffer, 100000)) {
	    if (read_val <= 0) 
	    {
		break;
	    }
	    write(fd_data, buffer, read_val);
    }
    fprintf( log , "This is Amal. Starting to digest the input file\n");

    size_t hash_size = fileDigest(fd_in, digest, fd_save);
    fprintf(log, "This is the hash size: %zu \n", hash_size);

    BIO_dump( bio_stdout, (const char *)digest, hash_size);
    size_t encryptLen = RSAEncrypt(digest, output, hash_size); 
    BIO_dump(bio_stdout, (const char *)output, encryptLen);
    write(fd_ctrl, output, encryptLen);     
    
    EVP_cleanup();
    ERR_free_strings();

    fclose( log ) ;  
    close(fd_data);
    close(fd_ctrl);
    close(fd_in);
    return 0 ;

}

size_t RSAEncrypt(uint8_t *digest, uint8_t *output, int digest_len) {

	int padding = RSA_PKCS1_PADDING;
	RSA *rsa = getRSAfromFile("amal/amal_priv_key.pem", 0);
	return RSA_private_encrypt(digest_len, digest, output, rsa, padding);
	
}

