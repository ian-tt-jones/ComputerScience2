#include "Navigator.h"

// Name: Navigator (string) - Overloaded Constructor
// Desc: Creates a navigator object to manage routes
// Preconditions:  Provided with a filename of ports to load
// Postconditions: m_filename is populated with fileName
Navigator::Navigator(string fileName){
  m_fileName = fileName;
}


// Name: Navigator (destructor)
// Desc: Deallocates all dynamic aspects of a Navigator
// Preconditions: There is an existing Navigator
// Postconditions: All ports and routes are cleared
Navigator::~Navigator(){
  for(int i = 0; i < int(m_routes.size()); i++){
    delete m_routes[i];
  }
  for(int i = 0; int(m_ports.size()); i++){
    delete m_ports[i];
  }
}


// Name: Start
// Desc: Loads the file and calls the main menu
// Preconditions: m_fileName is populated
// Postconditions: All ports are loaded and the main menu runs
void Navigator::Start(){
  ReadFile();
  MainMenu();
}


// Name: DisplayPorts
// Desc: Displays each port in m_ports
// Preconditions: At least one port is in m_ports
// Postconditions: Displays all ports. Uses overloaded << provided in Port.h
void Navigator::DisplayPorts(){
  for(int i = 0; i < int(m_ports.size()); i++){
    cout << i + 1 << ". ";
    cout << *m_ports[i] << endl;
  }
}


// Name: ReadFile
// Desc: Reads in a file that has data about each port including name, location, degrees
//       north and degrees west. Dynamically allocates ports and stores them in m_ports
//       The vector can hold many ports.
// Preconditions: Valid file name of ports
// Postconditions: Dynamically allocates each port and enters it into m_ports
void Navigator::ReadFile(){
  ifstream data;
  string port;
  string name, location;
  double north, west;
  int comma1 = 0;
  int comma2 = 0;
  int counter = 0;
  data.open(m_fileName.c_str());
  cout << "file opened" << endl;
  // finds the characters between each comma and passes the data into a new port
  while(getline(data, port)){
    for(int j = 0; j < 4; j++){
      if(comma1 < int(port.length())){
        comma2 = port.find(",", comma1);
      }
      else{
        comma2 = port.length();
      }
      switch(j){
        case 0:
          name = port.substr(comma1, comma2-comma1);
        break;
        case 1:
          location = port.substr(comma1, comma2-comma1);
        break;
        case 2:
          north = stod(port.substr(comma1, comma2-comma1));
        break;
        case 3:
          west = stod(port.substr(comma1, comma2-comma1));
        break;
        default:
        break;
      }
      comma1 = comma2 + 1;
    }
    Port *p = new Port(name, location, north, west);
    m_ports.push_back(p);
  
  counter += 1;
  }
  data.close();
}


// Name: InsertNewRoute
// Desc: Dynamically allocates a new route with the user selecting each port in the route.
//       Route named based on the first and last port automatically
//       For example, Baltimore to Boston
//       Once route is created, inserted into m_routes.
// Preconditions: Populated m_routes
// Postconditions: Inserts a new route into m_routes
void Navigator::InsertNewRoute(){
  DisplayPorts();
  int choice = 0;
  // creates a new route
  Route *r = new Route();
  do{
    cout << "Enter the number of the port to add to your Route: (-1 to end)" << endl;
    cin >> choice;
    if(((choice < 1) || (choice > 36)) && (choice != -1)){
      cout << "Choice must be between 1 and 36 or -1." << endl;
      cin >> choice;
    }else if(choice != -1){
      Port *p = m_ports[choice - 1];
      // passes port selected into insert end in Route.cpp
      r -> InsertEnd(p -> GetName(), p -> GetLocation(), p -> GetNorth(), p -> GetWest());
    }
  }while(choice != -1);
  r -> UpdateName();
  m_routes.push_back(r);
}


