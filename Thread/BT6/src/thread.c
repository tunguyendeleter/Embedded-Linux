#include "thread.h"

short MyArray[MAX_SIZE_ARRAY];
Counter_Type MyCounter[MAX_COUNTER];
long long GlobalSum = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void Generate_Random(short *number)
{
    static char first_call = 0;

    /* Check first time call this function */
    if (!first_call)
    {
        srand(time(NULL));
        first_call = 1;
    }

    /* Calculate random number */
    *number = rand() % 10000 + 1;
}

void Init_Array(short *Array, int len)
{
    for (int idx = 0; idx < len; idx++)
    {
        Generate_Random(&Array[idx]);
    }
}

void Print_Array(short *Array, int len)
{
    for (int idx = 0; idx < len; idx++)
    {
        printf("Array[%d] = %d\n", idx, Array[idx]);
    }
}

void Count_Array_Without_Thread(short *Array, int len)
{
    GlobalSum = 0;
    for (int idx = 0; idx < len; idx++)
    {
        GlobalSum += Array[idx];
    }
    printf("[INFO] Final Total Sum (No thread) = %lld\n", GlobalSum);
}

void Init_Counter(int CounterIdx)
{
    /* Calculate the starting index in the array */
    int StartArrayIdx = MAX_SIZE_ARRAY - (MAX_SIZE_ARRAY / MAX_COUNTER) * (4U - CounterIdx);

    /* Initialize MyCounter info */
    MyCounter[CounterIdx].ArrayPtr = &MyArray[StartArrayIdx];
    MyCounter[CounterIdx].MaxCount = MAX_SIZE_ARRAY / 4U;
    MyCounter[CounterIdx].LocalSum = 0;

    /* Create thread for MyCounter */
    if (pthread_create(&MyCounter[CounterIdx].CounterThread, NULL, Counter_Handler, NULL))
    {
        printf("pthread_create() for Counter fail\n");
        return;
    }
}

void DeInit_Counter(int CounterIdx)
{
    pthread_join(MyCounter[CounterIdx].CounterThread, NULL);
}

void *Counter_Handler(void *arg)
{
    /* Get thread ID and Counter ID */
    pthread_t ThreadID = pthread_self();
    int CounterID;

    /* Handle thread */
    if (pthread_equal(ThreadID, MyCounter[0].CounterThread))
    {
        CounterID = 0;
    }
    else if (pthread_equal(ThreadID, MyCounter[1].CounterThread))
    {
        CounterID = 1;
    }
    else if (pthread_equal(ThreadID, MyCounter[2].CounterThread))
    {
        CounterID = 2;
    }
    else /* if (pthread_equal(ThreadID, MyCounter[3].CounterThread)) */
    {
        CounterID = 3;
    }

    for (int idx = 0; idx < MyCounter[CounterID].MaxCount; idx++)
    {
        /* Update Local sum */
        MyCounter[CounterID].LocalSum += MyCounter[CounterID].ArrayPtr[idx];

        /* Update Global sum with mutex*/
        pthread_mutex_lock(&lock);
        printf("[COUNTER %d], Local sum = %d\n", CounterID, MyCounter[CounterID].LocalSum);
        GlobalSum += MyCounter[CounterID].ArrayPtr[idx];
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}