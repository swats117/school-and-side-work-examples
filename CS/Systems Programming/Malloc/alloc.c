/**
 * Machine Problem: Malloc
 * CS 241 - Fall 2016
 * author: Charles Swarts
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// #include "other_helper_functions.h"


typedef struct block
{
	// Bits for encoding variable are as follows
	// [31] for free status
	// [30] for last status
	// [29] for first status
	// [28-0] for size of the storage area measured in 8 byte chunks
	int encoding;
	// When a block is in use, this information isn't kept.
	// When it isn't in use, these act as the links in the 
	// doubly linked list.
	struct block* prev;
	struct block* next;
	// At the end of a block, the last 4 bytes are also reserved
	// as a boundary tag for the encoding again.
} block;


/* global variables */

// There are 28 block size tiers. 
// The smallest block tier covers sizes from 2^0 to 2^1-1.
// It is Followed by a tier which covers sizes 2^1 to (2^2-1). 
// The largest block tier covers sizes 2^29 to(2^30-1). 
block* block_headList [28]={NULL};

// We keep track of which block is last so we can request less space.

block* lastBlock;

int heap_initialized_flag;


// We expand the heap logarithmically to speed things up, that means the program
// uses an artificial heap...
size_t bytes_left_in_heap;
void* top_of_the_heap;

int heap_size;
size_t heap_sizes [29] = {0, 24, 48, 96, 192, 384, 768, 1536, 3072, 6144, 12288, /*10*/
						  24576, 49152, 98304, 196608, 393216, 786432, 1572864, /*17*/
						  3145728, 6291456, 12582912, 25165824, 50331648, 100663296, /*23*/
						  201326592, 402653184, 805306368, 1610612736, 2500000000};


// Basically a block looks like this

// When not in use
// |Encoding|Prev|Next| ... |Encoding|

// When in use
// |Encoding|Storage|Encoding|

/* helper function signatures */

// Takes in a size in bytes and rounds up to the nearest size
// in 8 byte chunks.
int calculate_size(size_t bytes)
{
	return (int)((bytes+7)/8);
}

block* return_block(void* ptr)
{
	return (block*) (((int*)ptr)-1);
}
void* return_storage(block* target)
{
	return (void*) (((int*)target)+1);
}

// Takes the size in 8 byte chunks and returns
// which pool the block would be put in it's freelist.
int storageSize_to_tier(int request);
// Takes the size requested by a block and returns
// which tier it is immediately able to take from.
int requestSize_to_tier(int request);

// 0 is occupied
// 1 is free
int getFree(block* target);
void setFree(block* target, int freedom_status);

// 0 is not last
// 1 is last
int getLast(block* target);
void setLast(block* target, int last_status);

// 0 is not first
// 1 is first
int getFirst(block* target);
void setFirst(block* target, int first_status);

// Gets and sets the size of the storage area of a block.
int getSize(block* target);
// setSize also sets the end boundary tag.
void setSize(block* target, int size);

block* getLeftNeighbor(block* target);
block* getRightNeighbor(block* target);



void removeFromFreeList(block* target);
void addToFreeList(block* target);

//Splits and initializes two children structs from a parent struct.
block* split_off_what_I_need(block* parent, int request);

block* splitManager(int targetTier);

block* expand_heap_for_newBlock(int request_size);

void coalesce_rightwards(block* target);
block* coalesce_leftwards(block* target);




// These are the functions implemented.

void* malloc(size_t size);
void free(void *ptr);
void *calloc(size_t num, size_t size);
void* realloc(void *ptr, size_t size);



int main()
{

	// Beginning to free given ptr:0xa5db02c
	// malloc for 268435458 returned pointer: 0x25db01c

	// Beginning to free given ptr:0x25db01c
	// malloc for 134217730 returned pointer: 0x25db01c
	// malloc for 134217730 returned pointer: 0x25db01c
	

	int* big_int = malloc(20*sizeof(int));

	for(int i=0; i<20; i++)
		big_int[i]=i;

	int* big_int2 = malloc(20*sizeof(int));
	big_int = realloc(big_int, 40*sizeof(int));

	for(int i=0; i<20; i++)
		// fprintf(stderr, "big_int i=%d\n", big_int[i]);

	free(big_int);
	free(big_int2);
	


	for(int i=0;i<28; i++)
	{
		// Problem in reporting indicates garbage values inserted in 
		// linked list.
		block* current=block_headList[i];
		while(current)
		{
			// fprintf(stderr, "%d encoding: %x\n", i, current->encoding);
			current = current->next;
		}

	}

	return 1;
}


