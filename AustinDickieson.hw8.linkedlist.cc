#include <iostream>

using namespace std;

class Node {
public:
  Node* next;
  int data;
  Node(int d) : data(d), next(nullptr) {};
  Node(int d, Node* n) : data(d), next(n) {};
};

class LinkedList {

public:
  LinkedList() : head(nullptr) {};

  void InsertFront(int n) {
    head = new Node(n, head);
  };

  int Length() {
    int len = 0;
    for (Node* nptr = head; nptr != nullptr; nptr = nptr->next) {
      len++;
    }
    return len;
  };

  // (a) [2 points] Write Print() that prints all the numbers in the list.
  void Print() {
    for (Node* p= head; p != nullptr; p= p->next)
    {
      cout << p -> data << " ";
    }
  };

  // (b) [2 points] Write FindBiggest() which returns the biggest number in
  // the list. If list is empty, return 0.
  int FindBiggest() {
    if (head == nullptr) return 0;
    int biggest = head -> data;
    for (Node* p= head; p != nullptr; p= p->next)
    {
      if (p-> data > biggest)
      {
        biggest = p-> data;
      }
    }
    return biggest;
  };

  void InsertBack(int n) {
    if (head == nullptr) {
      head = new Node(n);
      return;
    }
    Node* nptr = head;
    while (nptr->next != nullptr) {
      nptr = nptr->next;
    }
    nptr->next = new Node(n);
  };

  void Reverse()
  {
    Node* curr = head;
    if (curr == nullptr) return;
    Node* next = curr-> next;
    curr-> next = nullptr;
    while (next != nullptr)
    {
      Node* tnext = next->next;
      next->next = curr;
      curr = next;
      next = tnext;
    }
	   head = curr;
  };

  void Clear() {
    Node* curr = head;
    if (curr == nullptr) return;
    Node* next = curr->next;
    while (true) {
      delete curr;
      curr = next;
      if (curr == nullptr) break;
      next = curr->next;
    }
    head = nullptr;
  };

  // (c) [10 points] Write Interleaeve function that takes two lists and sets
  // head to be the interleaved version of the two input lists.
  // Assume two input lists have exactly the same length.
  // Suppose list1 is a1 a2 a3 a4, and list2 is b1 b2 b3 b4.
  // Then head should be a1 b1 a2 b2 a3 b3 a4 b4.
  // Do not make new Nodes. Point head to a1, and change the next pointers of
  // all the nodes to make the interleaved list.
  // Make sure no memory leak.
  void Interleave(Node* list1, Node* list2) {
    //If both lists are empty
    if (list1 == nullptr && list2 == nullptr) return;
    //If both lists have only one node
    else if (list1-> next == nullptr && list2-> next == nullptr)
    {
      head = list1;
      list1->next = list2;
    }

    else {
      head = list1;
      Node* curr1 = list1; //point to first node in each list
      Node* curr2 = list2;
      Node* next1 = list1-> next; //point to second node in each list
      Node* next2 = list2-> next;

      while(curr2-> next != nullptr)
      {
        curr1-> next = curr2;
        curr1 = next1;
        curr2 = next2;

        //when the first list ends
        if(curr1-> next == nullptr)
        {
          curr1-> next = curr2;
          tail = curr2; //tail
          break;
        }
        //traverse both lists
        next1 = next1-> next;
        next2 = next2-> next;
      }
    }
  };

  // (d) [10 points] Write InsertSorted function which assumes that that list
  // is initially sorted from smallest to biggest. Insert an integer into the
  // list, maintaining the sorted order.
  void InsertSorted(int n)
  {
    if (head == nullptr) return;
    //If n is smaller than head it goes to front
    else if (n < head-> data) InsertFront(n);
    else
    {
      Node* curr = head;
      Node* next1 = head-> next;
      bool inserted = false;
      //if n is between head and next1
      if(n < next1-> data)
      {
        curr-> next = new Node(n, next1);
      }
      //Main case to handle larger linked list
      else
      {
        while(next1-> next != nullptr)
        {
          //Insertion
          if(n < next1-> data)
          {
            curr-> next = new Node(n,next1);
            inserted = true;
          }
          //interating through
          curr = curr-> next;
          next1 = next1-> next;
        }
        //If n is the largest element
        if(inserted == false)
        {
          InsertBack(n);
        }
      }
    }
  };

  void PrintTail() {
    if (tail != nullptr) {
      cout << "Tail is: " << tail->data << endl;
    }
  };

private:
  // Assume only positive numbers in the list. If empty list, head is nullptr.
  Node* head;
  // (e) [6 points] Add a tail member variable. It points to the last Node
  // in the list. If list empty, tail is nullptr. Rewrite InsertBack() to
  // make use of this new variable. Rewrite all other functions to make sure
  // that tail member variable always points to the last Node.
  Node* tail;
};


int main() {
  LinkedList L;
  L.InsertFront(7);
  L.InsertFront(21);
  L.InsertFront(11);
  L.InsertBack(5);
  L.Print();
  L.PrintTail();
  cout << "Biggest is: " << L.FindBiggest() << endl;

  L.Reverse();
  L.PrintTail();

  Node* list1 = nullptr;
  Node* list2 = nullptr;
  for (int i = 0; i < 8; i++) {
    list1 = new Node(i*2, list1);
    list2 = new Node(10 + i*3, list2);
  }
  cout << "Created lists" << endl;
  for (Node* p = list1; p != nullptr; p = p->next) {
    cout << p->data << " ";
  }
  cout << endl;
  for (Node* p = list2; p != nullptr; p = p->next) {
    cout << p->data << " ";
  }
  cout << endl;
  L.Interleave(list1, list2);
  cout << "Interleaved" << endl;
  L.Print();
  L.PrintTail();

  return 0;
}



/*

11 21 7 5
Tail is: 5
Biggest is: 21
Tail is: 11
Created lists
14 12 10 8 6 4 2 0
31 28 25 22 19 16 13 10
Interleaved
14 31 12 28 10 25 8 22 6 19 4 16 2 13 0 10
Tail is: 10

*/
