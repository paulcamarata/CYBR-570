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
    if(pickNextTask() == NULL) {
        exit(0);
    }
    Task *currentTask = (Task *) malloc(sizeof(Task));
    currentTask = pickNextTask();

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
    int sjf = temp->task->burst;
    int i = 0;
    Task *chosenTask = (Task *) malloc(sizeof(Task));
    chosenTask = temp->task;

    while (temp != NULL) {
        i = i+1;
        if(temp->task->burst < sjf) {
            sjf = temp->task->burst;
            chosenTask = temp->task;
//            printf("Current Task = %s\n",chosenTask->name); //debugging statement
        }
        if(temp->next == NULL) {
            return chosenTask;
        }
        temp = temp->next;
    }
}

// printf("[%s] [%d] [%d]\n",temp->task->name, temp->task->priority, temp->task->burst);
