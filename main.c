#include <stdio.h>
#include <string.h>
#include <assert.h>
#pragma warning(disable:4996)

//===========================================================
// TRUCS PRIOS A FAIRE 
//===========================================================
//EVAN : BILAN + rapport + gihtub
//HOCINE : FINIT SP3 PENDANT QUE JE FAIS BILAN

//J'ai refait les séparateurs c'est + joli
//Verif taille servait à rien vu qu'on  a le droit à strlen donc je l'ai viré
//Init liste servait à rien aussi donc au revoir
//J'ai refait la structure de tout le programme c'est plus propre et lisible
//Oublie pas const quand on ne modifie rien sinon on perd des points
//Aussi j'ai changé le type de certaines fonctions genre char verif => int verif

//J'ai mis des asserts un peu partout
//Evan : J'ai retiré la plupart des printfs non demandés dans la docu pour éviter tout problème avec les inout

//FAUT LOCKIN C'EST A RENDRE CE SOIR
//LE RAPPORT AUSSI

//===========================================================
// ENUM ET CONSTANTES ET STRUCTURES
//===========================================================

enum {
    MAX_TAILLECMD = 31,// 30 caracteres + '\0' car str (pareil pour toutes les srting)  
    MAX_PARTICIPANTS = 100,
    MAX_NOM_CONCOURS = 31,
    MAX_PRENOM_JOUEUR = 31,
    MAX_NOM_JOUEUR = 31,
    MAX_NOMBRE_CONCOURS = 20
};

typedef struct {
    char nom_joueur[MAX_NOM_JOUEUR];
    char prenom_joueur[MAX_PRENOM_JOUEUR];
    int scores[MAX_NOMBRE_CONCOURS];
}Participant;

typedef struct {
    int nbParticipants;
    Participant participants[MAX_PARTICIPANTS];
}Liste_participants;

typedef struct {
    char Nom_concours[MAX_NOM_CONCOURS];
}Concours;

typedef struct {
    int nbConcours;
    Concours concours[MAX_NOMBRE_CONCOURS];
}Liste_concours;

//============================================================
// FONCTIONS DE LA STRUCT PARTICIPANTS 
//============================================================ 

//Verifie que le participant ai une place dans la liste et qu'il n'est pas deja inscrit
int verif_p(const Participant* p, const Liste_participants* lp) {
    //on regarde si le participant est deja inscrit
    for (int i = 0; i < lp->nbParticipants; ++i) {
        if (strcmp(p->prenom_joueur, lp->participants[i].prenom_joueur) == 0 && strcmp(p->nom_joueur, lp->participants[i].nom_joueur) == 0) {
            return 0; //le participant est deja inscrit
        }
    }
    return 1; //le participant n'est pas inscrit
}

//Commande INSCRIRE
void inscrire(Liste_participants* lp) {
    //Création d'un participant temporaire pour les tests que l'on ajoutera ensuite dans la liste des participants si tout est raccord
    Participant temp;
    //on verifie que la taille du tableau est valide et que le max de participants n'est pas atteint
    assert(lp->nbParticipants >= 0 && lp->nbParticipants < MAX_PARTICIPANTS);
    //le 30s permet de couper la str et garder que la taille limite donc ça evite les erreurs
    scanf("%30s %30s", temp.prenom_joueur, temp.nom_joueur);
    //du coup les asserts ne servent pas trop à grand chose mais bon ils sont obligatoires
    assert(strlen(temp.prenom_joueur) <= MAX_PRENOM_JOUEUR);
    assert(strlen(temp.nom_joueur) <= MAX_NOM_JOUEUR);
    //on met 0 partout dans les scores meme pour les concours qui existent pas encore
    for (int i = 0; i < MAX_NOMBRE_CONCOURS; ++i) {
        temp.scores[i] = 0;
    }
    //Si tout est raccord alors on finalise l'inscription sinon on dit que c'est incorrect
    if (verif_p(&temp, lp)) {
        lp->participants[lp->nbParticipants] = temp; //On copie le participant temporaire dans la liste
        ++lp->nbParticipants;
        printf("Inscription enregistree (%d)\n", lp->nbParticipants);
    }
    else {
        printf("Nom incorrect\n");//si verif false
    }
}

//Pour afficher le nombre de concours ou le participant a un score non nul
int compte_non_nul(const Participant* p, const Liste_concours* lc) {
    int c = 0;
    for (int i = 0; i < lc->nbConcours; ++i){
        if (p->scores[i] != 0) {//Si le score est nul alors on incrémente
            ++c;
        }
    }
    return c;
}

//Commande PARTICIPANTS
void affiche_participants(const Liste_participants* lp,const Liste_concours* lc) {
    //Si personne est inscrit
    if (lp->nbParticipants == 0) {
        printf("Aucun participant inscrit\n");
        return;
    }
    //On compte les concours ou le participant a un score non nul
    for (int i = 0; i < lp->nbParticipants; ++i) {
        int n = compte_non_nul(&lp->participants[i], lc);
        printf("(%d) %s %s : %d concours\n",i + 1,lp->participants[i].prenom_joueur,lp->participants[i].nom_joueur,n);
    }
    return;
}

//===========================================================
// FONCTIONS DE LA STRUCT CONCOURS
//===========================================================

