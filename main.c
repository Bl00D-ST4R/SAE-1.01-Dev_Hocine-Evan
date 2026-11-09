#include <stdio.h>
#include <string.h>
#include <assert.h>
#pragma warning(disable:4996)

//=========================================================== TRUC PRIO A FAIRE : ========================================================================

//EVAN : FINIR LA FONCTION VERIFICATION_PARTICIPANTS 
//HOCINE : faire les trucs de la struc concours avec les fonctions et tout en suivant le modèle de participant


//=========================================================== ENUM ET CONSTANTES ET STRUCTS ===============================================================

enum {
	/*
	//Je me suis permis de rajouter true/false pour les booléens
	//strcmp renvoie 0 lorsque les deux str sont identiques... Donc ça donne un truc bizarre avec les TRUE FALSE
	STRCMP_TRUE = 0,
	STRCMP_FALSE = 1,
	//C'est plus clair pour nous
	TRUE = 1,
	FALSE = 0,*/
	//Au final mr De Botton a dit 0 et 1 c'est pas des nombres magiques doooonc bon je les mets en comments en attendant
	MAX_TAILLECMD = 31,
	MAX_ETUDIANTS = 100, //il sert à quoi lui ???
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

// à virer dans le rendu final 
void exemple_de_fonction_qui_marche(int YaRienQuiMarchePtdrr){
	printf("On fait genre ça marche tkt");
}
//Dès qu'un truc marche à 100% Tu le mets là on touche pu sauf exceptions mais c'est moi qui gère dans ce cas

//Fonction qui initialise la liste des participants avec nb participants à 0 
//et le tableau participant à des valeurs Null ou placeholder partout pour faciliter les comparaisons et le remplissage ultérieur
//On va faire pareil pour concours donc retient bien comment ça marche
//Fin la logique derrière au moins stp
void init_participants(Liste_participants* lp) {
	lp->nbParticipants = 0;
	Participant placeholder;
	//au debut j'ai essayé avec placeholder.nom_joueur = "NULL" mais j'avais oublié que fallait mettre strcpy *emoji clown*
	strcpy(placeholder.nom_joueur, "NULL");
	strcpy(placeholder.prenom_joueur, "NULL");
	for (int i = 0;i < MAX_PARTICIPANTS;++i) {
		lp->participants[i] = placeholder;
	}
}

//============================================================ FONCTIONS IMPORTANTES ======================================================================
//Pour les fonctions ou tu touches pas au truc juste tu regardes les données mets const 
char verif_p(const Participant* p, const Liste_participants* lp) {
	//verifie qu'on puisse ou non inscrire ce putain de participant temporaire

	if (lp->nbParticipants < MAX_PARTICIPANTS) { //deja on verifie que y'ai la place pour inscrire le boug

	}
	return 0;
}

void inscrire(Liste_participants* lp) {
	//à virer après hein
	printf("LOREM IPSUM VOTEZ LFI\n");
	//Création d'un participant temporaire pour les test que l'on ajoutera ensuite dans la liste des participants si tout est raccord
	Participant temp;
	do{ //Boucle qui demande le nom et prénom du participant tant que la taille n'est pas respectée
		printf("Saisir votre nom et prenom:\n");
		scanf("%s %s", temp.nom_joueur, temp.prenom_joueur);
	//Verifie que ça dépasse pas la taille
	//A mettre plus tard dans verif_taille pour la proprete stv mais eeeeh 
	} while ((((sizeof(temp.nom_joueur) / sizeof(temp.nom_joueur[0])) < MAX_NOM_JOUEUR) && (((sizeof(temp.prenom_joueur) / sizeof(temp.prenom_joueur[0]))) < MAX_PRENOM_JOUEUR)));
	
	
	//JUSQUE LA CA MARCHE========================================================================

	int indice_nv = lp->nbParticipants;
	if (verif_p(&temp, lp )) {
		lp->participants[indice_nv] = temp ;
		++lp->nbParticipants;
		printf("Inscription enregistree du participant n° %d");
	}
	else {
	}

}


//============================================================ FONCTION MAIN BOUCLE PRINCIPALE =============================================================


int main() {
	//Initialisation de la struct participants avec déclaration, pointeur, et fonction init (voir la fonction meme pour explications)
	Liste_participants liste_participants;
	int* p_liste = &liste_participants;
	init_participants(p_liste);
	
	//on initialise tous les participants à NULL pour simplifier tkt Hocine je fais après

	Liste_concours liste_concours;

	//Boucle principale 
	char saisie[MAX_TAILLECMD];
	do {
		//Liste des fonctions pour l'utilisateur
		printf("Voici les differentes commandes:\nEXIT\nINSCRIRE\nPARTICIPANTS\nCREER\nCONCOURS\nGAIN\nSCORES\nCLASSEMENT\nCOMPARAISON\nBILAN\nVeuillez entre une de ces commandes:\n");
		scanf("%s", saisie);
		if (strcmp(saisie, "INSCRIRE") == 0) {
			inscrire(p_liste);
		}
		if (strcmp(saisie, "PARTICIPANTS") == 0) {
			//affiche_participants(p_liste);
		}
		else {
			printf("Saisie incorrecte ! Merci de bien vouloir réessayer\n");
		}

	} while (strcmp(saisie, "EXIT") == 1);
	printf("FIN DE PROGRAMME");
}


//========================================= FOURRE TOUT AVEC LES TRUCS QUI SERVENT A RIEN POUR L'INSTANT====================

char verif_taille(int taille, int max) {
	if (taille < max) {
		return 1;
	}
	else { return 0; }
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
