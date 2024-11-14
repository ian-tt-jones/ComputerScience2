#ifndef LQUEUE_CPP
#define LQUEUE_CPP
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//Templated node class used in templated linked list
template <class T>
class Node {
   public:
  Node( const T& data ); //Constructor
  T& GetData(); //Gets data from node
  void SetData( const T& data ); //Sets data in node
  Node<T>* GetNext(); //Gets next pointer
  void SetNext( Node<T>* next ); //Sets next pointer
private:
  T m_data;
  Node<T>* m_next;
};

//Overloaded constructor for Node
template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = NULL;
}

//Returns the data from a Node
template <class T>
T& Node<T>::GetData() {
   return m_data;
}

//Sets the data in a Node
template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

//Gets the pointer to the next Node
template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

//Sets the next Node
template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
class Lqueue {
 public:
  // Name: Lqueue() (Linked List Queue) - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
  // Required
  Lqueue();
  // Name: ~Lqueue() - Destructor
  // Desc: Used to destruct a Lqueue
  // Preconditions: There is an existing lqueue with at least one node
  // Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
  // Required
 ~Lqueue();
  // Name: Lqueue (Copy Constructor)
  // Preconditions: Creates a copy of existing LQueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  // Required
  Lqueue(const Lqueue&);
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: Copies an Lqueue into an existing Lqueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  // Required
  Lqueue<T>& operator= (Lqueue&);
  // Name: Push
  // Preconditions: Takes in data. Creates new node. 
  //                Requires a Lqueue
  // Postconditions: Adds a new node to the end of the lqueue.
  // Required
  void Push(const T&);
  // Name: Pop
  // Preconditions: Lqueue with at least one node. 
  // Postconditions: Removes first node in the lqueue, returns data from first node.
  // Required
  T Pop();
  // Name: Display
  // Preconditions: Outputs the lqueue.
  // Postconditions: Displays the data in each node of lqueue
  // Required (used only for testing)
  void Display();
  // Name: Front
  // Preconditions: Requires a populated lqueue
  // Postconditions: Returns whatever data is in front
  // Required
  T Front();
  // Name: IsEmpty
  // Preconditions: Requires a lqueue
  // Postconditions: Returns if the lqueue is empty.
  // Required
  bool IsEmpty();
  // Name: GetSize
  // Preconditions: Requires a lqueue
  // Postconditions: Returns m_size
  // Required
  int GetSize();
  // Name: Find()
  // Preconditions: Requires a lqueue
  // Postconditions: Iterates and if it finds the thing, returns index, else -1
  // Required
  int Find(T&);
  // Name: Swap(int)
  // Preconditions: Requires a lqueue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  // Required
  void Swap(int);
  // Name: Clear
  // Preconditions: Requires a lqueue
  // Postconditions: Removes all nodes in a lqueue
  // Required
  void Clear();
  // Name: At
  // Precondition: Existing Lqueue
  // Postcondition: Returns object from Lqueue at a specific location
  // Desc: Iterates to node x and returns data from Lqueue
  // Required
  T At (int x);
private:
  Node <T> *m_head; //Node pointer for the head
  Node <T> *m_tail; //Node pointer for the tail
  int m_size; //Number of nodes in queue
};

//**********Implement Lqueue Class Here***********
//**********All Functions Are Required Even If Not Used for Trivia**************

// Name: Lqueue() (Linked List Queue) - Default Constructor
// Desc: Used to build a new linked queue (as a linked list)
// Preconditions: None
// Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
// Required
template <class T>
Lqueue<T>::Lqueue(){
   m_head = nullptr;
   m_tail = nullptr;
   m_size = 0;
}


// Name: ~Lqueue() - Destructor
// Desc: Used to destruct a Lqueue
// Preconditions: There is an existing lqueue with at least one node
// Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
//                 to have no memory leaks!
// Required
template <class T>
Lqueue<T>::~Lqueue(){
   Node<T> *temp = m_head;
   Node<T> *temp2 = temp;
   while(temp != nullptr){
      temp2 = temp -> GetNext();
      delete temp;
      temp = temp2;
   }

   m_head = nullptr;
   m_tail = nullptr;
   m_size = 0;
}


// Name: Lqueue (Copy Constructor)
// Preconditions: Creates a copy of existing LQueue
//                Requires a Lqueue
// Postconditions: Copy of existing Lqueue
// Required
template <class T>
Lqueue<T>::Lqueue(const Lqueue& queue){
   if(queue.m_head == nullptr){
      m_head = nullptr;
      m_tail = nullptr;
      return;
   }

   // passes in data of first node to m_head
   Node<T> *temp = queue.m_head;
   // m_head -> SetData(temp -> GetData());
   // m_head -> SetNext(nullptr);
   m_head = new Node<T>(queue.m_head -> GetData());

   // current points to m_head and temp is moved down
   Node<T> *curr = m_head;
   temp = temp -> GetNext();

   while(temp != nullptr){
      // allocates for the next node
      Node<T> *N = new Node<T>(temp -> GetData());

      // sets this new node to next
      curr -> SetNext(N);

      // moves curr down
      curr = curr -> GetNext();

      // moves temp down
      temp = temp -> GetNext();
   }
   // delete temp;
   m_tail = curr;
   m_size = queue.m_size;
}