//Commande CREER
void creer(Liste_concours* lc) {
    char nom[MAX_NOM_CONCOURS];
    //On verifie que le max concours n'est pas atteint
    //On aurait pu mettre unsigned à la place de >=0 comme ça on aurait été sur de travailler qu'avec des positifs
    assert(lc->nbConcours >= 0 && lc->nbConcours < MAX_NOMBRE_CONCOURS);
    scanf("%30s", nom);//Encore une fois grace au 30s le assert ne sert pas à grand chose
    assert(strlen(nom) <= MAX_NOM_CONCOURS);
    //pas besoin de faire une sous fonction comme verif car y'a juste un str à comparer
    for (int i = 0; i < lc->nbConcours; ++i) {
        if (strcmp(nom, lc->concours[i].Nom_concours) == 0) {
            printf("Nom incorrect\n");
            return;
        }
    }
    //Si le concours n'est pas deja dans la liste concours
    strcpy(lc->concours[lc->nbConcours].Nom_concours, nom);
    ++lc->nbConcours;
    printf("Creation enregistree (%d)\n", lc->nbConcours);
    return;
}

//Compte le nombre de participants ayant un score non nul dans un concours
int p_non_nul(const Liste_participants* lp, int indice_concours){
    int n = 0;
    for (int i = 0; i < lp->nbParticipants; ++i) {
        if (lp->participants[i].scores[indice_concours] != 0) {
            ++n;
        }
    }
    return n;
}

//Commande CONCOURS
void affiche_concours(const Liste_concours* lc, const Liste_participants* lp) {
    //Quand il n'y a pas de concours 
    if (lc->nbConcours == 0){
        printf("Aucun concours cree\n");
        return;
    }
    for (int i = 0; i < lc->nbConcours; ++i) {
        int n = p_non_nul(lp, i);
        printf("(%d) %s : %d participants\n",i + 1,lc->concours[i].Nom_concours,n);
    }
    return;
}

//===========================================================
// FONCTIONS GAIN ET SCORE SP2 FAIT PAR HOCINE
//===========================================================

//Utilisée par gain et score donc autant en faire une fonction
int verif_idp(int idp, Liste_participants* lp) {
    if (idp < 1 || idp > lp->nbParticipants) {
        return 1;
    }
    return 0;
}

//Commande GAIN
void gain(Liste_participants* lp, const Liste_concours* lc) {
    //Variables temporaires que l'user va rentrer
    int idp, idc, pts;
    scanf("%d %d %d", &idp, &idc, &pts);

    //Teste s'il ya a un participants à l'id demandé
    if (verif_idp(idp, lp)) {
        printf("Participant incorrect\n");
        return;
    }
    //Pareil pour concours
    if (idc < 1 || idc > lc->nbConcours) {
        printf("Concours incorrect\n");
        return;
    }
    //Pas possible d'avoir des points négatifs sauf evan en dictée ce dyslexique
    if (pts <= 0) {
        printf("Points incorrects\n");
        return;
    }
    //Quand tout est bon rajout des points
    lp->participants[idp - 1].scores[idc - 1] += pts;
    printf("Gain enregistre\n");
}

//Commande SCORES
void affiche_scores(const Liste_participants* lp, const Liste_concours* lc) {
    int idp;
    scanf("%d", &idp);
    //Teste s'il ya a un participants à l'id demandé
    if (verif_idp(idp, lp)) {
        printf("Identifiant incorrect\n");
        return;
    }
    //Pour eviter de recopier &lp->participants[idp - 1] à chaque fois
    const Participant* p = &lp->participants[idp - 1];
    printf("%s %s\n", p->prenom_joueur, p->nom_joueur);

    //Pour verifier si le participant a des points
    int a_pts = 0;
    for (int i = 0; i < lc->nbConcours; ++i) {
        if (p->scores[i] != 0) {
            a_pts = 1;
            printf("(%d) %s : %d points\n",i + 1,lc->concours[i].Nom_concours,p->scores[i]);
        }
    }
    //Quand le participant n'a pas de points dans tout les concours
    if (!a_pts) {
        printf("Aucun gain\n");
    }
}

//===========================================================
// BOUCLE PRINCIPALE AVEC MAIN ET INVITE DE COMMANDE
//===========================================================

int main(void) {
    //initialisation des structs et leurs pointeurs
    Liste_participants liste_participants;
    int* p_liste = &liste_participants;
    liste_participants.nbParticipants = 0;
    Liste_concours liste_concours;
    int* p_concours = &liste_concours;
    liste_concours.nbConcours = 0;
    //Boucle principale avec invite de commande
    char saisie[MAX_TAILLECMD];
    do {
        //Encore une fois apparrement on veut pas que ça apparaisse dans le out donc c'est ciao ma jolie UI ;_;
        //Liste des fonctions pour l'utilisateur
        //printf("Voici les differentes commandes:\nEXIT\nINSCRIRE\nPARTICIPANTS\nCREER\nCONCOURS\nGAIN\nSCORES\nCLASSEMENT\nCOMPARAISON\nBILAN\nVeuillez entre une de ces commandes:\n");
        scanf("%30s", saisie);//On verifie quand meme la taille
        if (strcmp(saisie, "INSCRIRE") == 0) {
            inscrire(p_liste);
        }
        else if (strcmp(saisie, "PARTICIPANTS") == 0) {
            affiche_participants(p_liste, p_concours);
        }
        else if (strcmp(saisie, "CREER") == 0) {
            creer(p_concours);
        }
        else if (strcmp(saisie, "CONCOURS") == 0) {
            affiche_concours(p_concours, p_liste);
        }
        else if (strcmp(saisie, "GAIN") == 0) {
            gain(p_liste, p_concours);
        }
        else if (strcmp(saisie, "SCORES") == 0) {
            affiche_scores(p_liste, p_concours);
        }
    } while (strcmp(saisie, "EXIT") != 0);
    return 0;
}
