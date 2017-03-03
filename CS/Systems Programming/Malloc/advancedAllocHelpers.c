/*
	advanced functions for Malloc
*/

block* split_off_what_I_need(block* parent, int size_needed)
{
	if(size_needed<2)
		size_needed=2;

	// fprintf(stderr, "\nentered split_off_what_I_need\n");
	// fprintf(stderr, "parent starts with encoding: %x\n", parent->encoding);
	int prior_size = getSize(parent);
	int difference_in_size = prior_size - size_needed;

	 // fprintf(stderr, "prior_size: %d, size_needed: %d\n", prior_size, size_needed);

	if(difference_in_size >2)
	{
		// fprintf(stderr, "the difference_in_size was >2\n");

		// We record if the parent was last.
		int last_status = getLast(parent);

		// We make the parent not last and make their size the size of the request.
		setLast(parent, 0);
		setSize(parent, size_needed);

		
		// fprintf(stderr, "parent now has encoding: %x\n", parent->encoding);

		// We then find where the offshoot will be.
		block* child = getRightNeighbor(parent);	

		// It will not be first, It will be free, and if the parent was last,
		// since the child is to the right of the parent, it will take on
		// the last status of the parent.
		setFirst(child, 0);
		// child gets freed in addToFreeList anyway
		// setFree(child, 1);
		setLast(child, last_status);

		setSize(child, difference_in_size-1);
		 // fprintf(stderr, "child now has encoding: %x\n", child->encoding);
		addToFreeList(child);
	}
	else
	{
		 // fprintf(stderr, "parent retains encoding: %x\n", parent->encoding);
	}
	// fprintf(stderr, "returning from split_off_what_I_need()\n");
	return parent;
}


// Checks the next tier up.
// If it's got a free block, it splits it and returns.
// If the next tier doesn't have a free block, but
// it is the size of the heap, it doubles the heap,
// and splits it then returns.
// it doubles the heap and splits.
block* splitManager(int request_size)
{
	// fprintf(stderr, "\nI'm the split manager!\n");

	int starting_tier = requestSize_to_tier(request_size);

	// fprintf(stderr, "Getting request of size: %d, which is tier: %d\n", request_size, starting_tier);

	for(int i=starting_tier ; i<28; i++)
	{
		block* freeBlock;
		if( (freeBlock = block_headList[i]) )
		{
			removeFromFreeList(freeBlock);
			 // fprintf(stderr,"sucessfully removed from freelist\n");
			return split_off_what_I_need(freeBlock, request_size);
		}
	}

	// This code searches through the eight largest tiers to recycle massive
	// storage sizes since it would be dangerous to request massive amounts of
	// space since that would overload the memory very fast.
	
	// fprintf(stderr,"About to do in depth search\n");

	for(int i=16; i<29; i++)
	if(starting_tier==i)
	{
		block* current = block_headList[i-1];
		while(current)
		{
			// fprintf(stderr, "LOOP??\n");
			if(getSize(current)>=request_size)
			{
				removeFromFreeList(current);
				return split_off_what_I_need(current, request_size);
			}
			current = current->next;
		}
	}

	// If we really can't find anything, we expand the heap.

	 // fprintf(stderr,"no immediately sourced blocks available\n");
	return expand_heap_for_newBlock(request_size);
	
}
// size_t bytes_left_in_heap;
// void* top_of_the_heap;

// int heap_size;
// size_t heap_sizes [29] = {0, 24, 48, 96, 192, 384, 768, 1536, 3072, 6144, 12288, 10
// 						  24576, 49152, 98304, 196608, 393216, 786432, 1572864, /*17*/
// 						  3145728, 6291456, 12582912, 25165824, 50331648, 100663296, /*23*/
// 						  201326592, 402653184, 805306368, 1610612736, 2500000000};
void double_the_heap()
{
	// fprintf(stderr, "\nentered double_the_heap\n");
	size_t current_heap_size = heap_sizes[heap_size];
	heap_size++;
	size_t next_heap_size = heap_sizes[heap_size];

	if(heap_size==29)
	{
		 // fprintf(stderr, "ran out of space, about to crash \n");
	}

	sbrk(next_heap_size-current_heap_size);

	bytes_left_in_heap += next_heap_size-current_heap_size;

	// fprintf(stderr,"Bytes left in heap: %lu \n", bytes_left_in_heap);
}

