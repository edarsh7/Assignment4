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
    int completed;
    int start1;
    int start2;
    int io_done;
    int wait_time;
    int turnaround;
    int first_time;
} node;

int flag = 0;
struct node *head = NULL; 
struct node *td_list = NULL;

void insert_at_end(thread_t *);
void insert_td_list(thread_t *);
void delete_from_begin();
int count = 0;
//=-----------------------------=

void td_arrival(thread_t *);
void td_completed(thread_t *);

void io_completed(thread_t *);
void wait_time(thread_t *);
void turnaround(thread_t *);
void left_queue(thread_t *);

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
  td_arrival(t);

  if(flag == 0 && head != NULL)
  {
    left_queue(head->thread);
    sim_dispatch(head->thread);
    flag = 1;
  }
}

void sys_read(thread_t *t) 
{
  flag = 0;
  delete_from_begin();


  if(flag == 0 && head != NULL)
  {
    left_queue(head->thread);
    sim_dispatch(head->thread);
    flag = 1;
  }
}

void sys_write(thread_t *t) 
{
  flag = 0;
  delete_from_begin();

  if(flag == 0 && head != NULL)
  {
    left_queue(head->thread);
    sim_dispatch(head->thread);
    flag = 1;
  }
}

void sys_exit(thread_t *t) 
{
  flag = 0;
  
  td_completed(t);
  delete_from_begin();

  if(flag == 0 && head != NULL)
  {
    left_queue(head->thread);
    sim_dispatch(head->thread);
    flag = 1;
  }
}

void io_complete(thread_t *t) 
{
  
  insert_at_end(t);
  io_completed(t);

  if(flag == 0)
  {
    left_queue(head->thread);
    sim_dispatch(head->thread);
    flag = 1;
  }
}

void io_starting(thread_t *t) 
{ 

}

stats_t *stats() { 
  int thread_count = count;
  stats_t *stats = malloc(sizeof(stats_t));
  stats->tstats = malloc(sizeof(stats_t) * thread_count);


  struct node *temp = td_list;

  int i = 0;
  while(temp != NULL)
  {
    if(i == 0)
    {
      temp = temp->next;
      i = 1;
      continue;
    }
    temp->start1++;
    temp = temp->next;
  }
  temp = td_list;
  while(temp != NULL)
  {
    turnaround(temp->thread);
    wait_time(temp->thread);
    printf("s1: %d    s2: %d  \n", temp->start1, temp->start2);
    temp = temp->next;
  }

  temp = td_list;
  int x = 0;
  int y = 0;
  while(temp != NULL)
  {
    stats->tstats[temp->thread->tid - 1].tid = temp->thread->tid;
    stats->tstats[temp->thread->tid - 1].turnaround_time = temp->turnaround;
    stats->tstats[temp->thread->tid - 1].waiting_time = temp->wait_time; 
    x = x + temp->turnaround;
    y = y + temp->wait_time;
    temp=temp->next;
  }
  stats->thread_count = count;
  stats->turnaround_time = x/count;
  stats->waiting_time = y/count;

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

//--------------------------------------------------------------------
//==================================================================
void td_arrival(thread_t *td)
{
  struct node *temp;
  temp = td_list;

  while(temp->thread->tid != td->tid)
  {
    temp = temp->next;
  }

  temp->first_time = 0;
  temp->arrival = sim_time();
}

void td_completed(thread_t *td)
{
  struct node *temp;
  temp = td_list;

  while(temp->thread->tid != td->tid)
  {
    temp = temp->next;
  }

  temp->completed = sim_time();
}

void io_completed(thread_t *td)
{
  struct node *temp;
  temp = td_list;

  while(temp->thread->tid != td->tid)
  {
    temp = temp->next;
  }

  temp->io_done = sim_time();
}

void wait_time(thread_t *td)
{  
  struct node *temp;
  temp = td_list;

  while(temp->thread->tid != td->tid)
  {
    temp = temp->next;
  }

  if(temp->io_done == 0)
  {
    temp->wait_time = temp->start1 - temp->arrival;
    return;
  }
}

void turnaround(thread_t *td)
{
  struct node *temp;
  temp = td_list;

  while(temp->thread->tid != td->tid)
  {
    temp = temp->next;
  }

  temp->turnaround = temp->completed - temp->arrival + 1;
}

void left_queue(thread_t *td)
{
  struct node *temp;
  temp = td_list;

  while(temp->thread->tid != td->tid)
  {
    temp = temp->next;
  }

  if(temp->first_time == 0)
  {
    temp->start1 = sim_time();
    temp->first_time = 1;
  }
  else
  {
    temp->start2 = sim_time();
    temp->first_time = 2;
  }
}
