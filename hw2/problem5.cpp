#include <iostream>

using namespace std;

struct Node
{
	int value;
	Node *next;
};

void split (Node *& in, Node *& smaller, Node *& larger, int pivot)
{
	if(!in)
		return;
	Node * temp = NULL;
	Node * next = in->next;
	if(in->value > pivot){
		temp = in;
		temp->next = larger;
		larger = temp;
	}
	else
	{
		temp = in;
		temp->next = smaller;
		smaller = temp;
	}
	in = next;
	split(in, smaller, larger, pivot);
}

void print(Node *& in)
{
	if(!in){
		cout << "NULL" << endl;
		return;
	}
	Node * temp = in;
	while(temp) 
	{
		cout << temp->value << "\t";
		temp = temp->next;
	}
	cout << endl;
}

int main()
{
	Node * head = NULL;

	cout << "Please, insert 10 numbers" << endl;
	for(int i = 0; i < 10; i++){
		int temp = 0;
		cin >> temp;
		Node * newNode = new Node();
		newNode->next = head;
		newNode->value = temp;
		head = newNode;
	}
	cout << endl;
	print(head);


	cout << "Please, insert the pivot" << endl;
	int pivot;
	cin >> pivot;
	Node * larger = NULL;
	Node * smaller = NULL;
	split(head, smaller, larger, pivot);
	print(smaller);
	print(larger);
	print(head);

	return 0;
}