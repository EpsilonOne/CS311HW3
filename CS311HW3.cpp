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
		EventNode* nodePtr;
		EventNode* prevNode;

		newNode = new EventNode; //create node
		//set attributes
		newNode->occurTime = occurT;
		newNode->type = eventT;

		if (isEmpty())//if list empty insert at beg
		{
			head = newNode;
			newNode->next = NULL;
		}

		else // traverse the list and find place
		{
			nodePtr = head;
			prevNode = head;
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

//function compares counts of queues and returns smallest
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
	srand(time(0)); //seed for rand()
	TellerQueue w1, w2, w3, w4;//4 queues
	EventList ev; //Event list
	int arrNextCust = 0;//arrival of next cust
	int serveTimeCurrCust = 0;//service time
	int numCustomers = 0;
	int currentTime = 0;
	int waitTime = 0;
	int deqArrTime;
	int deqServTime;

	cout << "Initializing EventList\n";
	ev.append(0, 0); //Initialize event list
	ev.print();

	while (!ev.isEmpty()) //While ev is not empty
	{
		int tempOccurT;//to hold current event occur time 
		int tempType;//to hold current event type

		
		ev.removeFrontEvent(tempOccurT, tempType);//remove event from front of event list
		currentTime = tempOccurT;

		if (tempType == 0)//if event is arrival
		{
			numCustomers += 1;//increase customer count by 1
			serveTimeCurrCust = rand() % 1200 + 1;//random service time of current cust <= 20 min
			arrNextCust = currentTime + (rand() % 300 + 1); //randon interval time of next cust arrival <= 5 min
			//currentTime = arrNextCust;//update current time to arrival of next customer
			if (arrNextCust <= 28800)//if next cust arrives while bank open create arrival event for new cust
			{
				cout << " Inserting Arrival to EventList\n";
				ev.insert(arrNextCust, 0);
				ev.print();
			}

			//call function to get smallest queue 
			int smallestQ = getSmallestQueue(w1.count, w2.count, w3.count, w4.count);

			//if stmnts to insert current cust into smallest line
			//if that line is empty create departure event for that cust and put in event list
			if (smallestQ == 1)
			{
				cout << "Enqueueing to W1\n";
				w1.enqueue(tempOccurT, serveTimeCurrCust);
				if (w1.count == 1)
				{
					cout << "w1 avail, Inserting departure w1 to EventList\n";
					ev.insert(arrNextCust, 1);
				}
			}
			else if (smallestQ == 2)
			{
				cout << "Enqueueing to W2\n";
				w2.enqueue(tempOccurT, serveTimeCurrCust);
				if (w2.count == 1)
				{
					cout << "w2 available, Inserting departure w2 to EventList\n";
					ev.insert(arrNextCust, 2);
				}
			}
			else if (smallestQ == 3)
			{
				cout << "Enqueueing to W3\n";
				w3.enqueue(tempOccurT, serveTimeCurrCust);
				if (w3.count == 1)
				{
					cout << "w3 avail, Inserting departure w3 to EventList\n";
					ev.insert(arrNextCust, 3);
				}
			}
			else
			{
				cout << "Enqueueing to W4\n";
				w4.enqueue(tempOccurT, serveTimeCurrCust);
				if (w4.count == 1)
				{
					cout << "w4 avail, Inserting departure w4 to EventList\n";
					ev.insert(arrNextCust, 4);
				}
			}

		}
		else if (tempType == 1)//departure from first queue
		{
			cout << "dequeueing from w1\n";
			w1.dequeue(deqArrTime, deqServTime);//dequeue from w1
			waitTime += currentTime + deqServTime - deqArrTime;
			if (!w1.isEmpty())
			{
				cout << "W1 !empty Inserting departure of next cust to EventList\n";
				ev.insert(currentTime + w1.front->serviceTime, 1);
			}
		}
		else if (tempType == 2)//departure from first queue
		{
			cout << "dequeueing from w2\n";
			w2.dequeue(deqArrTime, deqServTime);//dequeue from w1
			waitTime += currentTime + deqServTime - deqArrTime;
			if (!w2.isEmpty())
			{
				cout << "W2 !empty Inserting departure of next cust to EventList\n";
				ev.insert(currentTime + w2.front->serviceTime, 2);
			}
		}
		else if (tempType == 3)//departure from first queue
		{
			cout << "dequeueing from w3\n";
			w3.dequeue(deqArrTime, deqServTime);//dequeue from w1
			waitTime += currentTime + deqServTime - deqArrTime;
			if (!w3.isEmpty())
			{
				cout << "W3 !empty Inserting departure of next cust to EventList\n";
				ev.insert(currentTime + w3.front->serviceTime, 3);
			}
		}
		else if (tempType == 4)//departure from first queue
		{
			cout << "dequeueing from w4\n";
			w4.dequeue(deqArrTime, deqServTime);//dequeue from w1
			waitTime += currentTime + deqServTime - deqArrTime;
			if (!w4.isEmpty())
			{
				cout << "W4 !empty Inserting departure of next cust to EventList\n";
				ev.insert(currentTime + w4.front->serviceTime, 4);
			}
		}

	}
	
	cout << "# of cust serverd = " << numCustomers
		<< "\nTotal wait time = " << waitTime
		<< "\nAverage wait time = " << waitTime / numCustomers << endl;
	return 0;
}