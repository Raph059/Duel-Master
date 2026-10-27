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

Personnage monstre[10] = {
    // EASY
    {500,10,0,0,0},
 {200,30,0,0,0},
 {1000,15,0,0,0},

    // MEDIUM
{400,20,0,10,0},
{300,35,0,0,0},

    // HARDCORE
{2000,10,0,0,0},
{120,50,0,0,0},
{250,15,0,30,0},
{600,40,0,0,0},
{1200,45,0,20,0},

};

// Initialisation du nombre de monstre en fonction du choix de difficulté choisi par l'utilisateur
int init_monstre () {
    int choix_difficulte=0;
    printf(" 1 | Easy - 3 monstres \n 2 | Medium - 5 monstres \n 3 | Hardcore - 10 monstres \n");
    printf("Choisissez votre niveau de difficulte : ");
    scanf ("%d", &choix_difficulte);

    switch (choix_difficulte) {
        case 1:
            return 3; // EASY - 3 monstres
        case 2:
            return 5; // MEDIUM - 5 monstres
        case 3:
            return 10; // HARDCORE - 10 monstres
        default:
            return 3; // Par défaut (EASY)
    }
}

// Permet d'initialiser les statistiques du joueur
void init_joueur (Personnage *j) {
    int choix_classe=0;
    printf("-------------------------------------------------------\n");
    printf("1 | Combattant | 120 PV | 50 ATK | 2 Armure | 1 Potion \n");
    printf("2 | Mage | 80 PV | 55 ATK | 4 Potions \n");
    printf("3 | Assassin | 75 PV | 75 ATK \n");
    printf("4 | Tireur | 95 PV | 55 ATK | 1 Armure | 2 Potion \n");
    printf("5 | Tank | 160 PV | 35 ATK | 4 Armure | 0 Potion \n");
    printf("------------------------------------------------------\n");
    printf("Choisissez votre classe : ");
    scanf ("%d", &choix_classe);

    switch (choix_classe) {
        case 1 :
            j->pv = 120;
            j->degats = 50;
            j->arme = 0;
            j->armure = 2;
            j->potion = 1;
            break;

        case 2:
            j->pv = 80;
            j->degats = 55;
            j->arme = 0;
            j->armure = 0;
            j->potion = 4;
            break;

        case 3:
            j->pv = 75;
            j->degats = 75;
            j->arme = 0;
            j->armure = 0;
            j->potion = 0;
            break;

        case 4:
            j->pv = 95;
            j->degats = 55;
            j->arme = 0;
            j->armure = 1;
            j->potion = 2;
            break;

        case 5:
            j->pv = 160;
            j->degats = 35;
            j->arme = 0;
            j->armure = 4;
            j->potion = 0;
            break;

        default:
            j->pv = 100;
            j->degats = 50;
            j->arme = 0;
            j->armure = 0;
            j->potion = 0;
            break;
    }
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
        printf("Vous etes mort\n");
    }
}

// Créer un coffre (~1 chance sur 3) et propose à l'utilisateur de l'ouvrir
void coffre(Personnage *j) {

    int choix_coffre = 0;
    int item_coffre = rand()%6;
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
                j->pv = j->pv/2 ;
                printf ("EXPLOSION !! \n");
                break;

            case 5:
                j->pv += 100;
                printf("SUPER HEAL !! (+100pv) \n");
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

    int attaque_joueur = j->degats + j->arme * 20; // Ajoute l'arme au dégâts de base du joueur
    int attaque_simple = attaque_joueur - m->armure; // Ajoute l'armure du monstre aux dégâts totaux
    int attaque_critique = (attaque_joueur * 2) - m->armure; // Ajoute l'armure du monstre aux dégâts totaux x2 (car coup critique)

    printf("Quel choix ? \n | 1 | Attaque simple %d degats \n | 2 | Attaque speciale %d degats, 1 chance sur 2 \n | 3 | Soigner (+30pv)\n",attaque_simple,attaque_critique);
    scanf("%d",&choix_combat);

    switch (choix_combat) {

        case 1:
            m->pv -= attaque_simple;
            j->pv -= degats_subis;
            break;

        case 2:
            if (rand()%2==1) {
                m->pv -= attaque_critique;
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
                j->pv += 30;
                j->potion -=1;
                printf ("Vous avez bu votre potion (+30pv)\n");
            }
            else {
                j->pv -= m->degats;
                printf ("Vous n'avez pas de potion\n");
            }
            break;

            default:
                j->pv -= degats_subis; //Empêche de spam un chiffre random pour attendre les coffres
                break;
    }
}

// JEU
int main(){

    // Appel de la stucture qui définit les personnages
    int index_monstre = 0;
    Personnage joueur;

    // Appel de la fonction qui initialise les statistiques
    int nb_monstres = init_monstre(); // Affecte le choix de difficulté du joueur (de init_monstre) à la variable du nb de monstre
    init_joueur(&joueur);

    // Permet au nombre random d'être différent à chaque partie
    srand(time(NULL));

    while (joueur.pv > 0 && index_monstre < nb_monstres) {

        //Affiche les PV du joueur et du monstre
        affichage_pv(joueur,monstre[index_monstre]);

        //Propose un coffre au joueur
        if (rand()%10<3) {
            coffre(&joueur);
            affichage_pv(joueur,monstre[index_monstre]);
            if (joueur.pv <= 0) {
                break;
            }
        }

        //Lance la mécanique de combat
        combat(&joueur,&monstre[index_monstre]);

        // Vérifie si le monstre est mort et passe au suivant
        if (monstre[index_monstre].pv <= 0) {
            printf("Vous avez vaincu le monstre !\n");
            index_monstre++; // Passe au monstre d'après
        }

    }

    //Affiche le message de fin gagné ou perdu
    if (index_monstre >= nb_monstres) {
        win_or_lose(joueur, monstre[nb_monstres - 1]);
    }
    else {
        win_or_lose(joueur, monstre[index_monstre]);
    }
}