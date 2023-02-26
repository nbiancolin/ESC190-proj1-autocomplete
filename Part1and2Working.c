#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "autocomplete.h"

int partition(term **terms, int low, int high) { // partition function for quicksort
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
        int pivot = partition(terms, low, high);
        sort_terms(terms, low, pivot - 1);
        sort_terms(terms, pivot + 1, high);
    }
}



void read_in_terms(term **terms, int *pnterms, char *filename) {
  FILE *fptr;
  char line[356];
  double weight;
  fptr = fopen(filename,"r");

  fscanf(fptr, "%d", pnterms);
  printf("Number of terms: %d\n", *pnterms);
  int loc_numterms = *pnterms;
  //num terms reading and assignment
  
  *terms = malloc(*pnterms * sizeof(term));
  // Memory management


  char *term = malloc(200 * sizeof(char));

  for (int i = 0; i < *pnterms; i++) {
    if(i == 0) {
      fgets(line,sizeof(line), fptr);
      sscanf(line, "%d", &loc_numterms);
    }

    fgets(line, sizeof(line), fptr);
    sscanf(line, "%lf %[^\n]", &weight, term);

    (*terms)[i].weight = weight;
    strcpy((*terms)[i].term, strdup(term));
    
  }

  
  sort_terms(terms, 0, *pnterms-1);

  fclose(fptr);

}

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
}

int main(void) {
    term* term_list;
    int num_terms;
    read_in_terms(&term_list, &num_terms, "cities.txt");

    for(int j = 0; j<num_terms; j++) {
        /*printf("Index: %d Term: %s\tWeight: %lf\n", j, (term_list)[j].term, (term_list)[j].weight);*/
    } 

  //test infrastructure only
char *query = "Zho";
int ind = lowest_match(term_list, num_terms, query);
printf("The index is: %d\n and the result is: %s", lowest_match(term_list, num_terms, query), term_list[ind].term);
  return 0;
}
