/** derived from */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

void createData(int const num_rows, int const num_cols, float* const a, float* const b,
                      float* const c, float* const ref);
void checkSol(int const num_rows, int const num_cols, float const* const a, float const* const b);

/**
 * optimize this code
 */
void add(float* const a, float* const b, float* const c, int const num_rows, int const num_cols)
{
     #pragma omp parallel for collapse(2)
    for(int col = 0; col < num_cols; col++) {
       for(int row = 0; row < num_rows; row++) {
           int i = col + row * num_cols;
           c[i] = a[i] + b[i];
       }
    }
}

int main()
{
    float *a, *b, *c, *sol;

    int    const NUM_ROWS = 2048;
    int    const NUM_COLS = 2048;
    size_t const N_BYTES = NUM_ROWS * NUM_COLS * sizeof(float);

    a   = (float*)malloc(N_BYTES);
    b   = (float*)malloc(N_BYTES);
    c   = (float*)malloc(N_BYTES);
    sol = (float*)malloc(N_BYTES);

    createData(NUM_ROWS, NUM_COLS, a, b, c, sol);

    // c = a + b
    add(a, b, c, NUM_ROWS, NUM_COLS);

    checkSol(NUM_ROWS, NUM_COLS, c, sol);

    free(a); 
    free(b); 
    free(c); 
    free(sol);

    return 0;
}

void createData(int const num_rows, int const num_cols, float* const a, float* const b, float* const c, float* const ref)
{
    int row, col;

    srand((unsigned)time(NULL));

    #pragma omp parallel for collapse(2)
    for(int row = 0; row < num_rows; row++) {
       for(int col = 0; col < num_cols; col++) {
           int i = col + row * num_cols;
           a[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
           b[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
           c[i] = 0.0f;
           ref[i] = a[i] + b[i];
        }
    }
}

void checkSol(int const num_rows, int const num_cols, float const* const a, float const* const b)
{
    int const N = num_rows * num_cols;

    int different = 0;

    #pragma omp parallel
    {
      int this_thread = omp_get_thread_num(), num_threads = omp_get_num_threads();
      size_t beginpos = (this_thread+0) * N / num_threads;
      size_t endpos   = (this_thread+1) * N / num_threads;
      // watch out for overflow in that multiplication.
      #pragma omp for reduction(|:different)
      for(size_t i=beginpos; i < endpos; i++) {
        different = (a[i] != b[i]); 
      }
    }
    
    if(different)
        printf("Arrays do not match.\n");
    else
        printf("Arrays match.\n");
}
