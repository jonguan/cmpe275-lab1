#include <iostream>

#include "omp.h"

/**
 * @brief basic starting point - what should you see? 
 *
 *      Author: gash
 */
int main(int argc, char **argv) {
// int i = 0;
   #pragma omp parallel
// for(i = 0; i < 8; i++)
   {
      int ID = omp_get_thread_num();
      #pragma omp critical
      std::cerr << "Hello (" << ID << ") " << std::endl;
   }

}
