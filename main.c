#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

struct joueur 
{ // Structure pour les infos des joueurs
  char Joueur[20];
  int Score;
} Joueur1, Joueur2, save;

struct plateau 
{
  int L; // Structure pour les infos du tableau0
  int C;
  int tab[9][9];
} pl;

void AfficherTableau() 
{ // Fonction permettant d'afficher le tableau
  for (int i = 1; i < pl.L + 1; i++) {
    for (int j = 2; j < pl.C + 2; j++) {
      if (pl.tab[i][j] > 0) {
        printf("\033[1;31m");
        printf("%3d", pl.tab[i][j]);
      } else if (pl.tab[i][j] < 0) {
        printf("\033[1;34m");
        printf("%3d", -pl.tab[i][j]);
      } else if (pl.tab[i][j] == 0) {
        printf("%3d", pl.tab[i][j]);
      }
      printf("\033[0m");
    }
    printf("\n");
  }
}

void InitJeu(int ligne,int col) 
{ // Fonction mettant toute les cases du tableau à 0
  pl.L = ligne;
  pl.C = col;

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      pl.tab[i][j] = 0;
    }
  }

  AfficherTableau();
}

void Jeu(int ligne, int col) {
  printf("%s sera rouge et %s sera bleu\n", Joueur1.Joueur, Joueur2.Joueur);
  int Jeton; // Utilisé pour le calcul du nombre de Jetons
  int pc, pol, dc, dl, lz, cz;
  bool
      ValJeton; // Pour vérifier que la valeur saisie dans le tableau est valide
  Joueur1.Score = 0;
  Joueur2.Score = 0;
  ValJeton = false;
  Jeton = ((ligne * col) - 1) / 2;
  printf("Chaque joueur aura %d jetons\n", Jeton);
  for (int k = 1; k < Jeton + 1; k++) {
    printf("%s, écrivez la ligne et la colonne\n", Joueur1.Joueur);

    while (!ValJeton) {
      scanf("%d", &pol);
      scanf("%d", &pc);
      if (pol <= pl.L && pc <= pl.C && pl.tab[pol][pc + 1] == 0 && pol != 0 &&
          pc != 0) {
        pl.tab[pol][pc + 1] = k;
        ValJeton = true;
      } else {
        printf("Coordonnées invalides\n");
      }
    }
    ValJeton = false;
    AfficherTableau();
    printf("%s, écrivez la ligne et la colonne\n", Joueur2.Joueur);
    while (!ValJeton) {
      scanf("%d", &dl);
      scanf("%d", &dc);
      if (dl <= pl.L && dc <= pl.C && pl.tab[dl][dc + 1] == 0 && dl != 0 &&
          dc != 0) {
        pl.tab[dl][dc + 1] = -k;
        ValJeton = true;
      } else {
        printf("Coordonnées invalides\n");
      }
    }
    ValJeton = false;
    AfficherTableau();
  }

  for (int n = 1; n < pl.L + 1; n++) {
    for (int o = 2; o < pl.C + 2; o++) {
      if (pl.tab[n][o] == 0) {
        lz = n;
        cz = o - 1;
      }
    }
  }

  for (int n = lz - 1; n < lz + 2; n++) {
    for (int o = cz; o < cz + 3; o++) {
      if (pl.tab[n][o] > 0) {
        Joueur1.Score = Joueur1.Score + pl.tab[n][o];
      } else if (pl.tab[n][o] < 0) {
        Joueur2.Score = Joueur2.Score + pl.tab[n][o];
      }
    }
  }
  printf("Le score de %s est %d et celui de %s est %d\n", Joueur1.Joueur,
         Joueur1.Score, Joueur2.Joueur, -Joueur2.Score);
  if (Joueur1.Score < -Joueur2.Score) {
    printf("%s est le Vainqueur\n", Joueur1.Joueur);
  } else if (-Joueur2.Score < Joueur1.Score) {
    printf("%s est le Vainqueur\n", Joueur2.Joueur);
  } else if (-Joueur2.Score == Joueur1.Score) {
    printf("Les Joueurs sont à égalité\n");
  }
  save = Joueur1;
  Joueur1 = Joueur2;
  Joueur2 = save;
}

bool Rejouer(bool *ContinuerAJouer) // Fonction pour demander à l'utilisateur s'il veut rejouer
{
  bool verif = false;
  printf("Voulez vous rejouer ? (o pour oui/n pour non)\n");
  char c_rejoue;
  while (!verif) {
    getchar();
    scanf("%c", &c_rejoue);
    if (c_rejoue == 'o') {
      *ContinuerAJouer = true;
      verif = true;
    } else if (c_rejoue == 'n') {
      *ContinuerAJouer = false;
      printf("Jeu terminé\n");
      verif = true;
    } else {
      printf("Valeur incorrecte\n");
    }
  }
}

void main() 
{
  printf("Entrez le pseudo du Joueur 1\n");
  scanf("%s", &Joueur1.Joueur);
  printf("Entrez le pseudo du Joueur 2\n");
  scanf("%s", &Joueur2.Joueur);

  printf("Les joueurs seront %s et %s\n", Joueur1.Joueur, Joueur2.Joueur);
  int ligne, col;
  bool valide, ContinuerAJouer = true;

  while (!valide) {
    printf("\n Entrez le nombre de ligne \n");
    scanf("%d", &ligne);
    switch (ligne) 
    {
      
      case 3:
      
      case 5:
      
      case 7: 
        {
          valide = true;
          break;
        }
      default: 
        {
        printf("\n Nombre de ligne invalide \n");
        break;
      }
    }
  }

  valide = false;

  while (!valide) {
    printf("Entrez le nombre de colonne \n");
    scanf("%d", &col);
    switch (col) {
    case 5:
    case 7:
    case 9: {
      valide = true;
      break;
    }

    default:
      printf("Nombre de colonne invalide\n");
      break;
    }
  }

  while (ContinuerAJouer) {
    InitJeu(ligne, col);
    Jeu(ligne, col);
    Rejouer(&ContinuerAJouer);
  }
}

// valide = ((L % 2 == 1) && (C % 2 == 1) && L >= 3 && L <= 7 && C >= 3 && C
// <= 7)