
#include <stdlib.h>
#include <stdio.h>

#include <math.h>
#include <limits.h>
#include <string.h>


struct table {
        int * tab;
        int size;
};

struct table* allocateTableAndInitialTheSource(int size) {
        struct table* tmp = malloc(sizeof(struct table));
        tmp->size = size;
        tmp->tab = malloc(size*sizeof(int));
    return tmp;
}

struct table* allocateTableAndInitialTheSource_copyValue(int* source,int size) {
        struct table* tmp = malloc(sizeof(struct table));
        tmp->size = size;
        tmp->tab = malloc(size*sizeof(int));
        int i;
    #pragma omp parallel for
    for(i = 0; i < size; i++){
            tmp->tab[i] = source[i];
    }
    return tmp;
  
}


//****************************************************//
struct table* allocateTableAndInitialTheResult_psum(int* source,int size){
     struct table* tmp = malloc(sizeof(struct table));
     tmp->size = size*2;
     tmp->tab = malloc(tmp->size*sizeof(int));
     int i;
#pragma omp parallel for
    for(i = 0; i < size; i++){
            tmp->tab[tmp->size/2+i] = source[i];
    }
    return tmp;
    
    
}

void psum_montee(struct table* result) {
        int l, j;
        for(l = log2(result->size)-1; l > 0; l--){
#pragma omp parallel for
                for(j = 1 <<(l-1); j <= (1 << l) - 1; j++){
                        result->tab[j] = result->tab[2*j] + result->tab[2*j+1];
                }
        }
}

void psum_descente(struct table * source, struct table * result) {
        // TODO : implementation de la phase de descente
        result->tab[1] = 0;
        int l, j;
        for(l = 2; l <= log2(source->size); l++){
#pragma omp parallel for
                for(j = 1 << (l-1); j <= (1 << l) - 1;  j++){
                        if(j % 2 == 0){
                                result->tab[j] = result->tab[j/2];
                        } else {
                                result->tab[j] = result->tab[j/2] + source->tab[j-1];
                        }
                }
        }
}

void psum_final(struct table * result_montee, struct table * result_descente) {
        // TODO : phase finale
        int j;
        int size = log2(result_montee->size);
#pragma omp parallel for
        for(j = 1 << (size - 1); j <= (1 << size) - 1; j++){
                result_descente->tab[j] = result_descente->tab[j] + result_montee->tab[j];
        }
}


// ******************************************************************************************************** //

struct table* allocateTableAndInitialTheResult_ssum(int* source,int size){
     struct table* tmp = malloc(sizeof(struct table));
     tmp->size = size*2;
     tmp->tab = malloc(tmp->size*sizeof(int));
     int i;
#pragma omp parallel for
    for(i = 0; i < size; i++){
            tmp->tab[tmp->size - i - 1] = source[i];
    }
    return tmp;
    
    
}

void ssum_montee(struct table* result) {

        int l, j;
        for(l = log2(result->size)-1; l > 0; l--){
#pragma omp parallel for
                for(j = 1 << (l-1); j <= (1 << l) - 1; j++){
                        result->tab[j] = result->tab[2*j] + result->tab[2*j+1];
                }
        }
}

void ssum_descente(struct table * source, struct table * result) {
     
        result->tab[1] = 0;
        int l, j;
        for(l = 2; l <= log2(source->size); l++){
#pragma omp parallel for
                for(j = 1 << (l-1); j <= (1 << l) - 1;  j++){
                        if(j % 2 == 0){
                                result->tab[j] = result->tab[j/2];
                        } else {
                                result->tab[j] = result->tab[j/2] + source->tab[j-1];
                        }
                }
        }
}

void ssum_final(struct table * result_montee, struct table * result_descente) {
        // TODO : phase finale
        int j;
        int size = log2(result_montee->size);
#pragma omp parallel for
        for(j = 1 << (size - 1); j <= (1 << size) - 1; j++){
                result_descente->tab[j] = result_descente->tab[j] + result_montee->tab[j];
        }
}


//**********************************************************//

struct table* allocateTableAndInitialTheSource_smax(struct table* source,int size) {
        struct table* tmp = malloc(sizeof(struct table));
        tmp->size = size*2;
        tmp->tab = malloc(tmp->size*sizeof(int));
            int i;
    #pragma omp parallel for
            for(i = 0; i < source->size/2; i++){
                    tmp->tab[tmp->size-i-1] = source->tab[source->size/2+i];
            }
    return tmp;
}




