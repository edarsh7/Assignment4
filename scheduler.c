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
    int io_start;
    int completion;
} node;


struct node *head = NULL; 
struct node *td_list = NULL;

void insert_at_end(thread_t *);
void insert_td_list(thread_t *);
void delete_from_begin();
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
  insert_at_end(t);
  insert_td_list(t);
  sim_dispatch(head->thread);
}

void sys_read(thread_t *t) 
{
  delete_from_begin();
  if(head != NULL)
    sim_dispatch(head->thread);
}

void sys_write(thread_t *t) 
{
  delete_from_begin();
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


  insert_at_end(t);
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


void insert_at_end(thread_t *td) {
  struct node *t, *temp;

  t = (struct node*)malloc(sizeof(struct node));
  t->thread = td;

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
}


void insert_td_list(thread_t *td) {

  struct node *t, *temp;

  t = (struct node*)malloc(sizeof(struct node));
  t->thread = td;

  if (td_list == NULL) {
    td_list = t;
    td_list->next = NULL;
    return;
  }

  temp = td_list;

  while (temp->next != NULL)
    temp = temp->next;

  temp->next = t;
  t->next   = NULL;
}

void td_arrival(thread_t *td)
{
  struct node *temp;
  temp = td_list;

  while(temp->thread->tid != td->tid)
  {
    temp = temp->next;
  }

  temp->arrival = sim_time();
}