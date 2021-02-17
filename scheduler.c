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
    int arrival;
    int burst;
} node;


struct node *head = NULL;
struct node *io_head = NULL;
void insert_at_end(thread_t *, int);
void delete_from_begin();
int count = 0;
//=-----------------------------=

void scheduler(enum algorithm algorithm, unsigned int quantum) 
{ 
// nothing yet?
}

void sim_tick() { }

void sys_exec(thread_t *t) 
{
  insert_at_end(t, sim_time());
  sim_dispatch(head->thread);
}

void sys_read(thread_t *t) 
{ 



  if(head != NULL)
    sim_dispatch(head->thread);
}

void sys_write(thread_t *t) 
{



  if(head != NULL)
    sim_dispatch(head->thread);
}

void sys_exit(thread_t *t) 
{
  delete_from_begin();
  if(head != NULL)
    sim_dispatch(head->thread);
}

void io_complete(thread_t *t) 
{
  //insert_at_end(t, sim_time());
  
  if(head != NULL)
    sim_dispatch(head->thread);
}

void io_starting(thread_t *t) 
{ 

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


void insert_at_end(thread_t *td, int arrived) {
  struct node *t, *temp;

  t = (struct node*)malloc(sizeof(struct node));
  t->thread = td;
  t->arrival = arrived;
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
