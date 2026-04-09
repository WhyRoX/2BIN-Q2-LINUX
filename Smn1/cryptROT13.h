#ifndef _CRYPTROT13_H_
#define _CRYPTROT13_H_

/** 
 * Read a character chain and return it as its crypted version
 * PRE: msg : char array
 * POST: a string has been crypted using rot13
 * RES: returns the crypted msg
 */
char* encrypt (char* msg);

/** 
 * Read a crypted character chain and return it as a normal character chain
 * PRE: msg : char array
 * POST: a string has been decrypted using rot13
 * RES: returns the decrypted msg
 */
char* decrypt (char* msg);

#endif  // _CRYPTROT13_H_
