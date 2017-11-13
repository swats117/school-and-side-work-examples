/*
	A strange pseudocode to find the largest independent set in a k-orderly graph.
*/


int getLookup#(start, bool* bucketContents){
	int lookup#
	for(int element=start, element<start+k+1; element++){
		if(bucketContents[i]==true) :
			lookup# += 1 << element - start
	}
	return lookup#
}



R(bool** graph,int start, bool* bucketContents){

	// If there are no more elements to consider.
	if start == N - K :
		return 0

	// Look for memoized answer
	memoized = memoTable[start][getLookup#(start, bucketContents)]
	if memoized != -1 :
		return memoized
	// Look for memoized answer


	// Shift window
	newElement = start+k+1
	bucketContents[start] = false
	// Shift window

	// Consider not adding new element to set
	dont_include_new = R(graph, start+1, bucketContents)

	independent = true
	for(int i=start+1; i<start+K+1; i++){
		// If the new element is connected to a member of the bucket
		// then the bucket Contents are an independent set.
		if graph[newElement][i]==true :
			independent = false
			break
	}

	include_new = 0
	if independent==true :
		// Consider when new element is added to the bucket
		bucketContents[newElement]=true
		include_new = 1 + R(graph, start+1, bucketContents)
		bucketContents[newElementCo] = false

	// Record the answer in the memo table.
	memoTable[start][getLookup#(start, bucketContents)] = max(include_new, dont_include_new)
	return memoTable[start][getLookup#(start, bucketContents)]

}





