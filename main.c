#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int read_choise(void);
void read_userkey(char key[], size_t minlen);
void keygen(char dest[], size_t lengtht);
void xor_string(char dest[], char string[], char key[], size_t length);

int main(int argc, char const *argv[]) {
  char plaintext[128];
  char ciphertext[128];
  char key[128];

  time_t t;
  srand((unsigned) time(&t)); // Use current time as seed for random gen.

  printf("Welcome to XORcipher\nPlease enter the text you want to encrypt\n-> ");
  fgets(plaintext, 128, stdin); // reads the plaintext while making sure of its length

  switch (read_choise()) {
    case 1:
      read_userkey(key, strlen(plaintext));
      break;
    case 2:
      keygen(key, strlen(plaintext));
      break;
  }

  // encrypt the message and print it
  xor_string(ciphertext, plaintext, key, strlen(plaintext));
  printf("\n\nYour encrypted message (HEX)\n-> ");
  for (size_t i = 0; i < (strlen(plaintext) - 1); i++) {
    printf(" %x", ciphertext[i]);
  }

  // decrypt the message and check if the operation was successfull
  char original_message[128];
  xor_string(original_message, ciphertext, key, strlen(plaintext));
  printf("\n\nYour original message (retrieved by doing the inverse operation)\n-> %s", original_message);

  return 0;
}

/**
* Ask the user to input an integer used to choose how to generate the key
*/
int read_choise() {
  int choise = 0;
  do {
    printf("\nPlease chose one of the following:\n"
           "1) Provide your own key (must be at least long as your plaintext)\n"
           "2) Generate a pseudo-randomic key\n-> ");
    scanf("%d", &choise);
  } while(choise != 1 && choise != 2);
  return choise;
}

/**
* Reads a 128 byte string from stdin
*/
void read_userkey(char key[], size_t minlen) {
  do {
    printf("\nPlease insert yout key (must be at least long as your message)\n-> ");
    int c; while ((c = getchar()) != '\n' && c != EOF); // clean the stdin before reading
    fgets(key, 128, stdin);
  } while(strlen(key) < minlen); // key length must be as long as the plaintext
}

/**
* Generate a preudo-randomic string and stores it on dest
*/
void keygen(char dest[], size_t length) {
  printf("\nYour pseudo-randomic key (HEX)\n-> ");
  for (size_t i = 0; i < length; i++) {
    dest[i] = (rand() % 128); // the random value must be a valid ASCII char
    printf(" %x", dest[i]);
  }
}

/**
* Execute the XOR operation between each char of string and key, and store the
* result on dest
*/
void xor_string(char dest[], char string[], char key[], size_t length) {
  for (size_t i = 0; i < length; i++) {
     dest[i] = string[i] ^ key[i];
  }
  dest[length] = '\n';
}
