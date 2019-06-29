#include <iostream>
using namespace std;

class Node {
public:
  float val;
  Node* next;
  Node* prev;
  Node(float v, Node* p, Node* n) :
    val(v), prev(p), next(n) {};
};

class LinkedList {
private:
  Node* head;
  Node* tail;
public:
  LinkedList() : head(nullptr), tail(nullptr) {};

  // (a) [5 points] Insert node with value v in the front of the list.
  // Make sure after the function call, head, tail, all prev, next and vals
  // of all nodes are correctly seat.
  void InsertFront(float v)
  {
    if (head == nullptr)
    {
      head = new Node(v, nullptr, nullptr);
      tail = head;
    }
    else
    {
      Node* nn = new Node(v, nullptr, head);
      head = nn;
    }
  };

  // (b) [5 points] Insert node with value v at the back of the list.
  // Make sure after the function call, head, tail, all prev, next and vals
  // of all nodes are correctly seat.
  void InsertBack(float v)
  {
    if (head == nullptr)
    {
      head = new Node(v, nullptr, nullptr);
      tail = head;
    }
    else
    {
      Node* nn = new Node(v, tail, nullptr);
      tail -> next = nn;
      tail = nn;
    }
  };

  // (c) [10 points] Remove all nodes whose value is val.
  // Make sure after the function call, head, tail, all prev, next and vals
  // of all nodes are correctly seat.
  // Make sure no memory leak.
  void Remove(float val)
  {
    if (head == nullptr) return;
    /*
    //For loop solution//
    for (Node* mover = head; mover != nullptr; mover = p-> next)
    {
      if (mover ->val == val)
      {
        if(mover == head)
        {
          //removes and sets new head
          Node* temp = head-> next;
          temp -> prev = nullptr;
          delete head;
          head = temp;
        }
        else if(mover == tail)
        {
          //removes and sets new tail
          Node* temp = tail-> prev;
          temp-> next = nullptr;
          delete tail;
          tail = temp;
        }
        else
        {
          mover-> prev-> next = mover->next; //skips deleted node
          mover-> next -> prev = mover-> prev; //connects prev and next fully
          delete mover;
        }
      }
    }
    */
    //While loop solution
    Node* mover = head;
    while (mover != nullptr)
    {
      if (mover -> val == val)
      {
        if(mover == head)
        {
          //removes head node and sets new head
          Node* temp = head-> next;
          temp -> prev = nullptr;
          delete head;
          head = temp;
        }
        else if(mover == tail)
        {
          //removes tail node and sets new tail
          Node* temp = tail-> prev;
          temp-> next = nullptr;
          delete tail;
          tail = temp;
        }
        else
        {
          mover-> prev-> next = mover->next; //skips deleted node
          mover-> next -> prev = mover-> prev; //connects prev and next fully
          delete mover;
        }
      }
      mover = mover -> next;
    }
  };

  // (d) [10 points] Reverse the list.
  // Make sure after the function call, head, tail, all prev, next and vals
  // of all nodes are correctly seat.
  void Reverse() {
/*
//Simpler solution,doesnt fully work
  if (head == nullptr)
      return;

	Node* current = head;
	while(current != nullptr)
	{
		// swap values of next and prev
		Node* next1 = current->next;
		current -> next = current -> prev;
		current -> prev = next1;

    //traverse list
		current = current -> prev;
	}
	// swap values of head and tail pointers
	current = head;
	head = tail;
	tail = current;
  }
*/
    if (head == nullptr)
      return;

    Node* temp = tail;
    Node* current = head;

    Node* mover = current -> next; //to move though LinkedList

    current -> next = nullptr; //establish as new tail
    tail = current;

    temp -> prev = nullptr; //establish as new head
    head = temp;

    while (mover != nullptr)
    {
      Node* next1 = mover-> next;
      mover -> next = current;
      current = mover;
      mover = next1;
    }
  };

  void Print() {
    for (Node* nptr = head; nptr != nullptr; nptr = nptr->next) {
      cout << nptr->val << " ";
    }
    cout << endl;
  };
};

int main() {
  LinkedList LL;
  LL.InsertFront(1.2);
  LL.InsertFront(0.5);
  LL.InsertBack(40.1);
  LL.InsertBack(5.8);
  LL.Print();
  LL.Reverse();
  LL.Print();
  LL.Reverse();
  LL.Print();
  LL.Remove(0.5);
  LL.Print();
  LL.InsertFront(113.45);
  LL.Print();
  LL.Remove(40.1);
  LL.Print();
  LL.Remove(5.8);
  LL.Print();
  return 0;
}

/*
0.5 1.2 40.1 5.8
5.8 40.1 1.2 0.5
0.5 1.2 40.1 5.8
1.2 40.1 5.8
113.45 1.2 40.1 5.8
113.45 1.2 5.8
113.45 1.2
*/
