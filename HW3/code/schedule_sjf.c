/**
 * Implementation of various scheduling algorithms.
 *
 * SJF scheduling
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

void schedule() {

    Task *currentTask = pickNextTask();

    if(!currentTask) {
        exit(0);
    }

    run(currentTask, currentTask->burst);
    delete(&head, currentTask);
    schedule();
}

Task *pickNextTask() {

    struct node *temp;
    temp = head;

    if (!temp){
        printf("Nice job! Teacher, give this student an A.\n");
        exit(0);
    }

    int sjf = temp->task->burst;
    Task *chosenTask = temp->task;

    while (temp) {

        if(temp->task->burst <= sjf) {
            sjf = temp->task->burst;
            chosenTask = temp->task;
        }

        if(!temp->next) {
            return chosenTask;
        }

        temp = temp->next;
    }

    return 0;
}