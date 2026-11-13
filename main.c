#include <stdio.h>
#include <string.h>
#include <assert.h>
#pragma warning(disable:4996)

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
    int anciennes_positions[MAX_NOMBRE_CONCOURS]; //Pour BILAN 
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
// FONCTIONS DE VERIFICATION DES IDENTIFIANTS
//============================================================

//Utilisee par gain et scores, renvoie 1 si l'identifiant participant est incorrect, 0 sinon
int verif_idp(int idp, const Liste_participants* lp) {
    if (idp < 1 || idp > lp->nbParticipants) {
        return 1;
    }
    return 0;
}

//Utilisee par gain, classement, comparaison et bilan, renvoie 1 si l'identifiant concours est incorrect, 0 sinon
int verif_idc(int idc, const Liste_concours* lc) {
    if (idc < 1 || idc > lc->nbConcours) {
        return 1;
    }
    return 0;
}

//============================================================
// FONCTIONS DE LA STRUCT PARTICIPANTS 
//============================================================ 

//Verifie que le participant n'est pas deja inscrit
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
void inscrire(Liste_participants* lp, const Liste_concours* lc) {
    //On verifie s'il reste de la place dans le tableau
    assert(lp->nbParticipants < MAX_PARTICIPANTS);
    //Création d'un participant temporaire pour les tests que l'on ajoutera ensuite dans la liste des participants si tout est raccord
    Participant temp;
    //le 30s permet de couper la str et garder que la taille limite donc ça evite les erreurs
    scanf("%30s %30s", temp.prenom_joueur, temp.nom_joueur);
    //on met 0 partout dans les scores meme pour les concours qui existent pas encore
    for (int i = 0; i < MAX_NOMBRE_CONCOURS; ++i) {
        temp.scores[i] = 0;
        //Le nouveau participant est a la derniere position dans chaque concours existant pour BILAN
        int n = 0;
        if (i < lc->nbConcours) {
            for (int j = 0; j < lp->nbParticipants; ++j) {
                if (lp->participants[j].scores[i] != 0) {
                    ++n;
                }
            }
        }
        temp.anciennes_positions[i] = n + 1;
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
    for (int i = 0; i < lc->nbConcours; ++i) {
        if (p->scores[i] != 0) {//Si le score est non nul alors on incrémente
            ++c;
        }
    }
    return c;
}

//Commande PARTICIPANTS
void affiche_participants(const Liste_participants* lp, const Liste_concours* lc) {
    //Si personne est inscrit
    if (lp->nbParticipants == 0) {
        printf("Aucun participant inscrit\n");
        return;
    }
    //On compte les concours ou le participant a un score non nul
    for (int i = 0; i < lp->nbParticipants; ++i) {
        int n = compte_non_nul(&lp->participants[i], lc);
        printf("(%d) %s %s : %d concours\n", i + 1, lp->participants[i].prenom_joueur, lp->participants[i].nom_joueur, n);
    }
}

//===========================================================
// FONCTIONS DE LA STRUCT CONCOURS
//===========================================================

//Commande CREER
void creer(Liste_concours* lc, Liste_participants* lp) {
    char nom[MAX_NOM_CONCOURS];
    //Idem que participants on verifie qu'il y a de la place pour le nouveau concours
    assert(lc->nbConcours < MAX_NOMBRE_CONCOURS);
    scanf("%30s", nom);
    //pas besoin de faire une sous fonction comme verif car y'a juste un str à comparer
    for (int i = 0; i < lc->nbConcours; ++i) {
        if (strcmp(nom, lc->concours[i].Nom_concours) == 0) {
            printf("Nom incorrect\n");
            return;
        }
    }
    //Si le concours n'est pas deja dans la liste concours
    strcpy(lc->concours[lc->nbConcours].Nom_concours, nom);
    //Tous les participants sont ex aequo en premiere position dans un nouveau concours
    for (int i = 0; i < lp->nbParticipants; ++i) {
        lp->participants[i].anciennes_positions[lc->nbConcours] = 1;
    }
    ++lc->nbConcours;
    printf("Creation enregistree (%d)\n", lc->nbConcours);
}

//Compte le nombre de participants ayant un score non nul dans un concours
int p_non_nul(const Liste_participants* lp, int indice_concours) {
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
    if (lc->nbConcours == 0) {
        printf("Aucun concours cree\n");
        return;
    }
    for (int i = 0; i < lc->nbConcours; ++i) {
        int n = p_non_nul(lp, i);
        printf("(%d) %s : %d participants\n", i + 1, lc->concours[i].Nom_concours, n);
    }
}

//===========================================================
// FONCTIONS GAIN ET SCORE SP2 FAIT PAR HOCINE
//===========================================================

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
    if (verif_idc(idc, lc)) {
        printf("Concours incorrect\n");
        return;
    }
    //Pas possible d'avoir des points négatifs
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
            printf("(%d) %s : %d points\n", i + 1, lc->concours[i].Nom_concours, p->scores[i]);
        }
    }
    //Quand le participant n'a pas de points dans tout les concours
    if (!a_pts) {
        printf("Aucun gain\n");
    }
}

