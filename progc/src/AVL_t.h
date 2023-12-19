#ifndef HEADER_AVL_T
#define HEADER_AVL_T
// TODO edit comments too

#define TOWN_NAME_LENGTH 50
#define DRIVER_NAME_LENGTH 50

typedef struct AVL_t {
    struct AVL_t* l;
    struct AVL_t* r;
    char town_name[TOWN_NAME_LENGTH];
    int count;
    int balance;
} AVL_t;


AVL_t* createAVL_t(const char* town_name);

void insertAVL_t(AVL_t** AVL, const char* town_name, int* balance);
/**
 *@brief Free the AVL from the heap
 *
 * @param AVL The AVL to free
 */
void freeAVL_t(AVL_t* AVL);

/**
 *@brief Beauty print the AVL in 2D
 *
 * @param AVL The AVL to print
 */
void print2DLeftToRight_t(AVL_t* AVL);
/**
 *@brief The infix travel of the AVL
 *
 * @param AVL The AVL to travel
 */
void infixTravel_t(AVL_t* AVL);

/**
 *@brief Get the number of node in the avl
 *
 * @param avl the avl to count from
 * @return int the number of node contained
 */
int height_t(AVL_t* avl);

#endif