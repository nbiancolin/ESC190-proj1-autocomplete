#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "autocomplete.h"

int x_i_star(term **terms, int low, int high) { // We love Jimmy Davis for ruining the word Partition so much that I had to rename this function in his honour (x_i*, the partition when evaluating an integral)
    term pivot = (*terms)[high];
    int i = low - 1;
    for (int j = low; j < high; j++) { // puts all terms less than pivot to the left of pivot
        if (strcmp((*terms)[j].term, pivot.term) < 0) {
            i++;
            term temp = (*terms)[i];
            (*terms)[i] = (*terms)[j];
            (*terms)[j] = temp;
        }
    }
    term temp = (*terms)[i + 1];
    (*terms)[i + 1] = (*terms)[high];
    (*terms)[high] = temp;
    return i + 1;
}

void sort_terms(term **terms, int low, int high) { // quicksort
    if (low < high) {
        int pivot = x_i_star(terms, low, high);
        sort_terms(terms, low, pivot - 1);
        sort_terms(terms, pivot + 1, high);
    }
}



void read_in_terms(term **terms, int *pnterms, char *filename) {
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

    //Finds number of terms (no need for a while loop, the number of terms is given)
    fgets(line, 200, p_file);
    nterms = atoi(line);
    *pnterms = nterms;

    *terms = malloc(nterms * sizeof(struct term)); //malloc's based on number of terms.
    if (*terms == NULL) { // check if malloc failed
        printf("Error allocating memory");
        exit(1);
    }
    rewind(p_file);
    fgets(line, 200, p_file); //skips over first line (bc it's just the number of terms)
    int i = 0;
    //char *mass;
    while (fgets(line, 200, p_file) != NULL) { // read in terms and weights

        char *token = strtok(line, "\n");
        while(*token == ' ')token++; //should take care of the whitespace at the beginning of each line (STUPID AND I HATE IT) -nick
        //printf("%s", token);
        token = strtok(token, "\t");
        (*terms)[i].weight = atof(token);


        token = strtok(NULL, "\0");
        strcpy((*terms)[i].term, token);
        i++;
    }
    sort_terms(terms, 0, nterms - 1);

    fclose(p_file);
}

/*  -- Old Code (I think)
int lowest_match(term *terms, int nterms, char *substr) {
    int left = 0;
    int right = nterms - 1;
    int index = -1;
    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = strncmp(terms[mid].term, substr, strlen(substr));
        if (cmp < 0) {
            left = mid + 1;
        } else if (cmp > 0) {
            right = mid - 1;
        } else {
            index = mid;
            right = mid - 1;
        }
    }
    return index;
} */

int lowest_match(term *terms, int nterms, char *substr) {

    int left = 0;
    int right = nterms - 1;
    int index = -1;

    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = strncmp(terms[mid].term, substr, strlen(substr));
        if (cmp < 0) {
            left = mid + 1;
        } else if (cmp > 0) {
            right = mid - 1;
        } else {
            index = mid;
            right = mid - 1;
        }

    }

    while (index > 0 && strncmp(terms[index-1].term, substr, strlen(substr))==0) { //here
        index--;
    }
    return index;
}

int highest_match(struct term *terms, int nterms, char *substr) {
    int left = 0;
    int right = nterms - 1;
    int index = -1;
    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = strncmp(terms[mid].term, substr, strlen(substr));
        if (cmp < 0) {
            left = mid + 1;
        } else if (cmp > 0) {
            right = mid - 1;
        } else {
            index = mid;
            right = mid - 1;
        }
    }
    while (index < nterms && strncmp(terms[index+1].term, substr, strlen(substr))==0) {
        index++;
    }
    return index;
}

int compare(const void *a, const void *b) { // compare function for qsort
    term *term1 = (term *) a;
    term *term2 = (term *) b;
    if (term1->weight > term2->weight) {
        return -1;
    } else if (term1->weight < term2->weight) {
        return 1;
    } else {
        return 0;
    }
}

void autocomplete(term **answer, int *n_answer, term *terms, int nterms, char *substr){
    /*
     * The function takes terms (assume it is sorted lexicographically in increasing order), the number
     * of terms nterms, and the query string substr, and places the answers in answer, with *n_answer
     * being the number of answers. The answers should be sorted by weight in non-increasing order.
     * qsort MUST be used (ok)
     */

    //Step 1: Call "read in terms" with *terms, to set up for the next question.

    read_in_terms(&terms, &nterms , "wiktionary.txt");  //Not sure the point of nterms but whatever.

    //Step 2: Find the lowest and highest matches of substring.

    int lowest = lowest_match(terms, nterms, substr);
    int highest = highest_match(terms, nterms, substr);

    if(lowest==-1 || highest ==-1) {
      *n_answer = 0;
      return;
    }
  
    //Step 3: Take selected terms and put them into an 'answer' array

    *answer = malloc((highest - lowest + 1) * sizeof(struct term));
    for(int i = lowest; i < highest; i++){
        (*answer)[i - lowest] = terms[i];
    }

    //Step 4: Sort the answer array by weight in non-increasing order. (could've just said decreasing but whatever)
    //qsort ftw

    qsort(*answer, highest - lowest + 1, sizeof(struct term), compare);

    //Step 5: Set n_answer to the number of answers.

    *n_answer = highest - lowest + 1;
    //return;

}



int main(void){
    term* term_list;
    term* answer;
    int num_terms;
    int num_answer;
   
  
    read_in_terms(&term_list, &num_terms, "wiktionary.txt"); //HASSAN MY CODE WORKS (at least, on my pc it works every time, maybe there's an error in your wikitionary file?)
    
  
   /* printf("Number of terms: %d", num_terms);
    for(int j = 0; j<10; j++){
        printf("Term: %s Weight: %f\n", (term_list[j]).term, (term_list[j]).weight);
    }*/

    
  
    int something = lowest_match(term_list, num_terms, "aa");
    int something2 = highest_match(term_list, num_terms, "aa");
    
  
    printf("Lowest match: %d\n", something);
    printf("term: %s\n", term_list[something].term);
    printf("Highest match: %d\n", something2);
    printf("term: %s\n", term_list[something2].term);
    printf("\n");//newline

    autocomplete(&answer, &num_answer, term_list, num_terms, "aaaf");
    for(int i = 0; i < num_answer-1; i++){
    printf("Index: %d Term: %s Weight: %f\n", i, (answer[i]).term, (answer[i]).weight);
    }

}

//
// Created by Nicholas and Hassan on 2023-02-01.
//