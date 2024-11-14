#include "Ong.h"

// Name: Ong (Default Constructor)
// Desc: Constructor to build an empty Ong Cipher
// Preconditions - None
// Postconditions - Creates a Ong cipher to be encrypted
Ong::Ong(){}


// Name: Ong (Overloaded Constructor)
// Desc: Constructor to build a populated Ong Cipher
// Preconditions - Pass it the message and isEncrypted
// Postconditions - Creates a Ong cipher to be encrypted
Ong::Ong(string message, bool isEncrypted) : Cipher(message, isEncrypted){

}


// Name: Ong (Destructor)
// Desc: Destructor - Anything unique to Ong to delete?
// Preconditions - ~Ong exists
// Postconditions - Ong destroyed
Ong::~Ong(){}


// Name: IsVowel (Helper function)
// Desc: Returns true if vowel, space, or punctuation
// Preconditions - Message exists
// Postconditions - Returns true or false as above
bool Ong::IsVowel(char c){
  bool isVowel = (c == 'a' or c == 'e' or c == 'i' 
                  or c == 'o' or c == 'u'
                  or c == 'A' or c == 'E' 
                  or c == 'I' or c == 'O' or c == 'U');
  return isVowel;
}


// Name: Encrypt
// Desc: If vowel then vowel and dash displayed. dog = dong-o-gong
// If consonant then consonant and ong and dash displayed.
// Preconditions - Message exists
// Postconditions - Encrypts as above
void Ong::Encrypt(){
  string message = GetMessage();
  string newMessage = "";
  for(int i = 0; i < message.length(); i++){
    if(! IsVowel(message[i])){
      if(message[i] == ' '){
        newMessage += message[i];
      }else if(message[i] == '.'){
        newMessage += message[i];
      }else if(message[i] == '('){
        newMessage += message[i];
      }else if(message[i] == '.'){
        newMessage += message[i];
      }else if(message[i] == ')'){
        newMessage += message[i];
      }else{
        newMessage += message[i];
        if((i == message.length() - 1) or (message[i + 1] == ' ') or
          (message[i + 1] == ')') or (message[i + 1] == '.')){
          newMessage += "ong";
        }else{
          newMessage += "ong-";
        }
      }
    }else{
      newMessage += message[i];
      if((i != message.length() - 1) and !(message[i + 1] == ' ') and
          !(message[i + 1] == ')') and !(message[i + 1] == '.')){
          newMessage += '-';
      }
    }
  }
  SetMessage(newMessage);
}


// Name: Decrypt
// Desc: Removes the dashes and "ong" when necessary cong-a-tong = cat
// Double check words like "wrong" so that they work correctly!
// Preconditions - Message exists
// Postconditions - Original message is displayed
void Ong::Decrypt(){
  string message = GetMessage();
  string newMessage = "";
  for(int i = 0; i < message.length(); i++){
      if(message[i] == ' '){
        newMessage += message[i];
      }else if(message[i] == '.'){
        newMessage += message[i];
      }else if(message[i] == '('){
        newMessage += message[i];
      }else if(message[i] == '.'){
        newMessage += message[i];
      }else if(message[i] == ')'){
        newMessage += message[i];
      }else if(message[i] == '-'){
      }else if(!(IsVowel(message[i]))){
        newMessage += message[i];
        i += 3;
      }else if(IsVowel(message[i])){
        newMessage += message[i];
      }
  }
  SetMessage(newMessage);
}


// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Ong in this case)
string Ong::ToString(){
  return "Ong";
}


// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - o, delimiter, isencrypted, delimiter,
//                  message, delimiter, blank are output
string Ong::FormatOutput(){
  string e;
  if(GetIsEncrypted()){
    e = "1";
  }else{
    e = "0";
  }
  return("o|" + e + "|" + GetMessage() + "| ");
}

