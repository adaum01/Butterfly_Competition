#include "Photo.h"
#include "csv.h"
#include <string.h>
#include <stdlib.h>

int photoCount = 1;

// read photo from CSV file if butterfly is in the list
// create and add contestant to list, if necessary
Photo * newPhotoFromFile(FILE * fp, ContestantList * p, const ButterflyNode* b, int* eof){  //NOT DONE
    *eof = 0;
    char cName[51];
    char bName[51];
    char *cNameHold = cName;
    char *bNameHold = bName;

    struct butterflyNode *pBfly = b->next;
    struct contestantNode *newList = *p;

    struct photo *newPhoto = (struct photo*)malloc(sizeof(struct photo));
    int x1 = getCSVString(cNameHold, 51, fp);
    int x2 = getCSVString(bNameHold, 51, fp);
    if(x1 == 0 || x2 == 0){
        return NULL;
    }
    if(x1 == -1 || x2 == -1){
        *eof = 1;
        return NULL;
    }

    //test if butterfly exists
    int bflyFound = 0;
    if(b != NULL) {
        if (strcmp(b->bfly->name, bNameHold) == 0 || strcmp(b->bfly->sciName, bNameHold) == 0) {
            bflyFound = 1;
            newPhoto->what = b->bfly;
            newPhoto->id = photoCount;
            photoCount++;
        }
        while (pBfly != NULL) {
            if (strcmp(pBfly->bfly->name, bNameHold) == 0 || strcmp(pBfly->bfly->sciName, bNameHold) == 0) {
                bflyFound = 1;
                newPhoto->what = pBfly->bfly;
                newPhoto->id = photoCount;
                photoCount++;
            }
            pBfly = pBfly->next;
        }
    }
    if(bflyFound == 0){
        *eof = 0;
        free(newPhoto);
        return NULL;
    }


    int contestantFound = 0;
    while(newList != NULL){
        if(strcmp(newList->c->name, cNameHold) == 0){
            contestantFound = 1;
            newPhoto->who = newList->c;
            addPhoto(newPhoto, newList->c->photos);
            newList->c->numPhotos += 1;
        }
        newList = newList->next;
    }
    if(contestantFound == 0){
        struct contestant *newContestant = (struct contestant*)malloc(sizeof(struct contestant));
        strcpy(newContestant->name, cNameHold);
        newContestant->numPhotos = 1;
        newPhoto->who = newContestant;

        struct photoNode *newPhotoNode = (struct photoNode*)malloc(sizeof(struct photoNode));
        newPhotoNode->p = newPhoto;
        newPhotoNode->next = NULL;
        newContestant->photos = newPhotoNode;

        addPhoto(newPhoto, newContestant->photos);
        *p = addContestant(newContestant, *p);
    }
    return newPhoto;
}

// read all photos from CSV file
PhotoList readPhotoFile(const char * filename, ContestantList * p, const ButterflyNode * b){
    FILE* fp = fopen(filename, "r");
    if(fp == 0){
        return NULL;
    }

    PhotoList retList = NULL;

    int eofVal = 0;
    int *eof = &eofVal;
    newPhotoFromFile(fp, p, b, eof);
    if(!eofVal){
        struct photo *newPhoto = (struct photo*)malloc(sizeof(struct photo));
        newPhoto = newPhotoFromFile(fp, p, b, eof);
        if(!eofVal) {
            retList = addPhoto(newPhoto, retList);
        }
    }

    while(!eofVal) {
        struct photo *newPhoto = (struct photo*)malloc(sizeof(struct photo));
        newPhoto = newPhotoFromFile(fp, p, b, eof);
        if(newPhoto != NULL){
            printf("%s\n", newPhoto->who->name);
            retList = addPhoto(newPhoto, retList);
        }
    }
    fclose(fp);
    return retList;
}

// print photo information to standard output
void printPhoto(const Photo* p){
    printf("%d - %s: ", p->id, p->who->name);
    printButterfly(p->what);
}

// print list of photos to standard output
void printPhotoList(const PhotoNode* list){
    if(list != NULL){
        printPhoto(list->p);
        printf("\n");
        struct photoNode *p = list->next;
        while(p != NULL){
            printPhoto(p->p);
            printf("\n");
            p = p->next;
        }
    }
}

// add photo to list, sorted by ID
PhotoList addPhoto(Photo * p, PhotoList list){
    struct photoNode *header = list;
    struct photoNode *p1 = header;
    struct photoNode *prev = NULL;

    struct photoNode *newNode = (struct photoNode*)malloc(sizeof(struct photoNode));
    newNode->p = p;
    newNode->next = NULL;

    while((p1 != NULL) && ((p1->p->id) < (newNode->p->id))){
        prev = p1;
        p1 = p1->next;
    }
    if(prev == NULL) {
        newNode->next = header;
        header = newNode;
    }
    else {
        prev->next = newNode;
        newNode->next = p1;
    }
    return header;
}

// print contestant info to standard output
void printContestant(const Contestant* c){
    printf("%s (%d)\n", c->name, c->numPhotos);
    struct photoNode *p = c->photos;
    while(p != NULL){
        printf("%d ", p->p->id);
        printButterfly(p->p->what);
        printf("\n");
        p = p->next;
    }
    printf("\n");
}

// print list of contestants to standard output
void printContestantList(const ContestantNode* list){
    if(list != NULL) {
        printContestant(list->c);
        struct contestantNode *p = list->next;
        while(p != NULL){
            printContestant(p->c);
            p = p->next;
        }
    }
}

// add contestant to list, sorted by name
ContestantList addContestant(Contestant * c, ContestantList list){
    struct contestantNode *header = list;
    struct contestantNode *p = header;
    struct contestantNode *prev = NULL;

    struct contestantNode *newNode = (struct contestantNode*)malloc(sizeof(struct contestantNode));
    newNode->c = c;
    newNode->next = NULL;

    while((p != NULL) && (strcmp(p->c->name, newNode->c->name) < 0)){
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

// return number of photos by the contestant with the specified color
int countColor(const Contestant* c, const char *color){
    int count = 0;
    struct photoNode *p = c->photos;
    while(p != NULL){
        if(strstr(p->p->what->colors, color) != NULL){
            count++;
        }
        p = p->next;
    }
    return count;
}

// return contestant with the most photos of the specified color
const Contestant * findMaxColor(const ContestantNode* list, const char * color){
    if(list != NULL){
        int maxCount = countColor(list->c, color);
        struct contestant *maxC = list->c;
        struct contestantNode *p = list->next;
        while(p != NULL){
            if(maxCount < countColor(p->c, color)){
                maxCount = countColor(p->c, color);
                maxC = p->c;
            }
            p = p->next;
        }
        if(maxCount == 0){
            return NULL;
        }
        else{
            return maxC;
        }
    }
    else{
        return NULL;
    }
}

// return total size of butterflies in all photos
int totalSize(const Contestant* c){
    int total = 0;
    struct photoNode *p = c->photos;
    while(p != NULL){
        total += p->p->what->size;
        p = p->next;
    }
    return total;
}

// return contestant with the largest total size of butterflies in photos
const Contestant * findMaxSize(const ContestantNode* list){
    if(list != NULL){
        int maxSize = totalSize(list->c);
        struct contestant *maxC = list->c;
        struct contestantNode *p = list->next;
        while(p != NULL){
            if(maxSize < totalSize(p->c)){
                maxSize = totalSize(p->c);
                maxC = p->c;
            }
            p = p->next;
        }
        return maxC;
    }
    else{
        return NULL;
    }
}