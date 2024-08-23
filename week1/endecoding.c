/*
0. 문자를 입력받기.
1. 문자를 8bit으로 표현하기
2. 길이 나누는 부분 -> base64 encoding은 6byte로 나눔
3. padding 처리 -> '='은 한개 혹은 2개밖에 나올 수가 없음.



원래 계획은 위대로 하는거였으나 구글링을 하다보니 stackoverflow에 인코딩 디코딩에 대한 openssl 코드 중 일부를 발견.

includePath 업데이트 오류로 터미널에서 아래 명령어를 실행하여 작동을 확인하였음. /opt/homebrew/include 와 /opt/homebrew/lib는 저의 Mac 로컬환경에서 openssl 헤더가 있는 위치입니다.
gcc -o endecoding endecoding.c -I/opt/homebrew/include -L/opt/homebrew/lib -lssl -lcrypto
./endecoding
*/

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
    char input_string[MAX_INPUT_LENGTH];
    char* encoded_string;
    char* decoded_string;
    
    while (1) {
        printf("1. Base64 encoding\n");
        printf("2. Base64 decoding\n");

        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = 0;
        
        if (strcmp(choice, "1") == 0) {     // 1을 입력했을 때
            fgets(input_string, sizeof(input_string), stdin);
            input_string[strcspn(input_string, "\n")] = 0;
            encoded_string = base64_encode((const unsigned char *)input_string, strlen(input_string));
            printf("%s\n", encoded_string);
            free(encoded_string);
            break;
        } else if (strcmp(choice, "2") == 0) {      // 2를 입력했을 때
            fgets(input_string, sizeof(input_string), stdin);
            input_string[strcspn(input_string, "\n")] = 0;
            decoded_string = base64_decode(input_string, strlen(input_string));
            printf("%s\n", decoded_string);
            free(decoded_string);
            break;
        } else {
            break;
        }
    }
    return 0;
}
