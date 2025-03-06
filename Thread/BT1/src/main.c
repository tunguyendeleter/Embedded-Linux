#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_t threadId1, threadId2;

void *Thread_handle(void *args)
{ /* Get thread id */
    pthread_t tid = pthread_self();

    /* Handle thread */
    if (pthread_equal(tid, threadId1))
    {
        printf("[THREAD 1] Hello I'm thread 1\n");
    }
    else if (pthread_equal(tid, threadId2))
    {
        printf("[THREAD 2] Hello I'm thread 2\n");
    }
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

    /* Join to prevent zombie thread */
    pthread_join(threadId1, NULL);
    pthread_join(threadId2, NULL);

    return 0;
}
