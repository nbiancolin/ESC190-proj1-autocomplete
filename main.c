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
    term* answer;
    int num_terms;
    int num_answer;
    printf("Hello");
    read_in_terms(&term_list, &num_terms, "cities.txt"); //HASSAN MY CODE WORKS (at least, on my pc it works every time, maybe there's an error in your wikitionary file?)
    printf("Hello");
    printf("Number of terms: %d", num_terms);
    for(int j = 0; j<10; j++){
        printf("Term: %s Weight: %f\n", (term_list[j]).term, (term_list[j]).weight);
    }

    printf("Hello");
    int something = lowest_match(term_list, num_terms, "Tor");
    int something2 = highest_match(term_list, num_terms, "Tor");
    printf("Hello");
    printf("Lowest match: %d", something);
    printf("term: %s", term_list[something].term);
    printf("Highest match: %d", something2);
    printf("term: %s", term_list[something2].term);
    printf("\n");//newline

    printf("hello");
    autocomplete(&answer, &num_answer, term_list, num_terms, "Tor");
    printf("Hello");
    for(int i = 0; i < num_answer; i++){
        //printf("Term: %s Weight: %f\n", (answer[i]).term, (answer[i]).weight);
        printf("Term: %s", (answer[i]).term);
    }

    //char hi = "Tor";
    char* hi2 = "Tor";
    something = lowest_match(term_list, num_terms, hi2);
    printf("Lowest match: %d", something);
    printf("term: %s", term_list[something].term);

}
/*
int main(void) {
    term* term_list;
    int num_terms;

    printf("hi");
    read_in_terms(&term_list, &num_terms, "cities.txt");



    //test infrastructure only
    char *query = "101";

    int low_ind = lowest_match(term_list, num_terms, query);
    printf("The low index is %d and the result is \"%s\"\n", lowest_match(term_list, num_terms, query), term_list[low_ind].term);

    int high_ind = highest_match(term_list, num_terms, query);
    printf("The high index is %d and the result is \"%s\"\n", highest_match(term_list, num_terms, query), term_list[high_ind].term);

    printf("%s", term_list[751].term);
    return 0;
}*/

