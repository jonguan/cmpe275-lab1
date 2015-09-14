#include <iostream>

/**
 * @brief basic starting point - no threading
 *
 *      Author: gash
 */
int main(int argc, char **argv) {

   #pragma omp parallel
   {
     int ID = -1;
     printf("Hello (%d)\n",ID);
   }

}
