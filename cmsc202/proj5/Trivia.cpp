/*****************************************************************************
 ** File: Trivia.cpp
 ** Project: CMSC 202 Project 5, Spring 2022
 ** Author:  Kush Shah and CMSC202
 ** Date:    04/05/2022
 ** Email:   k216@umbc.edu
 **
 Description: CPP file for Trivia class. Includes both class definition and
 class function definitions. Loads a file of trivia questions
*****************************************************************************/

#ifndef TRIVIA_CPP
#define TRIVIA_CPP
#include "Lqueue.cpp"
#include "Question.cpp"
#include <fstream>
#include <vector>
using namespace std;

const string DEFAULT_FILE = "proj5_string.txt";
const char DELIMITER = '|';

template <class T>
class Trivia {
public:
  // Name: Default Constructor
  // Desc: Displays the title, Loads Questions and calls menu
  // Indicates if the file was not loaded.
  // Precondition: None
  // Postcondition: User is prompted with assignment menus
  Trivia(string filename= DEFAULT_FILE);
  // Name: Destructor
  // Desc: Deallocates memory allocated for the Questions and
  // resets all variables.
  // Precondition: A Trivia exists.
  // Postcondition: All dynamically allocated memory in Trivia is deleted.
  ~Trivia();
  // Name: LoadQuestions
  // Desc: Each input file will be for a specific type of question (int, double, string)
  //       Reads in Questions from a file and stores them in anLqueue.
  //       An input file will be for exactly one type of question (int, double, string)
  // Precondition: None.
  // Postcondition: Returns true if file was read. Otherwise, it returns false.
  bool LoadQuestions(string filename);
  // Name: MainMenu
  // Desc: Presents user with menu options for showing subjects and allowing
  // user to work on a subject.
  // Precondition: None.
  // Postcondition: The main menu is presented.
  void MainMenu();
  // Name: DisplaySubjects
  // Desc: Presents all Subjects with corresponding numerical identifiers.
  // Precondition: Subjects have been added.
  // Postcondition: All assignments are printed to the screen.
  void DisplaySubjects();
  // Name: StartSubject
  // Desc: Starts working on a selected Subject.
  // Displays the number of questions in subject.
  // Starts at beginning and goes through each question.
  // After all questions have been answered:
  //       displays total correct, incorrect, and percentage correct
  // Precondition: m_questions has been populated
  // Postcondition: Returns to main menu
  void StartSubject();
  // Name: AddSubject
  // Desc: Checks to see if a subject exists in m_subjects.
  //       If not, inserts subject into m_subjects.
  // Precondition: A Subject exists.
  // Postcondition: Add subject to m_subjects if new subject.
  void AddSubject(string subject);
  // Name: ChooseSubject
  // Desc: Allows a user to choose one of the subjects to work on. Lists all subjects
  // in m_subjects and allows use to choose one. Returns value - 1 (location in vector)
  // Precondition: A Subject exists.
  // Postcondition: Returns value entered minus one
  int ChooseSubject();
  // Name: QuestionsPerSubject
  // Desc: Iterates over m_questions and counts how many questions match the subject
  // passed into function
  // Precondition: A Subject exists.
  // Postcondition: Returns number of questions of a particular subject
  int QuestionsPerSubject(string subject);
  // Name: DisplayTitle
  // Desc: Displays opening Welcome message
  // Precondition: None.
  // Postcondition: Title is displayed.
  void DisplayTitle();
private:
  Lqueue<Question<T>* >* m_questions; // Holds questions using a specific data type
  vector<string> m_subjects; //Populated as file is loaded
};

//**********Implement Trivia Class Here***********

// Name: Default Constructor
// Desc: Displays the title, Loads Questions and calls menu
// Indicates if the file was not loaded.
// Precondition: None
// Postcondition: User is prompted with assignment menus
template <class T>
Trivia<T>::Trivia(string filename){
  m_questions = new Lqueue<Question<T>* >;
  DisplayTitle();
  if(LoadQuestions(filename)){
    cout << "questions loaded" << endl;
  }
  MainMenu();
}


// Name: Destructor
// Desc: Deallocates memory allocated for the Questions and
// resets all variables.
// Precondition: A Trivia exists.
// Postcondition: All dynamically allocated memory in Trivia is deleted.
template <class T>
Trivia<T>::~Trivia(){
  for(int i = 0; i < m_questions -> GetSize(); i++){
    delete m_questions -> At(i);
  }
  delete m_questions;
}


// Name: LoadQuestions
// Desc: Each input file will be for a specific type of question (int, double, string)
//       Reads in Questions from a file and stores them in anLqueue.
//       An input file will be for exactly one type of question (int, double, string)
// Precondition: None.
// Postcondition: Returns true if file was read. Otherwise, it returns false.
template <class T>
bool Trivia<T>::LoadQuestions(string filename){
  fstream questions;
  string holder;
  string subject, question, difficulty, datatype; 
  T answer;
  questions.open(filename);
  int count = 1;
  while(!(questions.eof())){
    if(count != 1){
      // gets rid of the \n
      getline(questions, holder);
    }
    // uses getline until answer to avoid \n
    getline(questions, subject, DELIMITER);
    AddSubject(subject);
    getline(questions, question, DELIMITER);
    getline(questions, datatype, DELIMITER);
    getline(questions, difficulty, DELIMITER);
    questions >> answer;
    count += 1;

    Question<T> *q = new Question<T>(subject, question, datatype, stoi(difficulty), answer);
    m_questions -> Push(q);
  }
  m_subjects.pop_back();
  questions.close();
  return true;
}


