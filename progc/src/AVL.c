#include <stdio.h>
#include <stdlib.h>

// TODO test the code

typedef struct AVL {
    struct AVL* l;
    struct AVL* r;
    float min;
    float max;
    float averageSum;
    int roadId;
    int stepNumber;
    int balance;
} AVL;

AVL* createAVL(int roadId, float distance) {
    AVL* t = malloc(sizeof(AVL));
    t->roadId = roadId;
    t->min = distance;
    t->max = distance;
    t->averageSum = distance;
    t->stepNumber = 1;

    t->balance = 0;
    t->l = NULL;
    t->r = NULL;
    return t;
}

int height(AVL* a) {
    if (a == NULL) {
        return 0;
    }
    int leftHeight = height(a->l);
    int rightHeight = height(a->r);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

//rotations
AVL* leftRotation(AVL* a) {
    AVL* b = a->r;
    a->r = b->l;
    b->l = a;
    a->balance = height(a->r) - height(a->l);
    b->balance = height(b->r) - height(b->l);
    return b;
}

AVL* rightRotation(AVL* a) {
    AVL* b = a->l;
    a->l = b->r;
    b->r = a;
    a->balance = height(a->r) - height(a->l);
    b->balance = height(b->r) - height(b->l);
    return b;
}

//double rotations
AVL* doubleLeftRotation(AVL* a) {
    a->r = rightRotation(a->r);
    return leftRotation(a);
}

AVL* doubleRightRotation(AVL* a) {
    a->l = leftRotation(a->l);
    return rightRotation(a);
}

//function to balance AVL
AVL* balanceAVL(AVL* a) {
    if (a->balance > 1) {
        if (a->r->balance < 0) {
            a = doubleLeftRotation(a);
        } else {
            a = leftRotation(a);
        }
    } else if (a->balance < -1) {
        if (a->l->balance > 0) {
            a = doubleRightRotation(a);
        } else {
            a = rightRotation(a);
        }
    }
    return a;
}

//function that insert into AVL tree
void insertAVL(AVL** a, int roadId, float distance, int* h) {
    //handling case where a is empty
    if (*a == NULL) {
        *a = createAVL(roadId, distance);
        *h = 1;
    } else if (roadId < (*a)->roadId) {
        insertAVL(&((*a)->l), roadId, distance, h);
        // FIXME can speed up teh process if we don't re calculate the balance each tie and pass it through the calls
        (*a)->balance = height((*a)->l) - height((*a)->l);
        if ((*a)->balance == -2) {
            *a = balanceAVL(*a);
        }
    } else if (roadId > (*a)->roadId) {
        insertAVL(&((*a)->l), roadId, distance, h);
        // FIXME can speed up teh process if we don't re calculate the balance each tie and pass it through the calls
        (*a)->balance = height((*a)->r) - height((*a)->l);
        if ((*a)->balance == 2) {
            *a = balanceAVL(*a);
        }
    } else {
        // handle the equal case since there are more data than a normal AVL
        (*a)->stepNumber++;
        if ((*a)->max < distance) {
            (*a)->max = distance;
        }
        if ((*a)->min > distance) {
            (*a)->min = distance;
        }
        (*a)->averageSum += distance;
    }
}

// Function to perform an in-order traversal of the AVL tree
void inOrderTravel(AVL* A) {
    if (A != NULL) {
        inOrderTravel(A->l);
        printf("%d ", A->roadId);
        inOrderTravel(A->r);
    }
}







