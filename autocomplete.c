#include <stdio.h>;
#include <stdlib.h>;
#include <string.h>;

#include "autocomplete.h";


void read_in_terms(struct term **terms, int *pnterms, char *filename){
    FILE *file;
    file = fopen(filename, "r");

    *terms = malloc((int)sizeof(char) * *pnterms); //Allocates enough memory for the file.

    char ch;
    char *buffer = '\0';

    while((ch = fgetc(file)) != EOF){ //This *should* work... no idea if it actually does haha.
        if(ch == '\t'){
            *pnterms += 1;
            **terms->term = buffer; //doesnt work.. idky why
            *buffer = '\0';
        } else {
            buffer = strcat(buffer, (char *) ch);
        }
    }

    fclose(file);


}



int main(void){


    return 0;
}


//
// Created by Nicholas on 2023-02-01.
//
