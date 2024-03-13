#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Butterfly.h"
#include "Photo.h"
#include "csv.h"

int main() {
    char bfilename[25];
    char pfilename[25];
    char color[25];
    ButterflyList bflyList = NULL;
    PhotoList photoList = NULL;
    ContestantList coList = NULL;

    // ask user for the name of the butterfly file
    printf("Butterfly file: ");
    fflush(stdout);
    scanf("%24s", bfilename);
    bflyList = readButterflyFile(bfilename);
    // read file and get butterfly list
    if (!bflyList) {
        printf("Butterfly file not read.\n");
        return 0;
    }

    // ask user for the name of the photos file
    printf("Photos file: ");
    fflush(stdout);
    scanf("%24s", pfilename);
    // read file and get photo list and contestant list
    photoList = readPhotoFile(pfilename, &coList, bflyList);
    if (!photoList) {
        printf("Photos file not read.\n");
        return 0;
    }

    // ask use for color
    printf("Prize color: ");
    fflush(stdout);
    scanf("%24s", color);

    // print butterfly list
    printf("===========================\n");
    printf("Butterflies in this contest\n");
    printf("===========================\n");
    printButterflyList(bflyList);

    // print all photos
    printf("\n--------------\n");
    printf("Photos entered\n");
    printf("--------------\n");
    printPhotoList(photoList);

    // print all contestants
    printf("\n++++++++++++++++++\n");
    printf("Contestant results\n");
    printf("++++++++++++++++++\n");
    printContestantList(coList);

    // print winners
    printf("--------------------------\n");
    const Contestant *w1 = findMaxColor(coList, color);
    if (w1) printf("Most photos of %s butterflies: %s\n", color, w1->name);
    else printf("Most photos of %s butterflies: <none>\n", color);
    const Contestant *w2 = findMaxSize(coList);
    if (w2) printf("Highest total size: %s\n", w2->name);
    else printf("Highest total size: <none>\n");

    return 0;
}
