#include <stdio.h>;
#include <stdlib.h>;
#include <string.h>;

#include "autocomplete.h";


void read_in_terms(struct term **terms, int *pnterms, char *filename) {
    FILE *p_file = fopen(filename, "r");
    if (p_file == NULL) { // check if fopen failed
        printf("Error opening file");
        exit(1);
    }
    int nterms = 0;
    char line[200];
    while (fgets(line, 200, p_file) != NULL) { // count number of lines in file
        nterms++;
    }
    *pnterms = nterms;
    *terms = malloc(nterms * sizeof(struct term));
    if (*terms == NULL) { // check if malloc failed
        printf("Error allocating memory");
        exit(1);
    }
    rewind(p_file);
    int i = 0;
    while (fgets(line, 200, p_file) != NULL) { // read in terms and weights
        char *token = strtok(line, " ");
        strcpy((*terms)[i].term, token);
        token = strtok(NULL, " ");
        (*terms)[i].weight = atof(token);
        i++;
    }
    fclose(p_file);
}

int lowest_match(term *terms, int nterms, char *substr){

}


int main(void){


    return 0;
}


//
// Created by Nicholas on 2023-02-01.
//
