/**
 *  \file insertion-sort-bisearch.cc
 *
 *  \brief Implement your insertion sort with binary search in this file.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


#include "sort.hh"

int binarySearch( keytype* A, int value, int low, int high)
{
  if (high <= low)
  {
    if (value > A[low])
      return low + 1;
    else
      return low;
  }
  int mid = (low + high) / 2;
  if (value == A[mid])
    return mid;
  else if (value > A[mid])
    return binarySearch(A, value, mid + 1, high);
  else 
    return binarySearch(A, value, low, mid - 1);
}

void 
mySort (int N, keytype* A)
{
  /* Lucky you, you get to start from scratch */
  int i, j, k, p;
  for (j = 1; j < N; j++) 
  {
    k = A[j];
    i = j - 1;
    p = binarySearch(A, k, 0, i);
    while (i >= p) 
    {
      A[i + 1] = A[i];
      i = i - 1;  
    }
    A[i + 1] = k;
  }
}
/* eof */
