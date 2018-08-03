/**
 * Implementation of various scheduling algorithms.
 *
 * FCFS scheduling
 */
 
#include <stdlib.h>
#include <stdio.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

// reference to the head of the list
struct node *head = NULL;

Task *pickNextTask();

// add a new task to the list of tasks
void add(char *name, int priority, int burst) {
    // first create the new task
    Task *newTask = (Task *) malloc(sizeof(Task));
    
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;
	
    // insert the new task into the list of tasks 
    insert(&head, newTask);
}

/**
 * Run the FCFS scheduler
 */
void schedule() {
    Task *currentTask = pickNextTask();
    if(currentTask == NULL) {
        exit(0);
    }

    if(currentTask->burst > QUANTUM) {
        run(currentTask, QUANTUM);
        currentTask->burst = currentTask->burst - QUANTUM;
        delete(&head, currentTask);
        insert(&head, currentTask);
    } else {
        run(currentTask, currentTask->burst);
        delete(&head, currentTask);
    }
    schedule();
}

/**
 * Returns the next task selected to run.
 */
Task *pickNextTask()
{
//    printf("start of pickNextTask\n"); //debugging statement
    struct node *temp;
    temp = head;
    int i = 0;
    if (temp == NULL){
        printf("No more jobs in the queue\n");
        exit(0);
    }
    int pri = temp->task->priority;
    Task *chosenTask = temp->task;

//    printf("before the while\n"); //debugging statement

    while (temp != NULL) {
//        printf("Stepping into while\n"); //debugging statement
        i = i+1;
        if(temp->task->priority <= pri) {
            pri = temp->task->priority;
            chosenTask = temp->task;
//            printf("Current Task = %s\n",chosenTask->name); //debugging statement
        }
        if(temp->next == NULL) {
            return chosenTask;
        }
        temp = temp->next;
    }
    printf("Temp == Null\n"); //debugging statement
    return 0;
}

// printf("[%s] [%d] [%d]\n",temp->task->name, temp->task->priority, temp->task->burst);