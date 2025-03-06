/******************************************************************************
 * Project Name:    NA
 * File Name:       NA
 *
 * Description: Usage of Condition Variables
 *              Target systems:           Ubuntu20
 *              Compiler:                 GCC
 *
 *****************************************************************************/
/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
#define MAX_SIZE 100
/******************************************************************************
 *  GLOBAL VARIABLE
 *****************************************************************************/
/**
 * @brief    Declear random-value variable
 */
char random_num;
char buffer = 0;

pthread_mutex_t lock;
pthread_cond_t cond;
char odd = 0;
char even = 0;

int arr_num[MAX_SIZE];

/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/
/**
 *   @brief      This function generate a random value for referenced input
 *
 *   @param[in]  char                   random_num
 *
 *   @return     void                   NA
 *
 *   @note       This function should be called by producer.
 *
 */
void Generate_Random(int *random_num)
{
    static char first_call = 0;

    /* Check first time call this function */
    if (!first_call)
    {
        srand(time(NULL));
        first_call = 1;
    }

    /* Calculate random number */
    *random_num = rand() % 100 + 1;
}

void Init_Array(int *array)
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        Generate_Random(&array[i]);
    }
}

void *Count_Odd_Number(void *arg)
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (arr_num[i] % 2 != 0)
        {
            odd++;
        }
    }
    printf("Number of odd numbers = %d\n", odd);
}

void *Count_Even_Number(void *arg)
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (arr_num[i] % 2 == 0)
        {
            even++;
        }
    }
    printf("Number of even numbers = %d\n", even);
}

int main()
{
    /* Initialize threads and mutex lock*/
    pthread_t prod, cons;
    Init_Array(arr_num);

    /* Create thread*/
    pthread_create(&prod, NULL, &Count_Odd_Number, NULL);
    pthread_create(&cons, NULL, &Count_Even_Number, NULL);

    /* Join to prevent zombie thread */
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    return 0;
}
