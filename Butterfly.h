#ifndef BUTTERFLY_H
#define BUTTERFLY_H

#include <stdio.h>

struct butterfly {
    char name[51];     // common name
    char sciName[51];  // scientific name
    char colors[51];   // main colors on wing (top)
    int size;          // typical size (inches)
};
typedef struct butterfly Butterfly;

struct butterflyNode {
    struct butterfly * bfly;
    struct butterflyNode * next;
};
typedef struct butterflyNode ButterflyNode;
typedef struct butterflyNode* ButterflyList;

// read butterfly info from a CSV file
Butterfly * newButterflyFromFile(FILE* fp);

// read all butterfly info from a CSV file, creating a list
ButterflyList readButterflyFile(const char* filename);

// print butterfly info to standard output
void printButterfly(const Butterfly* b);

// print a list of butterflies to standard output
void printButterflyList(const ButterflyNode * list);

// add butterfly to list, sorted by common name
// returns head of updated list
ButterflyList addButterfly(Butterfly * b, ButterflyList list);


#endif //BUTTERFLY_H
