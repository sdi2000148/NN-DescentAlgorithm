#include "read.h"

#define BUFFER_SIZE 1024

double *readme(char *fileName, Dataset *dataset, int objects, int dimensions) {
    int row = 0, column, i = 0;
    FILE *fp;
    char buffer[BUFFER_SIZE], *value;
    double *numbers = malloc(objects * dimensions * sizeof(double));
    
    dataset_initialize(dataset, objects, dimensions);

    fp = fopen(fileName, "r");
    

    if(!fp) {
        printf("Can't open file\n");
        fclose(fp);
        return numbers;
    }

    while(fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        value = strtok(buffer, " \t\n\r");
        column = 0;

        while(value != NULL) {
            numbers[i] = strtod(value, NULL);
            dataset_addFeature((*dataset), row, column, &numbers[i]);
            column++;
            i++;
            value = strtok(NULL, " \t\n\r");
        }
        row++;
    }

    fclose(fp);

    return numbers;
}

float *readSigmod(char *fileName, Dataset *dataset) {
    float *numbers;
    int row = 0, column = 0, dimensions = 100, fp;
    uint32_t N;
    

    fp = open(fileName ,O_RDONLY,0);
    
    if(fp == -1) {
        printf("Can't open file\n");
        close(fp);
        return NULL;
    }

    if (read(fp, &N, sizeof(uint32_t) ) == 0) {
        printf("Can't read N (number of obects)\n");
        close(fp);
        return NULL;
    }

    numbers = malloc(N*dimensions*sizeof(float));

    dataset_initialize(dataset, N, dimensions);

    for (int i = 0; i < ((int)N * dimensions); i++) {
        if (read(fp, &numbers[i], sizeof(float)) == 0) {
            printf("Can't read float (item of obect)\n");
            close(fp);
            return numbers;
        }

        dataset_addFeature((*dataset), row, column, &numbers[i]);
        
        column++;
        if (column == dimensions) {
            column = 0;
            row++;
        }
    }

    close(fp);
    return numbers;
}
