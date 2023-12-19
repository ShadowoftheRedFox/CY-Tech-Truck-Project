#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./AVL_s.h"
#include "./AVL_t.h"
#include "./main.h"

/*
TODO: check if argument valid, check alloc result, try to change all types in errorcode for easier error tracking
*/
typedef struct town {
    int departure_number;
    int arrival_number;
    int travel_number;
    char name[NAME_ARRAY_SIZE];
}town;

void check_driver() {

}

//calculation of the number of travels for each town
int calculationtravels(FILE* t_argument) {
    int number = 0;
    FILE* file_town_a = NULL;
    FILE* file_town_b = NULL;
    file_town_a = fopen("./temp/t_argument_townA.txt", "r+");
    if (file_town_a == NULL) {
        printf("Error code: %s \n", errno);
        printf("Error message: %s \n", strerror(errno));
    }
    file_town_b = fopen("./temp/t_argument_townB.txt", "r+");
    if (file_town_b == NULL) {
        printf("Error code: %s \n", errno);
        printf("Error message: %s \n", strerror(errno));
    }
    //variables that will be used to count the number of appearances of each town
    int town_a_number;
    int town_b_number;
    town** towns;
    fclose(file_town_a);
    fclose(file_town_b);
    return number;
}

ErrorCode TArgumentProcess(int argc, char const* argv[]) {
    // TODO t argument C code

    printf("Begin t process...\n"); // TEST

    // data to process
    char* line = malloc(sizeof(char) * NAME_ARRAY_SIZE);
    char town_name_A[TOWN_NAME_LENGTH], town_name_B[TOWN_NAME_LENGTH];
    char driver_name[DRIVER_NAME_LENGTH];
    int route_id;
    // useless but needed to read line
    float distance;
    int step_id;

    // create the AVL with a city name that will never appear
    AVL_t* avl = createAVL_t("Town_Test_0");

    // read each file
    for (int i = 2; i < argc - 1; i++) {
        printf("Data source file: %s\n", argv[i]); // TEST
        FILE* sourceFile = fopen(argv[i], "r");

        if (sourceFile == NULL) {
            perror("Error opening file");
            return CODE_FILE_OPEN_ERROR;
        }

        // assuming the first line contains headers 
        fgets(line, sizeof(char) * (NAME_ARRAY_SIZE), sourceFile);
        // process each line of the CSV file

        while (!feof(sourceFile)) {
            fgets(line, sizeof(char) * (NAME_ARRAY_SIZE), sourceFile);
            if (ferror(sourceFile)) {
                return CODE_FILE_READ_ERROR;
            }

            // parse the data from the line
            sscanf(line, "%d;%d;%50[^;];%50[^;];%f;%[^\n]", &route_id, &step_id, town_name_A, town_name_B, &distance, driver_name);

            // TEST
            // printf("ROUTE_ID: %d,\t TOWN A: %s,\t TOWN B: %s,\t DRIVER: %s\n", route_id, town_name_A, town_name_B, driver_name);

            // if the names are the same in the same step
            if (strcmp(town_name_A, town_name_B) == 0) {
                insertAVL_t(&avl, town_name_A, &(avl->balance));
            } else {
                insertAVL_t(&avl, town_name_A, &(avl->balance));
                insertAVL_t(&avl, town_name_B, &(avl->balance));
            }
        }

        fclose(sourceFile);
    }

    // travel infix the avl, and fprintf the ROUTE_ID;TIMES CROSSED;DRIVER CROSSED
    printf("Output file: %s\n", argv[argc - 1]);

    AVL_t* temp = avl;
    // get the top 10 city in crossed amount
    while (height_t(temp) > 11) {
        printf("%d\n", height_t(temp));
        temp = temp->r;
    }
    printf("%d\n", height_t(temp));

    FILE* output_file = fopen(argv[argc - 1], "w+");
    if (output_file == NULL) {
        // failed to save
        printf("Failed to create the output file\n");
        return CODE_FILE_CREATE_ERROR;
    }

    return CODE_OK;
}

