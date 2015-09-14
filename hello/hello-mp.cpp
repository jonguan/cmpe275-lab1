#include <iostream>

#include "omp.h"

/**
 * @brief basic starting point - adding openMP calls
 *
 *      Author: gash
 */
int main(int argc, char **argv) {

   #pragma omp parallel
   {
     int ID = omp_get_thread_num();
     printf("Hello (%d)\n",ID);
   }

}
