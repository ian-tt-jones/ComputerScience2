#include "Chemist.h"

// Name: Chemist() - Default Constructor
// Desc: Used to build a new Chemist
// Preconditions - Requires default values
// Postconditions - Creates a new Chemist (with a default name of "Beaker" and
//       m_numSubstances = 0
Chemist::Chemist(){
  m_myName = "Beaker";
  m_numSubstances = 0;
}


// Name: Chemist(name) - Overloaded constructor
// Desc - Used to build a new Chemist
// Preconditions - Requires name
// Postconditions - Creates a new Chemist (with passed name and m_numSubstance = 0)
Chemist::Chemist(string name){
  m_myName = name;
  m_numSubstances = 0;
}


// Name: GetName()
// Desc - Getter for Chemist name
// Preconditions - Chemist exists
// Postconditions - Returns the name of the Chemist
string Chemist::GetName(){
  return m_myName;
}


// Name: SetName(string)
// Desc - Allows the user to change the name of the Chemist
// Preconditions - Chemist exists
// Postconditions - Sets name of Chemist
// May not be used in the project explicitly but please impelement
void Chemist::SetName(string name){
  m_myName = name;
}


// Name: CheckSubstance(Substance)
// Desc - Checks to see if the Chemist has a substance if so, returns
//        the index where it exists, if not returns -1
// Preconditions - Chemist already has substance
// Postconditions - Returns index of substance if Chemist has it else -1
int Chemist::CheckSubstance(Substance substance){
  for(int s = 0; s < PROJ2_SIZE; s++){
    if(m_mySubstances[s].m_name == substance.m_name){
      return s;
    }
  }
  return -1;
}


// Name: AddSubstance(string)
// Desc - Inserts a material into the Chemist's list of substances. Has
//        to see if it exists in m_mySubstances first to find location.
//        Then adds substance and increments m_numSubstances
// Preconditions - Chemist exists
// Postconditions - Add a substances to the Chemist's m_mySubstances with a quantity of 0
void Chemist::AddSubstance(Substance substance){
    m_mySubstances[m_numSubstances] = substance;
    m_numSubstances += 1;
  }



// Name: IncrementQuantity(Substance)
// Desc - Adds quantity to list of substances the chemist knows.
//        Has to find location in array first. Then increments quantity
// Preconditions - Chemist exists
// Postconditions - Increases quantity of material for chemist
void Chemist::IncrementQuantity(Substance substance){
  for(int s = 0; s < PROJ2_SIZE; s++){
    if(m_mySubstances[s].m_name == substance.m_name){
      m_mySubstances[s].m_quantity += 1;
    }
  }
}


// Name: DecrementQuantity(Substance)
// Desc - Reduces quantity from chemist's inventory with true, if no quantity false
// Preconditions - Chemist exists
// Postconditions - Reduces quantity of substance for chemist
bool Chemist::DecrementQuantity(Substance substance){
  for(int s = 0; s < PROJ2_SIZE; s++){
    if(m_mySubstances[s].m_name == substance.m_name){
      m_mySubstances[s].m_quantity -= 1;
      return true;
    }
  }
  return false;
}


// Name: CheckQuantity(Substance)
// Desc - Checks to see if quantity of two merge substances is greater than one.
//        if the quantity of substance 1 is greater than one and the
//        quantity of substance two is greater than one, returns true else false
// Preconditions - Chemist exists with substances
// Postconditions - Returns true if both are available
bool Chemist::CheckQuantity(Substance substance_1, Substance substance_2){
  // makes sure the quantites are both greater than 0 before decrementing
  if(substance_1.m_quantity > 0){
    if(substance_2.m_quantity > 0){
      if(DecrementQuantity(substance_1)){
        if(DecrementQuantity(substance_2)){
          return true;
        }
      }
    }else{
      return false;
    }
  }else{
    return false;
  }
  return false;
}


// Name: GetSubstance(int)
// Desc - Returns a substance at at specific index
// Preconditions - Chemist already has substances
// Postconditions - Returns substance at specific index
Substance Chemist::GetSubstance(int substance){
  return m_mySubstances[substance];
}


// Name: GetTotalSubstances
// Desc - Iterates over m_mySubstances and counts each substance with a quantity higher than 0
// Preconditions - Chemist may have no substances
// Postconditions - Returns number of substances with a quantity greater than 0
int Chemist::GetTotalSubstances(){
  int numSubstances = 0;

  for(int s = 0; s < PROJ2_SIZE; s++){
    numSubstances += m_mySubstances[s].m_quantity;
  }

  return numSubstances;
}

