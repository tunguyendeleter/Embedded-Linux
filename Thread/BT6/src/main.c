#include "thread.h"

int main()
{
    /* Create random-value Array and Counter */
    Init_Array(MyArray, MAX_SIZE_ARRAY);
    Init_Counter(0);
    Init_Counter(1);
    Init_Counter(2);
    Init_Counter(3);
    DeInit_Counter(0);
    DeInit_Counter(1);
    DeInit_Counter(2);
    DeInit_Counter(3);

    /* Print Local Sum and Global Sum */
    printf("[INFO] Local SUM Counter 0 = %d\n", MyCounter[0].LocalSum);
    printf("[INFO] Local SUM Counter 1 = %d\n", MyCounter[1].LocalSum);
    printf("[INFO] Local SUM Counter 2 = %d\n", MyCounter[2].LocalSum);
    printf("[INFO] Local SUM Counter 3 = %d\n", MyCounter[3].LocalSum);
    printf("[INFO] Final Total Sum (thread) = %lld\n", GlobalSum);
    Count_Array_Without_Thread(MyArray, MAX_SIZE_ARRAY);
    return 0;
}
