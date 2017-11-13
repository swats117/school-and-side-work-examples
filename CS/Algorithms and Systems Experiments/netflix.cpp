#include <cstdio>
#include <iostream>
#include <map>

using namespace std;

string to_next(int source, int dest, int width){

	int dx = (dest%width) - (source%width);
	int dy = (dest/width) - (source/width);
	string output("");
	if(dx > 0){
		output += 'r' + to_string(dx);
	} else if(dx < 0){
		output += 'l' + to_string(-dx);
	}

	if(dy > 0){
		output += 'd' + to_string(dy);
	} else if(dy < 0){
		output += 'u' + to_string(-dy);
	}
	
	return output+'!';
}


string spell(string word, map<char, int> alpha_map, int width){
	int current = 0;
	string output("");
	for(int i=0; i<word.size(); i++){
		cout << word[i] << endl;
		int next = alpha_map[word[i]];
		output += to_next(current, next, width);
		current = next;
	}
	return output;
}

int main(){
	

	string alphabet = "abcdefghijklmnopqrstuvwxyz";

	int width = 5;

	map<char, int> alpha_map;

	for(int i=0; i<alphabet.size(); i++){
		alpha_map[alphabet[i]] = i;
	}

	string word = "dog";

	
	cout << spell(word,alpha_map,width) << '\n';

	return 0; 
}





