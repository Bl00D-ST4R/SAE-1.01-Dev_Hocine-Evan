#include <stdio.h>
#include <string.h>
#include <assert.h>
#pragma warning(disable:4996)


//=========================================================== ENUM ET CONSTANTES ET STRUCT ===============================================================

enum {
	/*
	//Je me suis permis de rajouter true/false pour les booléens
	//strcmp renvoie 0 lorsque les deux str sont identiques... Donc ça donne un truc bizarre avec les TRUE FALSE
	STRCMP_TRUE = 0,
	STRCMP_FALSE = 1,
	//C'est plus clair pour nous
	TRUE = 1,
	FALSE = 0,*/
	MAX_TAILLECMD = 31,
	MAX_ETUDIANTS = 100,
	MAX_PARTICIPANTS = 100,
	MAX_NOM_CONCOURS = 30 + 1,
	MAX_PRENOM_JOUEUR = 30 + 1,
	MAX_NOM_JOUEUR = 30 + 1,
	MAX_NOMBRE_CONCOURS = 20,
};

//structure pour un seul participant
typedef struct { 
	char nom_joueur[MAX_NOM_JOUEUR];
	char prenom_joueur[MAX_PRENOM_JOUEUR];
}Participant;

//structure qui reunit tout les participants pour eviter de les mettre dans un tableau 
typedef struct { 
	int nbParticipants;
	Participant participants[MAX_PARTICIPANTS];
}Liste_participants;

//meme type de structure pour les autres trucs
typedef struct {
	char Nom_concours[MAX_NOM_CONCOURS];
	unsigned int nb_participants_concours;
}Concours;
typedef struct {
	int nb_concours;
	Concours concours[MAX_NOMBRE_CONCOURS];
}Liste_concours;


//============================================================ FONCTIONS QUI MARCHENT PAS TOUCHER =========================================================

//Exemple_de_fonction_qui_marche( int YaRienQuiMarchePtdrr){}

//============================================================ FONCTIONS IMPORTANTES ======================================================================


void inscrire(Liste_participants* lp) {
	printf("LOREM IPSUM VOTEZ LFI\n");
	Participant temp;
	//Boucle qui demande le nom et prénom du joueur tant que la taille n'est pas respectée
	do{
		printf("Saisir votre nom et prenom:\n");
		scanf("%s %s", temp.nom_joueur, temp.prenom_joueur);
	//Verifie que ça dépasse pas la taille
	} while ((((sizeof(temp.nom_joueur) / sizeof(temp.nom_joueur[0])) < MAX_NOM_JOUEUR) && (((sizeof(temp.prenom_joueur) / sizeof(temp.prenom_joueur[0]))) < MAX_PRENOM_JOUEUR)));
	
	//int a = verif_taille((sizeof(temp.nom_joueur) / sizeof(temp.nom_joueur[0]), MAX_PRENOM_JOUEUR));

	/*
	if (verification(temp, liste_p )) {
		printf("Inscription enregistree(%d)");
	}
	else {
	}
	*/
}
char verification() {

}

char verif_taille(int taille, int max) {
	if (taille < max) {
		return 1;
	}else{ return 0; }
}

/*
void Creation_concours() {
	Concours temp;
	printf("Saisir le nom d'un concours");
	scanf("%s", temp.Nom_concours);
	for (int i = 0; i <= MAX_NOMBRE_CONCOURS; ++i) {
		if (strcmp(temp.Nom_concours, AAAAAAAAAA[i].Nom_concours == 1)) {
			liste_concours[i].Nom_concours = temp.Nom_concours;
			printf("Creation enregistrée (%d) ", i);
		}
		else {
			printf("Nom incorrect");
		}
	}
}
*/


//============================================================ FONCTION MAIN BOUCLE PRINCIPALE ================================================================


int main() {
	char saisie[MAX_TAILLECMD];
	Liste_participants liste_participants;
	Liste_concours liste_concours;
	liste_participants.nbParticipants = 0;
	//définition des pointeurs
	int* p_liste = &liste_participants;
	//on initialise tous les participants à NULL pour simplifier tkt Hocine je fais après
	//init_liste();

	//Boucle principale 
	do {
		//Liste des fonctions pour l'utilisateur
		printf("Voici les differentes commandes:\nEXIT\nINSCRIRE\nPARTICIPANTS\nCREER\nCONCOURS\nGAIN\nSCORES\nCLASSEMENT\nCOMPARAISON\nBILAN\nVeuillez entre une de ces commandes:\n");
		scanf("%s", saisie);
		if (strcmp(saisie, "INSCRIRE") == 0) {
			inscrire(&liste_participants);
		}
		else {}

	} while (strcmp(saisie, "EXIT") == 1);
	printf("FIN DE PROGRAMME");
}
