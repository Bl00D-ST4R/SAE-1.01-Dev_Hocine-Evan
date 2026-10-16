#include <stdio.h>
#include <string.h>
#include <assert.h>
#pragma warning(disable:4996)

enum { //Je me suis permis de rajouter true/false pour les booléens
	//strcmp renvoie 0 lorsque les deux str sont identiques... Donc ça donne un truc bizarre avec les TRUE FALSE 
	STRCMP_TRUE = 0,
	STRCMP_FALSE = 1,
	//C'est plus clair pour nous
	TRUE = 1,
	FALSE = 0,
	MAX_TAILLECMD = 31,
	MAX_ETUDIANTS = 100,
	MAX_PARTICIPANTS = 100,
	MAX_NOM_CONCOURS = 30 + 1,
	MAX_PRENOM_JOUEUR = 30 + 1,
	MAX_NOM_JOUEUR = 30 + 1,
	MAX_NOMBRE_CONCOURS = 20,
};

typedef struct { //structure pour un seul participant
	char nom_joueur[MAX_NOM_JOUEUR];
	char prenom_joueur[MAX_PRENOM_JOUEUR];
}Participant;

typedef struct { //structure qui reunit tout les participants pour eviter de les mettre dans une tableau 
	int nbParticipants;
	Participant participants[MAX_PARTICIPANTS];
}Liste_participants;

void inscrire(liste) {
	Participant temp;
	printf("saisir votre nom et prenom:\n");
	scanf("%s %s", temp.nom_joueur, temp.prenom_joueur);
	
	/*
	if (verification(/*temp, liste_p )) {
		printf("Inscription enregistree(%d)");
	}
	else {
	}
	*/
}
char verification() {

}

int main() {
	char saisie[MAX_TAILLECMD];
	Liste_participants liste_participants;
	//définition des pointeurs
	int *p_liste = &liste_participants;
	//on initialise tous les participants à NULL pour simplifier tkt Hocine je fais après
	//init_liste();
	do {
		//Liste des fonctions pour l'utilisateur
		printf("Voici les differentes commandes:\nEXIT\nINSCRIRE\nPARTICIPANTS\nCREER\nCONCOURS\nGAIN\nSCORES\nCLASSEMENT\nCOMPARAISON\nBILAN\nVeuillez entre une de ces commandes:\t ");
		scanf("%s", saisie);
		if (strcmp(saisie, "INSCRIRE" == STRCMP_TRUE)) {
			inscrire(&p_liste);
		}else{}

	} while (strcmp(saisie, "EXIT" == STRCMP_FALSE)); 
}
