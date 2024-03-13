#include "Butterfly.h"
#include "csv.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// read butterfly info from a CSV file
Butterfly * newButterflyFromFile(FILE* fp){
    struct butterfly *b = (struct butterfly*)malloc(sizeof(struct butterfly));
    int *num = &(b->size);
    int x1 = getCSVString(b->name, 51, fp);
    int x2 = getCSVString(b->sciName, 51, fp);
    int x3 = getCSVString(b->colors, 51, fp);
    int x4 = getCSVInt(num, fp);
    if (x4 == 0) getCSVString(b->colors, 51, fp);   //special case for
    if(x1 == -1 || x2 == -1 || x3 == -1|| x4 == -1){
        return NULL;
    }
    return b;
}

// read all butterfly info from a CSV file, creating a list
ButterflyList readButterflyFile(const char* filename){
    FILE* fp = fopen(filename, "r");
    if(fp == 0){
        return NULL;
    }
    struct butterfly *headerBfly;// = (struct butterfly*)malloc(sizeof(struct butterfly));
    newButterflyFromFile(fp);  //cycle out column headers
    headerBfly = newButterflyFromFile(fp);
    struct butterflyNode *header = (struct butterflyNode*)malloc(sizeof(struct butterflyNode));
    header->bfly = headerBfly;
    header->next = NULL;

    struct butterfly *newBfly;
    struct butterflyNode *newNode;


    while (true){
        struct butterflyNode *p = header;
        struct butterflyNode *prev = NULL;
        newBfly = newButterflyFromFile(fp);
        if(newBfly == NULL) break;

        newNode = (struct butterflyNode*)malloc(sizeof(struct butterflyNode));
        newNode->bfly = newBfly;
        newNode->next = NULL;

        while((p != NULL) && (strcmp(p->bfly->name, newNode->bfly->name) < 0)){
            prev = p;
            p = p->next;
        }
        if(prev == NULL) {
            newNode->next = header;
            header = newNode;
        }
        else {
            prev->next = newNode;
            newNode->next = p;
        }
    }
    fclose(fp);
    return header;
}

// print butterfly info to standard output
void printButterfly(const Butterfly* b){
    printf("%s (%s)", b->name, b->sciName);
}

// print a list of butterflies to standard output
void printButterflyList(const ButterflyNode * list){
    if(list != NULL) {
        printButterfly(list->bfly);
        printf("\n");
        struct butterflyNode *p = list->next;
        while(p != NULL){
            printButterfly(p->bfly);
            printf("\n");
            p = p->next;
        }
    }
}

// add butterfly to list, sorted by common name
// returns head of updated list
ButterflyList addButterfly(Butterfly * b, ButterflyList list){
    struct butterflyNode *header = list;
    struct butterflyNode *p = header;
    struct butterflyNode *prev = NULL;

    struct butterflyNode *newNode = (struct butterflyNode*)malloc(sizeof(struct butterflyNode));
    newNode->bfly = b;
    newNode->next = NULL;

    while((p != NULL) && (strcmp(p->bfly->name, newNode->bfly->name) < 0)){
        prev = p;
        p = p->next;
    }
    if(prev == NULL) {
        newNode->next = header;
        header = newNode;
    }
    else {
        prev->next = newNode;
        newNode->next = p;
    }
    return header;
}
