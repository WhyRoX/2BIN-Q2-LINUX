#include <stdio.h>
#include <stdlib.h>

#include "cryptPolybe.h"

static char square[8][8] =
{{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'},
{'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'},
{'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X'},
{'Y', 'Z', '0', '1', '2', '3', '4', '5'},
{'6', '7', '8', '9', ' ', '!', '"', '#'},
{'$', '%', '&', '\'', '(', ')', '*', '+'},
{',', '-', '.', '/', ':', ';', '<', '='},
{'>', '?', '@', '[', '\\', ']', '^', '_'}};

static char* polybe(char* msg) {

    int sz = 0;
    char* m = msg;
    while(*m != '\0') {
        sz++;
        m++;
    }
    
    char* res = malloc((2 * sz + 1) * sizeof(char));
    if (res == NULL) {
        perror("Polybe 00");
        exit(23);
    }
    
    char c;
    int i = sz;
    char* m1 = msg;
    char* m2 = res;
    while(i != 0) {
        i--;
        c = *m1;
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < 8; k++) {
                if (square[j][k] == c) {
                *m2++ = '1' + j;
                *m2++ = '1' + k;
                break;
                }
            }
        }
        m1++;
    }
      
    *m2 = '\0';
    return res;
}

char* encrypt (char* msg) {
    return polybe(msg);
}

char* decrypt (char* msg) {
    int sz = 0;
    char* m = msg;
    while(*m != '\0') {
        sz++;
        m++;
    }
    
    char* res = malloc((sz / 2 + 1) * sizeof(char));
    if (res == NULL) {
        perror("Polybe error");
        exit(23);
    }
    
    char c1, c2;
    int i = sz;
    char* m1 = msg;
    char* m2 = res;
    while(i != 0) {
        i -= 2;
        c1 = *m1++ - '1';
        c2 = *m1++ - '1';
        *m2++ = square[c1][c2];
    }
      
    *m2 = '\0';
    return res;
}