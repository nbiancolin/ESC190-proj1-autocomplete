#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "autocomplete.h"

/*
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
}*/

void read_in_terms(struct term **terms, int *pnterms, char *filename) {
    FILE *p_file = fopen(filename, "r");
    //FILE *p_file = fopen("cities2.txt", "r");
    if (p_file == NULL) { // check if fopen failed
        printf("Error opening file");
        exit(1);
    }
    int nterms = 0;
    char line[200];

    //while (fgets(line, 200, p_file) != NULL) { // old dumb code to count lines (deprecated)
    //    nterms++;
    //}

    fgets(line, 200, p_file); //gets first line of file and puts it in line
    nterms = atoi(line); //gets int of first line of file
    *pnterms = nterms; //assigns pointer
    *terms = malloc(nterms * sizeof(struct term)); //malloc's based on number of terms.
    if (*terms == NULL) { // check if malloc failed
        printf("Error allocating memory");
        exit(1);
    }
    rewind(p_file);
    fgets(line, 200, p_file); //skips over first line (bc it's just the number of terms)
    int i = 0;
    char *mass;
    while (fgets(line, 200, p_file) != NULL) { // read in terms and weights
        /*
        char *token = strtok(line, " ");
        strcpy((*terms)[i].term, token);
        token = strtok(NULL, " ");
        (*terms)[i].weight = atof(token);
        i++;
         */

        char *token = strtok(line, " ");
        while(*token == ' ')token++; //should take care of the whitespace at the beginning of each line (STUPID AND I HATE IT) -nick
        //printf("%s", token);
        token = strtok(token, "\t");
        (*terms)[i].weight = atof(token); //weight works, term does not.
        //char *token2 = strtok(line, " ");
        token = strtok(NULL, "\n");
        //char *token2 = strtok(line,"\t");
        //token2 = strtok(NULL,"\n");

        strcpy((*terms)[i].term, token);
        //token = strtok(line, "\t");
        //token = strtok(NULL, "\t");
        //strcpy((*terms)[i].term, token);
        //token = strtok(NULL, "\t");
        //(*terms)[i].weight = atof(token);
        i++;
    }
    fclose(p_file);
}

/*
int main(void) {
    term* term_list;
    int num_terms;
    printf("Hello");
    read_in_terms(&term_list, &num_terms, "cities.txt");
    printf("Hello");
    for(int j = 0; j<10; j++){
        printf("Term: %s\n Weight: %f", (term_list[j]).term, (term_list[j]).weight);
    }

    return 0;
} */


//
// Created by Nicholas on 2023-02-01.
//
