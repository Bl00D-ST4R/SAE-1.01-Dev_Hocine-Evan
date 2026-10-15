#include <stdio.h>
#include <string.h>
#include <assert.h>
#pragma warning(disable:4996)

//Je me suis permis de rajouter true/false pour les booléens
enum { TRUE = 1, FALSE = 0, TAILLECMD = 31 };

int main() {
	char saisie[TAILLECMD];
	do {
		printf("Voici les differentes commandes:\nEXIT\nINSCRIRE\nPARTICIPANTS\nCREER\nCONCOURS\nGAIN\nSCORES\nCLASSEMENT\nCOMPARAISON\nBILAN\nVeuillez entrer une de ces commandes:\t ");
		scanf("%s", &saisie);
	} while (strcmp(saisie, "EXIT" != 0)); //dès que exit ça plante tout
}
