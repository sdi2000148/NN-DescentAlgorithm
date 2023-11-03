#include "read.h"

#define BUFFER_SIZE 1024

//διαβασμα απο αρχειο των αρχικών dataset
double *readme(char *fileName, Dataset *dataset) {
    int objects = 0, dimensions = 0, count = 0;
    FILE *fp;
    char buffer[BUFFER_SIZE], *value;
    double *numbers;

    fp = fopen(fileName, "r");

    if(!fp) {
        printf("Can't open file\n");
        fclose(fp);
        return NULL;
    }

    //βρες τον αριθμό των objects και το dimension τους
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        if (objects == 0) {
            value = strtok(buffer, " \t\n\r"); 
            while (value != NULL) {
                dimensions++;
                value = strtok(NULL, " \t\n\r");
            }
        }
        objects++;
    }

    //αρχικοποιηση δομης dataset
    numbers = malloc(objects * dimensions * sizeof(double));
    dataset_initialize(dataset, objects, dimensions);

    fseek(fp, 0, SEEK_SET);

    //διαβασμα και αποθηκευση του κάθε object
    for (int row = 0; row < objects; row++) {
    
        fgets(buffer, BUFFER_SIZE, fp);

        for (int column = 0; column < dimensions; column++) {

            if (column == 0) value = strtok(buffer, " \t\n\r");
            else value = strtok(NULL, " \t\n\r");

            numbers[count] = strtod(value, NULL);
            dataset_addFeature((*dataset), row, column, &numbers[count]);
            
            count++;   
        }
    }

    fclose(fp);

    return numbers;
}


//διαβασμα απο αρχειο του dataset του διαγωνισμου SIGMOD
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

    //διαβασμα του αριθμου των objects
    if (read(fp, &N, sizeof(uint32_t) ) == 0) {
        printf("Can't read N (number of obects)\n");
        close(fp);
        return NULL;
    }

    //αρχικοποιηση δομης dataset (εδω το dimension ειναι παντα 100)
    numbers = malloc(N*dimensions*sizeof(float));

    dataset_initialize(dataset, N, dimensions);

    //διαβασμα και αποθηκευση του κάθε object
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
