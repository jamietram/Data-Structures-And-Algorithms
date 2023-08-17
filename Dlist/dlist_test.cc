#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "timer.c"

using namespace std;

#include "dlist.h"

int main(int argc, char* argv[])
{
  int N = -1;
  int T = 50;
  if (argc == 2) {
    N = atoi (argv[1]);
    assert (N > 0);
  }
  long double total_t = 0.0L, average_t = 0.0L;
  stopwatch_init ();
  struct stopwatch_t* timer = stopwatch_create (); assert (timer);

  DList myList;
  for (int i = 1; i <= N; i++){
    myList.add_to_back(i);
  }

  srand((unsigned)time(NULL));
  for(int i = 0; i < T; i++){    
    int r = rand() % N + 1;
    stopwatch_start(timer);
    ListNode* found = myList.search_value(r);
    int value = found->val; 
    myList.remove(found);
    long double t_qs = stopwatch_stop(timer);
    total_t += t_qs;

    myList.add_to_front(value);
    stopwatch_stop(timer);
  }
  average_t = total_t / T;
  printf ("Time: %Lg \n", average_t);
  printf ("\n");
  stopwatch_destroy (timer);
  return 0;
}