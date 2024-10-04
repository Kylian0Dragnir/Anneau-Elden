// Auteur Mermin Kylian et Novais Amori, Date : 06/09/24

#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>

#define MAX_SLOTS 10

int pv = 100;
int res = 0;
int nVig = 0;
int nFor = 0;
int nInt = 0;
int nRes = 0;
char backpack[MAX_SLOTS] = {'p', 'p', 'v', 'v', 'v', 'v', 'v', 'v', 'v', 'v'};

int spellUnlock = 0;

int playerX = 5;
int mobX = 20;

void playerAttackHits(int playerX, int mobX);
void playerAttackMisses(int playerX, int mobX);
void mobAttackHits(int playerX, int mobX);

void setColor(int color);
void addNiv(int xp);
void showItems();
void usePotion(int potion);
bool isFull();
void addItem(char item);
void choice(void (*paraActu)(), void (*para1)(), void (*para2)());
void fight(int pvMob);
int playerFightPart(int pvMob);
void mobFightPart();
int lightAttack(int pvMob);
int heavyAttack(int pvMob);
int castSpell(int pvMob);
void takeDamage(int damage);
void checkDeath();
int gameOver();
void p1();
void p2();
void p3();
void p4();
void p5();
void p6();
void p7();
void p8();
void p9();
void p10();
void p11();
void p12();
void p13();
void p14();
void credits();


int main() {
    system("cls");
    char nomHero[30];
    printf("RULES :\nVos pv sont egaux a 100 + 5 fois votre niveaux de vigeur.\nPour le combat, vous pouvez faire une light Attack ou une heavy Attack,\nvous touchez votre cible a tout les coups avec une light attack mais vous faites de petits degats,\nvous avez 1 chance sur 2 de toucher votre cible avec une heavy Attack mais vous faites des degats considerables.\nPour une light Attack, vous faites entre 1 et 15 degats + votre niveau de force.\nPour une heavy Attack, vous faites entre 1 et 30 degats + 2 fois votre niveau de force.\nVous pouvez debloquer les sorts a un moment de l'histoire mais ils ne sont pas debloque par defaut,\navec un sort vous touchez a chaque fois et vous mettez 2 fois votre niveau en intelligence.\nQuand vous prenez des degats, 2 fois votre niveau de resistance est retire aux degats que vous devriez prendre.\n\n");
    printf("Entrer votre prenom pour commencer l'aventure: ");
    scanf("%s", nomHero);
    system("cls");
    printf("Bienvenue %s, vous commencez l'aventure avec 2 potions de soin\n\n", nomHero);
    printf("Vous avez 25 points d'experience a associer a differente stats. (Vigueur/Force/Intelligence/Resistance)\n");
    addNiv(25);
    p1();
    return 0;
}

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void addNiv(int xp) {
    int nVigP = 0;
    int nForP = 0;
    int nIntP = 0;
    int nResP = 0;
    printf("Vigeur = %d + ",nVig);
    scanf("%d", &nVigP);
    printf("Force = %d + ", nFor);
    scanf("%d", &nForP);
    printf("Intelligence = %d + ", nInt);
    scanf("%d", &nIntP);
    printf("Resistance = %d + ", nRes);
    scanf("%d", &nResP);
    if (xp - nVigP - nForP - nIntP - nResP == 0) {
        nVig += nVigP;
        nFor += nForP;
        nInt += nIntP;
        nRes += nResP;
        pv += 5*nVigP;
        res += nResP;
        xp = 0;
        printf("vous avez maintenant %d niveaux en Vigeur, %d niveaux en Force, %d niveaux en Intelligence et %d niveaux Resistance\n", nVig, nFor, nInt, nRes);
        printf("Vous avez donc %d pv", pv);
        Sleep(2000);
    } else if (xp - nVigP - nForP - nIntP - nResP < 0) {
        printf("Mmmmh tu as mis un peu trop de niveaux bro, recommence\n");
        Sleep(1500);
        addNiv(xp);
    } else if (xp - nVigP - nForP - nIntP - nResP > 0) {
        printf("Il te restait des niveaux a mettre bro, recommence\n");
        Sleep(1500);
        addNiv(xp);
    }
}

