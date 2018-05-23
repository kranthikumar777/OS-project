/*
 File: scheduler.C
 
 Author:
 Date  :
 
 */

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include "scheduler.H"
#include "thread.H"
#include "console.H"
#include "utils.H"
#include "assert.H"
#include "simple_keyboard.H"
#include "simple_timer.H"

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* METHODS FOR CLASS   S c h e d u l e r  */
/*--------------------------------------------------------------------------*/

Scheduler::Scheduler() {
  //assert(false);
	//Initially the thread queue is empty
	q_head = NULL;
	q_tail = NULL;
  Console::puts("Constructed Scheduler.\n");
}

void Scheduler::yield() {
  //assert(false);
	//First disable the interrupts
	Machine::disable_interrupts();
	
	if (q_head == NULL) {
		assert(true);
	}
	//Assign the next thread in queue to dispatch the thread
 	ready_queue * next_thr = q_head;
	Thread * next_thread = next_thr->thread;
	if (q_head == q_tail) {
		q_tail == NULL;	
	}
	q_head = q_head->next;
	delete next_thr;
	//dispatch the thread 
	Thread::dispatch_to(next_thread);
	//Enable the interrupts agian back
	Machine::enable_interrupts();	
}

void Scheduler::resume(Thread * _thread) {
  //assert(false);
	//First disable the interrupts
	Machine::disable_interrupts();
	
	ready_queue * new_thread = new ready_queue;
	new_thread->thread = _thread;
	new_thread->next = NULL;
	if (q_head == NULL) {
		q_head = new_thread;
		q_tail = new_thread;
	} else {
		q_tail->next = new_thread;
		q_tail = q_tail->next;
	}

	//Enable the interrupts agian back
	Machine::enable_interrupts();	
}

void Scheduler::add(Thread * _thread) {
  //assert(false);
	resume(_thread);
}

void Scheduler::terminate(Thread * _thread) {
  //assert(false);
	delete _thread;
	yield();
}


//Round Robin scheduler Implementation

RRScheduler::RRScheduler(unsigned _eoq) {
  //assert(false);
	//Initially the thread queue is empty
	q_head = NULL;
	q_tail = NULL;
	EOQ = _eoq;
	//Constructing a 50ms timer and handles interrupts handler
	SimpleTimer * timer = new SimpleTimer(1000/EOQ);  
	InterruptHandler::register_handler(0,timer);
  Console::puts("Constructed Round Robin Scheduler.\n");
}

void RRScheduler::yield() {
  //assert(false);
	//First disable the interrupts
	//Machine::disable_interrupts();
	
	if (q_head == NULL) {
		assert(true);
	}
	//Assign the next thread in queue to dispatch the thread
 	ready_queue * next_thr = q_head;
	Thread * next_thread = next_thr->thread;
	if (q_head == q_tail) {
		q_tail == NULL;	
	}
	q_head = q_head->next;
	delete next_thr;
	//dispatch the thread 
	Thread::dispatch_to(next_thread);
	//Enable the interrupts agian back
	Machine::enable_interrupts();	
}

void RRScheduler::resume(Thread * _thread) {
  //assert(false);
	//First disable the interrupts
	//Machine::disable_interrupts();
	
	ready_queue * new_thread = new ready_queue;
	new_thread->thread = _thread;
	new_thread->next = NULL;
	if (q_head == NULL) {
		q_head = new_thread;
		q_tail = new_thread;
	} else {
		q_tail->next = new_thread;
		q_tail = q_tail->next;
	}

	//Enable the interrupts agian back
	//Machine::enable_interrupts();	
}

void RRScheduler::add(Thread * _thread) {
  //assert(false);
	//resume(_thread);
	//First disable the interrupts
	Machine::disable_interrupts();
	
	ready_queue * new_thread = new ready_queue;
	new_thread->thread = _thread;
	new_thread->next = NULL;
	if (q_head == NULL) {
		q_head = new_thread;
		q_tail = new_thread;
	} else {
		q_tail->next = new_thread;
		q_tail = q_tail->next;
	}

	//Enable the interrupts agian back
	Machine::enable_interrupts();	
}

void RRScheduler::terminate(Thread * _thread) {
  //assert(false);
	delete _thread;
	yield();
}