void smax_montee(struct table * result) {

        // TODO: Boucle de calcul pour la montée dans l'arbre/tableau
        int l, j;
        for(l = log2(result->size)-1; l > 0; l--){
#pragma omp parallel for
                for(j = 1 << (l-1); j <= (1 << l) - 1; j++){
                        result->tab[j] = fmax(result->tab[2*j], result->tab[2*j+1]);
                }
        }
}

void smax_descente(struct table * source, struct table * result) {
        // TODO : implementation de la phase de descente
        source->tab[1] = INT_MIN;
        int l, j;
        for(l = 2; l <= log2(source->size); l++){
#pragma omp parallel for
                for(j = 1 << (l-1); j <= (1 << l) - 1;  j++){
                        if(j % 2 == 0){
                                result->tab[j] = result->tab[j/2];
                        } else {
                                result->tab[j] = fmax(result->tab[j/2], source->tab[j-1]);
                        }
                }
        }
}

void smax_final(struct table * result_montee, struct table * result_descente) {
        // TODO : phase finale
        int j;
        int size = log2(result_montee->size);
#pragma omp parallel for
        for(j = 1 << (size - 1); j <= (1 << size) - 1; j++){
                result_descente->tab[j] = fmax(result_descente->tab[j], result_montee->tab[j]);
        }
}


//****************************************************************//
struct table* allocateTableAndInitialTheSource_pmax(struct table* source,int size) {
        struct table* tmp = malloc(sizeof(struct table));
        tmp->size = size*2;
        tmp->tab = malloc(tmp->size*sizeof(int));
            int i;
    #pragma omp parallel for
            for(i = 0; i < source->size/2; i++){
                    tmp->tab[tmp->size/2+i] = source->tab[source->size-i-1];
            }
    return tmp;
}

void pmax_montee( struct table * result) {

        int l, j;
        for(l = log2(result->size)-1; l > 0; l--){
#pragma omp parallel for
                for(j = 1 << (l-1); j <= (1 << l) - 1; j++){
                        result->tab[j] = fmax(result->tab[2*j], result->tab[2*j+1]);
                }
        }
}

void pmax_descente(struct table * result_montee, struct table * result_descente) {
        // TODO : implementation de la phase de descente
        result_descente->tab[1] = INT_MIN;
        int l, j;
        for(l = 2; l <= log2(result_montee->size); l++){
#pragma omp parallel for
                for(j = 1<< (l-1); j <= (1 << l) - 1;  j++){
                        if(j % 2 == 0){
                                result_descente->tab[j] = result_descente->tab[j/2];
                        } else {
                                result_descente->tab[j] = fmax(result_descente->tab[j/2], result_montee->tab[j-1]);
                        }
                }
        }
}

void pmax_final(struct table * result_montee, struct table *result_descente) {
        // TODO : phase finale
        int j;
        int size = log2(result_montee->size);
#pragma omp parallel for
        for(j = 1 << (size - 1); j <= (1 << size) - 1; j++){
                result_descente->tab[j] = fmax(result_montee->tab[j], result_descente->tab[j]);
        }
}

//****************************************************************//

void make_max(struct table * q, struct table * pmax, struct table * smax, struct table * ssum, struct table * psum, struct table * result){
        int i;
        struct table * ms = allocateTableAndInitialTheSource(q->size);
        struct table * mp = allocateTableAndInitialTheSource(q->size);
#pragma omp parallel for
        for(i = 0; i < q->size; i++){
                ms->tab[i] = pmax->tab[pmax->size/2+i] - ssum->tab[ssum->size-i-1];
                mp->tab[i] = smax->tab[smax->size-i-1] - psum->tab[psum->size/2+i];
                result->tab[i] = ms->tab[i] + mp->tab[i] + q->tab[i];
        }
        free(ms->tab);
        free(ms);
        free(mp->tab);
        free(mp);
}
void find_max(struct table * m, int * maxIndex, int * minIndex){
        int i;
        int value = INT_MIN;
        int value_min = INT_MAX;
        int value_max = INT_MIN;
        int * maxIndexA = malloc(m->size*sizeof(int));
        int * minIndexA = malloc(m->size*sizeof(int));
#pragma omp parallel for
        for(i = 0; i < m->size; i++){
                maxIndexA[i] = INT_MIN;
                minIndexA[i] = INT_MAX;
        }
#pragma omp parallel for reduction(max: value)
        for(i = 0; i < m->size; i++){
                if(m->tab[i] > value){
                        value = m->tab[i];
                        minIndexA[i] = i;
                        maxIndexA[i] = i;
                } else if(m->tab[i] == value){
                        maxIndexA[i] = i;
                }
        }

#pragma omp parallel for reduction(max: value_max) reduction(min: value_min)
        for(i = 0; i < m->size; i++){
                if((maxIndexA[i] > value_max) && (value == m->tab[maxIndexA[i]])){
                        value_max = maxIndexA[i];
                }
                if((minIndexA[i] < value_min) && (value == m->tab[minIndexA[i]])){
                        value_min = minIndexA[i];
                }
        }
        *maxIndex = value_max;
        *minIndex = value_min;
        free(maxIndexA);
        free(minIndexA);
}

