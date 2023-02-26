#include "autocomplete.h"
#include <stdio.h>
/*
int main(void)
{
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, "cities.txt");
    lowest_match(terms, nterms, "Tor");
    highest_match(terms, nterms, "Tor");
    
    struct term *answer;
    int n_answer;
    autocomplete(&answer, &n_answer, terms, nterms, "Tor");
    //free allocated blocks here -- not required for the project, but good practice
    return 0;
} */

int main(void){
    term* term_list;
    int num_terms;
    printf("Hello");
    read_in_terms(&term_list, &num_terms, "cities.txt");
    printf("Hello");
    printf("Number of terms: %d", num_terms);
    for(int j = 0; j<10; j++){
        printf("Term: %s Weight: %f\n", (term_list[j]).term, (term_list[j]).weight);
    }
}

