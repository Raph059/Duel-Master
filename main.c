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
    int potion;
}Personnage;

// Permet d'initialiser les statistiques du joueur
void init_joueur (Personnage *j) {
    j->pv = 100;
    j->degats = 50;
    j->arme = 0;
    j->armure = 0;
    j->potion = 0;
}

// Permet d'initialiser les statistiques du monstre
void init_monstre (Personnage *m) {
    m->pv = 500;
    m->degats = 10;
    m->arme = 0;
    m->armure = 0;
    m->potion = 0;
}

// AFFICHAGES
// Permet d'afficher les PV du Joueur et du Monstre
void affichage_pv(Personnage joueur, Personnage monstre) {
    printf("Vos PV sont de %d (armure : %d | arme : %d | potion : %d) \n",joueur.pv,joueur.armure,joueur.arme,joueur.potion);
    printf("Les PV du monstre sont de %d \n",monstre.pv);
}

// Permet d'afficher qui a gagné
void win_or_lose(Personnage joueur, Personnage monstre) {
    if (joueur.pv <= 0 && monstre.pv <= 0) {
        printf("Vous vous etes entre-tuer\n");
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

    int choix_coffre = 0;
    int item_coffre = rand()%5;
    printf("Vous etes tombe sur un coffre, voulez vous l'ouvrir (1 : OUI 2 : NON) \n");
    scanf("%d", &choix_coffre);

    if (choix_coffre == 1) {
        switch (item_coffre) {

            case 0:
                j->armure +=2;
                printf("Tresor ! +2 d'armure \n");
                break;

            case 1:
                j->pv -= 15;
                printf("Piege ! (-15pv) \n");
                break;

            case 2:
                j->potion +=1;
                printf("Bravo, vous avez trouve une potion (+30pv) !\n");
                break;

            case 3:
                j->arme +=1;
                printf("Vous avez trouve une arme (+20 degats) !\n");
                break;

            case 4:
                j->pv = 0;
                printf ("EXPLOSION !! \n");
                break;

            default:
                break;
        }
    }
}

void combat (Personnage *j,Personnage *m) {

    //Vérification pour que l'armure ne heal pas si elle est supérieur aux dégâts du monstre
    int degats_subis = m->degats - j->armure;
    if (degats_subis < 0) {
        degats_subis =0;
    }

    int choix_combat = 0;
    int degats_joueur = j->degats + j->arme * 20;
    printf("Quel choix ? \n | 1 | Attaque simple %d degats \n | 2 | Attaque speciale %d degats, 1 chance sur 2 \n | 3 | Soigner (+30pv)\n",degats_joueur,degats_joueur*2);
    scanf("%d",&choix_combat);

    switch (choix_combat) {

        case 1:
            m->pv -= degats_joueur;
            j->pv -= degats_subis;
            break;

        case 2:
            if (rand()%2==1) {
                m->pv -= degats_joueur*2;
                printf("Coup critique !\n");
                j->pv -= degats_subis;
            }
            else {
                j->pv -= degats_subis;
                printf("Attaque ratee !\n");
            }
            break;

        case 3:
            if (j->potion>0) {
                j->pv -= degats_subis;
                j->pv += 30 + degats_subis;
                j->potion -=1;
                printf ("Vous avez bu votre potion (+30pv)\n");
            }
            else {
                j->pv -= m->degats;
                printf ("Vous n'avez pas de potion\n");
            }
            break;

        default:
            break;
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

    while (joueur.pv > 0 && monstre.pv > 0) {

        //Affiche les PV du joueur et du monstre
        affichage_pv(joueur,monstre);

        //Propose un coffre au joueur
        if (rand()%10<3) {
            coffre(&joueur);
            affichage_pv(joueur,monstre);
            if (joueur.pv <= 0) {
                break;
            }
        }

        combat(&joueur,&monstre);
    }
    win_or_lose(joueur,monstre);
}