// /**
//  * Allocate memory block
//  *
//  * Allocates a block of size bytes of memory, returning a pointer to the
//  * beginning of the block.  The content of the newly allocated block of
//  * memory is not initialized, remaining with indeterminate values.
//  *
//  * @param size
//  *    Size of the memory block, in bytes.
//  *
 /* @return
 *    On success, a pointer to the memory block allocated by the function.
 *
 *    The type of this pointer is always void*, which can be cast to the
 *    desired type of data pointer in order to be dereferenceable.
 *
 *    If the function failed to allocate the requested block of memory,
 *    a null pointer is returned.
 *
 * @see http://www.cplusplus.com/reference/clibrary/cstdlib/malloc/
 */
void* malloc(size_t size) 
{

	block* new_block = splitManager(calculate_size(size));

	void* storage_ptr = return_storage(new_block);

	// fprintf(stderr, "malloc for %lu returned pointer: %p\n", size, storage_ptr);
	return storage_ptr;

}

/**
 * Allocate space for array in memory
 *
 * Allocates a block of memory for an array of num elements, each of them size
 * bytes long, and initializes all its bits to zero. The effective result is
 * the allocation of an zero-initialized memory block of (num * size) bytes.
 *
 * @param num
 *    Number of elements to be allocated.
 * @param size
 *    Size of elements.
 *
 * @return
 *    A pointer to the memory block allocated by the function.
 *
 *    The type of this pointer is always void*, which can be cast to the
 *    desired type of data pointer in order to be dereferenceable.
 *
 *    If the function failed to allocate the requested block of memory, a
 *    NULL pointer is returned.
 *
 * @see http://www.cplusplus.com/reference/clibrary/cstdlib/calloc/
 */
void *calloc(size_t num, size_t size) {
  size_t product = num*size;
  void* output = malloc(product);
  memset(output, 0, product);
  return output;
}

/**
 * Deallocate space in memory
 *
 * A block of memory previously allocated using a call to malloc(),
 * calloc() or realloc() is deallocated, making it available again for
 * further allocations.
 *
 * Notice that this function leaves the value of ptr unchanged, hence
 * it still points to the same (now invalid) location, and not to the
 * null pointer.
 *
 * @param ptr
 *    Pointer to a memory block previously allocated with malloc(),
 *    calloc() or realloc() to be deallocated.  If a null pointer is
 *    passed as argument, no action occurs.
 */
void free(void *ptr) 
{
	// fprintf(stderr,"\nBeginning to free given ptr:%p\n", ptr);
	block* target = return_block(ptr);
	// fprintf(stderr,"Beginning to free block mem:%p\n", target);
	
	// Just set the target to free, don't add to freeList
	// because if coalesce_leftwards returns target, we 
	// will get a segfault.
	setFree(target,1);
	// fprintf(stderr,"Beginning to coalesce\n");
	coalesce_rightwards(target);
	block* newFree = coalesce_leftwards( target );
	addToFreeList(newFree);
	// fprintf(stderr,"Done freeing\n");
}

/**
 * Reallocate memory block
 *
 * The size of the memory block pointed to by the ptr parameter is changed
 * to the size bytes, expanding or reducing the amount of memory available
 * in the block.
 *
 * The function may move the memory block to a new location, in which case
 * the new location is returned. The content of the memory block is preserved
 * up to the lesser of the new and old sizes, even if the block is moved. If
 * the new size is larger, the value of the newly allocated portion is
 * indeterminate.
 *
 * In case that ptr is NULL, the function behaves exactly as malloc, assigning
 * a new block of size bytes and returning a pointer to the beginning of it.
 *
 * In case that the size is 0, the memory previously allocated in ptr is
 * deallocated as if a call to free was made, and a NULL pointer is returned.
 *
 * @param ptr
 *    Pointer to a memory block previously allocated with malloc(), calloc()
 *    or realloc() to be reallocated.
 *
 *    If this is NULL, a new block is allocated and a pointer to it is
 *    returned by the function.
 *
 * @param size
 *    New size for the memory block, in bytes.
 *
 *    If it is 0 and ptr points to an existing block of memory, the memory
 *    block pointed by ptr is deallocated and a NULL pointer is returned.
 *
 * @return
 *    A pointer to the reallocated memory block, which may be either the
 *    same as the ptr argument or a new location.
 *
 *    The type of this pointer is void*, which can be cast to the desired
 *    type of data pointer in order to be dereferenceable.
 *
 *    If the function failed to allocate the requested block of memory,
 *    a NULL pointer is returned, and the memory block pointed to by
 *    argument ptr is left unchanged.
 *
 * @see http://www.cplusplus.com/reference/clibrary/cstdlib/realloc/
 */
