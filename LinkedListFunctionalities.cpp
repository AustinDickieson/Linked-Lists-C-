//Program to explore many functionalities of a linked list
#include <iostream>
using namespace std;

template <class T>
class Node{
  public:
    T val;
    Node* next;
    Node(T v, Node* n): val(v), next(n) {};
};

template <class T>
class LinkedList{
  private:
    Node<T>* head;
    Node<T>* tail;
  public:
    LinkedList() : head(nullptr), tail(nullptr) {};
    int Length(){
      int len = 0;
      for (Node<T>* p = head; p != nullptr; p = p -> next){
        len ++;}
      return len;
    };
    void InsertFront(T val){
      Node<T>* nn = new Node<T>(val, head);
      if (head == nullptr)
      {
        head = nn;
        tail = nn;
      }
      head = nn;
    };
    T GetHead(){
      return head -> val;
    };
    T GetTail(){
      return tail -> val;
    };
    Node<T>* ReturnHead(){
      return head;
    };
    Node<T>* ReturnTail(){
      return tail;
    };
    void InsertBack(T val){
        //solution not using tail
        Node<T>* nn = new Node<T> (val, nullptr);
        if (head == nullptr)
        {
          head = nn;
          tail = nn;
        }
        Node<T>* move = head;
        while (move -> next != nullptr)
        {
          move = move -> next;
        }
        move -> next = nn;
        tail = nn;
        //solution using tail
        /*Node<T>* nn = new Node<T>(val, nullptr);
        tail -> next = nn;
        tail = nn;*/
    };
    void InsertAt(int index, T v) //inserts new node with value v at index i
    {
      if (index == 0)
      {
        Node<T>* nn = new Node<T>(v, head);
        head = nn;
        return;
      }
      Node<T>* p = head;
      for (int count = 0; count < index-1; count++)
      {
        p = p-> next;
      }
      Node<T>* curr = p -> next;
      Node<T>* nn = new Node<T> (v, curr);
      p -> next = nn;
    };
    void DeleteAfter(int index)//deletes node after passed in index
    {
      Node<T>* p = head;
      for (int count = 0; count < index; count++)
      {
        p = p-> next;
      }
      Node<T>* curr = p-> next;
      Node<T>* after = curr -> next;
      delete curr;
      p -> next = after;
    };
    void DeleteAt(int index)//deletes node at passed in index
    {
      Node<T>* p = head;
      if (index == 0)
      {
        Node<T>* after = head -> next;
        delete head;
        head = after;
        return;
      }
      for (int count = 0; count < index-1; count++)
      {
        p = p-> next;
      }
      Node<T>* curr = p-> next;
      Node<T>* after = curr -> next;
      delete curr;
      p -> next = after;
    };
    void Delete(T n) //Deletes any node with value n
    {
      Node<T>* nptr = head;
      Node<T>* move = nptr -> next;
      if (nptr == nullptr) return;
      while (nptr -> next != nullptr)
      {
        if (nptr -> val == n)
        {
          Node<T>* curr = nptr;
          head = head-> next;
          delete curr;
          nptr = head;
        }
        if (move -> val == n)
        {
          Node<T>* curr = move;
          move = move -> next;
          delete curr;
          nptr -> next = move;
        }
        else
        {
          nptr = move;
          move = move -> next;
        }
      }
      tail = nptr;
    };
    void Clear()
    {
      Node<T>* curr = head;
      if (curr ==  nullptr) return;
      Node<T>* after = curr -> next;
      while(after != nullptr)
      {
        delete curr;
        curr = after;
        if (curr == nullptr) break;
        after = curr -> next;
      }
      head = nullptr;
      tail = head;
    };

    //Between every two nodes, inserts a value halfway between the two
    //1,5,7,11,7 becomes 1,3,5,6,7,9,11,9,7
    void RecursiveInterpolate()
    {
      head = InterpolateHelper(head);
    };
    static Node<T>* InterpolateHelper(Node<T>* list)
    {
      if ((list == nullptr) || (list-> next == nullptr)) return list;
      T newval = (list -> val + list->next->val)/2;
      list -> next = new Node<T> (newval, InterpolateHelper(list->next));
      return list;
    };

