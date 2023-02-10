#include <stdio.h>;
#include <stdlib.h>;
#include <string.h>;

#include "autocomplete.h";


void read_in_terms(struct term **terms, int *pnterms, char *filename){
    FILE *file;
    file = fopen(filename, "r");

    //*terms = malloc((int)sizeof(char) * *pnterms); //Allocates enough memory for the file.
    *terms; //= pointer to all the words in memory.


    char ch;
    char *buffer = '\0'; //Purpose of the buffer (in my mind) was to store the word until a tab is found, then store the pointer to the buffer in the term struct.

    while((ch = fgetc(file)) != EOF){ //Finds the number of terms in the file.
        if(ch == '\t'){
            *pnterms += 1; //I found out how to count the terms in this file, but don't know how to store them.
            //**terms->term = buffer; //should store the pointer to the buffer in the term struct.
            //*buffer = '\0';
        } else {
            //buffer = strcat(buffer, (char *) ch);
        }

    }

    *terms = malloc((int)sizeof(char) * *pnterms); //Allocates enough memory for the file.

    fclose(file);


}



int main(void){


    return 0;
}


//
// Created by Nicholas on 2023-02-01.
//
