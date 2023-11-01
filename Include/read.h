#include "dataset.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

float *readSigmod(char *fileName, Dataset *dataset);
double *readme(char *fileName, Dataset *dataset);