//****************************************************************************//
struct table * getArray(FILE * file) {
  int k =-1;
  int i = 0;
  int oldsize = 2;
  struct table * input = allocateTableAndInitialTheSource(2);
  while ( (fscanf(file , "%d", &k) != EOF )) {
    if ( i > input->size - 1 ) {
      oldsize = input->size;
      input->size *= 2;
      input->tab = realloc(input->tab, input->size * sizeof(int));
    }
    input->tab[i] = k;
    i ++;
  }
  return input;
}

//***************************************************************//





int main(int argc, char **argv) {

//    int size = argc-1;
//    int a[size];
//    for(int i=0;i<size;i++){
//        a[i] = atoi(argv[i+1]);
//    }
//
    FILE * file = fopen(argv[1], "r");
    struct table * input = getArray(file);
     fclose(file);
    int size = input->size;
    int a[size];
    for(int i=0;i<size;i++){
        a[i] = input->tab[i];
    }
    free(input->tab);
    free(input);

 

    struct table* source = allocateTableAndInitialTheSource_copyValue(a,size);
    //********************************************//
    struct table* source_psum_montee = allocateTableAndInitialTheResult_psum(a,size);
    psum_montee(source_psum_montee);
    struct table* source_psum_decente = allocateTableAndInitialTheSource(size*2);
    psum_descente(source_psum_montee, source_psum_decente);
    psum_final(source_psum_montee, source_psum_decente);
    free(source_psum_montee->tab);
    free(source_psum_montee);
   //********************************************//
    struct table* source_ssum_montee = allocateTableAndInitialTheResult_ssum(a, size);
    ssum_montee(source_ssum_montee);
    struct table* source_ssum_descente = allocateTableAndInitialTheSource(size*2);
    ssum_descente(source_ssum_montee, source_ssum_descente);
    ssum_final(source_ssum_montee, source_ssum_descente);
    free(source_ssum_montee->tab);
    free(source_ssum_montee);
    //********************************************//
    struct table* source_smax_montee = allocateTableAndInitialTheSource_smax(source_psum_decente,size);
    smax_montee(source_smax_montee);
    struct table* source_smax_descente = allocateTableAndInitialTheSource(size*2);
    smax_descente(source_smax_montee, source_smax_descente);
    smax_final(source_smax_montee,source_smax_descente);
    free(source_smax_montee->tab);
    free(source_smax_montee);
    //********************************************//
    
    struct table* source_pmax_monte = allocateTableAndInitialTheSource_pmax(source_ssum_descente, size);
    pmax_montee(source_pmax_monte);
    struct table* source_pmax_descente = allocateTableAndInitialTheSource(size*2);
    pmax_descente(source_pmax_monte, source_pmax_descente);
    pmax_final(source_pmax_monte, source_pmax_descente);
    free(source_pmax_monte->tab);
    free(source_pmax_monte);
   
     //********************************************//
    
    struct table* resultFinal = allocateTableAndInitialTheSource(size);
    make_max(source, source_pmax_descente, source_smax_descente, source_ssum_descente, source_psum_decente, resultFinal);
    int maxIndex = -1, minIndex = -1;
    find_max(resultFinal, &maxIndex, &minIndex);
    printf("%d",resultFinal->tab[minIndex]);
    int i ;
    for(i = minIndex; i <= maxIndex; i++){
            if(resultFinal->tab[i] == resultFinal->tab[minIndex]){
                    printf(" %d", source->tab[i]);
            } else {
                    i = maxIndex+1;
            }
    }
    printf("\n");
    free(resultFinal->tab);
    free(resultFinal);
    free(source_pmax_descente->tab);
    free(source_pmax_descente);
    free(source_smax_descente->tab);
    free(source_smax_descente);
    free(source_ssum_descente->tab);
    free(source_ssum_descente);
    free(source_psum_decente->tab);
    free(source_psum_decente);
    free(source->tab);
    free(source);
    
}
