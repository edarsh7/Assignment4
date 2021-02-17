/**
 * See scheduler.h for function details. All are callbacks; i.e. the simulator 
 * calls you when something interesting happens.
 */
#include <stdlib.h>
#include <stdio.h>

#include "simulator.h"
#include "scheduler.h"



/*
 code for list implementation borrowed from https://www.programmingsimplified.com/c/data-structures/c-program-implement-linked-list
*/
//=-----------------------------=
typedef struct node {
    thread_t * thread;
    struct node * next;
} node;


struct node *head = NULL;
void insert_at_end(thread_t *);
void delete_from_begin();
int count = 0;
//=-----------------------------=

thread_t * top_of_list();


void scheduler(enum algorithm algorithm, unsigned int quantum) 
{ 
 printf("1");
}

void sim_tick() { }

void sys_exec(thread_t *t) 
{
  printf("2");
}

void sys_read(thread_t *t) 
{ 
printf("3");
}

void sys_write(thread_t *t) 
{
printf("4");
}

void sys_exit(thread_t *t) 
{ 
  printf("5");
}

void io_complete(thread_t *t) 
{ printf("6");

}

void io_starting(thread_t *t) 
{ 
printf("7");
}


stats_t *stats() { 
  int i = 0; // Remove - only here to fail code warnings check
  return NULL; 
}


void insert_at_end(thread_t *td) {
  struct node *t, *temp;

  t = (struct node*)malloc(sizeof(struct node));
  t->thread = td;
  count++;

  if (head == NULL) {
    head = t;
    head->next = NULL;
    return;
  }

  temp = head;

  while (temp->next != NULL)
    temp = temp->next;

  temp->next = t;
  t->next   = NULL;
}

void delete_from_begin() {

  struct node *t;


  if (head == NULL) {
    return;
  }


  t = head->next;
  free(head);
  head = t;
  count--;

}

thread_t * top_of_list()
{
  if(head != NULL)
    return head->thread;
  
}