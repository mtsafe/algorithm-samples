#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void permutations(int [], int [], int, int, int);
void print_permutation(int *, int, int);

/*
The number of permutations of n objects taken r at a time
(with repetitions not allowed) is determined as: 
   P(n, r) = (n!) / ((n-r)!)
Parameters:
   set is an array of integers to be permuted.
   target is the memory location to hold the results of the permutations.
   n is the number of objects.
   r is the number of places that they can go into.
   level is the level of recursion starting with zero.
*/
void permutations(int set[], int target[], int n, int r, int level) {
   int n_l, r_l;
   int indx, tmp_indx, cnt;
   int *tmp_array;
   int target_offset;
   size_t block_size;

   printf("permutations(%p, %p, %i, %i, %i);\n", set, target, n, r, level);

   n_l = n - level;
   r_l = r - level;

   if (r_l<1) return ;
   block_size = (n_l * r_l) * sizeof(int);
   printf("The set is:\n");
   print_permutation(set, n_l, 1);

   if (r_l==1){
      for (indx=0; indx<n_l; indx++) {
         target_offset = r * indx + level;
         target[target_offset] = set[indx];
      }
      return ;
   }

   level++;
   // allocate temporary memory
   block_size = (n_l - 1) * sizeof(int);
   tmp_array = (int *)malloc(block_size);
   for (indx=0; indx<n_l; indx++) {
      // put each element to start
      for (cnt=0; cnt<n_l-1; cnt++)
         target[r * ((n_l - 1) * indx + cnt)] = set[indx];
      // permute the remaining spaces
         // first, save the remaining numbers to the tmp memory
      for (cnt=0, tmp_indx=0; cnt<n_l; cnt++) {
         if (cnt == indx) continue;
         tmp_array[tmp_indx] = set[cnt];
         tmp_indx++;
      }
         // second, recurse to do the remainding numbers
      target_offset = (r_l * indx) * sizeof(int);
      permutations(tmp_array, target + target_offset, n, r, level);
   }
   // clean up and return
   free(tmp_array);
   return ;
}

void print_permutation(int *perm, int r, int nPr) {
   int perm_cnt, element_cnt;

   for (perm_cnt = 0; perm_cnt < nPr; perm_cnt++) {
      printf("{");
      for (element_cnt = 0; element_cnt < r; element_cnt++) {
         printf("%i, ", perm[perm_cnt * r + element_cnt]);
      }
      printf("}\n");
   }
   return ;
}

int main(int argc, char* argv[]) {
   int *perm;
   int indx;
   int n = 3, r = 2;
   int set[] = {1, 2, 3};
   int nPr;
   size_t block_size;
   int err = 0;

   // check for error conditions
   if (n <= 0) {
      printf("Error: n must be greater than zero\n");
      err++;
   }
   if (r <= 0) {
      printf("Error: r must be greater than zero\n");
      err++;
   }
   if (n < r) {
      printf("Error: n must be greater than r\n");
      err++;
   }
   if (err > 0) {
      printf("   exiting with %i errors\n", err);
      exit(err);
   }

   // calculate the size of memory to hold the permutations
   nPr = 1;
   for (indx = n; indx > (n - r); indx--)
      nPr *= indx;
   block_size = nPr * sizeof(int);
   printf("block_size is %zu\n", block_size);
   
   // allocate the memory to hold the permutations
   perm = (int *)malloc(block_size);

   // create the permutations
   permutations(set, perm, n, r, 0);

   // print the results
   printf("\nThe permutations of the set of %i objects %i at a time:\n", n, r);
   print_permutation(perm, r, nPr);

   // clean up and exit
   free(perm);
   exit(err);
}
