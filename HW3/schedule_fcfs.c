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

    while (temp != NULL) {
        if(temp->next == NULL) {
            return temp->task;
        }

        temp = temp->next;
    }

    return 0;
}
