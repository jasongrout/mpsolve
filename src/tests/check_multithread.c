#include <mps/mps.h>    
#include <stdlib.h>
#include <pthread.h>

#define N_THREADS 128

void *
work (int * i)
{
  printf (" %2d", *i);
  /* while (1); */
  return NULL;
}

int main (int argc, char ** argv)
{
  mps_status * s = mps_status_new ();
  mps_thread_pool * pool = mps_thread_pool_new (s);
  int i[N_THREADS];
  int j;

  for(j = 0; j < N_THREADS; j++)
    i[j] = j;
  j = 0;

  printf (" => Created a thread pool with %d threads\n", pool->n);

  printf (" => Asking the threads to print an integer...\n");
  
  for (j = 0; j < N_THREADS; j++)
    mps_thread_pool_assign (s, pool, (mps_thread_work) work, i + j);

  mps_thread_pool_wait (s, pool);
  printf ("\n => All the threads have completed their work\n");

  printf (" => Doing it again (testing re-usability of the thread pool)\n");

  for (j = 0; j < N_THREADS; j++)
    mps_thread_pool_assign (s, pool, (mps_thread_work) work, i + j);

  mps_thread_pool_wait (s, pool);

  printf ("\n => Trying to stop all the threads..."); 
  mps_thread_pool_free (s, pool); 
  printf ("done\n"); 
}