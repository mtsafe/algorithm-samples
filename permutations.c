#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void permutations(int [], int [], int, int, int);
void print_permutation(int *, int, int);
int main(int, char *[]);

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
   int set_indx, tmp_indx, cnt;
   int *tmp_array;
   int target_offset;
   size_t block_size;
   char *indent;
   unsigned b4;

   n_l = n - level;
   r_l = r - level;
   block_size = (2 * level + 1) * sizeof(char);
   indent = (char *)malloc(block_size);
   memset(indent,' ', block_size-1);
   indent[block_size-1] = 0;

   printf("%spermutations(", indent);
   print_permutation(set, n_l, 1);
   b4 = (unsigned int)0xFFFF & (unsigned int)target;
   printf(", 0x%04x, %i, %i, %i) {\n", b4, n, r, level);

   if (r_l<1) return ;
   // block_size = (n_l * r_l) * sizeof(int);

   if (r_l==1){
      for (set_indx=0; set_indx<n_l; set_indx++) {
         target_offset = r * set_indx + level;
         target[target_offset] = set[set_indx];
         b4 = (unsigned int)0xFFFF & (unsigned int)(target + target_offset);
   printf("%s1 PUT value %i at 0x%04x\n", indent, set[set_indx], b4);
   printf("%s1   Indx %i offset is: %i with value %i\n", indent, set_indx, target_offset, set[set_indx]);
      }
   printf("%s1   return; }\n", indent);
   free(indent);
      return ;
   }

   level++;
   // allocate temporary memory
   block_size = (n_l - 1) * sizeof(int);
   tmp_array = (int *)malloc(block_size);
   for (set_indx=0; set_indx<n_l; set_indx++) {
      // put each element to start
      for (cnt=0; cnt<n_l-1; cnt++) {
         target_offset = r * ((n_l - 1) * set_indx + cnt);
         target[target_offset] = set[set_indx];
         b4 = (unsigned int)0xFFFF & (unsigned int)(target + target_offset);
   printf("%s2 PUT value %i at 0x%04x\n", indent, set[set_indx], b4);
   printf("%s2   Indx %i offset is: %i with value %i\n", indent, set_indx, target_offset, set[set_indx]);
      }
         // target[r * ((n_l - 1) * indx + cnt)] = set[set_indx];
      // permute the remaining spaces
         // first, save the remaining numbers to the tmp memory
      for (cnt=0, tmp_indx=0; cnt<n_l; cnt++) {
         if (cnt == set_indx) continue;
         tmp_array[tmp_indx] = set[cnt];
         tmp_indx++;
      }
         // second, recurse to do the remainding numbers
      // target_offset = r * set_indx;
      // target_offset = r * n_l * set_indx;
      target_offset = r * (n - 1) * set_indx;
      b4 = (unsigned int)0xFFFF & (unsigned int)target;
   printf("%s3 Indx %i with target 0x%04x + offset %i\n", indent, set_indx, b4, target_offset);
      permutations(tmp_array, target + target_offset, n, r, level);
   }
   // clean up and return
   printf("%s4 return; }\n", indent);
   free(tmp_array);
   free(indent);
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

int main(int argc, char *argv[]) {
   int *perm;
   int num;
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
   for (num = n; num > (n - r); num--)
      nPr *= num;
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