void* realloc(void *storage_ptr, size_t size) 
{
	// fprintf(stderr, "\nReallocing %p, to size %lu\n", storage_ptr, size);

	// Right from the docs.
	// If it is 0 and ptr points to an existing block of memory, the memory
 	// block pointed by ptr is deallocated and a NULL pointer is returned.
	if(storage_ptr && !size)
	{
		free(storage_ptr);
		return NULL;
	}
	// In case that ptr is NULL, the function behaves exactly as malloc, assigning
 	// a new block of size bytes and returning a pointer to the beginning of it.
	if(!storage_ptr && size)
	{
		return malloc(size);
	}
	// In the malloc docs, it says that they will never malloc size 0, so 
	// we don't need to worry about the third case.

	block* target_block = return_block(storage_ptr);

	int oldSize = getSize(target_block);
	int newSize = calculate_size(size);

	// If we are downsizing or staying the same, we don't do much.
	if(newSize<=oldSize)
	{
		// fprintf(stderr, "the newSize is smaller than the oldSize\n");
		split_off_what_I_need(target_block, newSize);
		// split_off_what_I_need takes care of all the details, and we
		// just return the original pointer.
		return storage_ptr;
	}
	// If we are upsizing, then we 
	// 1: copy the first 16 bytes of storage.
	// 2: free the ptr, but keep it around.
	// 3: call split manager.
	// if split manager returns the same block, then
	// we replace the first 16 bytes and send it off
	// otherwise we put in the first 16 bytes and copy
	// the rest from the storage section of the now free block.
	else
	{
		// fprintf(stderr, "The newSize is bigger than the oldSize\n");

		//1: copy in the first 16 bytes of storage
		int* int_cast_SP = (int*)storage_ptr;
		int first_16[4] = {int_cast_SP[0], int_cast_SP[1], int_cast_SP[2], int_cast_SP[3]};

		// 2: free the ptr, but keep it around.
		// free(storage_ptr);

		// 3: call split manager.
		block* new_block = splitManager(calculate_size(size));


		// if split manager returns the same block
		if(new_block==target_block)
		{
			// fprintf(stderr,"Split Manager returned same block\n");
			// we replace the first 16 bytes and send it off
			int_cast_SP[0] = first_16[0];
			int_cast_SP[1] = first_16[1];
			int_cast_SP[2] = first_16[2];
			int_cast_SP[3] = first_16[3];

			return storage_ptr;
		}
		else
		{
			// fprintf(stderr, "Split manager returned different block\n");
			// otherwise we put in the first 16 bytes and copy
			// the rest from the storage section of the now free block.
			void* new_storage_ptr = return_storage(new_block);
			// fprintf(stderr, "new block is sized %d\n", getSize(new_block));
			// fprintf(stderr, "new block is %p\n", new_block);
			// fprintf(stderr, "new storage_ptr is %p\n", new_storage_ptr);

			int* int_cast_NSP = (int*)new_storage_ptr;
			int_cast_NSP[0] = first_16[0];
			int_cast_NSP[1] = first_16[1];
			int_cast_NSP[2] = first_16[2];
			int_cast_NSP[3] = first_16[3];

			int size_in_ints = oldSize*2;
			for(int i=4; i<size_in_ints; i++)
			{
				int_cast_NSP[i]=int_cast_SP[i];
			}
			free(storage_ptr);
			return new_storage_ptr;
		}
	}
	// fprintf(stderr,"error in realloc\n");
  	return NULL;
}