ErrorCode FillOutputFile(FILE* handle, AVL_s* input) {
    // file handle invalid or invalid AVL
    if (handle == NULL || input == NULL) {
        return CODE_ARG_INVALID;
    }
    // to keep track in case of error
    int result = CODE_OK;
    // go to the left side
    if (input->l) {
        result = FillOutputFile(handle, input->l);
    }
    //edge case where the route id is -1 (the AVL root)
    if (input->roadId != -1) {
        fprintf(handle, "%d;%.3f;%.3f;%.3f\n", input->roadId, input->averageSum / (float)input->stepNumber, input->min, input->max);
    }
    // go to the right side
    if (input->r) {
        result = FillOutputFile(handle, input->r);
    }
    return result;
}

ErrorCode SArgumentProcess(int argc, char const* argv[]) {
    printf("Begin s process...\n"); // TEST

    char* line = malloc(sizeof(char) * NAME_ARRAY_SIZE);
    int route_id;
    float distance;

    // create the AVL starting from route ID -1 since ID are all positiv
    AVL_s* avl = createAVL_s(-1, 0.0);

    // read each file
    for (int i = 2; i < argc - 1; i++) {
        printf("Data source file: %s\n", argv[i]); // TEST
        FILE* sourceFile = fopen(argv[i], "r");

        if (sourceFile == NULL) {
            perror("Error opening file");
            return CODE_FILE_OPEN_ERROR;
        }

        // assuming the first line do not contains headers 
        // process each line of the CSV file

        while (!feof(sourceFile)) {
            fgets(line, sizeof(char) * NAME_ARRAY_SIZE, sourceFile);
            if (ferror(sourceFile)) {
                return CODE_FILE_READ_ERROR;
            }

            // parse the Route ID and Distance values from the line
            sscanf(line, "%d;%f", &route_id, &distance);

            // TEST
            // printf("ROUTE_ID: %d, DISTANCE: %.3f\n", route_id, distance);

            // push everything in a AVL 
            insertAVL_s(&avl, route_id, distance, &(avl->balance));
        }

        fclose(sourceFile);
    }

    // travel infix the avl, and fprintf the ROUTE_ID;AVERAGE;MIN;MAX
    printf("Output file: %s\n", argv[argc - 1]);

    FILE* output_file = fopen(argv[argc - 1], "w+");
    if (output_file == NULL) {
        // failed to save
        printf("Failed to create the output file\n");
        return CODE_FILE_CREATE_ERROR;
    }

    //TEST -------------------------------------------------
    // print2DLeftToRight(avl);
    // printf("balance %d\n", height(avl->r) - height(avl->l));
    //TEST -------------------------------------------------

    ErrorCode result = FillOutputFile(output_file, avl);
    if (result != CODE_OK) {
        //BUG false error report
        // printf("Error while filling the output file: %d\n", result);
    }

    // close the file handle
    fclose(output_file);
    // free the avl
    freeAVL_s(avl);
    // free the line buffer
    free(line);

    return CODE_OK;
}

int main(int argc, char const* argv[]) {
    // first argument is the type of sort we're dealing with (t or s), going by just the character
    // the in between arguments are the path to the files to get the data from
    // last file is the output file
    if (argc < 4) {
        printf("Not enough argument.\n");
        return CODE_ARG_INVALID;
    }

    //TEST --------------------------------
   /*  printf("Type of data: %s\n", argv[1]);
    for (int i = 2; i < argc - 1; i++) {
        printf("Data source file: %s\n", argv[i]);
    }
    printf("Output file: %s\n", argv[argc - 1]); */
    //TEST --------------------------------

    if (argv[1][0] == 's') {
        return SArgumentProcess(argc, argv);
    } else if (argv[1][0] == 't') {
        return TArgumentProcess(argc, argv);
    } else {
        printf("Unknown first argument\"%c\".\nAborting.\n", argv[1][0]);
        return CODE_ARG_INVALID;
    }
    return CODE_OK;
}
