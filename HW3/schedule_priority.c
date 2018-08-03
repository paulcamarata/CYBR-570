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

    run(currentTask, currentTask->burst);
    delete(&head, currentTask);
    schedule();
}

/**
 * Returns the next task selected to run.
 */
Task *pickNextTask()
{
    struct node *temp;
    temp = head;
    int i = 0;
    if (temp == NULL){
        printf("No more jobs in the queue\n");
        exit(0);
    }
 
    int pri = temp->task->priority;
    Task *chosenTask = temp->task;

    while (temp != NULL) {
        i = i+1;
        if(temp->task->priority < pri) {
            pri = temp->task->priority;
            chosenTask = temp->task;
        }
        if(temp->next == NULL) {
            return chosenTask;
        }
        temp = temp->next;
    }
    return 0;
}