// Name: MainMenu
// Desc: Displays the main menu and manages exiting
// Preconditions: Populated m_ports
// Postconditions: Exits when someone chooses 5
void Navigator::MainMenu(){
  int choice = 0;
  do{
  cout << "What would you like to do?:" << endl;
  cout << "1. Create New Route" << endl;
  cout << "2. Display Route" << endl;
  cout << "3. Remove Port From Route" << endl;
  cout << "4. Reverse Route" << endl;
  cout << "5. Exit" << endl;
  cin >> choice;
  while((choice < 1) or (choice > 5)){
    cout << "Choice must be 1-5." << endl;
    cin >> choice;
  }
  switch(choice){
    case 1:
      InsertNewRoute();
    break;
    case 2:
      DisplayRoute();
    break;
    case 3:
      RemovePortFromRoute();
    break;
    case 4:
      ReverseRoute();
    break;
    case 5:
      cout << "Bye." << endl;
    break;
    default:
    break;
      }

  }while(choice != 5);
}


// Name: ChooseRoute
// Desc: Allows user to choose a specific route to work with by displaying numbered list
// Preconditions: Populated m_routes
// Postconditions: Returns the index of the selected route minus 1
int Navigator::ChooseRoute(){
  int choice;
  do{
    cout << "Which route would you like to work with?" << endl;
    for(int i = 0; i < int(m_routes.size()); i++){
      cout << i + 1 << ". " << m_routes[i] -> GetName() << endl;
    }
    cin >> choice;
    if(!(choice <= int(m_routes.size()) && (choice >= 1))){
      cout << "Number must be in the list of routes.";
    }
  }while(!(choice <= int(m_routes.size())) && (choice >= 1));
  return choice - 1;
}


// Name: DisplayRoute
// Desc: Using ChooseRoute, displays a numbered list of all routes.
//       If no routes, indicates that there are no routes to display
//       User selects a route from list to display
//       Displays numbered list of each port in route
//       Displays total miles of a route using RouteDistance
// Preconditions: Routes has more than one port
// Postconditions: Displays all ports in a route and the total miles of the route
void Navigator::DisplayRoute(){
  if(m_routes.size() == 0){
    cout << "There are no routes." << endl; 
  }else{
    int route = ChooseRoute();
    m_routes[route] -> DisplayRoute();
    cout << "The total miles of this route is " << 
      RouteDistance(m_routes[route]) << " miles" << endl;
  }
}


// Name: RemovePortFromRoute()
// Desc: Using ChooseRoute, displays a numbered list of all routes.
//       User selects one of the routes to remove a port from.
//       Displays a numbered list of all ports in selected route.
//       User selects port to remove from list.
//       Removes port from route. If first or last port removed, updates name of route.
// Preconditions: Routes has more than one port
// Postconditions: Displays updated route with removed port and new name
void Navigator::RemovePortFromRoute(){
  int route = ChooseRoute();
  m_routes[route] -> DisplayRoute();
  int port;
  cout << "Which port would you like to remove?" << endl;
  cin >> port;
  while((port < 1) or (port > m_routes[route] -> GetSize())){
    cout << "That is not one of the ports. Try again.";
    cin >> port;
  }
  m_routes[route] -> RemovePort(port);
}


// Name: RouteDistance
// Desc: Calculates the total distance of a route
//       Goes from port 1 to port 2 then port 2 to port 3 and repeats for
//       length of route. Calculates the distance using CalcDistance (provided)
//       Aggregates the total and returns the total in miles
// Preconditions: Populated route with more than one port
// Postconditions: Returns the total miles between all ports in a route
double Navigator::RouteDistance(Route* route){
  double d = 0;
  Port* p = route -> GetData(1);
  for(int i = 0; i < route -> GetSize() - 1; i++){
    d += CalcDistance(p -> GetNorth(), p -> GetWest(), 
      p -> GetNext() -> GetNorth(), p -> GetNext() -> GetWest());
    p = p -> GetNext();
  }
  return d;
}


// Name: ReverseRoute
// Desc: Using ChooseRoute, users chooses route  and the route is reversed
//       If no routes in m_routes, indicates no routes available to reverse
//       Renames route based on new starting port and ending port
//       For example, Baltimore to Boston becomes Boston to Baltimore
// Preconditions: Populated m_routes
// Postconditions: Reverses a specific route by reversing the ports in place
//                 Must move ports, cannot just change data in ports.
void Navigator::ReverseRoute(){
  if(m_routes.size() == 0){
    cout << "There are no routes.";
  }else{
    int route = ChooseRoute();
    m_routes[route] -> ReverseRoute();
    m_routes[route] -> UpdateName();
    }
  }





