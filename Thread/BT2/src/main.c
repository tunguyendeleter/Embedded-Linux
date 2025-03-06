#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_COUNTER 1000000U

pthread_t threadId1, threadId2, threadId3;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
volatile int counter = 0;

void *Thread_handle(void *args)
{
    /* Take mutex lock */
    pthread_mutex_lock(&lock);

    /* Increase counter by 1*/
    while (counter < MAX_COUNTER)
    {
        counter++;
        printf("counter = %d\n", counter);
    }
    
    /* Release mutex lock */
    pthread_mutex_unlock(&lock);

    /* Clean thread while exiting */
    pthread_exit(NULL); 

}

int main()
{
    /* Initialize variables */
    int ret;

    /* Create thread 1 */
    if (ret = pthread_create(&threadId1, NULL, &Thread_handle, NULL))
    {
        printf("pthread_create() fail, error number=%d\n", ret);
        return -1;
    }

    /* Create thread 2 */
    if (ret = pthread_create(&threadId2, NULL, &Thread_handle, NULL))
    {
        printf("pthread_create() fail, error number=%d\n", ret);
        return -1;
    }

    /* Create thread 2 */
    if (ret = pthread_create(&threadId3, NULL, &Thread_handle, NULL))
    {
        printf("pthread_create() fail, error number=%d\n", ret);
        return -1;
    }

    /* Join to prevent zombie thread */
    pthread_join(threadId1, NULL);
    pthread_join(threadId2, NULL);
    pthread_join(threadId3, NULL);
    printf("Final counter = %d\n", counter);

    return 0;
}
