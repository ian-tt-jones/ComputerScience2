#include "RailFence.h"

// Name: RailFence (Default Constructor)
// Desc: Constructor to build an empty RailFence Cipher (Defaults to 3 rails)
// Preconditions - None
// Postconditions - Creates a RailFence cipher
RailFence::RailFence(){
  m_rails = 3;
}


// Name: RailFence (Overloaded Constructor)
// Desc: Constructor to build a populated RailFence Cipher (Defaults to 3 rails)
// Preconditions - Pass it the message, isEncrypted, and number of rails (any integer)
// Postconditions - Creates a RailFence cipher to be encrypted
RailFence::RailFence(string message, bool isEncrypted, int rails) : Cipher(message, isEncrypted){
  m_rails = rails;
}


// Name: RailFence (Destructor)
// Desc: Destructor - Anything specific part of RailFence to delete?
// Preconditions - ~RailFence exists
// Postconditions - RailFence destroyed
RailFence::~RailFence(){}


// Name: Encrypt
// Desc: Letters are placed on a fence rail based on the number of rails
//       Letters are read from one rail at a time into a single string
// Preconditions - Message exists
// Postconditions - A single encrypted string is stored
void RailFence::Encrypt(){
  string message = GetMessage();
  string newMessage = "";
  int increment = 1;
  int railTracker = 0;
  string rails[m_rails];
  for(int i = 0; i < message.length(); i++){
    rails[railTracker] += message[i];
    railTracker += increment;
    if(railTracker == m_rails - 1){
      increment *= -1;
    }
    if((railTracker == 0) and (i != 0)){
      increment *= -1;
    }
  }
  for(int i = 0; i < m_rails; i++){
    newMessage += rails[i];
  }
  SetMessage(newMessage);
}


// Name: Decrypt
// Desc: Single encrypted string is pushed back on the rails and reversed
// Preconditions - Message exists
// Postconditions - The decrypted string is stored
void RailFence::Decrypt(){
  // variables used to track values
  string message = GetMessage();
  string newMessage = "";
  char rails[m_rails][message.length()];
  int increment = 1;
  int increment2 = 1;
  int railTracker = 0;
  int railTracker2 = 0;
  int c = 0;

  for(int i = 0; i < m_rails; i++){
    for(int j = 0; j < message.length(); j++){
      rails[i][j] = 0;
    }
  }

  // plots the path of the railfence
  for(int i = 0; i < message.length(); i++){
    rails[railTracker][i] = '#';
    railTracker += increment;
    if(railTracker == m_rails - 1){
      increment *= -1;
    }else if(railTracker == 0){
      increment *= -1;
    }
  } 

  // replaces the # with the letters in the word
  for(int i = 0; i < m_rails; i++){
    for(int j = 0; j < message.length(); j++){
      if(rails[i][j] == '#'){
        rails[i][j] = message[c];
        c++;
      }
    }
  }
 
  // goes through the path and builds the new message
  for(int i = 0; i < message.length(); i++){
    newMessage += rails[railTracker2][i];
    railTracker2 += increment2;
    if(railTracker2 == m_rails - 1){
      increment2 *= -1;
    }else if(railTracker2 == 0){
      increment2 *= -1;
    }
  }

  SetMessage(newMessage);

}


// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (RailFence in this case)
string RailFence::ToString(){
  return("Railfence");
}


// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - r, delimiter, isencrypted, delimiter,
//                  message, delimiter, m_rails are returned for output
string RailFence::FormatOutput(){
  string message = GetMessage();
  string e;
  if(GetIsEncrypted()){
    e = "1";
  }else{
    e = "0";
  }
  return("r|" + e + "|" + message + "|" + to_string(m_rails));
}

