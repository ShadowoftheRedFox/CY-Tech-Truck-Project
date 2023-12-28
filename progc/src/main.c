#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./AVL_s.h"
#include "./AVL_t.h"
#include "./main.h"
// TODO: check if argument valid, check alloc result, try to change all types in errorcode for easier error tracking

ErrorCode TArgumentProcess(int argc, char const* argv[]) {
    // TODO t argument C code

    printf("Begin t process...\n"); // TEST

    // data to process
    char* line = malloc(sizeof(char) * LINE_LENGTH);
    char town_name_A[TOWN_NAME_LENGTH + 1], town_name_B[TOWN_NAME_LENGTH + 1];
    char driver_name[DRIVER_NAME_LENGTH + 1];
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
        fgets(line, sizeof(char) * (LINE_LENGTH), sourceFile);
        // process each line of the CSV file

        while (!feof(sourceFile)) {
            fgets(line, sizeof(char) * (LINE_LENGTH), sourceFile);
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

ErrorCode FillOutputFile_s(FILE* handle, AVL_s* input) {
    // file handle invalid or invalid AVL
    if (handle == NULL || input == NULL) {
        return CODE_ARG_INVALID;
    }
    // to keep track in case of error
    int result = CODE_OK;
    // go to the left side
    if (input->l) {
        result = FillOutputFile_s(handle, input->l);
    }
    //edge case where the route id is -1 (the AVL root)
    if (input->roadId != -1) {
        fprintf(handle, "%d;%.3f;%.3f;%.3f\n", input->roadId, input->averageSum / (float)input->stepNumber, input->min, input->max);
    }
    // go to the right side
    if (input->r) {
        result = FillOutputFile_s(handle, input->r);
    }
    return result;
}

ErrorCode SArgumentProcess(int argc, char const* argv[]) {
    printf("Begin s process...\n"); // TEST

    char* line = malloc(sizeof(char) * LINE_LENGTH);
    int route_id;
    float distance;
    //useless but needed for parsing
    int step_id;
    char town_name_A[TOWN_NAME_LENGTH + 1];
    char town_name_B[TOWN_NAME_LENGTH + 1];
    char driver_name[DRIVER_NAME_LENGTH];

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
            fgets(line, sizeof(char) * LINE_LENGTH, sourceFile);
            if (ferror(sourceFile)) {
                return CODE_FILE_READ_ERROR;
            }

            // parse the data from the line
            sscanf(line, "%d;%d;%50[^;];%50[^;];%f;%[^\n]", &route_id, &step_id, town_name_A, town_name_B, &distance, driver_name);

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

    ErrorCode result = FillOutputFile_s(output_file, avl);
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
