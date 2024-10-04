#include <stdio.h>
#include <windows.h>  // Pour Sleep() et clear screen

// Fonction pour effacer l'écran (Windows)
void clear_screen() {
    system("cls");
}

// Fonction pour afficher le joueur et l'ennemi sur la même ligne
void displaySituation(int playerX, int mobX) {
    clear_screen();

    // Affichage du terrain
    printf("Joueur vs Ennemi\n");
    printf("----------------\n");

    // Affichage du joueur et de l'ennemi sur la même ligne
    for (int i = 0; i < playerX; i++) {
        printf(" ");
    }
    printf(" O "); // Tête du joueur

    for (int i = playerX + 3; i < mobX; i++) { // Espaces entre le joueur et l'ennemi
        printf(" ");
    }
    printf(" X \n"); // Tête de l'ennemi

    for (int i = 0; i < playerX; i++) {
        printf(" ");
    }
    printf("/|\\");  // Corps du joueur

    for (int i = playerX + 3; i < mobX; i++) {
        printf(" ");
    }
    printf("/|\\\n"); // Corps de l'ennemi

    for (int i = 0; i < playerX; i++) {
        printf(" ");
    }
    printf("/ \\");  // Jambes du joueur

    for (int i = playerX + 3; i < mobX; i++) {
        printf(" ");
    }
    printf("/ \\\n"); // Jambes de l'ennemi
}
// Animation lorsque le joueur attaque et touche l'ennemi
void playerAttackHits(int playerX, int mobX) {
    displaySituation(playerX, mobX);
    int distance = mobX - playerX;

    // Déplacement du joueur vers l'ennemi
    for (int i = 0; i < distance; i++) {
        displaySituation(playerX + i, mobX);
        Sleep(100); // Pause rapide pour l'animation
    }
}

// Animation lorsque le joueur attaque mais manque l'ennemi (avec recul de l'ennemi)
void playerAttackMisses(int playerX, int mobX) {
    displaySituation(playerX, mobX);
    int distance = mobX - playerX;

    // Déplacement du joueur vers l'ennemi
    for (int i = 0; i < distance - 2; i++) {  // Le joueur s'arrête juste avant de toucher
        displaySituation(playerX + i, mobX);
        Sleep(100);
    }

    // L'ennemi recule avant que le joueur ne l'atteigne
    for (int i = 0; i < 5; i++) {  // L'ennemi recule de 5 positions
        displaySituation(playerX + (distance - 2), mobX + i);
        Sleep(100);
    }
}

// Animation lorsque l'ennemi attaque et touche le joueur
void mobAttackHits(int playerX, int mobX) {
    displaySituation(playerX, mobX);
    int distance = mobX - playerX;

    // Déplacement de l'ennemi vers le joueur
    for (int i = 0; i < distance; i++) {
        displaySituation(playerX, mobX - i);
        Sleep(100); // Pause rapide pour l'animation
    }
}


