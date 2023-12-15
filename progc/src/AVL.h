#ifndef HEADER_AVL
#define HEADER_AVL

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

/**
 *@brief Create the root of an AVL
 *
 * @param roadId The ID of the road to be put in the AVL
 * @param distance The length of the road that is put in
 * @return AVL* The AVL created
 */
AVL* createAVL(int roadId, float distance);
/**
 *@brief Insert a new node in the AVL
 *
 * @param AVL The already existing AVL
 * @param roadId The ID of the road to be put in the AVL
 * @param distance The length of the road that is put in
 * @param balance The balance of the AVL node
 */
void insertAVL(AVL** AVL, int roadId, float distance, int* balance);
/**
 *@brief Free the AVL from the heap
 *
 * @param AVL The AVL to free
 */
void freeAVL(AVL* AVL);

/**
 *@brief Beauty print the AVL in 2D
 *
 * @param AVL The AVL to print
 */
void print2DLeftToRight(AVL* AVL);
/**
 *@brief The infix travel of the AVL
 *
 * @param AVL The AVL to travel
 */
void infixTravel(AVL* AVL);

int height(AVL* a);

#endif