void showItems() {
    int potion = 0;
    int relique = 0;

    for (int i = 0; i < MAX_SLOTS; i++) {
        switch (backpack[i]) {
            case 'p' :
                potion++;
                break;
            case 'r':
                relique++;
                break;
            default :
                break;
        }
    }
    printf("Vous avez %d potion(s) et %d relique(s) dans votre sac a dos.\n", potion, relique);
    printf("Voulez vous boire une potion ? (y/n) : ");
    while (1) {
        char input;
        scanf(" %c", &input);
        if (input == 'y') {
            system("cls");
            usePotion(potion);
            break;
        } else if (input == 'n') {
            printf("\nL'histoire continue...\n");
            system("cls");
            break;
        } else {
           printf("\nNon pas cette touche");
        }
     }
}

void usePotion(int potion) {
    int stop = 0;
    if (potion > 0) {
        for (int i = 0; i < MAX_SLOTS; i++) {
            if (backpack[i] == 'p') {
                potion -= 1;
                backpack[i] = 'v';
                pv += 10;
                setColor(2);
                printf("Vous avez bue une potion ! Vos PV sont maintenant de %d.\n", pv);
                setColor(7);
                Sleep(2000);
                printf("Voulez vous boire une autre potion ? (y/n) : ");
                while (!stop) {
                    char input;
                    scanf(" %c", &input);
                    if(input == 'y') {
                        usePotion(potion);
                        stop = 1;
                        break;
                    } else if(input == 'n') {
                        printf("L'histoire continue...\n");
                        stop = 1;
                        break;
                    } else {
                        printf("\nNon pas cette touche\n");
                    }
                }
            }
        }
    } else {
        printf("Il n'y a pas de potions a utiliser.\n");
        Sleep(1500);
        }
}


bool isFull(){
    for(int i = 0; i < MAX_SLOTS; i++){
        if (backpack[i] == 'v'){
            return false;
        }
    }
    return true;
}

void addItem(char item){
    if (isFull() == false){
        for(int i = 0; i < MAX_SLOTS; i++){
            if (backpack[i] == 'v'){
                backpack[i] = item;
                printf("vous avez 1 potion en plus !\n");
                break;
            }
        }
    } else {
        printf("Votre sac a dos est plein !\n");
    }
}

void choice(void (*paraActu)(), void (*para1)(), void (*para2)()){
    while (1) {
    char input;
    scanf(" %c", &input);

        switch (input) {
            case '1':
                system("cls");
                para1();
                break;

            case '2':
                system("cls");
                para2();
                break;

            case '3':
                system("cls");
                showItems();
                paraActu();
                break;

            default:
                printf("Non pas cette touche\n");
                break;
            }
        }
}

void fight(int pvMob) {
        while (pvMob > 0){
            pvMob = playerFightPart(pvMob);
            printf("C'est maintenant a l'ennemi d'attaquer");
            Sleep(2000);
            mobFightPart();
        }
        printf("\nvous avez battut le monstre");
        Sleep(2000);
}

int playerFightPart(int pvMob){
    printf("\nL'ennemi a %d pv !", pvMob);
            if (spellUnlock = 1){
                printf("\nComment l'attaquez vous ? | l : light attack / h : heavy attack / c : cast spell |\n");
            } else {
                printf("\nComment l'attaquez vous ? | l : light attack / h : heavy attack |\n");
            }
            int dam = 0;
            char type;
            scanf(" %c", &type);
            switch (type) {
                case 'l':
                    dam = lightAttack(pvMob);
                    pvMob -= dam;
                    return pvMob;
                    break;
                case 'h':
                    dam = heavyAttack(pvMob);
                    pvMob -= dam;
                    return pvMob;
                    break;
                case 'c':
                    if (spellUnlock = 1){
                        dam = castSpell(pvMob);
                        pvMob -= dam;
                        return pvMob;
                    } else {
                        printf("not unlocked");
                        return pvMob;
                    }
                    break;
                default :
                    printf("ERROR : fight type arguments : 'l', 'h', 's'.");
                    break;
            }
}