// Name: operator= (Overloaded Assignment Operator)
// Preconditions: Copies an Lqueue into an existing Lqueue
//                Requires a Lqueue
// Postconditions: Copy of existing Lqueue
// Required
template <class T>
Lqueue<T>& Lqueue<T>::operator= (Lqueue<T>& queue){
   Clear();
   Node<T> *copy = queue.m_head;
   Node<T> *curr = new Node<T>(copy -> GetData());
   Node<T> *temp;
   m_head = curr;
   copy = copy -> GetNext();
   while(copy != nullptr){
      temp = new Node<T>(copy -> GetData());
      curr -> SetNext(temp);
      copy = copy -> GetNext();
      curr = curr -> GetNext();
   }
   m_size = queue.m_size;
   m_tail = curr;
                
   return *this;
}


// Name: Push
// Preconditions: Takes in data. Creates new node. 
//                Requires a Lqueue
// Postconditions: Adds a new node to the end of the lqueue.
// Required
template <class T>
void Lqueue<T>::Push(const T& data){
   Node<T> *N = new Node<T>(data);
   if(m_size == 0){
      m_head = N;
      m_tail = N;
   }else{
      m_tail -> SetNext(N);
      m_tail = N;
   }
   m_size += 1;
}


// Name: Pop
// Preconditions: Lqueue with at least one node. 
// Postconditions: Removes first node in the lqueue, returns data from first node.
// Required
template <class T>
T Lqueue<T>::Pop(){
   Node<T> *temp = m_head;
   T data = m_head -> GetData();
   m_head = m_head -> GetNext();
   delete temp;
   m_size--;
   return data;
}


// Name: Display
// Preconditions: Outputs the lqueue.
// Postconditions: Displays the data in each node of lqueue
// Required (used only for testing)
template <class T>
void Lqueue<T>::Display(){
   Node<T> *temp = m_head;
   int count = 1;
   while(temp != nullptr){
      cout << count << ". " << temp -> GetData() << endl;
      temp = temp -> GetNext();
   }
}


// Name: Front
// Preconditions: Requires a populated lqueue
// Postconditions: Returns whatever data is in front
// Required
template <class T>
T Lqueue<T>::Front(){
   return m_head -> GetData();
}


// Name: IsEmpty
// Preconditions: Requires a lqueue
// Postconditions: Returns if the lqueue is empty.
// Required
template <class T>
bool Lqueue<T>::IsEmpty(){
   if(m_head == nullptr){
      return true;
   }
   return false;
}


// Name: GetSize
// Preconditions: Requires a lqueue
// Postconditions: Returns m_size
// Required
template <class T>
int Lqueue<T>::GetSize(){
   return m_size;
}


// Name: Find()
// Preconditions: Requires a lqueue
// Postconditions: Iterates and if it finds the thing, returns index, else -1
// Required
template <class T>
int Lqueue<T>::Find(T& data){
   Node<T> *temp = m_head;
   int c = 0;
   while(temp != nullptr){
      if(temp -> GetData() == data){
         return c;
      }
      c++;
      temp = temp -> GetNext();
   }
   return -1;
}


// Name: Swap(int)
// Preconditions: Requires a lqueue
// Postconditions: Swaps the nodes at the index with the node prior to it.
// Required
template <class T>
void Lqueue<T>::Swap(int node){
   Node<T> temp = m_head;
   Node<T> temp2;
   Node<T> N;
   for(int i = 0; i < node; i++){
      if(i == node - 1){
         N = temp;
      }
      temp = temp -> GetNext();
   }
   temp2 = temp;
   temp = N;
   N = temp2;
}


// Name: Clear
// Preconditions: Requires a lqueue
// Postconditions: Removes all nodes in a lqueue
// Required
template <class T>
void Lqueue<T>::Clear(){
   Node<T> *temp = m_head;
   Node<T> *temp2 = temp;
   while(temp != nullptr){
      temp2 = temp -> GetNext();
      delete temp;
      temp = temp2;
   }
   delete temp2;
   delete temp;
   m_head = nullptr;
   m_tail = nullptr;
   m_size = 0;
}


// Name: At
// Precondition: Existing Lqueue
// Postcondition: Returns object from Lqueue at a specific location
// Desc: Iterates to node x and returns data from Lqueue
// Required
template <class T>
T Lqueue<T>::At (int x){
   Node<T> *N = m_head;
   for(int i = 0; i < x; i++){
      N = N -> GetNext();
   }
   return N -> GetData();
}



#endif
