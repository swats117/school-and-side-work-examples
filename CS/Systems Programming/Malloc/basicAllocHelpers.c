/*
	base functions for malloc
*/



int getFree(block* target)
{
	return (target->encoding) & 0x80000000;
}
void setFree(block* target, int freedom)
{
	// fprintf(stderr, "setting target %p freedom to %d\n",target, freedom );
	if(freedom)
		target->encoding = target->encoding | 0x80000000;
	else
		target->encoding = target->encoding & 0x7FFFFFFF;
}

// 0 means this block isn't last
// 1 means this block is last

int getLast(block* target)
{
	return (target->encoding) & 0x40000000;
}
void setLast(block* target, int last_status)
{
	// fprintf(stderr, "\nentered setLast()\n");
	if(last_status)
	{
		// fprintf(stderr, "setting block to last\n");
		// Make sure the last last block is no longer last.
		if(lastBlock)
		{
			// fprintf(stderr, "lastBlock exists, setting it to not last\n");
			setLast(lastBlock, 0);
		}

		target->encoding = target->encoding | 0x40000000;
		lastBlock = target;
	}
	else
		target->encoding = target->encoding & 0xbfffffff;
}

// 0 means this block isn't first
// 1 means this block is first

int getFirst(block* target)
{
	// fprintf(stderr, "\n in getFirst\n");
	return (target->encoding) & 0x20000000;
}
void setFirst(block* target, int first_status)
{
	// fprintf(stderr, "\n entered setFirst(), modifying target at %p\n", target);
	if(first_status)
		target->encoding = target->encoding | 0x20000000;
	else
		target->encoding = target->encoding & 0xdfffffff;
}


int getSize(block* target)
{
	return target->encoding & 0x1fffffff;
}
void setSize(block* target, int size)
{
	target->encoding = (target->encoding & 0xe0000000) | (size);
	*(((int*)target)+ 2*size + 1) = (target->encoding);
}

// Adds a pool to the appropriate freelist.
// Does this by adding the pool to the top
// of the stack.
void addToFreeList(block* target)
{

	// fprintf(stderr, "\nEntering addToFreeList()\n");
	// fprintf(stderr, "Adding %p with encoding %x to free list\n", target, target->encoding);
	setFree(target, 1);
	int tier = storageSize_to_tier(getSize(target));
	block* next = block_headList[tier];
	block_headList[tier] = target;
	target->next = next;
	if(next)
		next->prev = target;
	target->prev = NULL;
	// fprintf(stderr, "Target added to freelist had next: %p and prev %p\n",next, target->prev);
}

// Removes a pool from a free list.
// Does this by setting the next neighbor's prev
// to this pool's prev.
// Also sets prev's next to this pool's next
// If the link is at the top, then it set's the
// headList entry for this tier to this link's next.
void removeFromFreeList(block* target)
{
	//TODO: fix this function for targets not added to free list.
	//Or fix other function to get this working properly.
	// fprintf(stderr, "\nEntered removeFromFreeList()\n");
	// fprintf(stderr, "target: %p, has next:%p and prev:%p\n",target, target->next, target->prev);
	setFree(target, 0);
	// fprintf(stderr, "\n");
	if(target->next)
	{
		
		(target->next)->prev=target->prev;
		// fprintf(stderr,"Target next now has prev: %p\n", target->prev);
	}
	if(target->prev)
	{
		
		(target->prev)->next=target->next;
		// fprintf(stderr, "Target prev now has next: %p\n", target->next);
	}
	else
	{
		// fprintf(stderr, "Target was the head of the list\n");
		block_headList[storageSize_to_tier(getSize(target))] = target->next;
	}
	// fprintf(stderr,"exiting removeFromFreeList()\n");
}


