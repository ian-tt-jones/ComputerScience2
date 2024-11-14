#include "Caesar.h" 

// Name: Caesar (Default Constructor)
// Desc: Constructor to build an empty Caesar Cipher (Defaults to shift 3)
// Preconditions - None
// Postconditions - Creates a Caesar cipher to be encrypted
Caesar::Caesar(){
	m_shift = 3;
}


// Name: Caesar (Overloaded Constructor)
// Desc: Constructor to build a populated Caesar Cipher (Defaults to shift 3)
// Preconditions - Pass it the message, isEncrypted, and shift (any integer)
// Postconditions - Creates a Caesar cipher to be encrypted
Caesar::Caesar(string message, bool isEncrypted, int shift) : Cipher(message, isEncrypted){
	m_shift = shift;
}


// Name: Caesar (Destructor)
// Desc: Destructor - Anything specific to Caesar to delete?
// Preconditions - ~Caesar exists
// Postconditions - Caesar destroyed
Caesar::~Caesar(){}


// Name: Encrypt
// Desc: Shifts characters right based on shift (lower stay lower, upper stay upper)
// Preconditions - Message exists
// Postconditions - Shifts each character "right".
void Caesar::Encrypt(){
	string message = GetMessage();
	for(int i = 0; i < message.length(); i++){
		for(int j = 0; j < m_shift; j++){
		    if(message[i] == 'z'){
		      message[i] = 'a';
		    }
		    else if(message[i] == 'Z'){
		      message[i] = 'A';
		    }
		    else if(message[i] == ' '){}
		    else{
			    message[i]++;
		    }
		}
	}
	SetMessage(message);
}


// Name: Decrypt
// Desc: Shifts characters left based on shift (lower stay lower, upper stay upper)
// Preconditions - Message exists
// Postconditions - Shifts each character "left".
void Caesar::Decrypt(){
	string message = GetMessage();
	for(int i = 0; i < message.length(); i++){
		for(int j = 0; j < m_shift; j++){
		    if(message[i] == 'a'){
		      message[i] = 'z';
		    }
		    else if(message[i] == 'A'){
		      message[i] = 'Z';
		    }
		    else if(message[i] == ' '){}
		    else{
			    message[i]--;
		    }
		}
	}
	SetMessage(message);
}


// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Caesar in this case)
string Caesar::ToString(){
	return "Caesar";
}


// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - c, delimiter, isencrypted, delimiter,
//                  message, delimiter, m_shift are returned for output
string Caesar::FormatOutput(){
	string message = GetMessage();
	string e;
	if(GetIsEncrypted()){
		e = "1";
	}else{
		e = "0";
	}
	return("c|" + e + "|" + message + "|" + to_string(m_shift));
}

