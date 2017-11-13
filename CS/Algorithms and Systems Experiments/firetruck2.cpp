#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

char* answer;
int answer_length;
int allocated_space;


class Graph{
private:
	int graph_matrix[25][25];
	int node_degree_list[25];
	int stack[25];
	int stack_length;
	int visited[25];
public:
	Graph(){
		memset(graph_matrix,0,(25*25*sizeof(int))); 
		memset(node_degree_list,0,(25*sizeof(int))); 
		memset(visited, 0, (25*sizeof(int)));
		stack_length=0;
	}
	void add_edge(int node_1, int node_2){
		graph_matrix[node_1][node_degree_list[node_1]++]=node_2;
		graph_matrix[node_2][node_degree_list[node_2]++]=node_1;
	}
	int depth_first_search(int destination, int start=1){
		// printf("stack_length: %d\n",stack_length);
		if(start == destination){
			stack[stack_length]=start;

			// prints the path we used to get here.
			answer_length+=sprintf(&(answer[answer_length]),"%d",stack[0]);
			for(int i=1; i<=stack_length; i++)
				answer_length+=sprintf(&(answer[answer_length])," %d",stack[i]);
			answer_length+=sprintf(&(answer[answer_length]),"\n");
			if(answer_length>allocated_space/2){
				allocated_space*=2;
				answer = (char*)realloc(answer, allocated_space);
			}
			return 1;
		}

		int results = 0;
		visited[start]=1;
		stack[stack_length++]=start;
		
		for(int i=0; i<node_degree_list[start]; i++){
			if(visited[graph_matrix[start][i]]==0)
				results += depth_first_search(destination, graph_matrix[start][i]);
		}
		stack_length--;
		visited[start]=0;
		return results;
	}
};


int main(){
	allocated_space=4096;
	answer = (char*)malloc(allocated_space);

	int fire_location;
	int node_1;
	int node_2;
	Graph* current_graph;
	int case_number=1;

	int bytes_recieved;
	while(scanf("%d", &fire_location) != EOF){

		current_graph = new Graph();
		while(1){
			scanf("%d %d\n",&node_1, &node_2);

			if(node_1==0 && node_2==0){
				answer_length+=sprintf(&(answer[answer_length]),"CASE %d:\n",case_number);
				case_number++;
				int numpaths = current_graph->depth_first_search(fire_location);
				answer_length+=sprintf(&(answer[answer_length]),"There are %d routes from the firestation to streetcorner %d.\n",numpaths,fire_location);

				
				delete current_graph;
				break;
			}
			current_graph->add_edge(node_1,node_2);
		}
	}

	printf("%s",answer);

	return 0;
}





