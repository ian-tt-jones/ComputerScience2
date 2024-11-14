#include "Lab.h"

// Name: Lab() Default Constructor
// Desc - Instantiates an object of type Lab
// Preconditions - None
// Postconditions - None
//Default Constructor
Lab::Lab(){}


// Name: LoadSubstances
// Desc - Loads each substance into m_substances from file
//        The loads all substances from m_substances into m_myChemist's substance array
// Preconditions - Requires file with valid substance data
// Postconditions - m_substance is populated with substance structs
void Lab::LoadSubstances(){
  string substance_str, name, type, formula, sub1, sub2;
  int comma1 = 0, comma2 = 0;

  fstream data;
  string item = "";
  string index = "";
  data.open(PROJ2_DATA);

  // loops through each line and breaks the line up by each comma
  // and gets the item between each comma and saves it as a string using 
  // substr() and find().
  for(int i = 0; i < PROJ2_SIZE; i++){
    getline(data, substance_str);
    for(int j = 0; j < 5; j++){
      if(comma1 < int(substance_str.length())){
        comma2 = substance_str.find(",", comma1);
      }
      else{
        comma2 = substance_str.length();
      }
      switch(j){
        case 0:
          name = substance_str.substr(comma1, comma2-comma1);
        break;
        case 1:
          type = substance_str.substr(comma1, comma2-comma1);
        break;
        case 2:
          formula = substance_str.substr(comma1, comma2-comma1);
        break;
        case 3:
          sub1 = substance_str.substr(comma1, comma2-comma1);
        break;
        case 4:
          sub2 = substance_str.substr(comma1, comma2-comma1);
        default:
          cout << "";
        break;
      }
      comma1 = comma2 + 1;
    }
    // Assigns values for each Substance struct in the list
    m_substances[i].m_name = name;
    m_substances[i].m_type = type;
    m_substances[i].m_formula = formula;
    m_substances[i].m_substance1 = sub1;
    m_substances[i].m_substance2 = sub2;
    m_substances[i].m_quantity = 0;
    comma1 = 0;
    comma2 = 0;
  }
  cout << endl << PROJ2_SIZE << " substances loaded." << endl;
}


// Name: StartLab()
// 1. Displays Lab Title (as implemented below)
// 2. Loads all substances and their recipes into m_substances (Load Substances)
// 3. Asks user for their chemist's name (store in m_myChemist as m_myName)
// 4. Copies all substances from m_substances into the chemist's substance array
// 5. Manages the game itself including win conditions continually calling the main menu 
// Preconditions - None
// Postconditions - m_substances and m_myChemist's substances populated
void Lab::StartLab(){
  // initial function calls
  LabTitle();
  LoadSubstances();
  string name;
  cout << "What is your chemists name? ";
  cin >> name;
  m_myChemist.SetName(name);
  int choice = 0;

  // copying substances into chemist's array
  for(int i = 0; i < PROJ2_SIZE; i++){
    m_myChemist.AddSubstance(m_substances[i]);
  }

  // main game loop
  while(choice != 5){
    choice = MainMenu();
    if(choice == 1){
      DisplaySubstances();
    }
    if(choice == 2){
      SearchSubstances();
    }
    if(choice == 3){
      CombineSubstances();
    }
    if(choice == 4){
      CalcScore();
    }
  }
}


// Name: DisplayMySubstances()
// Desc - Iterates over m_myChemist's substances
// Preconditions - Player's chemist has substances
// Postconditions - Displays a numbered list of substances
void Lab::DisplaySubstances(){
  // displays the current stock of substances
  cout << "My chemist has " << m_myChemist.GetTotalSubstances() 
    << " different substances in inventory currently" << endl;
  for(int i = 0; i < PROJ2_SIZE; i++){
    Substance sub = m_myChemist.GetSubstance(i);
    cout << i + 1 << ". " << sub.m_name;
    cout << " (" << sub.m_formula << ") ";
    cout << sub.m_quantity << endl;
  }
}


// Name: MainMenu()
// Desc - Displays and manages menu
// Preconditions - Player has an Chemist
// Postconditions - Returns number including exit
int Lab::MainMenu(){
  // gets decision from the user
  int decision = 0;
  cout << "What would you like to do?" << endl;
  cout << "1. Display your Chemist's Substances" << endl;
  cout << "2. Search for Elements" << endl;
  cout << "3. Attempt to Merge Substances" << endl;
  cout << "4. See Score" << endl;
  cout << "5. Quit" << endl;

  cin >> decision;
  while((decision < 1) or (decision > 5)){
    cout << "choice must be between 1 and 5.\n";
    cin >> decision;
  }

  return decision;
}


