#include <stdbool.h>

#ifndef _BIBLIO_H
#define _BIBLIO_H

typedef enum {
    BANDE_DESSINEE, POESIE, THEATRE, ROMAN_HISTORIQUE, 
    LITTERATURE_FRANCAISE, LITTERATURE_ETRANGERE, SCIENCES, INFORMATIQUE, 
    SCIENCE_FICTION, SANTE, HISTOIRE
} Genre;

typedef struct
{
    char titre[128];
    char auteur[80];
    long int isbn;
    char editeur[50];
    int annee_edition;
    Genre genre;
} Livre;

/**
 * Reads a book from the input.
 * PRE: None
 * POST: A book has been read from the input.
 * RES: Returns true if the book was successfully read, false otherwise.
 */
bool lireLivre();

/**
 * Converts a string to a Genre enum.
 * PRE: str: a valid string representing a genre
 * POST: None
 * RES: Returns the corresponding Genre enum value.
 */
Genre str2genre(char *str);

/**
 * Converts a Genre enum to a string.
 * PRE: genre: a valid Genre enum value
 * POST: None
 * RES: Returns a string representation of the genre.
 */
char const* genre2str(Genre genre);

/**
 * Converts a Livre struct to a string.
 * PRE: livre: a valid Livre struct
 * POST: None
 * RES: Returns a string representation of the book.
 */
char* livre2str(Livre livre);

/**
 * Displays the library.
 * PRE: biblio: an array of Livre structs
 *      nbLivres: the number of books in the library
 * POST: The library has been displayed.
 * RES: None
 */
void afficherBib (Livre *biblio, int nbLivres);

/**
 * Adds a book to the library.
 * PRE: livre: a valid Livre struct
 * POST: The book has been added to the library.
 * RES: Returns true if the book was successfully added, false otherwise.
 */
bool ajouterLivre(Livre **biblio, int *nbLivres, int *taillePhysique, Livre livre);

#endif