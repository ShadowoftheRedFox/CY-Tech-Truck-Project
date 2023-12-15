#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./AVL.h"

AVL* createAVL(int roadId, float distance) {
    AVL* a = malloc(sizeof(AVL));
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

int absolute(int a) {
    if (a < 0) {
        return -a;
    }
    return a;
}

//function that insert into AVL tree
void insertAVL(AVL** a, int roadId, float distance, int* h) {
    //handling casse where a is empty
    if (*a == NULL) {
        *a = createAVL(roadId, distance);
        *h = 1;
    } else if (roadId < (*a)->roadId) {
        insertAVL(&((*a)->l), roadId, distance, h);
        *h = -(*h);
    } else if (roadId > (*a)->roadId) {
        insertAVL(&((*a)->r), roadId, distance, h);
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
        *h = 0;
        return a;
    }

    if (*h != 0) {
        (*a)->balance += *h;
        *a = balanceAVL(*a);
        if ((*a)->balance == 0) {
            *h = 0;
        } else {
            *h = 1;
        }
    }
}

// Function to perform an in-order traversal of the AVL tree
void infixTravel(AVL* a) {
    if (a != NULL) {
        infixTravel(a->l);
        printf("%d ", a->roadId);
        infixTravel(a->r);
    }
}

void print2DLeftToRightUtil(AVL* a, int space) {
    // Base case
    if (a == NULL) {
        return;
    }

    // Increase distance between levels
    space += 10;

    // Process right child first
    print2DLeftToRightUtil(a->r, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", a->roadId);

    // Process left child
    print2DLeftToRightUtil(a->l, space);
}

// Wrapper over print2DLeftToRightUtil()
void print2DLeftToRight(AVL* a) {
    if (a == NULL) {
        printf("Empty Tree\n");
        return;
    }
    // Pass initial space count as 0
    print2DLeftToRightUtil(a, 0);
}

void freeAVL(AVL* a) {
    if (a == NULL) return;
    if (a->l) {
        freeAVL(a->l);
    }
    if (a->r) {
        freeAVL(a->r);
    }
    free(a);
}

// CODE TO TEST THE FILE
/* int main(int argc, char const* argv[]) {
    srand(time(NULL));

    AVL* a = createAVL(1, (rand() % 990) / 10.0 + 1.0);
    for (int i = 2; i <= 20; i++) {
        insertAVL(&a, i, (rand() % 990) / 10.0 + 1.0, &(a->balance));
    }

    infixTravel(a);
    print2DLeftToRight(a);
    printf("%d\n", height(a->r) - height(a->l));
    freeAVL(a);
    return 0;
} */