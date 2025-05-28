#include "binarytree.h"
#include <string>
void getQuestions(ifstream &fin, vector<string> &q, vector<string> &a)
{
  // variables to store the question and answer
  string question;
  string answer;

  //while question is being collected, collect and store question and answer
  while(getline(fin, question, '.'))
  {
    fin >> answer; // collect answer
    q.push_back(question); // store the question
    a.push_back(answer); // store the answer
  }
}

bool restart()
{
  Clear;
  string input;
  while(true)
  {
    cout << "Would you like to play again?" << endl;
    getline(cin, input);
    for(int i=0; i<input.length(); i++)
      input[i] = toupper(input[i]);

    if(input == "YES" || input == "Y" || input == "NO" || input == "N")
      break;
    
    else
      cout << endl << "Inncorrect input. Please try again." << endl;
  }
  Clear;
  if(input == "YES" || input == "Y")
    return true;
  else
    return false;
}

int main()
{
  srand(time(0));

  ifstream fin;
  fin.open("questions.txt");
  // if file is not open, print error
  if(!fin)
  {
    cout << "\"qustions.txt\" is unavailable";
    return -1;
  }

  // questions to be stored in the nodes
  vector<string> questions;

  // answers to be stores in the nodes
  vector<string> answers;

  // funciton to get questions and answers from outside file
  getQuestions(fin, questions, answers);

  while(true)
  {
    // make binary tree
    BT a;
    
    // inserting nodes and assigning questions and answers
    for(int i = 0; i < questions.size(); i++)
        a.insert(questions[i], answers[i]);

    // user welcome message (introduction)
    a.display();
    
    // goes through nodes
    a.game();

    // to print tree of nodes
    ofstream fout;
    fout.open("tree.txt");
    if(!fout)
    {
      cout << "\"tree.txt.\" can't be opened.";
      return -1;
    }

    a.print(fout);
    
    fout.close();

    if(restart()==false)
    {
      Clear;
      cout << "Thank you for playing!";
      a.hitEnter();
      break;
    }
  }

  return 0;
}