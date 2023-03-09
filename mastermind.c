#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TENTATIVES 10
#define LARGEUR_CODE 4
#define NUMERO_COULEUR 6

void generateCode(int *code)
{
    int i, j;
    bool used[NUMERO_COULEUR] = {false}; // Tableau de booléens pour indiquer si un numéro est déjà utilisé
    for (i = 0; i < LARGEUR_CODE; i++) {
        
        do {
            // Choisir un nombre aléatoire entre 1 et 6
            code[i] = rand() % NUMERO_COULEUR + 1; 
        }
        while (used[code[i]-1]); // Répéter tant que le nombre choisi a déjà été utilisé
        
        used[code[i]-1] = true; // Marquer le nombre comme utilisé
    }
}


void getGuess(int *guess) {
    int i;
    char input[20];
    printf("Entrez votre tentative : ");
    fgets(input, sizeof(input), stdin); 
    for (i = 0; i < LARGEUR_CODE; i++) {
        guess[i] = input[i * 2] - '0';
    }
}

int checkGuess(int *guess, int *code) {
    int i, j;
    int correct = 0;
    int almostCorrect = 0;
    for (i = 0; i < LARGEUR_CODE; i++) {
        if (guess[i] == code[i]) {
            correct++;
        }
    }
    return correct;
}

int checkMauvaisePlace(int *guess, int *code) {
    int i, j;
    int almost = 0;
    for (i = 0; i < LARGEUR_CODE; i++) {
        for (j = 0; j < LARGEUR_CODE; j++) {
            // On fait 3 vérifs au lieu de 4 :
            if (guess[i] != code[i] && guess[i] == code[j]) {
                almost++;
            }
        }
    }
    return almost;
}

void AfficherMastermind() {
    int i;
    for (i = 0; i < MAX_TENTATIVES; i++) {
        printf("|---------------|\n");
        printf("|   |   |   |   |..| Ligne %d\n", i);
    }
    printf("|---------------|\n\n");
}

void launch() {
    void generateCode(int *code);
    void getGuess(int *guess);
    int checkGuess(int *guess, int *code);
}

int main() {
    int code[LARGEUR_CODE];
    int guess[LARGEUR_CODE];
    int guessesLeft = MAX_TENTATIVES;
    int i;
    int result;
    int result2;

    srand(time(NULL));

    launch();
    generateCode(code);
    AfficherMastermind();
    printf("\n\n");
    printf("Mastermind - Projet 3\n");
    printf("Il faut trouver une séquence de %d couleurs parmi %d choix.\n", LARGEUR_CODE, NUMERO_COULEUR);
    printf("Vous avez %d tentatives pour le deviner.\n\n", MAX_TENTATIVES);

    // Tant que le code n'est pas trouvé et qu'il reste des tentatives :
    while (guessesLeft > 0)
    {
        printf("Il reste %d tentatives.\n", guessesLeft);

        // On demande à l'utilisateur de saisir son code
        getGuess(guess);

        // On récupère le nombre de couleur bien placé avec la bonne position
        result = checkGuess(guess, code);

        // On récupère le nombre de couleur bien placé avec la bonne position
        result2 = checkMauvaisePlace(guess, code);


        if (result == LARGEUR_CODE) {
            printf("Félicitations, vous avez gagné !\n");
            return 0;
        }
        
        else {
            guessesLeft--;
            printf("%d couleurs sont correctes et bien placées.\n", result);
            printf("%d couleurs sont correctes mais mal placées.\n\n", result2);
        }
    }

    printf("Perdu! Le code était :");
    for (i = 0; i < LARGEUR_CODE; i++) {
        printf("%d ", code[i]);
    }

    printf("\n");
    return 0;
}