// Returns the left neighbor through pointer arithmetic.
// Finds the end boundary tag of previous neighbor
// Extracts the size information from the tag.
// Finds the left neighbor
// If there is no left neighbor: returns NULL.
block* getLeftNeighbor(block* target)
{
	// fprintf(stderr, "\nEntered getLeftNeighbor()\n");
	// fprintf(stderr, "Target encoding is %x\n",target->encoding);
	if(getFirst(target))
	{
		// fprintf(stderr, "Target is first, returning NULL\n" );
		return NULL;
	}
	// fprintf(stderr, "Target is not first\n");

	int leftNeighborSize = getSize((block*)(((int*)target) - 1));

	// fprintf(stderr, "The left neighbor has size is %d\n", leftNeighborSize);

	return (block*) (((int*)target) - (2*leftNeighborSize + 2 ) );
}
// Returns the right neighbor through pointer arithmetic.
// If there is no right neighbor: returns NULL.
block* getRightNeighbor(block* target)
{
	// fprintf(stderr, "\nEntered getRightNeighbor()\n");
	if(getLast(target))
	{
		// fprintf(stderr, "Target is last, returning NULL\n");
		return NULL;
	}
	int targetSize = getSize(target);
	// fprintf(stderr, "Target size is %d\n", targetSize);
	block* rightNeighbor = (block*)  ( ((int*)target) + (2*targetSize) + 2);
	// fprintf(stderr, "Right neighbor is %p\n", rightNeighbor);
	return rightNeighbor;
}





int storageSize_to_tier(int request)
{   // The first one is really for blocks of size 2 and 3
	// since the minimum size is 2.
		 if( 4         >request )return 0 ;
	else if( 8         >request )return 1 ;
	else if( 16        >request )return 2 ;
	else if( 32        >request )return 3 ;
	else if( 64        >request )return 4 ;
	else if( 128       >request )return 5 ;
	else if( 256       >request )return 6 ;
	else if( 512       >request )return 7 ;
	else if( 1024      >request )return 8 ;
	else if( 2048      >request )return 9 ;
	else if( 4096      >request )return 10;
	else if( 8192      >request )return 11;
	else if( 16384     >request )return 12;
	else if( 32768     >request )return 13;
	else if( 65536     >request )return 14;
	else if( 131072    >request )return 15;
	else if( 262144    >request )return 16;
	else if( 524288    >request )return 17;
	else if( 1048576   >request )return 18;
	else if( 2097152   >request )return 19;
	else if( 4194304   >request )return 20;
	else if( 8388608   >request )return 21;
	else if( 16777216  >request )return 22;
	else if( 33554432  >request )return 23;
	else if( 67108864  >request )return 24;
	else if( 134217728 >request )return 25;
	else if( 268435456 >request )return 26;
	else if( 312500001 >request )return 27;
	else return -1;
}


int requestSize_to_tier(int request)
{       
		 if( 3         >request )return 0 ;
	else if( 5         >request )return 1 ;
	else if( 9         >request )return 2 ;
	else if( 17        >request )return 3 ;
	else if( 33        >request )return 4 ;
	else if( 65        >request )return 5 ;
	else if( 129       >request )return 6 ;
	else if( 257       >request )return 7 ;
	else if( 513       >request )return 8 ;
	else if( 1025      >request )return 9 ;
	else if( 2049      >request )return 10;
	else if( 4097      >request )return 11;
	else if( 8193      >request )return 12;
	else if( 16385     >request )return 13;
	else if( 32769     >request )return 14;
	else if( 65537     >request )return 15;
	else if( 131073    >request )return 16;
	else if( 262145    >request )return 17;
	else if( 524289    >request )return 18;
	else if( 1048577   >request )return 19;
	else if( 2097153   >request )return 20;
	else if( 4194305   >request )return 21;
	else if( 8388609   >request )return 22;
	else if( 16777217  >request )return 23;
	else if( 33554433  >request )return 24;
	else if( 67108865  >request )return 25;
	else if( 134217729 >request )return 26;
	else if( 268435457 >request )return 27;
	else if( 312500001 >request )return 28;
	else return -1;
}