    void Interpolate()
    {
      Node<T>* nptr = head;
      if (nptr == nullptr) return;
      while (nptr -> next != nullptr)
      {
        Node<T>* next = nptr -> next;
        T newval = (nptr-> val + next-> val)/ 2;
        nptr -> next = new Node<T> (newval, next);
        nptr = next;
      }
    };

    void RemoveIndexRange(int FromIndex, int ToIndex) //removes nodes inbetween range
    {
      //memory leak solution
      /*
      Node<T>* beforeFrom = nullptr;
      Node<T>* afterTo = nullptr;
      int count = 0;
      for (Node<T>* nptr = head; nptr != nullptr; nptr = nptr-> next)
      {
        if (count + 1 == FromIndex) //stops before FromIndex
          beforeFrom = nptr;
        else if (count == FromIndex +1) //stops after ToIndex
          afterTo = nptr;
        //sets before and after node pointers correctly
        count++;
      }
      if (beforeFrom == nullptr)
        head = afterTo;
      else
        beforeFrom -> next = afterTo; // skips over desired range
      */

      //without leak, assuming correct range passed
      int index = 0;
      Node<T>* nptr = nullptr;
      for (nptr = head; index < FromIndex-1; nptr = nptr-> next)
      {
        index++;
      }
      while (index <= ToIndex-1)
      {
        Node<T>* curr = nptr -> next;
        Node<T>* after = curr -> next;
        delete curr;
        nptr -> next = after;
        index++;
      }
    };

    void Reverse()
    {
      tail = head;
      Node<T>* curr = head;
      if (curr == nullptr) return;
      Node<T>* after = curr-> next;
      curr -> next = nullptr; //create new Tail
      while (after != nullptr)
      {
        Node<T>* afterAfter = after -> next;
        after -> next= curr; //reverses after
        curr = after;
        after = afterAfter; //moves both curr and after forward one
      }
      head = curr; //sets new head
    };
    //tail not set correctly
    Node<T>* RecursiveReverse(Node<T>* list)
    {
      if (list == nullptr)
           return nullptr;
      if (list -> next == nullptr)
      {
           head = list;
           return list;
       }
       Node<T>* node1 = RecursiveReverse(list->next);
       node1 -> next = list;
       list -> next = nullptr;
       return list;
    };

    void Print()
    {
      if (head == nullptr)
      {
        cout << "List is empty" << endl;
        return;
      }
      for (Node<T>* p = head; p != nullptr; p= p->next)
      {
        cout << p -> val << " ";
      }
      cout << endl;
    };

    Node<T>* RecursivePrint(Node<T>* headOfList)
    {
      if (headOfList -> next == nullptr)
      {
        cout << headOfList -> val << endl;
        return headOfList;
      }
      else{
        cout << headOfList -> val << " ";
        RecursivePrint(headOfList -> next);
      }
    };

    //Not functioning
    void Sort(){
      if (head == nullptr) return;
      for (Node<T>* p = head; p != nullptr; p = p-> next)
      {
        for (Node<T>* j = head-> next; j != nullptr; j = j -> next)
        {
          T tempVal = p -> val;
          p -> val = j -> val;
          j -> val = tempVal;
        }
      }
    };
    void RecursiveSort();

    void Skip() //skips and deletes every other node
    {
      Node<T>* nptr = head;
      while ((nptr != nullptr) && (nptr -> next!= nullptr))
      {
        Node<T>* after = nptr -> next;
        nptr -> next = after -> next; //skips over "after" node
        delete after; //removes after
        nptr = nptr -> next; //iterates list
      }
    };

    void RecursiveSkip()
    {
      head = RecursiveSkipHelper(head);
    };

