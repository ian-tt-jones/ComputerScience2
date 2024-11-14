#include "CipherTool.h"

// Name: CipherTool Constructor
// Desc - Creates a new CipherTool and sets m_filename based on string passed
// Preconditions - Input file passed and populated with Cipher
// Postconditions - CipherTool created
CipherTool::CipherTool(string filename){
    m_filename = filename;
}


// Name: CipherTool Destructor
// Desc - Calls destructor for all ciphers in m_ciphers
// Preconditions - m_ciphers is populated
// Postconditions - m_ciphers deallocated and vector emptied
CipherTool::~CipherTool(){
    for(int i = 0; i < m_ciphers.size(); i++){
        delete m_ciphers[i];
    }
}


// Name: LoadFile
// Desc - Opens file and reads in each Cipher. Each Cipher dynamically allocated
// and put into m_ciphers (c is Caesar, r is RailFence, and o is Ong)
// Preconditions - Input file passed and populated with Ciphers
// Postconditions - m_ciphers populated with Ciphers
void CipherTool::LoadFile(){
  fstream ciphers;
  cout << m_filename << endl;
  ciphers.open(m_filename);
  string line;
  while(getline(ciphers, line)){
    char cipher = line[0];
    char isEncrypted = line[2];
    string message = "";
    string shift;
    int count = 4;
    for(int i = 0; i < 2; i++){
      string element = "";
      if(i == 0){
        while(line[count] != '|'){
          element += line[count];
          count += 1;
          }
        count += 1;
        }else{
            element = line[count];
            count += 2;
        }
        if(i == 0){
          message = element;
        }
        if(i == 1){
          shift = element;
        }
    element = "";
    }

    // creates ciphers based on which one it is
    Cipher *c;
    bool e = StringToBoolean(to_string(isEncrypted));
    if(cipher == 'c'){
        c = new Caesar(message, e, stoi(shift));
    }if(cipher == 'r'){
        c = new RailFence(message, e, stoi(shift));
    }if(cipher == 'o'){
        c = new Ong(message, e);
    }
    m_ciphers.push_back(c);
  }
  ciphers.close();
}


// Name: StringToBoolean
// Desc - Helper function that converts a string to a boolean for reading in file
// Preconditions - Passed string of either 0 or 1
// Postconditions - Returns false if 0 else true
bool CipherTool::StringToBoolean(string input){
    if(input == "0"){
        return false;
    }
    if(input == "1"){
        return true;
    }
    return true;
}


// Name: DisplayCiphers
// Desc - Displays each of the ciphers in the m_ciphers
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - Displays ciphers
void CipherTool::DisplayCiphers(){
    for(int i = 0; i < m_ciphers.size(); i++){
        cout << i + 1 << ". ";
        cout << m_ciphers[i] -> GetMessage() << endl;
    }
}


// Name: EncryptDecrypt
// Desc - Encrypts or decrypts each of the ciphers in the m_ciphers
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - Either Encrypts or Decrypts each cipher in m_ciphers
void CipherTool::EncryptDecrypt(bool isEncrypted){
    for(int i = 0; i < m_ciphers.size(); i++){
        if(m_ciphers[i] -> GetIsEncrypted()){
            m_ciphers[i] -> Decrypt();
        }else{
            m_ciphers[i] -> Encrypt();
        }
    }
}


// Name: Export
// Desc - Exports each of the ciphers in the m_ciphers (so they can be reused)
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - All ciphers exported
void CipherTool::Export(){
    string filename;
    cout << "What you like to be the name of the file?" << endl;
    cin >> filename;

    ofstream file;
    file.open(filename);
    for(int i = 0; i < m_ciphers.size(); i++){
        file << m_ciphers[i] -> FormatOutput() << endl;
    }
    file.close();
}


// Name: Menu
// Desc - Displays menu and returns choice
// Preconditions - m_ciphers all populated
// Postconditions - Returns choice
int CipherTool::Menu(){
    int choice;
    do{
    cout << "What would you like to do?\n";
    cout << "1. Display All Ciphers\n";
    cout << "2. Encrypt All Ciphers\n";
    cout << "3. Decrypt All Ciphers\n";
    cout << "4. Export All Ciphers\n";
    cout << "5. Quit\n";
    cin >> choice;
    if((choice < 1) or (choice > 5)){
        cout << "choice must be between 1 and 5." << endl;
    }
    }while((choice < 1) or (choice > 5));   
    return(choice);
}


// Name: Start
// Desc - Loads input file, allows user to choose what to do
// Preconditions - m_ciphers populated with ciphers
// Postconditions - none
void CipherTool::Start(){
    LoadFile();
    int choice = 0;
    while(choice != 5){
        choice = Menu();
        if(choice == 1){
            DisplayCiphers();
        }if(choice == 2){
            cout << "but this ran" << endl;
            for(int i = 0; i < m_ciphers.size(); i++){
                if(!(m_ciphers[i] -> GetIsEncrypted())){
                    cout << "this ran" << endl;
                    m_ciphers[i] -> Encrypt();
                }
            }
        }if(choice == 3){
            for(int i = 0; i < m_ciphers.size(); i++){
                if((m_ciphers[i] -> GetIsEncrypted())){
                    m_ciphers[i] -> Decrypt();
                }
            }
        }if(choice == 4){
            Export();
        }
    }
}

