/*
 * Given a linear 3x3 matrix return the minimum cost to turn the input into a 3x3 magic square
 * which means its rows, columns and diagonals should sum to the same value.
 */

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

#define BOOL char
#define TRUE 1
#define FALSE 0

BOOL is_magic_square(int* list){
  // 3x3 matrix.
#define COUNT 8
  // 3 horizontal.
  int v[COUNT]= {list[0]+list[1]+list[2], list[3]+list[4]+list[5], list[6]+list[7]+list[8],
    // 3 vertical.
    list[0]+list[3]+list[6], list[1]+list[4]+list[7], list[2]+list[5]+list[8],
    // 2 diagonal.
    list[0]+list[4]+list[8], list[2]+list[4]+list[6]};
  for (int i=1; i<COUNT;i++){
    if(v[i] != v[i-1])
      return FALSE;
  }
  return TRUE;
}

void swap(int* l, int* r){
  int temp = *l;
  *l = *r;
  *r = temp;
}

// generate all the possible 3x3 magic squares.
int generate_magic_squares(int* list, int l, int r, int size, int** square_pointers, int square_count){
  // permutation using backtracking.
  if (l==r){
    if (is_magic_square(list)){
      // will be freed later.
      int* h = malloc(sizeof(int) * size);
      memcpy(h, list, sizeof(int) * size);
      square_pointers[square_count++] = h; 
    }
  }
  else {
    for (int i=l; i<=r; i++){
      swap(list+l, list+i);
      square_count = generate_magic_squares(list, l+1, r, size, square_pointers, square_count); 
      swap(list+l, list+i);    
    } 
  }

  return square_count;
}

// compare an input square with every other 3x3 magic square
// and return the minimum cost to turn the input into a magic square.
int magic_sqaure_min_cost(int* square){
#define SIZE 9
  int list[SIZE] = {1,2,3,4,5,6,7,8,9};
  // taking the easy way since I already know there are only 8 3x3 magic squares.
  int* square_pointers[8] = {0};
  int square_count = generate_magic_squares(list, 0, SIZE - 1, SIZE, square_pointers, 0);
  int cost = INT_MAX;

  int costs[square_count]; 
  for (int i=0; i< square_count; i++){
    int this_cost = 0;
    for (int j=0; j< SIZE; j++){
      this_cost+= abs(square_pointers[i][j] - square[j]);
    }
    // this was allocated when generating the square.
    free(square_pointers[i]);
    costs[i] = this_cost;
  }

  // get lowest cost.
  int lowest = costs[0];
  for (int i=0; i<square_count; i++){
    if (costs[i] < lowest){
      lowest = costs[i];
    }
  }

  return lowest;    
}

int main(){

  // sample input:
  // 5 3 4
  // 1 5 8
  // 6 4 2
  // turns into
  // 8 3 4
  // 1 5 9
  // 6 7 2
  // with the cost of 7.
  int input[] = {5,3,4,1,5,8,6,4,2}; 
  printf("%d\n", magic_sqaure_min_cost(input));

  return 0;
}
