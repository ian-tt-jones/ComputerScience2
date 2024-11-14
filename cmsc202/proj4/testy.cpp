#include <iostream>
#include <fstream>
#include <string>
using namespace std;
bool isVowel(char);

int main(){
  // fstream ciphers;
  // ciphers.open("proj4_test4.txt");
  // string line;
  // while(getline(ciphers, line)){
  //   char cipher = line[0];
  //   char isEncrypted = line[2];
  //   string message = "";
  //   string shift;
  //   int count = 4;
  //   for(int i = 0; i < 2; i++){
  //     string element = "";
  //     if(i == 0){
  //     	while(line[count] != '|'){
  //     	  element += line[count];
  //     	  count += 1;
	 //      }
  // 	    count += 1;
  //       }else{
  //       	element = line[count];
  //       	count += 2;
  //       }
  //       if(i == 0){
  // 	      message = element;
  //       }
  //       if(i == 1){
  // 	      shift = element;
  //       }
  //   element = "";
  //   }
  //   cout << "The cipher is: " << cipher << endl;
  //   cout << "is it encrypted: " << isEncrypted << endl;
  //   cout << "message: " << message << endl;
  //   cout << "shift: " << shift << endl;
  // }
  // string m_message = "dog (the dog)";
  // string new_message = "";
  // for(int i = 0; i < m_message.length(); i++){
  //   if(! isVowel(m_message[i])){
  //     if(m_message[i] == ' '){
  //       new_message += m_message[i];
  //     }else if(m_message[i] == '.'){
  //       new_message += m_message[i];
  //     }else if(m_message[i] == '('){
  //       new_message += m_message[i];
  //     }else if(m_message[i] == '.'){
  //       new_message += m_message[i];
  //     }else if(m_message[i] == ')'){
  //       new_message += m_message[i];
  //     }else{
  //       new_message += m_message[i];
  //       if((i == m_message.length() - 1) or (m_message[i + 1] == ' ') or
  //         (m_message[i + 1] == ')') or (m_message[i + 1] == '.')){
  //         new_message += "ong";
  //       }else{
  //         new_message += "ong-";
  //       }
  //     }
  //   }else{
  //     new_message += m_message[i];
  //     if((i != m_message.length() - 1) and !(m_message[i + 1] == ' ') and
  //         !(m_message[i + 1] == ')') and !(m_message[i + 1] == '.')){
  //         new_message += '-';
  //     }
  //   }
  // }
  // cout << new_message << endl;

  string m_message = "Pong-e-a-cong-e bong-e-gong-i-nong-song wong-i-tong-hong a song-mong-i-long-e-. (-Mong-o-tong-hong-e-rong Tong-e-rong-e-song-a-)";
  string newMessage = "";
  for(int i = 0; i < m_message.length(); i++){
      if(m_message[i] == ' '){
        newMessage += m_message[i];
      }else if(m_message[i] == '.'){
        newMessage += m_message[i];
      }else if(m_message[i] == '('){
        newMessage += m_message[i];
      }else if(m_message[i] == '.'){
        newMessage += m_message[i];
      }else if(m_message[i] == ')'){
        newMessage += m_message[i];
      }else if(m_message[i] == '-'){
      }else if(!(isVowel(m_message[i]))){
        newMessage += m_message[i];
        i += 3;
      }else if(isVowel(m_message[i])){
        newMessage += m_message[i];
      }
  }
  cout << newMessage;
  // cout << newMessage << endl;
  // string newMessage = "";
  // int increment = 1;
  // int railTracker = 0;
  // string rails[m_rails];
  // for(int i = 0; i < m_message.length(); i++){
  //   rails[railTracker] += m_message[i];
  //   railTracker += increment;
  //   if(railTracker == m_rails - 1){
  //     increment *= -1;
  //   }
  //   if((railTracker == 0) and (i != 0)){
  //     increment *= -1;
  //   }
  // }
  // for(int i = 0; i < m_rails; i++){
  //   newMessage += rails[i];
  // }
  // cout << newMessage << endl;

  // variables used to track values
  // string newMessage = "";
  // int m_shift = 3;
  // char rails[m_shift][m_message.length()];
  // int increment = 1;
  // int increment2 = 1;
  // int railTracker = 0;
  // int railTracker2 = 0;
  // int c = 0;

  // for(int i = 0; i < m_shift; i++){
  //   for(int j = 0; j < m_message.length(); j++){
  //     rails[i][j] = 0;
  //   }
  // }

  // // plots the path of the railfence
  // for(int i = 0; i < m_message.length(); i++){
  //   rails[railTracker][i] = '#';
  //   railTracker += increment;
  //   if(railTracker == m_shift - 1){
  //     increment *= -1;
  //   }else if(railTracker == 0){
  //     increment *= -1;
  //   }
  // } 

  // // replaces the # with the letters in the word
  // for(int i = 0; i < m_shift; i++){
  //   for(int j = 0; j < m_message.length(); j++){
  //     if(rails[i][j] == '#'){
  //       rails[i][j] = m_message[c];
  //       c++;
  //     }
  //   }
  // }
 
  // // goes through the path and builds the new message
  // for(int i = 0; i < m_message.length(); i++){
  //   newMessage += rails[railTracker2][i];
  //   railTracker2 += increment2;
  //   if(railTracker2 == m_shift - 1){
  //     increment2 *= -1;
  //   }else if(railTracker2 == 0){
  //     increment2 *= -1;
  //   }
  // }

  // m_message = newMessage;
}


bool isVowel(char c){
  bool isVowel = (c == 'a' or c == 'e' or c == 'i' or c == 'o' or c == 'u'
                  or c == 'A' or c == 'E' or c == 'I' or c == 'O' or c == 'U');
  return isVowel;
}
