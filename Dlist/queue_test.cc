#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "timer.c"

#include "queue.h"

int main (int argc, char* argv[])
{
    int N = -1, T = -1;
    long double total_t = 0.0L, average_t = 0.0L;

    if (argc == 3) {
        N = atoi (argv[1]);
        T = atoi (argv[2]);
        assert (N > 0);
        assert (T > 0);
    } else {
        fprintf (stderr, "usage: %s <n>\n", argv[0]);
        fprintf (stderr, "where <n> is the length of the list to sort.\n");
        return -1;
    }

    stopwatch_init ();
    struct stopwatch_t* timer = stopwatch_create (); assert (timer);

    Queue q(N);
    srand((unsigned)time(NULL));
    for(int i = 0; i < N; i++){
        q.enqueue(((float)rand())/RAND_MAX);  
    }

	float x;
    //dequeue, enqueue t times
    for(int i = 0; i < T; i++){
        stopwatch_start (timer);
    	x = q.dequeue();
        q.enqueue(x);
        long double t_qs = stopwatch_stop (timer);
        total_t += t_qs;
    }

    //calculate average
    average_t = total_t / T;

	printf("Average Time: %Lg", average_t);
    printf ("\n");
    stopwatch_destroy (timer);
    return 0;
}