    Node<T>* RecursiveSkipHelper(Node<T>* list)
    {
      if ((list == nullptr) || (list -> next == nullptr))
      {
        return list;
      }
      else
      {
        cout << list -> val << endl;
        Node<T>* after = list -> next;
        list -> next = after -> next; //skips over "after" node
        delete after;
        RecursiveSkipHelper(list-> next);
        return list;
      }
    };

    //Takes two lists and makes the object list a interleaved version
    //Ex: if list2 is 1,3,5,7,9 and list2 is 2,4,6,8,10,
    //the called list will now be 1,2,3,4,5,6,7,8,9,10
    void Interleave(Node<T>* list1, Node<T>* list2)
    {
      Clear();
      head = list1;
      list1 = list1 -> next;
      int i = 1;
      for (Node<T>* p = head; p != nullptr; p = p-> next)
      {
        if (i > 0)
        {
          p -> next = list2;
          if(list2 != nullptr)
          {
            tail = list2;
            list2 = list2 -> next;
          }
        }
        else
        {
          p -> next = list1;
          if (list1 != nullptr)
          {
            tail = list1;
            list1 = list1 -> next;
          }
        }
        i = -i; //switches back and forth between lists
      }
    };

    T GetBiggest()
    {
      if (head == nullptr) return 0;
      Node<T>* biggest = head;
      for (Node<T>* p = head; p != nullptr; p = p-> next)
      {
        if (p -> val > biggest -> val)
          biggest = p;
      }
      return biggest -> val;
    };
};

int main()
{
  LinkedList <float> l1;
  l1.InsertFront(2);
  l1.InsertFront(1);
  l1.InsertBack(3);
  l1.InsertBack(4);
  l1.InsertBack(5);
  l1.InsertBack(6);
  l1.InsertBack(7);
  //l1.InsertAt(1, 7);
  cout << "Length is " << l1.Length() << endl;
  l1.Print();
  cout << "Head ->" << l1.GetHead() << " " << l1.GetTail() << "<- Tail" << endl;
  cout << "Deleting 5"<< endl;
  l1.Delete(5);
  l1.Print();
  cout << "Deleting index 0" << endl;
  l1.DeleteAt(0);
  l1.Print();
  cout << "Deleting index 2" << endl;
  l1.DeleteAfter(1);
  l1.Print();
  cout << "Biggest value is " << l1.GetBiggest() << endl;
  //l1.Clear();
  cout << "Reversing Linked List" << endl;
  l1.RecursiveReverse(l1.ReturnHead());
  //l1.Reverse();
  //l1.RecursivePrint(l1.ReturnHead());
  l1.Print();
  cout << "Head ->" << l1.GetHead() << " " << l1.GetTail() << "<- Tail" << endl;
  cout << "Inserting 10 at index 2" << endl;
  l1.InsertAt(2, 10);
  l1.Print();
  cout << "Interpolating!" << endl;
  l1.Interpolate();
  l1.Print();
  cout << "Skipping!" << endl;
  //l1.Skip();
  l1.RecursiveSkip();
  l1.Print();
  cout << "Recursively Interpolating!" << endl;
  l1.RecursiveInterpolate();
  l1.Print();
  cout << "Removing Index 3-6!" << endl;
  l1.RemoveIndexRange(3,6);
  l1.Print();

  cout << "New List #1" << endl;
  LinkedList <float> l2;
  l2.InsertFront(3);
  l2.InsertFront(1);
  l2.InsertBack(5);
  l2.InsertBack(7);
  l2.InsertBack(9);
  l2.Print();

  cout << "New List #2" << endl;
  LinkedList <float> l3;
  l3.InsertFront(4);
  l3.InsertFront(2);
  l3.InsertBack(6);
  l3.InsertBack(8);
  l3.InsertBack(10);
  l3.Print();

  cout<< "Interleaving new lists!" << endl;
  l1.Interleave(l2.ReturnHead(), l3.ReturnHead());
  l1.Print();

  return 0;
}
