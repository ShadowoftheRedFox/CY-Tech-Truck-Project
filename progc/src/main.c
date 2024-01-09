#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./AVL_s.h"
#include "./AVL_t.h"
#include "./main.h"
// TODO: check if argument valid, check alloc result, try to change all types in errorcode for easier error tracking

ErrorCode GetTop10(AVL_t* input, AVL_t* top_10[10], int count) {
    // array invalid or invalid AVL
    if (input == NULL || top_10 == NULL) {
        return CODE_ARG_INVALID;
    }
    // to keep track in case of error
    int result = CODE_OK;
    // go to the left side
    if (input->l) {
        result = GetTop10(input->l, top_10, count);
    }
    //edge case where the route id is -1 (the AVL root)
    if (strcmp(FIRST_NODE_TOWN_NAME, input->town_name) != 0) {
        if (count < 10) {
            // fill the array if not fiull yet
            top_10[count++] = input;
        } else {
            // replace the smallest crossed city and replace it with the new if it's bigger
            int minId = 0;
            for (int i = 0; i < 10; i++) {
                if ((top_10[minId])->count > (top_10[i])->count) {
                    minId = i;
                }
            }
            // replace if bigger
            if (input->count > (top_10[minId])->count) {
                top_10[minId] = input;
            }
        }
    }
    // go to the right side
    if (input->r) {
        result = GetTop10(input->r, top_10, count);
    }
    return result;
}

ErrorCode TArgumentProcess(int argc, char const* argv[]) {
    // TODO t argument C code

    printf("Begin t process...\n"); // TEST

    // data to process
    char* line = malloc(sizeof(char) * LINE_LENGTH);
    char town_name_A[TOWN_NAME_LENGTH + 1], town_name_B[TOWN_NAME_LENGTH + 1];
    int step_id;
    // useless but needed to read line
    char driver_name[DRIVER_NAME_LENGTH + 1];
    int route_id;
    float distance;

    // create the AVL with a city name that will never appear
    AVL_t* avl = createAVL_t(FIRST_NODE_TOWN_NAME);

    int c = 0;

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
            if (step_id == 1) {
                insertAVL_t(&avl, town_name_A, &(avl->balance), true);
            } else {
                insertAVL_t(&avl, town_name_A, &(avl->balance), false);
            }
            insertAVL_t(&avl, town_name_B, &(avl->balance), false);
            c++;
        }

        fclose(sourceFile);
    }
    free(line);

    // travel infix the avl, and fprintf the ROUTE_ID;TIMES CROSSED;DRIVER CROSSED
    printf("Output file: %s\n", argv[argc - 1]);

    AVL_t* top_10[10] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };

    // get the top 10 most corssed cities and put them in the array
    ErrorCode res = GetTop10(avl, top_10, 0);

    // stop if error
    if (res != CODE_OK) {
        printf("Error while getting the top 10 cities: %d\n", res);
        return res;
    }

    // fill the output file
    FILE* output_file = fopen(argv[argc - 1], "w+");
    if (output_file == NULL) {
        // failed to save
        printf("Failed to create the output file\n");
        return CODE_FILE_CREATE_ERROR;
    }

    for (int i = 0; i < 10; i++) {
        // there can be less than 10 cities, so check if it's full
        if (top_10[i] != NULL) {
            //fprintf(output_file, "%s;%d;%d\n", (top_10[i])->town_name, ((top_10[i])->count + 2) / 2, (top_10[i])->start);
            fprintf(output_file, "%s;%d;%d\n", (top_10[i])->town_name, (top_10[i])->count, (top_10[i])->start);
        }
    }

    freeAVL_t(avl);
    fclose(output_file);
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

        // assuming the first line contains headers, only in the first source file
        if (i == 2) {
            fgets(line, sizeof(char) * (LINE_LENGTH), sourceFile);
            printf("Skipped first line: %s\n", line);
        }
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
