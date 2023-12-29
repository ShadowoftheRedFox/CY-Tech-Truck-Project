#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "./AVL_t.h"

AVL_t* createAVL_t(const char town_name[TOWN_NAME_LENGTH + 1]) {
    AVL_t* a = malloc(sizeof(AVL_t));
    strcpy(a->town_name, town_name);
    a->count = 1;
    a->start = 0;
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
void insertAVL_t(AVL_t** a, const char town_name[TOWN_NAME_LENGTH + 1], int* h, Bool isStart) {
    //handling casse where a is empty
    if (*a == NULL) {
        *a = createAVL_t(town_name);
        if (isStart) {
            (*a)->start = 1;
        }
        *h = 1;
    } else if (strcmp((*a)->town_name, town_name) < 0) {
        insertAVL_t(&((*a)->l), town_name, h, isStart);
        *h = -(*h);
    } else if (strcmp((*a)->town_name, town_name) > 0) {
        insertAVL_t(&((*a)->r), town_name, h, isStart);
    } else {
        // handle the equal case since there are more data than a normal AVL_t
        *h = 0;
        (*a)->count++;
        (*a)->start += (int)isStart;
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
    freeAVL_t(a->l);
    freeAVL_t(a->r);
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