// Name: MainMenu
// Desc: Presents user with menu options for showing subjects and allowing
// user to work on a subject.
// Precondition: None.
// Postcondition: The main menu is presented.
template <class T>
void Trivia<T>::MainMenu(){
  int choice = 1;
  while(choice != 3){
    do{
      cout << "Choose an option." << endl;
      cout << "1. Display Subjects" << endl;
      cout << "2. Start Subject" << endl;
      cout << "3. Quit" << endl;
      cin >> choice;
      if((choice < 1) or (choice > 3)){
        cout << "Invalid option. Try again." << endl;
      }
    }while((choice < 1) or (choice > 3));

    if(choice == 1){
      DisplaySubjects();
    }
    if(choice == 2){
      StartSubject();
    }
  }
}


// Name: DisplaySubjects
// Desc: Presents all Subjects with corresponding numerical identifiers.
// Precondition: Subjects have been added.
// Postcondition: All assignments are printed to the screen.
template <class T>
void Trivia<T>::DisplaySubjects(){
  for(int i = 0; i < int(m_subjects.size()); i++){
    cout << i + 1 << ". " << m_subjects[i] << endl;
  }
}


// Name: StartSubject
// Desc: Starts working on a selected Subject.
// Displays the number of questions in subject.
// Starts at beginning and goes through each question.
// After all questions have been answered:
//       displays total correct, incorrect, and percentage correct
// Precondition: m_questions has been populated
// Postcondition: Returns to main menu
template <class T>
void Trivia<T>::StartSubject(){
  // initializing variables
  double correct = 0;
  double incorrect = 0;
  int subject = ChooseSubject();
  int num_questions = QuestionsPerSubject(m_subjects[subject]);

  // Displaying prompt to user
  cout << "There are " << num_questions << " questions in this subject." << endl;
  T answer;
  // loops through all the questions and displays the ones
  // with the subjects the user chose
  for(int q = 0; q < m_questions -> GetSize(); q++){
    if(m_questions -> At(q) -> m_subject == m_subjects[subject]){
      cout << *m_questions -> At(q);
      cout << endl;
      cin >> answer;
      if(m_questions -> At(q) -> CheckAnswer(answer)){
        correct += 1;
        cout << "Correct" << endl;
      }else{
        incorrect += 1;
        cout << "Incorrect" << endl;
      }
    }
  }

  // displays results
  cout << "You got " << correct << " answers correct." << endl;
  cout << "You got " << incorrect << " answers incorrect." << endl;
  double percentage = (correct / num_questions) * 100;
  cout << "Which is " << percentage << "%." << endl;
}


// Name: AddSubject
// Desc: Checks to see if a subject exists in m_subjects.
//       If not, inserts subject into m_subjects.
// Precondition: A Subject exists.
// Postcondition: Add subject to m_subjects if new subject.
template <class T>
void Trivia<T>::AddSubject(string subject){
  bool exists = false;
  for(int i = 0; i < int(m_subjects.size()); i++){
    if(m_subjects[i] == subject){
      exists = true;
    }
  }
  if(not exists){
    m_subjects.push_back(subject);
  }
}


// Name: ChooseSubject
// Desc: Allows a user to choose one of the subjects to work on. Lists all subjects
// in m_subjects and allows user to choose one. Returns value - 1 (location in vector)
// Precondition: A Subject exists.
// Postcondition: Returns value entered minus one
template <class T>
int Trivia<T>::ChooseSubject(){
  int choice = 0;
  cout << "Which subject would you like to attempt?" << endl;
  DisplaySubjects();
  cin >> choice;
  while((choice < 1) or (choice > int(m_subjects.size()))){
    cout << "Invalid option. Try again." << endl;
    DisplaySubjects();
    cin >> choice;
  }
  return choice - 1;
}


// Name: QuestionsPerSubject
// Desc: Iterates over m_questions and counts how many questions match the subject
// passed into function
// Precondition: A Subject exists.
// Postcondition: Returns number of questions of a particular subject
template <class T>
int Trivia<T>::QuestionsPerSubject(string subject){
  int count = 0;
  for(int i = 0; i < m_questions -> GetSize(); i++){
    if(m_questions -> At(i) -> m_subject == subject){
      count += 1;
    }
  }
  return count;
}


// Name: DisplayTitle
// Desc: Displays opening Welcome message
// Precondition: None.
// Postcondition: Title is displayed.
template <class T>
void Trivia<T>::DisplayTitle(){
  cout << "Welcome to UMBC Trivia!" << endl;
}

#endif
