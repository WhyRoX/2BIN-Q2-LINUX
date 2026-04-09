#include <stdio.h>
#include <stdlib.h>
#include "biblio.h"
#include "utils_v1.h"
#include <string.h>

#define MAX_LIVRES 2
#define MAX_TITRE 128
#define MAX_AUTEUR 50
#define MAX_EDITEUR 50

char const* genres_map[] = {
    "Bande dessinée",
    "Poésie",
    "Théatre",
    "Roman historique",
    "Littérature francaise",
    "Littérature étrangère",
    "Sciences",
    "Informatique",
    "Science-fiction",
    "Santé",
    "Histoire",
    NULL
};

int main(int argc, char const *argv[]) {
    Livre *biblio = malloc(MAX_LIVRES * sizeof(Livre)); // = NULL marche aussi car realloc au moment de l'ajout
    int taillePhysique = MAX_LIVRES;
    int nbLivres = 0;
    Livre livre;
    while (lireLivre(&livre))
    {
        if (!ajouterLivre(&biblio, &nbLivres, &taillePhysique, livre))
        {
            printf("Bibilio full???????\n");
            break;
        }
    }

    //printf("%d\n", nbLivres);
    afficherBib(biblio, nbLivres);

    free(biblio);
    return 0;
}
// lire en C : char* buffer[45], buffer est un tableau de 45 qui contient des pointeurs vers des char

// bool lireLivre(Livre *l) {
//     // buffer de lecture
//     char ligne[MAX_TITRE+2];

//     // lecture du titre
//     if (readLimitedLine(ligne, MAX_TITRE+2) <= 0) return false;
//     strcpy(l->titre, ligne);

//     // lecture de l'auteur
//     if (readLimitedLine(ligne, MAX_AUTEUR+2) <= 0) return false;
//     strcpy(l->auteur, ligne);

//     // lecture de l'isbn
//     if (scanf("%ld\n", &l->isbn) != 1) return false;

//     // lecture de l'éditeur
//     if (readLimitedLine(ligne, MAX_EDITEUR+2) <= 0) return false;
//     strcpy(l->editeur, ligne);

//     // lecture de l'année
//     if (scanf("%d\n", &l->annee_edition) != 1) return false;

//     // lecture du genre
//     if (readLimitedLine(ligne, MAX_TITRE+2) <= 0) return false;
//     if ((l->genre = str2genre(ligne)) == -1) return false;

//     // on va skip la ligne vide
//     if (fgets(ligne, sizeof(ligne), stdin) == NULL) return false;


//     return true;
// }

bool lireLivre(Livre *l) {
    // buffer de lecture
    char ligne[MAX_TITRE+2];

    // lecture du titre
    if (readLimitedLine(ligne, MAX_TITRE+2) <= 0) {
        printf("Failed to read title\n");
        return false;
    }
    strcpy(l->titre, ligne);

    // lecture de l'auteur
    if (readLimitedLine(ligne, MAX_AUTEUR+2) <= 0) {
        printf("Failed to read author\n");
        return false;
    }
    strcpy(l->auteur, ligne);

    // lecture de l'isbn
    if (fgets(ligne, sizeof(ligne), stdin) == NULL) {
        printf("Failed to read ISBN line\n");
        return false;
    }
    l->isbn = strtol(ligne, NULL, 10);
    if (l->isbn == 0 && (ligne[0] != '0' || ligne[1] != '\n')) {
        printf("Failed to convert ISBN: %s\n", ligne);
        return false;
    }

    // lecture de l'éditeur
    if (readLimitedLine(ligne, MAX_EDITEUR+2) <= 0) {
        printf("Failed to read editor\n");
        return false;
    }
    strcpy(l->editeur, ligne);

    // lecture de l'année
    if (fgets(ligne, sizeof(ligne), stdin) == NULL) {
        printf("Failed to read year line\n");
        return false;
    }
    l->annee_edition = strtol(ligne, NULL, 10);
    if (l->annee_edition == 0 && (ligne[0] != '0' || ligne[1] != '\n')) {
        printf("Failed to convert year: %s\n", ligne);
        return false;
    }

    // lecture du genre
    if (readLimitedLine(ligne, MAX_TITRE+2) <= 0) {
        printf("Failed to read genre\n");
        return false;
    }
    if ((l->genre = str2genre(ligne)) == -1) {
        printf("Failed to convert genre\n");
        return false;
    }

    // on va skip la ligne vide
    if (fgets(ligne, sizeof(ligne), stdin) == NULL) {
        printf("Failed to skip empty line\n");
        return false;
    }

    return true;
}

Genre str2genre(char *str)
{
    char const** it = genres_map;

    int i = 0;
    while(*it){
        if (strcmp(str, *it) == 0)
            return i;
        it++;
        i++;
    }
    printf("Genre non reconnu %s\n", str);
    return -1;
}

char const* genre2str(Genre genre)
{
    return genres_map[genre];
}

char* livre2str(Livre livre)
{
    char *str = malloc(512 * sizeof(char));
    if (str == NULL)
    {
        printf("Erreur malloc\n");
        return NULL;
    }
    
    sprintf(str, "Titre: %s\nAuteur: %s\nISBN: %ld\nEditeur: %s\nAnnée: %d\nGenre: %s\n",
            livre.titre, livre.auteur, livre.isbn, livre.editeur, livre.annee_edition, genre2str(livre.genre));
    return str;
}

void afficherBib(Livre *biblio, int nbLivres)
{
    for (int i = 0; i < nbLivres; i++)
    {
        char *livreStr = livre2str(biblio[i]);
        printf("%s\n", livreStr);
        free(livreStr);
    }
}

bool ajouterLivre(Livre **biblio, int *nbLivres, int *taillePhysique, Livre livre)
{
    if (*nbLivres == *taillePhysique)
    {
        printf("reallocating\n");
        *taillePhysique *= 2;
        *biblio = realloc(*biblio, *taillePhysique * sizeof(Livre));
        if (*biblio == NULL)
        {
            printf("Erreur réalloc\n");
            return false;
        }
    }
    (*biblio)[*nbLivres] = livre;
    *nbLivres = *nbLivres+1;
    return true;
}
