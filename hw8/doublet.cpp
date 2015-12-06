#include "minheap.h"
#include <unordered_set>
#include <fstream>
#include <exception>
#include <iostream>
#include "util.h"
#include <list>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct node{
	string word;
	list<node *> adjacencyList;
	int g;
	int h;
	int f;
	node * parent;
};

unordered_set<string> valid_words;
unordered_map<string, node *> graph;
string start;
string finish;

void calculate_adjacencies(node * n){
	for(int i = 0; i < (int)n->word.size(); i++){
		for(char c = 'a'; c < 'z'; c++){
			string new_str = n->word;
			new_str[i] = c;
			if(new_str == n->word)
				continue;
			if(graph.count(new_str) > 0){
				n->adjacencyList.push_front(graph[new_str]);
			}
		}
	}
}

void init_wordgraph(const char filename[]){
	ifstream input(filename);
	if(!input.is_open()){
		throw exception();
	}

	string line;
	getline(input, line);
	while(getline(input, line)){
		line = convToLower(line);
		valid_words.insert(line);
		//cout << line << endl;
	}

	//Initialize graph
	for(string word : valid_words){
		string s(start);
		if(word.size() == s.size()){
			node * n = new node();
			n->word = word;
			n->h = 0;
			n->g = 0;
			n->f = 0;
			graph.emplace(word, n);
			//calculate_adjacencies(word);
		}
	}
}

bool diffByOne(string a, string b){
	int d = 0;
	for(char c : a){
		for(char k : b){
			if(c != k)
				d++;
			if(d > 1)
				return false;
		}
	}
	return d == 1;
}

int compute_g(node * n){
	if(n == nullptr)
		return 0;

	return compute_g(n->parent) + 1;
}

int compute_h(node * n){
	if(n == nullptr){
		return 0;
	}

	int h = 0;
	for(int i = 0; i < (int)n->word.size(); i++){
		if(n->word[i] != finish[i]){
			h++;
		}
	}
	return h;
}

bool search(string start, string last){
	node * current = graph[start];

	unordered_set<node *> openSet;
	unordered_set<node *> closedSet;
	MinHeap minF(2);

	closedSet.insert(current);

	do{
		//Initialize
		calculate_adjacencies(current);

		//cout << current->word << endl;

		for(node * n : current->adjacencyList){
			if(closedSet.count(n) > 0){
				continue;
			} else if (openSet.count(n) > 0){
				//recompute g
				int new_g = compute_g(n);
				if(new_g < n->g){
					n->parent = current;
					n->g = new_g;
					n->f = n->g + n->h;
					minF.update(n->word, n->f);
				}
			} else {
				n->parent = current;
				n->g = compute_g(n);
				n->h = compute_h(n);
				n->f = n->g + n->h;
				openSet.insert(n);
				minF.add(n->word, n->f);
			}
		}

		if(openSet.size() == 0){
			break;
		}

		//Node with lowest f in open set
		string w = minF.peek();
		minF.remove();
		current = graph[w];

		closedSet.insert(current);
		openSet.erase(current);

	} while(current->word != graph[last]->word);

	if(current->word == graph[finish]->word){
		return true;
	}

	return false;
}

int main(int argc, char const *argv[])
{
	if(argc < 4){
	    cerr << "please insert the correct parameters" << endl;
	    return 1;
  	}

  	start = string(argv[1]);
  	finish = string(argv[2]);
  	init_wordgraph(argv[3]);

  	bool found = search(start, finish);
  	cout << found << endl;

  	if(found){
  		node * current = graph[finish];
	  	while(current->word != graph[start]->word){
	  		cout << current->word << endl;
	  		current = current->parent;
	  	}
	  	cout << current->word << endl;
  	}

	return 0;
}