void mobFightPart(){
    srand(time(NULL));
    int dam = rand()%30 + 15;
    mobAttackHits(playerX, mobX);
    takeDamage(dam);
}

int lightAttack(int pvMob){
    srand(time(NULL));
    int dam = rand()%15 + 1 + nFor;
    playerAttackHits(playerX, mobX);
    printf("Bravo, votre attaque a inflige %d de degats au Mob\n", dam);
    Sleep(2000);
    return dam;
}

int heavyAttack(int pvMob){
    srand(time(NULL));
    int dam = rand()%30 + 1 + 2*nFor;
    int chance = rand()%3;
    if (chance == 1){
        playerAttackHits(playerX, mobX);
        printf("Bravo, votre attaque a inflige %d de degats au Mob\n", dam);
        Sleep(2000);
        return dam;
    } else {
        playerAttackMisses(playerX, mobX);
        printf("L'ennemi a esquiver !!\n");
        Sleep(2000);
        return 0;
    }
}

int castSpell(int pvMob){
    int dam = 2*nInt;
    printf("Bravo, votre sort a inflige %d de degats au Mob\n", dam);
    Sleep(2000);
    return dam;
}

void takeDamage(int damage) {
    pv -= damage - 2*res;
    setColor(12);
    printf("Vous avez pris %d degats, il vous reste %d pv\n", damage, pv);
    setColor(7);
    checkDeath();
    Sleep(1500);
}

void checkDeath(){
    if (pv <= 0) {
        system("cls");
        printf("Malheureusement vous etes mort, quel dommage votre aventure prend fin ici ...\n");
        gameOver();
        Sleep(1500);
    }
}

int gameOver(){
    printf("Merci d'avoir jouer a notre jeux !\n\n");
    Sleep(1500);
    credits();
}

// Paragraphe 1
void p1() {
    system("cls");
    printf("Vous ouvrez les yeux dans une plaine devastee. Vous etes un Sans-Eclat, rappele pour restaurer l'Anneau d'Elden. Devant vous, une grande arche de pierre et, au loin, l'Arbre-Monde qui scintille d'or.\n");
    printf("Pour vous approchez de l'arche, Appuyer sur 1 ... \n");
    printf("Pour explorez les ruines, Appuyer sur 2 ... \n");
    printf("Si vous voulez ouvrir votre sac a dos, Appuyer sur 3 ... \n");
    choice(p1, p2, p3);
}

// Paragraphe 2
void p2() {
    system("cls");
    printf("Sous l'arche, un chevalier massif en armure doree, monte sur un cheval, vous attend. Sans un mot, il attend son prochain adversaire.\n");
    printf("Pour lancer le combat, Appuyer sur 1 ... \n");
    printf("Pour fuir vers un chemin secondaire, Appuyer sur 2 ... \n");
    printf("Si vous voulez ouvrir votre sac a dos, Appuyer sur 3 ... \n");
    choice(p2, p4, p5);  // Le combat sera géré ailleurs, donc on renvoie simplement le choix
}

// Paragraphe 3
void p3() {
    system("cls");
    printf("Vous trouvez une dalle cachee dans les ruines et decouvrez un passage sombre. Une faible lumiere bleue vous attire vers une caverne.\n");
    printf("Pour descendre dans la caverne, Appuyer sur 1 ... \n");
    printf("Pour continuer a explorer les ruines, Appuyer sur 2 ... \n");
    printf("Si vous voulez ouvrir votre sac a dos, Appuyer sur 3 ... \n");
    choice(p3, p6, p7);
}