//===========================================================
// FONCTIONS CLASSEMENT ET COMPARAISON 
//===========================================================

//On trie les participants par leur ordre dans le classement
int trie_classement(const Liste_participants* lp, int indice_concours, int ordre[]) {
    //On verifie que le concours existe 
    assert(indice_concours >= 0 && indice_concours < MAX_NOMBRE_CONCOURS);
    int n = 0;
    for (int i = 0; i < lp->nbParticipants; ++i) {
        int score = lp->participants[i].scores[indice_concours];
        if (score != 0) {
            int j = n;
            while (j > 0) {
                int precedent = ordre[j - 1];
                if (lp->participants[precedent].scores[indice_concours] >= score) {
                    break;//OUI C'est pas beau mais ça marche et on a plus le temps Hocine
                }
                ordre[j] = ordre[j - 1];
                --j;
            }
            ordre[j] = i;
            ++n;
        }
    }
    return n;
}

//Recalcule la position des participants en fonction de leur score
int position_actuelle(const Liste_participants* lp, int id_participant, int indice_concours) {
    //On verifie que le concours et le participants existent 
    assert(id_participant >= 0 && id_participant < lp->nbParticipants);
    assert(indice_concours >= 0 && indice_concours < MAX_NOMBRE_CONCOURS);
    int position = 1;
    int score = lp->participants[id_participant].scores[indice_concours];
    for (int i = 0; i < lp->nbParticipants; ++i) {
        if (lp->participants[i].scores[indice_concours] > score) {
            ++position;
        }
    }
    return position;
}

//Affiche le classement d'un concours ; bilan vaut 1 pour ajouter les places gagnees/perdues
void affiche_classement(Liste_participants* lp, const Liste_concours* lc, int idc, int bilan) {
    //On verifie que l'identifiant du concours est valide
    assert(!verif_idc(idc, lc));
    int indice_concours = idc - 1;
    int ordre[MAX_PARTICIPANTS];
    int n;
    int rang = 0;

    printf("%s\n", lc->concours[indice_concours].Nom_concours);
    n = trie_classement(lp, indice_concours, ordre);

    if (n == 0) {
        printf("Aucun participant\n");
    }
    else {
        for (int i = 0; i < n; ++i) {
            int idp = ordre[i];
            int score = lp->participants[idp].scores[indice_concours];
            int nb_ex_aequo = 0;

            //Le rang est celui de la premiere personne ayant ce score
            if (i == 0 || score != lp->participants[ordre[i - 1]].scores[indice_concours]) {
                rang = i + 1;
            }

            //On compte les participants ayant le meme score pour afficher "ex"
            for (int j = 0; j < n; ++j) {
                if (lp->participants[ordre[j]].scores[indice_concours] == score) {
                    ++nb_ex_aequo;
                }
            }

            if (bilan) {
                int places = lp->participants[idp].anciennes_positions[indice_concours] - rang;
                printf("%d%s -> (%d) %s %s : %d points : %+d places\n",
                    rang,nb_ex_aequo > 1 ? "ex" : "",idp + 1,lp->participants[idp].prenom_joueur,lp->participants[idp].nom_joueur,score,places);
            }
            else {
                printf("%d%s -> (%d) %s %s : %d points\n",rang,nb_ex_aequo > 1 ? "ex" : "",idp + 1,lp->participants[idp].prenom_joueur,lp->participants[idp].nom_joueur,score);
            }
        }
    }

    //On memorise les nouvelles positions pour la prochaine execution de BILAN
    //Si pas de score pour un participant il ne bouge pas
    if (bilan) {
        for (int i = 0; i < lp->nbParticipants; ++i) {
            if (lp->participants[i].scores[indice_concours] != 0) {
                lp->participants[i].anciennes_positions[indice_concours] =
                    position_actuelle(lp, i, indice_concours);
            }
        }
    }
}

