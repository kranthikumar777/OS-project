/*
 File: vm_pool.C
 
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

#include "vm_pool.H"
#include "console.H"
#include "utils.H"
#include "assert.H"
#include "simple_keyboard.H"
#include "page_table.H"

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
/* METHODS FOR CLASS   V M P o o l */
/*--------------------------------------------------------------------------*/

VMPool::VMPool(unsigned long  _base_address,
               unsigned long  _size,
               ContFramePool *_frame_pool,
               PageTable     *_page_table) {
    //assert(false);
	base_address = _base_address;
	size = _size;
	frame_pool = _frame_pool;
	page_table = _page_table;
	page_table->register_pool(this);
	//Create a virtual table 
	memory_list * vrt_mem_table = (memory_list *) base_address;
	vrt_mem_table -> start_address = (base_address >> 12);
	vrt_mem_table -> size = 1;
	int i;
	for (i=1; i<512; i++) {
		vrt_mem_table ++;
		vrt_mem_table -> start_address = -1;
		vrt_mem_table -> size = 1;
	}
    Console::puts("Constructed VMPool object.\n");
}

unsigned long VMPool::allocate(unsigned long _size) {
    //assert(false);
	unsigned long n_pages;
	if (_size & 0x00000FFF) {
		n_pages = (_size >> 12) +1;
	} else {
		n_pages = (_size >> 12);
	}
	memory_list * vrt_mem_table = (memory_list *) base_address;
	memory_list * vrt_mem_table_prev = (memory_list *) base_address;
	int i;
	for (i=1; i<512; i++) {
		vrt_mem_table ++;
		if (vrt_mem_table -> size == 0) {
			vrt_mem_table_prev = vrt_mem_table - 1;
			if ((vrt_mem_table->start_address - vrt_mem_table_prev->start_address) > (n_pages + vrt_mem_table_prev->size) ) {
				break;
			}		
		}	
	}
	if (i==512) {
		//assert (false);
	}
	vrt_mem_table->start_address = vrt_mem_table_prev->start_address + vrt_mem_table_prev->size;
	vrt_mem_table->size = n_pages;
    Console::puts("Allocated region of memory.\n");
	return (vrt_mem_table->start_address << 12 );
}

void VMPool::release(unsigned long _start_address) {
    //assert(false);
	unsigned long n_page;
	n_page = (_start_address >> 12);
	memory_list * vrt_mem_table = (memory_list *) base_address;
	memory_list * vrt_mem_table_next = (memory_list *) base_address;
	int i;
	for (i=1; i<512; i++) {
		vrt_mem_table ++;
		if (vrt_mem_table -> start_address == n_page) {
			vrt_mem_table_next = vrt_mem_table + 1;
			break;		
		}	
	}
	if (i==512) {
		assert (false);
	}
	int j;
	for (j=0; j<vrt_mem_table->size; j++) {
		page_table->free_page(vrt_mem_table->start_address + j);
	}
	if (i == 511) {
		vrt_mem_table->start_address = -1;
	} else {
		vrt_mem_table->start_address = vrt_mem_table_next->start_address;
	}
	vrt_mem_table->size = 0;
	unsigned long page_start = vrt_mem_table->start_address;
	vrt_mem_table--;
	while ((unsigned long) vrt_mem_table > base_address && vrt_mem_table->size == 0) {
		vrt_mem_table->start_address = page_start;
		vrt_mem_table--;
	}
    Console::puts("Released region of memory.\n");
}

bool VMPool::is_legitimate(unsigned long _address) {
    //assert(false);
	unsigned long page = _address >> 12;
	if ((_address >= base_address + size) || (base_address > _address)) {
		return false;
	}
	if (page == (base_address >> 12)) {
		return true;
	}
	int i;
	for (i=0; i<512; i++) {
		memory_list * vrt_mem_table = (memory_list *) (base_address) + i;
		if ((page <(vrt_mem_table->start_address + vrt_mem_table->size)) && (vrt_mem_table->start_address <= page)) {
			break;
		}
	}
Console::puts("Checked whether address is part of an allocated region.\n");
	if (i == 512) {
		return false;
	} else {
		return true;
	}
    
}