// Name: SearchSubstances()
// Desc - Attempts to search for raw substances (must be type "element")
// Preconditions - Raw substances loaded
// Postconditions - Increases quantity in Chemist's posession of substances
void Lab::SearchSubstances(){
  srand (time(NULL));
  int substance_index = rand() % 29;
  Substance element = m_myChemist.GetSubstance(substance_index);
  m_myChemist.IncrementQuantity(element);
  cout << element.m_name << " found!" << endl;
}


// Name: CombineSubstances()
// Desc - Attempts to combine known substances. If combined, quantity of substance decreased
// 1. Requests user to choose two substances (RequestSubstance)
// 2. Checks to see if formula exists for combining two chosen substances
//     (checks sub1, sub2 and sub2, sub1) using SearchFormula
// 3. If there is an available formula for two chosen substances, checks
//     quantity for two chosen substance.
// If no quantity for two substances, tells user that there is no available quantity
// If quantity is available, decreases quantity for two chosen substances
//     from the chemist then increases new substance
// 4. If there is no available formula, tells user that nothing happens when you try and merge two chosen substances
// Preconditions - Chemist is populated with substances
// Postconditions - Increments quantity of substance "made", decreases quantity of source items
void Lab::CombineSubstances(){
  // stores the elements to be combined in these ints
  int sub1, sub2;
  RequestSubstance(sub1);
  RequestSubstance(sub2);
  // creates substance objects of the substances to be combined
  Substance s1 = m_myChemist.GetSubstance(sub1);
  Substance s2 = m_myChemist.GetSubstance(sub2); 
  string substance1 = s1.m_formula;
  string substance2 = s2.m_formula;
  // passes their formulas into the search formula function
  int substance = SearchFormulas(substance1, substance2);
  Substance s3  = m_myChemist.GetSubstance(substance);
   // return value from SearchFormula tells if the merge was a
   // success or not
  if(substance == 0){
    cout << "Nothing happens when you merge " << s1.m_name << 
      " and " << s2.m_name << "." << endl;
  }else{
    // if the two substances can be merged the quantity is checked
    if(m_myChemist.CheckQuantity(s1, s2)){
        // create the substance
        m_myChemist.IncrementQuantity(s3);
        cout << substance1 << " combined with " << substance2 <<
          " to make " << s3.m_name << "!" << endl;
      }else{
        // say there isn't enough
        cout << "You do not have enough of either " << s1.m_name <<
          " or " << s2.m_name << " to make " << s3.m_name << "." << endl;
      }
    }
  }



// Name: RequestSubstance()
// Desc - Allows the user to choose a substance to try and merge.
//        Returns the index of chosen substance
// Preconditions - Chemist has substances to try and merge
// Postconditions - Returns integer of substance selected by user
void Lab::RequestSubstance(int &choice){
  // gets the substances the user wants to merge
  choice = -1;
  while(choice == -1){
    cout << "Which substances would you like to merge?" << endl;
    cout << "To list known substances enter -1" << endl;
    cin >> choice;
    while(choice == 0){
      cout << "Choice cannot be 0." << endl;
      cin >> choice;
    }
    if(choice == -1){
      DisplaySubstances();
    }
    while((choice < -1) or (choice > 283)){
      cout << "choice must be a substance or -1" << endl;
      cout << "Which substances would you like to merge?" << endl;
      cout << "To list known substances enter -1" << endl;
      cin >> choice;
    }
  }
  choice -= 1;
}


// Name: SearchFormulas()
// Desc - Searches formulas for two strings (name of item)
// Preconditions - m_substances is populated
// Postconditions - Returns int index of matching formula
int Lab::SearchFormulas(string sub1, string sub2){
  for(int i = 0; i < PROJ2_SIZE; i++){
    // check which substance is made by the two requested by the user
    if(m_substances[i].m_substance1 == sub1){
      if(m_substances[i].m_substance2 == sub2){
        return i;
      }
    }else if(m_substances[i].m_substance1 == sub2){
      if(m_substances[i].m_substance2 == sub1){
        return i;
      }
    }
  }
  return 0;
}


// Name: CalcScore()
// Desc - Displays current score for Chemist
// Preconditions - Chemist is populated with substances
// Postconditions - Displays total number of substances found. Displays
//        percentange found as number found divided by total available
void Lab::CalcScore(){
  double substances = 0;
  Substance s;
  double score;
  for(int i = 0; i < PROJ2_SIZE; i++){
    s = m_myChemist.GetSubstance(i);
    if (s.m_quantity > 0){
      substances += 1;
    }
  }
  score = substances / PROJ2_SIZE;
  cout << "***The Chemist***" << endl;
  cout << "The Great Chemist " << m_myChemist.GetName() << endl;
  cout << "You have found " << substances << " substances so far." << endl;
  cout << "This is " << score * 10 << "%" << endl;
}
