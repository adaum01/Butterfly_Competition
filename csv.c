#include "csv.h"
#include <stdio.h>

// read a string field from a CSV file
int getCSVString(char * str, int limit, FILE* fp){


    int holdInt;
    char holdarr;               //used to check wrong type
    char *holdc = &holdarr;
    if ((fscanf(fp, "%d%c", &holdInt, holdc)) == 2) {    //if integer is read, wrong type, return 0
        return 0;
    }


    int count = 0;          //counter to move through return string
    int checkDbl = 0;
    int breakVal = 0;


    if (fscanf(fp, "%c", holdc) != EOF) {   //check first char
        if(*holdc == '\"'){
            while ((fscanf(fp, "%c", holdc)) != EOF){
                if (count < limit -1) {
                    if (checkDbl == 1) {
                        if (*holdc == '\"'){
                            *(str + count) = '\"';
                            checkDbl = 0;
                            count++;
                        }
                        else{
                            *(str + count) = '\0';
                            break;
                        }
                    }
                    else if (*holdc == '\"') {
                        checkDbl = 1;
                    }
                    else{
                        *(str + count) = *holdc;
                        count++;
                    }
                }
                else{
                    *(str + limit - 1) = '\0';

                    if (checkDbl == 1) {
                        if (*holdc == '\"'){
                            checkDbl = 0;
                        }
                        else{
                            break;
                        }
                    }
                    else if (*holdc == '\"') {
                        checkDbl = 1;
                    }
                }
            }
        }
        else{
            *(str + count) = *holdc;
            count++;
            while ((fscanf(fp, "%c", holdc)) != EOF){
                if(*holdc == ',' || *holdc == '\n'){
                    *(str + count) = '\0';
                    breakVal = 1;
                }
                else if(count < limit - 1){
                    *(str + count) = *holdc;
                    count++;
                }
                else {
                    *(str + count) = '\0';
                }
                if(breakVal == 1){
                    break;
                }
            }
        }
    }
    else {
        return -1;
    }
    return 1;
}

// read an integer field from a CSV file
int getCSVInt(int *n, FILE* fp){
    char hold;

    if((fscanf(fp, "%d", n)) == 0){
        return 0;
    }
    if((fscanf(fp, "%c", &hold)) == EOF){
        return -1;
    }
    return 1;
}