/*
     File        : blocking_disk.c

     Author      : 
     Modified    : 

     Description : 

*/

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include "assert.H"
#include "utils.H"
#include "console.H"
#include "blocking_disk.H"
#include "scheduler.H"
#include "simple_disk.H"
#include "thread.H"

extern Scheduler * SYSTEM_SCHEDULER;

/*--------------------------------------------------------------------------*/
/* CONSTRUCTOR */
/*--------------------------------------------------------------------------*/

BlockingDisk::BlockingDisk(DISK_ID _disk_id, unsigned int _size) 
  : SimpleDisk(_disk_id, _size) {
}

//We can do it in two methods i.e., 1. Changing read and write functions to make the threads blocking at each instance or 2. We can implement sceduler and give keep the thread in queue for blocking when it has the cpu

//Is_ready is already implemented in Simple disk so we can use that 
void BlockingDisk::wait_until_ready() {
	while (!is_ready()) {
		//Machine::disable_interrupts();
		//Put the current thread into the ready_queue
		SYSTEM_SCHEDULER->resume(Thread::CurrentThread());
		//Give yeild to CPU while we are waiting for I/O operations
		SYSTEM_SCHEDULER->yield();
		//Machine::enable_interrupts();
	}
}
/*--------------------------------------------------------------------------*/
/* SIMPLE_DISK FUNCTIONS */
/*--------------------------------------------------------------------------*/
/*
void BlockingDisk::read(unsigned long _block_no, unsigned char * _buf) {
  // -- REPLACE THIS!!!
  //SimpleDisk::read(_block_no, _buf);
	issue_operation(READ,_block_no);
	while(!is_ready) {
		//Put the current thread into the ready_queue
		SYSTEM_SCHEDULER->resume(Thread::CurrentThread());
		//Give yeild to CPU while we are waiting for I/O operations
		SYSTEM_SCHEDULER->yield();
	}
	int i;
  	unsigned short tmpw;
  	for (i = 0; i < 256; i++) {
    		tmpw = Machine::inportw(0x1F0);
   		_buf[i*2]   = (unsigned char)tmpw;
    		_buf[i*2+1] = (unsigned char)(tmpw >> 8);
  	}
}


void BlockingDisk::write(unsigned long _block_no, unsigned char * _buf) {
  // -- REPLACE THIS!!!
  //SimpleDisk::read(_block_no, _buf);
	issue_operation(WRITE,_block_no);
	while(!is_ready) {
		//Put the current thread into the ready_queue
		SYSTEM_SCHEDULER->resume(Thread::CurrentThread());
		//Give yeild to CPU while we are waiting for I/O operations
		SYSTEM_SCHEDULER->yield();
	}
	int i;
  	unsigned short tmpw;
  	for (i = 0; i < 256; i++) {
    		tmpw = Machine::inportw(0x1F0);
   		_buf[i*2]   = (unsigned char)tmpw;
    		_buf[i*2+1] = (unsigned char)(tmpw >> 8);
  	}
}
*/
