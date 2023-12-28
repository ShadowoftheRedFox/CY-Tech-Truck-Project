#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./AVL_s.h"

AVL_s* createAVL_s(int roadId, float distance) {
    AVL_s* a = malloc(sizeof(AVL_s));
    a->roadId = roadId;
    a->min = distance;
    a->max = distance;
    a->averageSum = distance;
    a->stepNumber = 1;

    a->balance = 0;
    a->l = NULL;
    a->r = NULL;
    return a;
}

int height_s(AVL_s* a) {
    if (a == NULL) {
        return 0;
    }
    int leftHeight = height_s(a->l);
    int rightHeight = height_s(a->r);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int getMax(const int a, const int b) {
    return (a >= b ? a : b);
}

int getMin(const int a, const int b) {
    return (a >= b ? b : a);
}

//rotations
AVL_s* leftRotation_s(AVL_s* a) {
    AVL_s* b = a->r;
    a->r = b->l;
    b->l = a;
    //FIXME can speed up using calculus
    a->balance = height_s(a->r) - height_s(a->l);
    b->balance = height_s(b->r) - height_s(b->l);

    //int aBal = a->balance;
    //int bBal = b->balance;
    //a->balance = aBal - getMax(bBal, 0) - 1;
    //b->balance = getMin(aBal - 2, getMin(aBal + bBal - 2, bBal - 1));

    return b;
}

AVL_s* rightRotation_s(AVL_s* a) {
    AVL_s* b = a->l;
    a->l = b->r;
    b->r = a;
    //FIXME can speed up using calculus
    a->balance = height_s(a->r) - height_s(a->l);
    b->balance = height_s(b->r) - height_s(b->l);

    //int aBal = a->balance;
    //int bBal = b->balance;
    //a->balance = aBal - getMin(bBal, 0) + 1;
    //b->balance = getMax(aBal + 2, getMax(aBal + bBal + 2, bBal + 1));

    return b;
}

//double rotations
AVL_s* doubleLeftRotation_s(AVL_s* a) {
    a->r = rightRotation_s(a->r);
    return leftRotation_s(a);
}

AVL_s* doubleRightRotation_s(AVL_s* a) {
    a->l = leftRotation_s(a->l);
    return rightRotation_s(a);
}

//function to balance AVL_s
AVL_s* balanceAVL_s(AVL_s* a) {
    if (a->balance > 1) {
        if (a->r->balance < 0) {
            a = doubleLeftRotation_s(a);
        } else {
            a = leftRotation_s(a);
        }
    } else if (a->balance < -1) {
        if (a->l->balance > 0) {
            a = doubleRightRotation_s(a);
        } else {
            a = rightRotation_s(a);
        }
    }
    return a;
}

//function that insert into AVL_s tree
void insertAVL_s(AVL_s** a, int roadId, float distance, int* h) {
    //handling casse where a is empty
    if (*a == NULL) {
        *a = createAVL_s(roadId, distance);
        *h = 1;
    } else if (roadId < (*a)->roadId) {
        insertAVL_s(&((*a)->l), roadId, distance, h);
        *h = -(*h);
    } else if (roadId > (*a)->roadId) {
        insertAVL_s(&((*a)->r), roadId, distance, h);
    } else {
        // handle the equal case since there are more data than a normal AVL_s
        (*a)->stepNumber++;
        if ((*a)->max < distance) {
            (*a)->max = distance;
        }
        if ((*a)->min > distance) {
            (*a)->min = distance;
        }
        (*a)->averageSum += distance;
        *h = 0;
    }

    if (*h != 0) {
        (*a)->balance += *h;
        *a = balanceAVL_s(*a);
        if ((*a)->balance == 0) {
            *h = 0;
        } else {
            *h = 1;
        }
    }
}

// Function to perform an in-order traversal of the AVL_s tree
void infixTravel_s(AVL_s* a) {
    if (a != NULL) {
        infixTravel_s(a->l);
        printf("%d ", a->roadId);
        infixTravel_s(a->r);
    }
}

void print2DLeftToRightUtil_s(AVL_s* a, int space) {
    // Base case
    if (a == NULL) {
        return;
    }

    // Increase distance between levels
    space += 10;

    // Process right child first
    print2DLeftToRightUtil_s(a->r, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", a->roadId);

    // Process left child
    print2DLeftToRightUtil_s(a->l, space);
}

// Wrapper over print2DLeftToRightUtil()
void print2DLeftToRight_s(AVL_s* a) {
    if (a == NULL) {
        printf("Empty Tree\n");
        return;
    }
    // Pass initial space count as 0
    print2DLeftToRightUtil_s(a, 0);
}

void freeAVL_s(AVL_s* a) {
    if (a == NULL) return;
    if (a->l) {
        freeAVL_s(a->l);
    }
    if (a->r) {
        freeAVL_s(a->r);
    }
    free(a);
}

// CODE TO TEST THE FILE
/* int main(int argc, char const* argv[]) {
    srand(time(NULL));

    AVL_s* a = createAVL_s(1, (rand() % 990) / 10.0 + 1.0);
    for (int i = 2; i <= 20; i++) {
        insertAVL(&a, i, (rand() % 990) / 10.0 + 1.0, &(a->balance));
    }

    infixTravel(a);
    print2DLeftToRight(a);
    printf("%d\n", height_s(a->r) - height_s(a->l));
    freeAVL(a);
    return 0;
} */