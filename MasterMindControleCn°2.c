#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*1.Créer une nouvelle structure pour le jeu:*/
struct MasterMind
{
    int combiVrai[4]; //combinaison à deviner
    int nbEssaiRestant;
    int nbPartieGagne;
    int nbPartiePerdue;
    int combiJoueur[4]; //combinaison devinée par joueur
};

struct ResultatChance
{
    int nbChiffPlace; //nombre de bons chiffres bien placés
    int nbChiff; //nombres de bons chiffres mais pas bien placés
};

int gagne;//Pour déterminer si le joueur a gagné son jeu ou pas

/*4.Fonction qui renvoie le nombre de bon chiffres bien placés ainsi que mal placés*/
struct ResultatChance TestCombi(struct ResultatChance res, struct MasterMind jeu)
{
    int cpt;

    //initialiser les membres de res
    res.nbChiff =0;
    res.nbChiffPlace =0;

    //résultat de chaque combinaison entrée
    for (int iJ=0; iJ<4; iJ++)
    {
        if(jeu.combiJoueur[iJ]==jeu.combiVrai[iJ])
        {
            res.nbChiffPlace ++;
        }
        else
        {
            cpt =0;
            for(int iV=0; iV<4; iV++)
            {
                if(jeu.combiJoueur[iJ]==jeu.combiVrai[iV])
                {
                    cpt++;
                }
            }
            if(cpt>0)
            {
                res.nbChiff ++;//chaque chiffre mal placé est compté seulement 1 fois
            }
        }
    }
    printf("%d bons chiffres bien places, %d bons chiffres mal places\n", res.nbChiffPlace, res.nbChiff);

    if(res.nbChiffPlace==4)//Si le joueur a trouvé la bonne combinaison, il gagne! La partie s'arrete.
    {
        gagne = 1;
    }

    return res;
};

int main()
{
    srand(time(NULL));
    int reJouer = 0;

    //Initialiser la structure jeu
    struct MasterMind jeu;
    //Initialiser le nombre de parties gagnees et perdues
    jeu.nbPartieGagne = 0;
    jeu.nbPartiePerdue = 0;

    struct ResultatChance res = {0,0};

    //Il joue
    do
    {
        gagne=0;//au début de chaque partie, il n'a pas encore gagné

        /*2.Genere la combinaison secrète stockée dans le tableau combiVrai de la structure jeu*/
        for(int i=0; i<4; i++)
        {
            jeu.combiVrai[i]=rand()%10;//Il génère d'un tableau de 4 chiffres de 0 à 9
        }

        /*Initialise le nombre d'essaie restant*/
        jeu.nbEssaiRestant = 10; //10 au début de chaque partie

        /*5.6.La partie s'arrete si le nombre d'essaie restant est 0 ou s'il gagne*/
        while((jeu.nbEssaiRestant>0)&&(gagne==0))
        {
            /*3.Le joueur entre successivement les 4 chiffres à deviner*/
            for(int i=0; i<4; i++)
            {
                printf("Entrez votre chiffre entre 0 et 9 de position %d : ", i+1);
                scanf("%d", &jeu.combiJoueur[i]);
            }
            jeu.nbEssaiRestant--;//décrémenter le nombre d'essaie chaque fois il entre 1 combinaison

            /*4.Test de la combinaison*/
            TestCombi(res,jeu);
            printf("\n");
        }

        //Fin de tour, si le joueur trouve la bonne combinaison, il gagne, sinon, il perd
        if(gagne==1)
        {
            printf("Gagne apres %d essaies!\n", 10-jeu.nbEssaiRestant);
            jeu.nbPartieGagne ++;
        }
        else
        {
            jeu.nbPartiePerdue ++;
            printf("Perdu !\n");
        }

        /*7.Informe le joueur commbien de parties gagnées et perdues*/
        printf("Vous avez gagne %d fois et perdu %d fois\n", jeu.nbPartieGagne, jeu.nbPartiePerdue);

        /*8. On propose s'il veut rejouer*/
        printf("Voulez vous rejouer ? 1: oui, 0: non\n");
        scanf("%d", &reJouer);
        printf("\n\n");
    }
    while(reJouer);//tant que il veut rejouer

    return 0;
}