// Paragraphe 4
void p4() {
    system("cls");
    printf("Le Chevalier de l'Arbre vous attaque avec violence. Vous etes en plein combat, chaque geste compte.\n");
    fight(150);
    Sleep(1000);
    p8();
}

// Paragraphe 5
void p5() {
    system("cls");
    printf("Vous parvenez a fuir le Chevalier et vous vous enfoncez dans les bois. Une lumiere provenant d'un feu attire votre attention.\n");
    printf("Pour allez vers le feu, Appuyer sur 1 ... \n");
    printf("Pour chercher refuge dans les bois, Appuyer sur 2 ... \n");
    printf("Si vous voulez ouvrir votre sac a dos, Appuyer sur 3 ... \n");
    choice(p5, p9, p7);
}

// Paragraphe 6
void p6() {
    system("cls");
    printf("Vous decouvrez une femme mysterieuse nommee Sellen, une sorciere erudite, entouree de livres. Elle vous propose de vous enseigner la sorcellerie.\n");
    printf("Pour accepter l'offre de Sellen, Appuyer sur 1 ... \n");
    printf("Pour refuser, quitter la caverne et partir explorer les bois, Appuyer sur 2 ... \n");
    printf("Si vous voulez ouvrir votre sac a dos, Appuyer sur 3 ... \n");
    choice(p6, p10, p7);
}

// Paragraphe 7
void p7() {
    system("cls");
    printf("En vous enfoncant plus loin dans les bois, une creature mysterieuse vous tend une embuscade.\n");
    fight(100);
    printf("Vous avez combattu vaillamment, vous apercevez un feu dore au loin et vous vous y dirigez.\n");
    Sleep(1500);
    p9();
}

// Paragraphe 8
void p8() {
    system("cls");
    printf("Vous terrassez le Chevalier de l'Arbre. Son corps s'effondre et la route est degagee.\n");
    printf("Vous continuez vers l'Arbre-Monde.\n");
    Sleep(1500);
    p9();
}

// Paragraphe 9
void p9() {
    system("cls");
    printf("Vous arrivez pres du feu dore. Ce site de grace vous permet de vous reposer. Une silhouette mysterieuse apparait: Melina vous propose son aide.\n");
    printf("Pour accepter l'aide de Melina, Appuyer sur 1 ... \n");
    printf("Pour refuser et continuer seul, Appuyer sur 2 ... \n");
    printf("Si vous voulez ouvrir votre sac a dos, Appuyer sur 3 ... \n");
    choice(p9, p12, p13);
}

// Paragraphe 10
void p10() {
    system("cls");
    printf("En acceptant l'offre de Sellen, vous apprenez rapidement vos premiers sorts magiques. Vous ressentez un nouveau pouvoir en vous.\n");
    spellUnlock = 1;
    printf("Vous sortez de la caverne pour aller explorer les bois.\n");
    Sleep(1500);
    p7();
}

// Paragraphe 11
void p11() {
    system("cls");
    printf("Vous tentez de fuir l'embuscade, mais les creatures vous rattrapent. Dans un dernier souffle, vous sentez leurs griffes percer votre chair.\n");
    pv = 0;
    checkDeath();
}

// Paragraphe 12
void p12() {
    system("cls");
    printf("Vous acceptez l'aide de Melina. Ensemble, vous poursuivez votre voyage vers l'Arbre-Monde.\n");
    printf("Fin de la premiere partie.\n");
    credits();
}

// Paragraphe 13
void p13() {
    system("cls");
    printf("Vous choisissez de continuer seul. Le chemin est long et perilleux, mais vous etes resolu a accomplir votre destin.\n");
    printf("Fin de la premiere partie.\n");
    credits();
}


void credits() {
    printf("CREDITS :\n");
    printf("Programme : Mermin Kylian\n");
    printf("Histoire : Mermin Kylian, Novais Amori et Hidetaka Miyazaki\n");
    printf("Play Tester : Mermin Kylian, Novais Amori et Leclercq Gabriel\n");
    Sleep(4000);
    exit(0);
}
