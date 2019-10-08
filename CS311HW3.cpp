/*
Shane Ghuste
004617897
ghust001@cougars.csusm.edu
*/

#include <iostream>
#include<cstdlib>
#include<cstdio>
#include<time.h>
using namespace std;


struct EventNode
{	
	int occurTime;
	int type;
	EventNode* next;
};

class EventList
{
public:

	EventNode* head;

	EventList()
	{
		head = NULL;
	}	
	
	void append(int occurT, int eventT)
	{
		cout << "appending EventNode" << endl;
		EventNode* newNode;
		EventNode* nodePtr;
		newNode = new EventNode;//create a node
		//set attributes
		newNode->occurTime = occurT;
		newNode->type = eventT;
		//new node will now be end of LL
		newNode->next = NULL;

		//if list is empty insert node
		if (head == NULL)
			head = newNode;

		else //traverse list to get to end
		{
			nodePtr = head;

			//while you are not at the end of list
			while (nodePtr->next != NULL)
			{
				nodePtr = nodePtr->next;
			}

			nodePtr->next = newNode;
		}
	}

	void insert(int occurT, int eventT)
	{
		EventNode* newNode;
		EventNode* nodePtr = head;
		EventNode* prevNode = head;

		newNode = new EventNode; //create node
		//set attributes
		newNode->occurTime = occurT;
		newNode->type = eventT;

		if (!head)//if list empty insert at beg
		{
			head = newNode;
			newNode->next = NULL;
		}

		else // traverse the list and find place
		{
			
			//while loop to get to node before node thatis after pName
			while (nodePtr != NULL && nodePtr->occurTime < occurT)
			{
				prevNode = nodePtr;
				nodePtr = nodePtr->next;
			}

			if (prevNode == NULL)//the first node
			{
				head = newNode;
				newNode->next = nodePtr;
			}
			else//insrt before current node
			{
				prevNode->next = newNode;
				newNode->next = nodePtr;
			}
		}
	}

	void removeFrontEvent(int &occurT, int &eventT)
	{
		EventNode* nodePtr;
		nodePtr = head;

		if (head == NULL)
			cout << "Nothing to remove, List Empty\n";
		else
		{
			occurT = nodePtr->occurTime;
			eventT = nodePtr->type;
			cout << "Removing front Event from List" << endl;
			head = head->next;
			delete nodePtr;
		}
	}

	bool isEmpty()
	{
		if (head == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void print()
	{
		cout << "Printing Event List\n";
		EventNode* nodePtr = head;//start of list
		int pos = 1;

		if (head == NULL)
		{
			cout << "List is Empty" << endl;
		}
		else
		{
			while (nodePtr)//while not at end of list
			{
				//output
				cout << pos << ". Occur Time:" << nodePtr->occurTime << " Event Type: "
					<< nodePtr->type << endl;
				nodePtr = nodePtr->next;//go to next node
				pos++;//increase pos for node count
			}
		}
	}

};

struct CustomerNode
{
	int arrivalTime;
	int serviceTime;
	CustomerNode* next;
};

class TellerQueue
{
public:
	CustomerNode* front;
	CustomerNode* rear;
	int count;

	TellerQueue()
	{
		front = NULL;
		rear = NULL;
		count = 0;
	}

	

	void enqueue(int aT, int sT)
	{
		cout << "Enqueueing\n";
		CustomerNode* newNode;
		newNode = new CustomerNode;
		newNode->arrivalTime = aT;
		newNode->serviceTime = sT;
		newNode->next = NULL;

		if (isEmpty())
		{
			front = newNode;
			rear = newNode;
		}
		else
		{
			rear->next = newNode;
			rear = newNode;
		}
		count++;
	}

	void dequeue(int &aT, int &sT)
	{
		cout << "Dequeueing from Queue\n";
		CustomerNode* nodePtr = front;

		if (isEmpty())
			cout << "[Queue EMPTY]" << endl;

		else
		{
			aT = nodePtr->arrivalTime;
			sT = nodePtr->serviceTime;
			front = front->next;
			delete nodePtr;

			count--;
		}
	}

	bool isEmpty()
	{
		if (count == 0)
			return true;
		else
			return false;
	}

	void displayAll()
	{
		cout << "Printing Queue\n";
		CustomerNode* nodePtr = front;

		if (isEmpty()) //no nodes in queue
			cout << "[Queue EMPTY]\n";
		else
		{
			while (nodePtr) //while pointing at a node
			{
				cout << "arrival: " << nodePtr->arrivalTime << " service: "
					<< nodePtr->serviceTime << endl;
				nodePtr = nodePtr->next;
			}
		}
	}
};

int getSmallestQueue(int q1, int q2, int q3, int q4)
{
	int smallest = q1;
	if (q2 < smallest)
		smallest = q2;
	if (q3 < smallest)
		smallest = q3;
	if (q4 < smallest)
		smallest = q4;

	if (smallest == q1)
		return 1;
	else if (smallest == q2)
		return 2;
	else if (smallest == q3)
		return 3;
	else
		return 4;
}

int main()
{
	srand(time(0));
	TellerQueue w1, w2, w3, w4;
	EventList ev;
	int arrNextCust = 0;
	int serveTimeCurrCust = 0;
	int numCustomers = 0;
	int currentTime = 0;
	int waitTime = 0;

	ev.append(0, 0);

	while (!ev.isEmpty())
	{
		int tempOccurT;
		int tempType;

		ev.removeFrontEvent(tempOccurT, tempType);

		if (tempType == 0)
		{
			numCustomers += 1;
			serveTimeCurrCust = rand() % 1200 + 1;
			arrNextCust = currentTime + (rand() % 300 + 1);
			currentTime = arrNextCust;
			if (arrNextCust <= 28800)
			{
				ev.insert(arrNextCust, 0);
			}
			int smallestQ = getSmallestQueue(w1.count, w2.count, w3.count, w4.count);
			//cout << "Smallest Q is: " << smallestQ << endl;
			if (smallestQ == 1)
			{
				w1.enqueue(tempOccurT, serveTimeCurrCust);
				if (w1.count == 0)
				{
					ev.insert(arrNextCust, 1);
				}
			}
			else if (smallestQ == 2)
			{
				w2.enqueue(tempOccurT, serveTimeCurrCust);
				if (w2.count == 0)
				{
					ev.insert(arrNextCust, 2);
				}
			}
			else if (smallestQ == 3)
			{
				w3.enqueue(tempOccurT, serveTimeCurrCust);
				if (w3.count == 0)
				{
					ev.insert(arrNextCust, 3);
				}
			}
			else
			{
				w4.enqueue(tempOccurT, serveTimeCurrCust);
				if (w4.count == 0)
				{
					ev.insert(arrNextCust, 4);
				}
			}

		}
		else
		{

		}
	}
	return 0;
}