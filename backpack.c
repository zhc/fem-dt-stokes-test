#include <stdio.h>
#include <time.h>
#include <gsl/gsl_combination.h>
#define NITEM      5
#define SACK_WEIGHT 10

typedef struct {
    int weight;
    int value;
} ITEM;

int main(void)
{
    srand(time(NULL));
    ITEM items[NITEM];
    int i,k,j;
    for(i=0; i<NITEM; i++){
        items[i].weight = rand() % 10 + 1;
        items[i].value = rand() % 10 + 1;
        printf("item %d has weight %d and value %d\n", i, items[i].weight, items[i].value);
    }
    gsl_combination *max_c = NULL;
    int max_val = 0;
    for(k=1; k<=NITEM; k++) {
        gsl_combination *c = gsl_combination_calloc(NITEM, k);
        do {
            int val = 0;
            int weight = 0;
            for(j=0; j<k; j++){
                val += items[gsl_combination_get(c, j)].value;
                weight += items[gsl_combination_get(c, j)].weight;
            }
            if (val > max_val && weight <= SACK_WEIGHT){
                max_val = val;
                if (max_c) {
                    gsl_combination_free(max_c);
                }
                max_c = gsl_combination_calloc(NITEM, k);
                gsl_combination_memcpy(max_c, c);
            }
        } while(gsl_combination_next(c) == GSL_SUCCESS);
        gsl_combination_free(c);
    }
    if (max_val > 0){
        printf("sack items: ");
        gsl_combination_fprintf(stdout, max_c, "%d ");
        printf("\n");
    }
    return 0;
}
