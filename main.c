#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// CRÉATION ENTITÉS
// Permet de créer les variables pour les statistiques des entités
typedef struct {
    int pv;
    int degats;
    int arme;
    int armure;
}Personnage;

// Permet d'initialiser les statistiques du joueur
void init_joueur (Personnage *j) {
    j->pv = 100;
    j->degats = 50;
    j->arme = 0;
    j->armure = 0;
}

// Permet d'initialiser les statistiques du monstre
void init_monstre (Personnage *m) {
    m->pv = 500;
    m->degats = 10;
    m->arme = 0;
    m->armure = 0;
}

// AFFICHAGES
// Permet d'afficher les PV du Joueur et du Monstre
void affichage_pv(Personnage joueur, Personnage monstre) {
    printf("Vos PV sont de %d (armure : %d ) \n",joueur.pv,joueur.armure);
    printf("Les PV du monstre sont de %d \n",monstre.pv);
}

// Permet d'afficher qui a gagné
void win_or_lose(Personnage joueur, Personnage monstre) {
    if (joueur.pv <= 0 && monstre.pv <= 0) {
        printf("Vous vous etes entre-tuer");
    }
    else if (monstre.pv <= 0) {
        printf("Vous avez gagne\n");
    }
    else {
        printf("Vous avez perdu\n");
    }
}

// Créer un coffre (~1 chance sur 3) et propose à l'utilisateur de l'ouvrir
void coffre(Personnage *j) {
    int nombre = rand() % 10;
    int choix_coffre = 0;
    if (nombre < 3) {
        printf("Vous etes tombe sur un coffre, voulez vous l'ouvrir (1 : OUI 2 : NON) \n");
        scanf("%d", &choix_coffre);
        if (choix_coffre == 1) {
            if (rand()%2 == 1) {
                j->armure +=2;
                printf("Tresor ! +2 d'armure.\n");
            }
            else {
                j->pv -= 15;
                printf("Piege ! -15 PV.\n");
            }
        }
    }
}

// JEU
int main(){

    // Appel de la stucture qui définit les personnages
    Personnage joueur;
    Personnage monstre;

    // Appel de la fonction qui initialise les statistiques
    init_joueur(&joueur);
    init_monstre(&monstre);

    // Permet au nombre random d'être différent à chaque partie
    srand(time(NULL));
    int choix_combat = 0;

    while (joueur.pv > 0 && monstre.pv > 0) {

        affichage_pv(joueur,monstre);

        coffre(&joueur);
        if (joueur.pv <= 0) {
            break;
        }

        printf("Quel choix d'attaque ? (1 : 50 degats | 2 : 100 degats, 1 chance sur 2)\n");
        scanf("%d",&choix_combat);
        if (choix_combat==1) {
            monstre.pv -= joueur.degats;
            joueur.pv -= monstre.degats - joueur.armure;
        }
        else if (choix_combat==2) {
            if (rand()%2==1) {
                monstre.pv -= joueur.degats*2;
                joueur.pv -= monstre.degats - joueur.armure;
            }
            else {
                joueur.pv -= monstre.degats;
            }
        }
    }
    win_or_lose(joueur,monstre);
}