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
   char *indent;

   n_l = n - level;
   r_l = r - level;
   block_size = (2 * level + 1) * sizeof(char);
   indent = (int *)malloc(block_size);
   for (indx=0; indx<block_size-1; indx++)
      indent[indx] = ' ';
   indent[indx] = NULL;

   printf("%spermutations(", indent);
   print_permutation(set, n_l, 1);
   printf(", %p, %i, %i, %i) {\n", target, n, r, level);

   if (r_l<1) return ;
   // block_size = (n_l * r_l) * sizeof(int);

   if (r_l==1){
      for (indx=0; indx<n_l; indx++) {
         target_offset = r * indx + level;
         target[target_offset] = set[indx];
   printf("%s1 Put value %i at %p\n", indent, set[indx], target + target_offset);
   printf("%s1 Indx %i offset is: %i with value %i\n", indent, indx, target_offset, set[indx]);
      }
   printf("%s1 return; }\n", indent);
   free(indent);
      return ;
   }

   level++;
   // allocate temporary memory
   block_size = (n_l - 1) * sizeof(int);
   tmp_array = (char *)malloc(block_size);
   for (indx=0; indx<n_l; indx++) {
      // put each element to start
      for (cnt=0; cnt<n_l-1; cnt++) {
         target_offset = r * ((n_l - 1) * indx + cnt);
         target[target_offset] = set[indx];
   printf("%s2 Put value %i at %p\n", indent, set[indx], target + target_offset);
   printf("%s2 Indx %i offset is: %i with value %i\n", indent, indx, target_offset, set[indx]);
      }
         // target[r * ((n_l - 1) * indx + cnt)] = set[indx];
      // permute the remaining spaces
         // first, save the remaining numbers to the tmp memory
      for (cnt=0, tmp_indx=0; cnt<n_l; cnt++) {
         if (cnt == indx) continue;
         tmp_array[tmp_indx] = set[cnt];
         tmp_indx++;
      }
         // second, recurse to do the remainding numbers
      target_offset = r * indx;
   printf("%s3 Indx %i with target %p + offset %i\n", indent, indx, target, target_offset);
      permutations(tmp_array, target + target_offset, n, r, level);
   }
   // clean up and return
   printf("%s4 return; }\n", indent);
   free(indent);
   free(tmp_array);
   return ;
}

void print_permutation(int *perm, int r, int nPr) {
   int perm_cnt, element_cnt;

   for (perm_cnt = 0; perm_cnt < nPr; perm_cnt++) {
      printf("{%i", perm[perm_cnt * r]);
      for (element_cnt = 1; element_cnt < r; element_cnt++) {
         printf(", %i", perm[perm_cnt * r + element_cnt]);
      }
      printf("}");
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
   if (argc!=3){
      printf("This program was executed with %i arguments.\n", argc);
      printf("Execute as:\n%s n r\n", argv[0]);
      printf("where n is the number of objects and\n");
      printf("r is the number of places that they can go into.\n");
      exit(0);
   }
   n = atoi(argv[1]);
   r = atoi(argv[2]);
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
   printf("\n");

   // clean up and exit
   free(perm);
   exit(err);
}
