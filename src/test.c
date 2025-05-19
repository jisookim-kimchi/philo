#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
	was ist race condition?
	A race condition occurs when a program depends on 
	the timing of one or more events to function correctly

	A race condition typically occurs when multiple threads
	access a shared variable( or state) at the same time
*/

//Thread function to generate sum of 0 to N
void	*computation(void *add)
{
	int *add_num = (int *) (add);
	int sum = 0;

	for (int i = 0; i < 10000; i++)
	{
		sum += *add_num;
	}
	return NULL;
}

int	main()
{
	//Thread ID
	pthread_t thread1;
	pthread_t thread2;

	int value1 = 1;
	int value2 = 2;
	
	
	//create attributes
	// pthread_attr_t attr;
	// pthread_attr_init(&attr);

	// computation((void *) &value1);
	// computation((void *) &value2);
	pthread_create(&thread1, NULL, computation, (void*) &value1);
	pthread_create(&thread2, NULL, computation, (void*) &value2);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	//pthread_join ist für Threads das, was waitpid für Prozesse ist:


	return 0;
}