//Commande CLASSEMENT
void classement(Liste_participants* lp, const Liste_concours* lc) {
    int idc;
    scanf("%d", &idc);
    if (verif_idc(idc, lc)) {
        printf("Identifiant incorrect\n");
        return;
    }
    affiche_classement(lp, lc, idc, 0);
}

//Commande COMPARAISON
void comparaison(const Liste_participants* lp, const Liste_concours* lc) {
    int idc1, idc2;
    int un_score = 0;
    int incompatibles = 0;
    scanf("%d %d", &idc1, &idc2);

    if (verif_idc(idc1, lc) || verif_idc(idc2, lc)) {
        printf("Identifiant incorrect\n");
        return;
    }

    for (int i = 0; i < lp->nbParticipants; ++i) {
        int score1 = lp->participants[i].scores[idc1 - 1];
        int score2 = lp->participants[i].scores[idc2 - 1];
        if (score1 != 0 || score2 != 0) {
            un_score = 1;
        }
        //Le concours 2 est affiche en premier : un score au concours 2 sans score au concours 1 est incompatible
        if (score2 != 0 && score1 == 0) {
            incompatibles = 1;
        }
    }

    //Le titre est affiche meme s'il n'y a aucun participant
    printf("%s versus %s\n", lc->concours[idc2 - 1].Nom_concours, lc->concours[idc1 - 1].Nom_concours);
    if (!un_score) {
        printf("Aucun participant\n");
        return;
    }
    if (incompatibles) {
        printf("Concours incompatibles\n");
        return;
    }
    for (int i = 0; i < lp->nbParticipants; ++i) {
        int score1 = lp->participants[i].scores[idc1 - 1];
        int score2 = lp->participants[i].scores[idc2 - 1];
        if (score1 != 0 || score2 != 0) {
            double pourcentage = score1 == 0 ? 0.0 : 100.0 * score2 / score1;
            printf("(%d) %s %s : %d points/%d points : %.2f%%\n",
                i + 1,
                lp->participants[i].prenom_joueur,
                lp->participants[i].nom_joueur,
                score2,
                score1,
                pourcentage);
        }
    }
}

//===========================================================
// FONCTION BILAN (Au final 90% du taff s'est fait dans les fonctions du SP3)
//===========================================================

//Commande BILAN
void bilan(Liste_participants* lp, const Liste_concours* lc) {
    int idc;
    scanf("%d", &idc);
    if (verif_idc(idc, lc)) {
        printf("Identifiant incorrect\n");
        return;
    }
    affiche_classement(lp, lc, idc, 1);
}

//===========================================================
// BOUCLE PRINCIPALE AVEC MAIN ET INVITE DE COMMANDE
//===========================================================

int main(void) {
    //initialisation des structs et leurs pointeurs
    Liste_participants liste_participants;
    Liste_participants* p_liste = &liste_participants;
    liste_participants.nbParticipants = 0;
    Liste_concours liste_concours;
    Liste_concours* p_concours = &liste_concours;
    liste_concours.nbConcours = 0;
    //Boucle principale avec invite de commande
    char saisie[MAX_TAILLECMD];
    do {
        scanf("%30s", saisie);//30s permet de limiter la taille de la str
        if (strcmp(saisie, "INSCRIRE") == 0) {
            inscrire(p_liste, p_concours);
        }
        else if (strcmp(saisie, "PARTICIPANTS") == 0) {
            affiche_participants(p_liste, p_concours);
        }
        else if (strcmp(saisie, "CREER") == 0) {
            creer(p_concours, p_liste);
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
        else if (strcmp(saisie, "CLASSEMENT") == 0) {
            classement(p_liste, p_concours);
        }
        else if (strcmp(saisie, "COMPARAISON") == 0) {
            comparaison(p_liste, p_concours);
        }
        else if (strcmp(saisie, "BILAN") == 0) {
            bilan(p_liste, p_concours);
        }
    } while (strcmp(saisie, "EXIT") != 0);
    return 0;
}
