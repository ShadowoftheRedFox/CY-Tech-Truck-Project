#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100

//TENTATIVE DE FAIRE UNE PARTIE DE LA MERDE EN SHELL

typedef struct town {
    int departure_number;
    int arrival_number;
    int travel_number;
    char name[SIZE];
}town;

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

typedef enum ErrorCode {
    CODE_OK,
    CODE_ARG_NULL,
    CODE_ARG_INVALID,
    CODE_FILE_OPEN_ERROR
} ErrorCode;

int SArgumentProcess(int argc, char const* argv[]) {
    printf("\n\nBegin s process...\n\n"); // TEST

    long double averageSum = 0.0;
    float min = 2147483647L;
    float max = 0.0;

    for (int i = 2; i < argc - 1; i++) {
        printf("Data source file: %s\n", argv[i]); // TEST
        FILE* csvFile = fopen(argv[i], "r");

        if (csvFile == NULL) {
            perror("Error opening file");
            return CODE_FILE_OPEN_ERROR;
        }

        // Assuming the first line contains headers and can be skipped
        char line[SIZE];

        // Process each line of the CSV file
        while (fgets(line, sizeof(line), csvFile) != NULL) {
            int route_id;
            int step_id;
            float distance;

            // Parse the ID and DISTANCE values from the line
            sscanf(line, "%d;%d;%f", &route_id, &step_id, &distance);

            averageSum += (long double)distance;

            if (distance > max) {
                max = distance;
            }
            if (distance < min) {
                min = distance;
            }

            // Process the data as needed
            printf("ROUTE_ID: %d, STEP_ID: %d, DISTANCE: %.3f\n", route_id, step_id, distance); // TEST
            //TODO push everything in a AVL 
        }

        fclose(csvFile);
    }
    return CODE_OK;
}

int main(int argc, char const* argv[]) {
    // first argument is the type of sort we're dealing with (t or s), going by just the character
    // the in between arguments are the path to the files to get the data from
    // last file is the ouput file
    if (argc < 4) {
        printf("Not enough argument.\n");
        return CODE_ARG_INVALID;
    }

    //TEST --------------------------------
    printf("Type of data: %s\n", argv[1]);
    for (int i = 2; i < argc - 1; i++) {
        printf("Data source file: %s\n", argv[i]);
    }
    printf("Output file: %s\n", argv[argc - 1]);
    //TEST --------------------------------

    return SArgumentProcess(argc, argv);

    return CODE_OK;
}
