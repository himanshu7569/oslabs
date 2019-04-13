#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define int fixedtime = 10;

void *time_check();
void *new_queries();
void *queries_handler();

int student_queue[100][2];
int teacher_queue[100][2];
int student_count = -1, teacher_count = -1, initial_time = 0, total_time_spent = 0, avg_query_time = 0;

void main()
{
    pthread_t timecheck, newqueries, querieshandler;
    int check;
    check = pthread_create(&timecheck, NULL, time_check, NULL);
    if (check == 0)
    {
    }
    check = pthread_create(&new_queries, NULL, newqueries, NULL);
    if (check == 0)
    {
    }
    check = pthread_create(&querieshandler, NULL, queries_handler, NULL);
    if (check == 0)
    {
    }
}

void *time_check()
{
}

void *new_queries()
{
    char flag;
start_new_queries:
    printf("\nEnter \n's' for Student. \n't' for Teacher.");
    scanf(% c, &flag);

    if (flag == 's' || flag == 'S')
    {
        printf("\nEnter Query Length");
        scanf(% d, &student_queue[++student_count][0]);
        student_queue[student_queue][1] = initial_time;
        goto start_new_queries;
    }
    else if (flag == 't' || flag == 't')
    {
        printf("\nEnter Query Length");
        scanf(% d, &teacher_queue[++teacher_count][0]);
        teacher_queue[teaceher_count][1] = initial_time;
        goto start_new_queries;
    }
    else if (flag == 'q' || flag == 'Q')
    {
        printf("Total time in Handling Queries : %d", total_time_spent);
        printf("Avg time to complete a Query : &d", avg_query_time);
        printf("\nEXIT\n");
    }
    else
    {
        printf("Wrong Input");
        goto start_new_queries;
    }
}

void *queries_handler()
{
    int position;
}