#ifndef HEADER_AVL_S
#define HEADER_AVL_S

#include "main.h"

typedef struct AVL_s {
    struct AVL_s* l;
    struct AVL_s* r;
    float min;
    float max;
    float averageSum;
    int roadId;
    int stepNumber;
    int balance;
} AVL_s;

/**
 *@brief Create the root of an AVL
 *
 * @param roadId The ID of the road to be put in the AVL
 * @param distance The length of the road that is put in
 * @return AVL* The AVL created
 */
AVL_s* createAVL_s(int roadId, float distance);
/**
 *@brief Insert a new node in the AVL
 *
 * @param AVL The already existing AVL
 * @param roadId The ID of the road to be put in the AVL
 * @param distance The length of the road that is put in
 * @param balance The balance of the AVL node
 */
void insertAVL_s(AVL_s** AVL, int roadId, float distance, int* balance);
/**
 *@brief Free the AVL from the heap
 *
 * @param AVL The AVL to free
 */
void freeAVL_s(AVL_s* AVL);

/**
 *@brief Beauty print the AVL in 2D
 *
 * @param AVL The AVL to print
 */
void print2DLeftToRight_s(AVL_s* AVL);
/**
 *@brief The infix travel of the AVL
 *
 * @param AVL The AVL to travel
 */
void infixTravel_s(AVL_s* AVL);

#endif