// Finds the top of the heap.
// Figures out if we can cut back on request-size
// by adding on to the last Block.
// It then calculates how much space we need to request
// It then 
block* expand_heap_for_newBlock(int request_size)
{
	// fprintf(stderr, "\nentered expand_heap_for_newBlock() with request: %d\n", request_size);

	if(request_size<2)
		request_size=2;

	int first_status =0;

	if(!heap_initialized_flag)
		{
			// fprintf(stderr,"Initializing the heap\n");
			first_status = 1;
			top_of_the_heap = sbrk(0);
			// fprintf(stderr,"top_of_the_heap is %p\n", top_of_the_heap);
			heap_initialized_flag = 1;
			double_the_heap();
		}

	int actual_request_size = request_size+1;

	block* new_block= (block*)top_of_the_heap;
	

	if(lastBlock && getFree(lastBlock))
	{
		// fprintf(stderr, "The last block, size: %d,  is available\n", getSize(lastBlock));
		// fprintf(stderr, "Removing last block from freelist\n");
		removeFromFreeList(lastBlock);

		actual_request_size = request_size - getSize(lastBlock);

		if(actual_request_size < 0)
			// fprintf(stderr, "Error in expand the heap, last block covers request\n");
			//Then the last block was so big it could fill the entire request
			//TODO figure out this part.
		first_status= getFirst(lastBlock);
		new_block = lastBlock;
	}

	 // fprintf(stderr, "new_block: %p\n", new_block);
	 // fprintf(stderr, "bytes_left_in_heap for new block: %lu\n", bytes_left_in_heap);
	 // fprintf(stderr, "the new block requests: %lu bytes\n", ((size_t)(actual_request_size*8)) );

	while( actual_request_size > ((int)(bytes_left_in_heap/8)) )
	{
		// fprintf(stderr,"doubling the heap\n");
		double_the_heap();
		 // fprintf(stderr, "\n");
	}

	bytes_left_in_heap -= (size_t)(8*actual_request_size);

	// fprintf(stderr, "broke from loop\n" );
	// fprintf(stderr, "new_block: %p\n", new_block);
	// fprintf(stderr, "bytes_left_in_heap: %lu\n", bytes_left_in_heap);


	

	//temporarily set the block as not last to get it's "right neighbor".
	//Set the size so that getRightNeighbor works right.
	setLast(new_block, 0);
	setSize(new_block, request_size);

	top_of_the_heap = (void*)getRightNeighbor(new_block);



	setFree(new_block, 0);
	setFirst(new_block, first_status);
	setLast(new_block, 1);
	

	// fprintf(stderr, "new top of the heap is at %p\n", top_of_the_heap);

	

	
	

	// fprintf(stderr, "Expanded the heap, new block has encoding %x\n", new_block->encoding);

	return new_block;
}


void coalesce_rightwards(block* target)
{
	// fprintf(stderr, "\nRight coalescing %p, with encoding %x\n", target, target->encoding);
	block* right_neighbor=target; 
	int new_size = getSize(target);

	while( (right_neighbor = getRightNeighbor(right_neighbor)) && getFree(right_neighbor))
	{
		 // fprintf(stderr, "right neighbor, %p, with encoding: %x, was free\n", right_neighbor, right_neighbor->encoding);
		removeFromFreeList(right_neighbor);
		new_size += getSize(right_neighbor) +1;
	}
	// getRightNeighbor only returns NULL if the right neighbor was last
	// If the neighbor we incorporate is last, then we become last.
	if(!right_neighbor)
	{
		// fprintf(stderr, "target is last\n");
		setLast(target, 1);
	}

	setSize(target, new_size);
	// fprintf(stderr, "finished right coallesce product, %p, has encoding: %x\n",target, target->encoding);
}

block* coalesce_leftwards(block* target)
{
	// fprintf(stderr, "\nLeft Coalescing %p, which has encoding %x\n",target, target->encoding);
	block* left_neighbor = target;
	block* current       = target;

	int new_size = getSize(target);
	int last_status = getLast(target);

	while( (left_neighbor = getLeftNeighbor(current)) && getFree(left_neighbor))
	{
		 // fprintf(stderr, "left neighbor %p, encoding: %x, was free\n", left_neighbor, left_neighbor->encoding);
		removeFromFreeList(left_neighbor);
		current = left_neighbor;
		new_size += getSize(left_neighbor)+1;
	}
	// getLeftNeighbor only returns NULL if it was first
	// so left_neighbor was first when we called for it's left neighbor.
	setLast(current, last_status);
	setSize(current, new_size);
	// fprintf(stderr, "finished left coallesce product, %p, has encoding: %x\n", current, current->encoding);

	return current;
}







