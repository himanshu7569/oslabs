// Question
/*
    Sudesh Sharma is a Linux expert who wants to have an online system where he can handle student queries. Some there can be multiple
    requests at any time he wishes to dedicate a fixed amount of time to every request so that everyone gets a fair share of the time.
    He will log into the system from 10am to 12am only. He wants to have separate requests queues for students and faculty. Implement
    a strategy for the same. The summary at the end the session should include the total time he spent on handling queries and average
    query time.
*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

#define FIXEDTIME 10;

// Threads Function Declaration
void *time_check();
void *new_queries();
void *queries_handler();

// Bool Declaration to Stop "time_check" and "queries_handler" Threads while Exiting from Program
bool timecheckexit = true;
bool querieshandlerexit = true;

// Shared Variables Declaration
int student_queue[100][2];
int teacher_queue[100][2];
int student_count = -1, teacher_count = -1, initial_time = 0, total_time_spent = 0, avg_query_time = 0, total_query_processed = 0;

// Main Method
int main()
{
    void *thread_message;
    pthread_t timecheck, newqueries, querieshandler;
    int check;
    check = pthread_create(&timecheck, NULL, time_check, NULL);
    if (check != 0)
    {
    }
    check = pthread_create(&newqueries, NULL, new_queries, NULL);
    if (check != 0)
    {
    }
    check = pthread_create(&querieshandler, NULL, queries_handler, NULL);
    if (check != 0)
    {
    }
    check = pthread_join(timecheck, &thread_message);
    if (check != 0)
    {
    }
    check = pthread_join(newqueries, &thread_message);
    if (check != 0)
    {
    }
    check = pthread_join(querieshandler, &thread_message);
    if (check != 0)
    {
    }
    exit(EXIT_SUCCESS);
    return 0;
}

// Thread to Control Time
void *time_check()
{
    while (timecheckexit)
    {
        initial_time++;
        if (initial_time == 25)
        {
            initial_time = 0;
        }
        sleep(2);
        if (initial_time == 10)
        {
            printf("\nQuery Handling Started.\n");
        }
        if (initial_time == 12)
        {
            printf("\nQuery Handling Closed\n");
        }
    }
    pthread_exit("Time Check Thread EXIT");
}

// Thread to Enter New Queries
void *new_queries()
{
    char flag;
start_new_queries:
    printf("\nEnter \n's' for Student. \n't' for Teacher. \n'q' for EXIT \n");
    scanf("%c", &flag);

    if (flag == 's' || flag == 'S')
    {
        // Enter Student Query
        printf("\nEnter Query Length\n");
        scanf("%d", &student_queue[++student_count][0]);
        student_queue[student_count][1] = initial_time;
        printf("Student Query Added Successfuly");
        goto start_new_queries;
    }
    else if (flag == 't' || flag == 't')
    {
        // Enter Teacher Query
        printf("\nEnter Query Length\n");
        scanf("%d", &teacher_queue[++teacher_count][0]);
        teacher_queue[teacher_count][1] = initial_time;
        printf("Teacher Query Added Successfuly");
        goto start_new_queries;
    }
    else if (flag == 'q' || flag == 'Q')
    {
        // EXIT from program
        printf("Total time in Handling Queries : %d\n", total_time_spent);
        if (total_query_processed != 0)
        {
            avg_query_time /= total_query_processed;
        }
        printf("Avg time to complete a Query : %d\n", avg_query_time);
        printf("\nEXIT\n");
        timecheckexit = false;      // To EXIT "time_check" Thread
        querieshandlerexit = false; // To EXIT "queries_handler" Thread
        pthread_exit("New Queries Thread EXIT");
    }
    else
    {
        // Wrong Input
        printf("Wrong Input");
        goto start_new_queries;
    }
    pthread_exit("New Queries Thread EXIT");
}

// Thread to Handle Queries
void *queries_handler()
{
    int temp_student_position = 0, temp_teacher_position = 0; // To Traverse Queries by Query Handler

    bool temp_changer = true; // To Handle Teacher and Student Queries Both One by One Simultaneously

    // While Loop to Exit Thread when Exiting from Main Program
    while (querieshandlerexit)
    {

        // If else to handle queries only between 10 to 12 as per the Question
        if (initial_time >= 10 && initial_time <= 12)
        {

            if (temp_changer)
            {
                // Teacher Queries
                if (temp_teacher_position <= teacher_count)
                {

                    teacher_queue[temp_teacher_position][0] -= FIXEDTIME;

                    if (teacher_queue[temp_teacher_position][0] <= 0)
                    {
                        // Calculate Average Query Time
                        total_query_processed++;
                        avg_query_time += initial_time - teacher_queue[temp_teacher_position][1]; // Current Time - Query Enter Time (Query Enter Time given at Entry)

                        // Check If the node is last node
                        if (temp_teacher_position == teacher_count)
                        {
                            teacher_count--;
                            temp_teacher_position = 0;
                        }
                        else
                        {
                            teacher_queue[temp_teacher_position][0] = teacher_queue[teacher_count][0];
                            teacher_queue[temp_teacher_position][1] = teacher_queue[teacher_count][1];
                            teacher_count--;
                        }
                    }
                    else
                    {
                        temp_teacher_position++;
                    }

                    // Calculate Total Time in Handling Queries
                    total_time_spent++;
                }
                else
                {
                    temp_teacher_position = 0;
                }

                temp_changer = false; // To Select Next Query of Student
            }
            else
            {
                // Student Queries
                if (temp_student_position <= student_count)
                {

                    student_queue[temp_student_position][0] -= FIXEDTIME;

                    if (student_queue[temp_student_position][0] <= 0)
                    {
                        // Calculate Average Query Time
                        total_query_processed++;
                        avg_query_time += initial_time - student_queue[temp_student_position][1];

                        // Check If the node is last node
                        if (temp_student_position == student_count)
                        {
                            student_count--;
                            temp_student_position = 0;
                        }
                        else
                        {

                            student_queue[temp_student_position][0] = student_queue[student_count][0];
                            student_queue[temp_student_position][1] = student_queue[student_count][1];
                            student_count--;
                        }
                    }
                    else
                    {
                        temp_student_position++;
                    }
                    // Calculate Total Time in Handling Queries
                    total_time_spent++;
                }
                else
                {
                    temp_student_position = 0;
                }

                temp_changer = true; // To Select Next Query of Teacher
            }
        }
    }

    pthread_exit("Queries Handler Thread EXIT");
}