/*
 * Fait par Baptiste PRUNIER
 * dernière modification le 21/03/2017
 */

#ifndef _INPUT_KLEVH_
#define _INPUT_KLEVH_

#include <stdio.h>
#include <stdlib.h>

/* liste de caractere utilisee pour la lecture d'une chaine de caractere
 * de taille inconnue
 */
typedef struct Element{
  struct Element *nxt;
  char c;
}Element;
typedef struct{
  Element *first;
  int taille;
}ListChar;

/* ----------------------------------------------------
 * Lecture d'une chaine de caractere de taille inconnue
 */
/*desalloue une liste de caractere*/
void freeListChar(ListChar);
/*transforme une liste de caractere en chaine de caractere si celle ci est bien construite, sinon NULL*/
char* ltoa(ListChar);
/*lit une chaine de caractere se terminant par end dans le fichier stream, enregistre sa taille dans n (si non NULL) et la retourne, retoune NULL si cela n'est pas possible. Ne ferme pas le fichier.*/
char* fread_str_(FILE *,int *n,char end);
/* appel fread_str_ avec FILE, NULL et \n si FILE est stdin, EOF sinon */
char * fread_str(FILE *);
/* appel fread_str_ avec stdin, NULL et \n */
char * read_str();
/* ouvre le fichier dont le chemin d'acces est passe en parametre et retourne le resultat de l'appel de fread_str_ avec ce fichier, NULL et EOF */
char * ofread_str(char *);
/* ----------------------------------------------------- */

/* -------------------------------------------
 * Lecture d'un nombre
 */
/* lit une ligne dans un fichier ouvert avant la fonction et la traduit en entier signe. Si cela n'est pas possible, retourne NULL, sinon le pointeur vers la valeur. Le fichier n'est pas ferme. */
int* read_int(FILE *);
/* lit une ligne dans un fichier ouvert avant la fonction et la traduit en flottant signe. Si cela n'est pas possible, retourne NULL, sinon le pointeur vers la valeur. Le fichier n'est pas ferme. */
float* read_float(FILE *);
/* ------------------------------------------- */

/* -------------------------------------------
 * Utilitaires
 */
/* parcours le fichier jusqu'a la fin de la ligne si il est stdin */
void viderBuffer(FILE *);
/* ------------------------------------------- */

#endif
