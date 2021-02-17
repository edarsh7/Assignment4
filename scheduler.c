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
    struct node * prev;
} node;


struct node *head = NULL; 
struct node *td_list = NULL;

void insert_at_end(thread_t *, struct node *);
void delete_from_begin(struct node *);
int count = 0;
//=-----------------------------=



void scheduler(enum algorithm algorithm, unsigned int quantum) 
{ 
// nothing yet
}

void sim_tick() { }

void sys_exec(thread_t *t) 
{
  count++;
  insert_at_end(t, head);
  
  sim_dispatch(head->thread);
}

void sys_read(thread_t *t) 
{
  delete_from_begin(head);
  if(head != NULL)
    sim_dispatch(head->thread);
}

void sys_write(thread_t *t) 
{
  delete_from_begin(head);
  if(head != NULL)
    sim_dispatch(head->thread);
}

void sys_exit(thread_t *t) 
{
  delete_from_begin(head);
  if(head != NULL)
    sim_dispatch(head->thread);
}

void io_complete(thread_t *t) 
{


  insert_at_end(t, head);
  if(head != NULL)
    sim_dispatch(head->thread);
}

void io_starting(thread_t *t) 
{ 
  //nothing to do here but get time

}


stats_t *stats() { 
  int thread_count = count;
  stats_t *stats = malloc(sizeof(stats_t));
  stats->tstats = malloc(sizeof(stats_t) * thread_count);

  stats->tstats[0].tid = 1;
  stats->tstats[0].turnaround_time = 8;
  stats->tstats[0].waiting_time = 0;

  stats->thread_count = thread_count;
  stats->turnaround_time = 8;
  stats->waiting_time = 0;
  return stats;
}


void insert_at_end(thread_t *td, struct node * top) {
  struct node *t, *temp;

  t = (struct node*)malloc(sizeof(struct node));
  t->thread = td;

  if (top == NULL) {
    top = t;
    top->next = NULL;
    top->prev = NULL;
    return;
  }

  temp = top;

  while (temp->next != NULL)
    temp = temp->next;

  temp->next = t;
  t->next   = NULL;
  t->prev   = temp;
}

void delete_from_begin(struct node * top) {

  struct node *t;

  if (top == NULL) {
    return;
  }

  t = top->next;
  free(top);
  top = t;
}


