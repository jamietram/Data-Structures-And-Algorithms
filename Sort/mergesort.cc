/**
 *  \file mergesort.cc
 *
 *  \brief Implement your mergesort in this file.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "sort.hh"

using namespace std;

void merge(keytype* A, int p, int q , int r) 
{
  int n1, n2;
  n1 = q - p + 1;
  n2 = r - q;

  keytype* L = newKeys (n1 + 1);
  keytype* R = newKeys (n2 + 1);

  int i, j;
  for (i = 0; i < n1; i++){
    L[i] = A[p + i];
  }
  for (j = 0; j < n2; j++) {
    R[j] = A[q + j + 1];
  }

  L[n1] = INT_MAX;
  R[n2] = INT_MAX;

  i = 0;
  j = 0;
  for (int k = p; k <= r; k++) {
    if (L[i] <= R[j]) {
      A[k] = L[i];
      i = i + 1;
    }
    else{
      A[k] =R[j];
      j = j + 1;
    }
  }
  delete[] L;
  delete[] R;
}

void mergeSort(keytype* A, int p, int r) {
  if (p < r) 
  {
    int q = (p + r) / 2;
    mergeSort(A, p, q);
    mergeSort(A, q + 1, r);
    merge(A, p, q, r);

  }
}

void
mySort (int N, keytype* A)
{
  /* Lucky you, you get to start from scratch */
  mergeSort(A, 0, N-1 );
}

/* eof */
