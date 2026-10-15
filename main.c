#include <stdio.h>
#include <string.h>
#include <assert.h>
#pragma warning(disable:4996)

//Je me suis permis de rajouter true/false pour les booléens
enum {  TRUE = 1, 
        FALSE = 0, 
		MAX_TAILLECMD = 31 
		MAX_TAILLECMD = 31,
		MAX_ETUDIANTS = 100,
		MAX_PARTICIPANTS = 100,
		MAX_NOM_CONCOURS = 30 + 1,
		MAX_PRENOM_JOUEUR = 30 + 1,
		MAX_NOM_JOUEUR = 30 + 1,
		MAX_NOMBRE_CONCOURS = 20,
};

int main() {
	char saisie[MAX_TAILLECMD];
	do {
		//Liste des fonctions pour l'utilisateur
		printf("Voici les differentes commandes:\nEXIT\nINSCRIRE\nPARTICIPANTS\nCREER\nCONCOURS\nGAIN\nSCORES\nCLASSEMENT\nCOMPARAISON\nBILAN\nVeuillez entre une de ces commandes:\t ");
		scanf("%s", saisie);
	} while (strcmp(saisie, "EXIT" != FALSE)); //strcmp renvoie 0 lorsque les deux str sont identiques... Donc ça donne un truc bizarre avec les TRUE FALSE 
}
