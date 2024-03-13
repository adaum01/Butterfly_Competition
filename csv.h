#ifndef CSV_H
#define CSV_H

#include <stdio.h>

// read a string field from a CSV file
int getCSVString(char * str, int limit, FILE* fp);

// read an integer field from a CSV file
int getCSVInt(int *n, FILE* fp);

#endif //CSV_H
