#include "Route.h"

// Name: Route() - Default Constructor
// Desc: Used to build a new Route (linked list) make up of ports
// Preconditions: None
// Postconditions: Creates a new Route where m_head and m_tail point to nullptr and size = 0
Route::Route(){
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}


// Name: SetName(string)
// Desc: Sets the name of the route (usually first port to last port)
// Preconditions: None
// Postconditions: Sets name of route
void  Route::SetName(string name){
  m_name = name;
}


// Name: ~Route() - Destructor
// Desc: Used to destruct a strand of Route
// Preconditions: There is an existing Route strand with at least one port
// Postconditions: Route is deallocated (including all dynamically allocated ports)
//                 to have no memory leaks!
Route::~Route(){
  if(m_size == 1){
    delete m_head;
  }else{
    Port *cur = m_head;
    Port *next = nullptr;
     while(cur != nullptr){
      next = cur -> GetNext();
      delete cur;
      cur = next;
     }
  }
  m_head = nullptr;
  m_tail = nullptr;
}


// Name: InsertEnd (string, string, double double)
// Desc: Creates a new port using the data passed to it.
//       Inserts the new port at the end of the route
// Preconditions: Takes in a Port
//                Requires a Route
// Postconditions: Adds the new port to the end of a route
void Route::InsertEnd(string name, string location, double north, double west){
  Port *p = new Port(name, location, north, west);
  if(m_head == nullptr){
    m_head = p;
  }
  else{
    // new port becomes tail
    Port *temp = m_head;
    while(temp -> GetNext() != nullptr){
      temp = temp -> GetNext();
    }
    temp -> SetNext(p);
    m_tail = p;
  }
  // increment size
  m_size++;
}


// Name: RemovePort(int index)
// Desc: Removes a port from the route at the index provided
//       Hint: Special cases (first port, last port, middle port)
// Preconditions: Index must be less than the size of the route
//       Cannot make route less than two ports. If the route has
//       two or fewer ports, fails.
// Postconditions: Name may be updated. Size is reduced. Route has one less port.
void Route::RemovePort(int port){
  if(m_size == 0){
    //we can't remove anymore ports if this is case
    cout << "There are no ports." << endl;
  }
  // removes head if its the first port
  else if(port == 1){
    Port *temp = m_head -> GetNext();
    delete m_head;
    m_head = temp;
    m_size --;
  }
  else if (m_size == 1){
    //no need to iterate since there is only one node
    delete m_head;
    m_head = nullptr;
    m_tail = nullptr;
    m_size --;
    
  }else{
    if(port > m_size){
      cout << "There are not that many ports in the route.";
    }else{
      Port *temp = m_head;
      for(int i = 1; i < port - 1; i++){
        temp = temp -> GetNext();
      }
      Port *temp2 = temp -> GetNext();
      temp -> SetNext(temp2 -> GetNext());
      delete temp2;
      m_size --;
    }
  }
  Port *t = m_head;
  while(t -> GetNext() != nullptr){
    t = t -> GetNext();
  }
  m_tail = t;
  UpdateName();
}

// Name: GetName()
// Desc: Returns the name of the route (Usually starting port to last port)
//       For example: Baltimore to Brunswick
// Preconditions: Requires a Route
// Postconditions: Returns m_name;
string Route::GetName(){
  return m_name;
}


// Name: UpdateName()
// Desc: Updates m_name based on the name of the first port in the route
//       and the last port in the route
//       For example: Baltimore to Brunswick
// Preconditions: Requires a Route with at least two ports
// Postconditions: Returns m_name;
string Route::UpdateName(){
  if(m_size > 1){
    m_name = m_head -> GetName() + " to " + m_tail -> GetName();
  }
  return m_name;
}


// Name: GetSize()
// Desc: Returns the number of ports in a route
// Preconditions: Requires a Route
// Postconditions: Returns m_size;
int Route::GetSize(){
  return m_size;
}


// Name: ReverseRoute
// Desc: Reverses a route
// Preconditions: Reverses the Route
// Postconditions: Route is reversed in place; nothing returned
void Route::ReverseRoute(){
  Port *cur = m_head;
  Port *prev = nullptr;
  Port *next = nullptr;
  while(cur != nullptr){
    // goes through and rearranges the ports
    next = cur -> GetNext();
    cur -> SetNext(prev);
    prev = cur;
    cur = next;
  }
  // lastly makes the last port m_head
  // and the last port m_tail.
  m_head = prev;
  Port *t = m_head;
  while(t -> GetNext() != nullptr){
    t = t -> GetNext();
  }
  m_tail = t;
}


// Name: GetData (int)
// Desc: Returns a port at a specific index
// Preconditions: Requires a Route
// Postconditions: Returns the port from specific item
Port* Route::GetData(int index){
  if(index == 1){
    return m_head;
  }
  else{
    Port *temp = m_head;
    for(int i = 0; i < index - 1; i++){
      temp = temp -> GetNext();
    }
    return temp;
  }
}


// Name: DisplayRoute
// Desc: Displays all of the ports in a route
// Preconditions: Requires a Route
// Postconditions: Displays all of the ports in a route
// Formatted: Baltimore, Maryland (N39.209 W76.517)
void Route::DisplayRoute(){
  Port *temp = m_head;
  for(int i = 0; i < m_size; i++){
    cout << i + 1 << ". " << temp -> GetName() << ", ";
    cout << temp -> GetLocation() << " (N" << temp -> GetNorth();
    cout << " W" << temp -> GetWest() << ")" << endl;
    temp = temp -> GetNext();
  }
}

