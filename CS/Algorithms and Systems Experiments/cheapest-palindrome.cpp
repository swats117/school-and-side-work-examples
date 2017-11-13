/* Keeping track of all the cows can be a tricky task so Farmer John has installed a system to automate it. 
He has installed on each cow an electronic ID tag that the system will read as the cows pass by a scanner. 
Each ID tag's contents are currently a single string with length M (1 ≤ M ≤ 2,000) characters drawn from 
an alphabet of N (1 ≤ N ≤ 26) different symbols (namely, the lower-case roman alphabet).

// Cows, being the mischievous creatures they are, sometimes try to spoof the system by walking backwards.
 While a cow whose ID is "abcba" would read the same no matter which direction the she walks, a cow with 
 the ID "abcb" can potentially register as two different IDs ("abcb" and "bcba").

// FJ would like to change the cows's ID tags so they read the same no matter which direction the cow walks 
by. For example, "abcb" can be changed by adding "a" at the end to form "abcba" so that the ID is palindromic
 (reads the same forwards and backwards). Some other ways to change the ID to be palindromic are include 
 adding the three letters "bcb" to the begining to yield the ID "bcbabcb" or removing the letter "a" to yield 
 the ID "bcb". One can add or remove characters at any location in the string yielding a string longer or 
 shorter than the original string.

// Unfortunately as the ID tags are electronic, each character insertion or deletion has a cost (0 ≤ cost ≤ 10,000) 
which varies depending on exactly which character value to be added or deleted. Given the content of a cow's ID tag 
and the cost of inserting or deleting each of the alphabet's characters, find the minimum cost to change the ID tag 
so it satisfies FJ's requirements. An empty ID tag is considered to satisfy the requirements of reading the same 
forward and backward. Only letters with associated costs can be added to a string.
*/

#include <cstdio>
#include <map>
#include <string.h>
#include <string>
#include <stdlib.h>
using namespace std;


int is_palindrome(string& possible_palindrome){

	// int partial_palindrome_length
	int ppl=0;
	int length = possible_palindrome.length()-1;
	// printf("%d\n", length);
	while(possible_palindrome[ppl]==possible_palindrome[length-ppl] && ppl<length-ppl){
		ppl++;
	}
	if(ppl==(length+1)/2)
		return -1;
	return ppl;
}



int main(){

	int letters, length;
	scanf("%d %d", &letters, &length);
	// printf("letters: %d, length:%d\n", letters,length);
	// char id_c_string[length+1];

	char* id_c_string = (char*)malloc(length+1);
	scanf("%s",id_c_string);
	string id = id_c_string;
	free(id_c_string);
	// printf("id_c_string:%s\n",id_c_string);
	char character;
	int cost_to_add;
	int cost_to_delete;

	map<string, int> cost;
	
	for(int i=0; i<letters; i++){
		// printf("%d",i);
		scanf(" %c %d %d", &character, &cost_to_add, &cost_to_delete);
		// printf("letter\"%c\", add:\"%d\", delete:\"%d\"",character,cost_to_add,cost_to_delete);
		cost[string(1,character)]=(cost_to_add<cost_to_delete?cost_to_add:cost_to_delete);
	}

	// printf("cost[\"a\"]:%d\n",cost["a"]);
	// printf("cost[\"b\"]:%d\n",cost["b"]);
	// printf("cost[\"c\"]:%d\n",cost["c"]);
	// string id = "abcb";
	// cost["b"]=350;
	// cost["a"]=1000;
	// cost["c"]=200;
	// strategy is the bottom-up strategy. 
	// 
	// a  b  c  b
	// 0  0  0  0
	//-------------
	//  ab  bc  cb
	// |b|  |b| |b|
	//-------------
	//   abc  bcb
	//  |bc|   0
	//-------------
	//     abcb
	// |bcb| or |a|


	map<string, int> memos;

	length = id.length();

	// individual characters are palindromes and don't cost anything.
	for(int i=0; i<length; i++){
		memos[string(1,id[i])]=0;
	}
	for(int substr_length=2; substr_length<=id.length(); substr_length++){
		// printf("substring_length:%d\n",substr_length);
		// printf("length:%d\n",length);
		for(int start_pos=0; start_pos<=length-substr_length; start_pos++){
			// first we need to test if this substring is a palindrome
			// printf("start_pos:%d\n",start_pos);
			string substring = id.substr(start_pos, substr_length);
			// printf("%s\n",substring.c_str());
			int answer = is_palindrome(substring);
			// -1 means palindrome
			if(answer == -1){
				// printf("is palindrome\n");
				memos[substring]=0;
			}
			// this means the string is a partial palindrome.
			// this means there is an inner string which we have calculated the cost of
			else if(answer >0 ){
				string subsubstring = substring.substr(answer, substr_length-answer*2);
				memos[substring] = memos[subsubstring];
				// printf("subsubstring: %s\n",subsubstring.c_str());
			}
			else{
				// printf("substr_length-1:%d\n",substr_length-1);
				string left_character=substring.substr(0,1);
				string right_string = substring.substr(1,substr_length-1);

				string right_character=substring.substr(substr_length-1,1);
				string left_string = substring.substr(0,substr_length-1);

				int left_cost = cost[left_character]+memos[right_string];
				int right_cost = cost[right_character]+memos[left_string];
				memos[substring]=(left_cost<right_cost?left_cost:right_cost);
			}
		}
	}
	printf("%d", memos[id]);

}





