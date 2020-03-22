# projetPara
Max subsequence

struct table* alloccateTableAndInitialTheSource(int size)                                   non parallel. 
****
struct table* allocateTableAndInitialTheSource_copyValue(int* source,int size)              parallel. 
****
struct table* allocateTableAndInitialTheResult_psum(int* source,int size)                   parallel. 
****
void psum_montee(struct table* result                                                       parallel.
****
void psum_descente(struct table * source, struct table * result)                            parallel. 
****
void psum_final(struct table * result_montee, struct table * result_descente)               parallel. 
****
struct table* allocateTableAndInitialTheResult_ssum(int* source,int size)                   parallel.
****
void ssum_montee(struct table* result)                                                      parallel.
****
void ssum_descente(struct table * source, struct table * result)                            parallel. 
****
void ssum_final(struct table * result_montee, struct table * result_descente)               parallel. 
****
struct table* allocateTableAndInitialTheSource_smax(struct table* source,int size)          parallel. 
****
void smax_montee(struct table * result)                                                     parallel. 
****
void smax_descente(struct table * source, struct table * result)                            parallel. 
****
void smax_final(struct table * result_montee, struct table * result_descente)               parallel. 
****
struct table* allocateTableAndInitialTheSource_pmax(struct table* source,int size)          parallel.
****
void pmax_montee( struct table * result)                                                    parallel.
****
void pmax_descente(struct table * result_montee, struct table * result_descente)            parallel. 
****
void pmax_final(struct table * result_montee, struct table *result_descente)                parallel. 
****
void make_max(struct table * q, struct table * pmax, struct table * smax, struct table * ssum, struct table * psum, struct table * result)                                                                             parallel. 
****
void find_max(struct table * m, int * maxIndex, int * minIndex)                             parallel. 
****
struct table * getArray(FILE * file)                                                        non parallel 
****





The programme which I used Xcode to write  executes all of tests in my Mac, the resultes are all ture, but when  I execute in the python script(the test file) , the results are false. I don't know what happen.


