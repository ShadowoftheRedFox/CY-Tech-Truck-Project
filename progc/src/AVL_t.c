#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "./AVL_t.h"

/*
Goal: faire fonctionner -t

Step 1: les fichiers d'entrés:
il nous faut les routes pour savoir combien il y a de routes par ville
les noms des conducteurs pour la même raison
et les ville A et B, pour avoir tout les cas
et peut être même les step pour avoir une optimization

donc tout sauf la distance

Step 2: le tri
on doit forcément trier par le nom des villes
mais il est peut être nécéssaire de faire un préprocéssus:
comme regarder si des villes n'apparaissent qu'une fois, ou faire une liste de conducteurs etc

mais par quel chemin passer?
-> je pense par les routes ID:
    un seul passage pour toutes les villes et les conducteurs
    on ajoute deux villes à la fois, on passe donc tout les cas

    TODO:on fait une liste qui associe un conducteur à un ID de route, comme ça on sait si il est déjà passé
    si il est pas passé on l'ajoute au nombre de conducteur et on l'ajoute à la liste

    idem pour l'ID des routes, une liste
    si déjà présent pour la route, on skip, sinon on ajoute 1 au conteur de la ville

! Check le cas ou la ville A = ville B

Step 3: Le top 10
par ordre alphabétique, avec NOM VILLE; NB ROUTE; NB CONDUCTEUR
Deux choix:
- on sort dans le fichier output seulement le top 10 -> fonction qui chope les 10 villes les plus traversé
- on sort tout et on cherche

IL Y A SUREMENT UNE METHODE PLUS EFFICACE, CAR ON REGARDE PLUSIEURS FOIS LES FICHIERS SOURCE

Step 4: Graph
devrait pas etre trop compliqué de faire un graph groupé, il a plein d'exemple dejà
*/

/*
alors
pour trier, on commence par l'AVL qui prend en paramètre principal le nom de la ville:
on les tries par ordre alphabétique, et on prend ville A et ville B sans distinction, donc pas besoin de couper le document pour ça
on les mets dans des noeuds et on compte le nombre d'occurences, avec ce nombre on peut calculer le nombre de fois qu'elles ont été traversé

on compte avec cela un compteur pour chaque route et conducteur unique
donc le nombre de ville dans compteur doit être pair avant le calcul (c'est un check de redondance!)
on calcul le nombre de trajet en une ville en faisant: ((compteur-2)/2) + 2 = (compteur+2)/2
c'est tout
*/

AVL_t* createAVL_t(const char* town_name) {
    AVL_t* a = malloc(sizeof(AVL_t));
    strcpy(a->town_name, town_name);
    a->count = 1;
    a->balance = 0;
    a->l = NULL;
    a->r = NULL;
    return a;
}

int height_t(AVL_t* a) {
    if (a == NULL) {
        return 0;
    }
    int leftHeight = height_t(a->l);
    int rightHeight = height_t(a->r);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

//rotations
AVL_t* leftRotation_t(AVL_t* a) {
    AVL_t* b = a->r;
    a->r = b->l;
    b->l = a;
    //FIXME can speed up using calculus
    a->balance = height_t(a->r) - height_t(a->l);
    b->balance = height_t(b->r) - height_t(b->l);
    return b;
}

AVL_t* rightRotation_t(AVL_t* a) {
    AVL_t* b = a->l;
    a->l = b->r;
    b->r = a;
    //FIXME can speed up using calculus
    a->balance = height_t(a->r) - height_t(a->l);
    b->balance = height_t(b->r) - height_t(b->l);
    return b;
}

//double rotations
AVL_t* doubleLeftRotation_t(AVL_t* a) {
    a->r = rightRotation_t(a->r);
    return leftRotation_t(a);
}

AVL_t* doubleRightRotation_t(AVL_t* a) {
    a->l = leftRotation_t(a->l);
    return rightRotation_t(a);
}

//function to balance AVL_t
AVL_t* balanceAVL_t(AVL_t* a) {
    if (a->balance > 1) {
        if (a->r->balance < 0) {
            a = doubleLeftRotation_t(a);
        } else {
            a = leftRotation_t(a);
        }
    } else if (a->balance < -1) {
        if (a->l->balance > 0) {
            a = doubleRightRotation_t(a);
        } else {
            a = rightRotation_t(a);
        }
    }
    return a;
}

//function that insert into AVL_t tree
void insertAVL_t(AVL_t** a, const char* town_name, int* h) {
    //handling casse where a is empty
    if (*a == NULL) {
        *a = createAVL_t(town_name);
        *h = 1;
    } else if (strcmp((*a)->town_name, town_name) < 0) {
        insertAVL_t(&((*a)->l), town_name, h);
        *h = -(*h);
    } else if (strcmp((*a)->town_name, town_name) > 0) {
        insertAVL_t(&((*a)->r), town_name, h);
    } else {
        // handle the equal case since there are more data than a normal AVL_t
        *h = 0;
        (*a)->count++;
    }

    if (*h != 0) {
        (*a)->balance += *h;
        *a = balanceAVL_t(*a);
        if ((*a)->balance == 0) {
            *h = 0;
        } else {
            *h = 1;
        }
    }
}

// Function to perform an in-order traversal of the AVL_t tree
void infixTravel_t(AVL_t* a) {
    if (a != NULL) {
        infixTravel_t(a->l);
        printf("%s", (*a).town_name);
        infixTravel_t(a->r);
    }
}

void print2DLeftToRightUtil_t(AVL_t* a, int space) {
    // Base case
    if (a == NULL) {
        return;
    }

    // Increase distance between levels
    space += 10;

    // Process right child first
    print2DLeftToRightUtil_t(a->r, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("%s\n", (*a).town_name);

    // Process left child
    print2DLeftToRightUtil_t(a->l, space);
}

// Wrapper over print2DLeftToRightUtil()
void print2DLeftToRight_t(AVL_t* a) {
    if (a == NULL) {
        printf("Empty Tree\n");
        return;
    }
    // Pass initial space count as 0
    print2DLeftToRightUtil_t(a, 0);
}

void freeAVL_t(AVL_t* a) {
    if (a == NULL) return;
    if (a->l) {
        freeAVL_t(a->l);
        freeAVL_t(a->r);

    }
    if (a->r) {
        freeAVL_t(a->r);
    }
    free(a->town_name);
    free(a);
}

// CODE TO TEST THE FILE
/* int main(int argc, char const* argv[]) {
    srand(time(NULL));

    AVL_t* a = createAVL_t(1, (rand() % 990) / 10.0 + 1.0);
    for (int i = 2; i <= 20; i++) {
        insertAVL(&a, i, (rand() % 990) / 10.0 + 1.0, &(a->balance));
    }

    infixTravel(a);
    print2DLeftToRight(a);
    printf("%d\n", height_t(a->r) - height_t(a->l));
    freeAVL(a);
    return 0;
} */