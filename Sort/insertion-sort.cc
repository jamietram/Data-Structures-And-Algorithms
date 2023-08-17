/**
 *  \file insertion-sort.cc
 *
 *  \brief Implement your insertion sort in this file.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "sort.hh"

void
mySort (int N, keytype* A)
{
  /* Lucky you, you get to start from scratch */
  int i, j, k;
  for (j = 1; j < N; j++) 
  {
    k = A[j];
    i = j - 1;
    while ((i >= 0) && (A[i] > k)) 
    {
      A[i + 1] = A[i];
      i = i - 1;
    }
    A[i + 1] = k;
  }
}

/* eof */
