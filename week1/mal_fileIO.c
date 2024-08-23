//gcc -o malFileIO mal_fileIO.c -I/opt/homebrew/include -L/opt/homebrew/lib -lssl -lcrypto
// malloc을 이용한 파일 입출력
// 텍스트파일에 Hello h4c!! 가 적혀있으면 SGVsbG8gaDRjISE= 로 인코딩됨. 디코딩은 그 반대.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#define MAX_INPUT_LENGTH 1024

char* base64_encode(const unsigned char* input, int length) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;
    char *encoded_buffer;
    
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, input, length);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    BIO_set_close(bio, BIO_NOCLOSE);
    BIO_free_all(bio);
    
    encoded_buffer = (char *)malloc(bufferPtr->length + 1);
    memcpy(encoded_buffer, bufferPtr->data, bufferPtr->length);
    encoded_buffer[bufferPtr->length] = '\0';
    BUF_MEM_free(bufferPtr);
    
    return encoded_buffer;
}

char* base64_decode(const char* input, int length) {
    BIO *bio, *b64;
    char *decoded_buffer = (char *)malloc(length);
    memset(decoded_buffer, 0, length);
    
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new_mem_buf(input, length);
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_read(bio, decoded_buffer, length);
    BIO_free_all(bio);
    return decoded_buffer;
}

int main() {
    char choice[MAX_INPUT_LENGTH];
    char filename[MAX_INPUT_LENGTH];
    char *input_string = NULL;
    char *output_string = NULL;
    size_t len = 0;

    printf("1. Base64 encoding\n");
    printf("2. Base64 decoding\n");
    fgets(choice, sizeof(choice), stdin);
    choice[strcspn(choice, "\n")] = 0;
    
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    getline(&input_string, &len, file);
    fclose(file);

    if (strcmp(choice, "1") == 0) {
        // 읽어온 내용을 인코딩
        output_string = base64_encode((const unsigned char *)input_string, strlen(input_string));
    } else if (strcmp(choice, "2") == 0) {
        // 읽어온 내용을 디코딩
        output_string = base64_decode(input_string, strlen(input_string));
    } else {
        printf("Invalid choice.\n");
        return 1;
    }

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }
    fprintf(file, "%s", output_string);
    fclose(file);

    printf("변환 완료.\n");

    if (input_string != NULL)
        free(input_string);
    if (output_string != NULL)
        free(output_string);

    return 0;
}
