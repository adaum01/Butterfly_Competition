#ifndef PHOTO_H
#define PHOTO_H

#include <stdio.h>
#include "Butterfly.h"

struct photo {
    int id;     // unique identifier
    struct contestant * who;  // who took the photo
    struct butterfly * what;  // which butterfly
};
typedef struct photo Photo;

struct photoNode {
    struct photo * p;
    struct photoNode * next;
};
typedef struct photoNode PhotoNode;
typedef struct photoNode* PhotoList;

struct contestant {
    char name[51];      // name of photographer
    int numPhotos;      // number of photos entered
    PhotoList photos;   // list of photos entered
};
typedef struct contestant Contestant;

struct contestantNode {
    struct contestant * c;
    struct contestantNode * next;
};
typedef struct contestantNode ContestantNode;
typedef struct contestantNode* ContestantList;

// read photo from CSV file if butterfly is in the list
// create and add contestant to list, if necessary
Photo * newPhotoFromFile(FILE * fp, ContestantList * p, const ButterflyNode* b, int* eof);

// read all photos from CSV file
PhotoList readPhotoFile(const char * filename, ContestantList * p, const ButterflyNode * b);

// print photo information to standard output
void printPhoto(const Photo* p);

// print list of photos to standard output
void printPhotoList(const PhotoNode* list);

// add photo to list, sorted by ID
PhotoList addPhoto(Photo * p, PhotoList list);

// print contestant info to standard output
void printContestant(const Contestant* c);

// print list of contestants to standard output
void printContestantList(const ContestantNode* list);

// add contestant to list, sorted by name
ContestantList addContestant(Contestant * c, ContestantList list);

// return number of photos by the contestant with the specified color
int countColor(const Contestant* c, const char *color);

// return contestant with the most photos of the specified color
const Contestant * findMaxColor(const ContestantNode* list, const char * color);

// return total size of butterflies in all photos
int totalSize(const Contestant* c);

// return contestant with the largest total size of butterflies in photos
const Contestant * findMaxSize(const ContestantNode* list);



#endif //SPR21_PROG3_PHOTO_H
