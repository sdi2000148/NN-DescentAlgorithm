#include "dataset.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* Given a filename(or path), initialize dataset and fill it with the features of the SIGMOD competition data files */
float *readSigmod(char *fileName, Dataset *dataset);

/* Given a filename(or path), initialize dataset and fill it with the features of the ASCII files of the specific datasets */
double *readme(char *fileName, Dataset *dataset);