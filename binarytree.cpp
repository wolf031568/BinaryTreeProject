#include "binarytree.h"

// blink
string Blink = "\x1b[5m";
// reset
string Reset = "\x1b[0m";
// italic
string Italic = "\x1b[3m";
// green
string Green = "\x1b[32m";
// yellow
string Yellow = "\x1b[33m";
// red
string Red = "\x1b[31m";
// blue
string Blue = "\x1b[34m";

// constructor
BT::BT()
{
  root = nullptr;
  rewardCounter = 0;
  gold = 0;
  rock = 0;
}

// helper function for destructor
void BT::deleteNode(Node* &p)
{
  if(p == nullptr)
    return;
  deleteNode(p->left);
  deleteNode(p->right);
  delete p;
}

// destructor
BT::~BT()
{
  deleteNode(root);
}

// max rewards function
int BT::maxReward()
{
  return maxRewardR(root);
}

// helper function for max reward
int BT::maxRewardR(Node* p)
{
  if(p == nullptr)
    return 0;
  return 1 + max(maxRewardR(p->left), maxRewardR(p->right));
}

// insert function
void BT::insert(string q, string a)
{
  insertR(root, q, a);
}

// helper function for insert
void BT::insertR(Node* &p, string q, string a)
{
  if(p == nullptr)
  {
    Node* temp = new Node();
    temp->question = q;
    temp->answer = a;
    temp->left = nullptr;
    temp->right = nullptr;
    p = temp;
  }
  else
  {
    if(rand() % 2 == 0)
      insertR(p->left, q, a);
    else
      insertR(p->right, q, a);
  }

}

// game function in charge of traveling the tree
void BT::game()
{
  gameR(root);
}

// helper function for game
void BT::gameR(Node* p)
{
  // if you reach a node that is nullptr, end of game
  if(p == nullptr)
  {
    cout << endl << "You've reached a dead end!" << endl;

    hitEnter();

    Clear;

    // message for if you got the max rewards possible
    if (rewardCounter == maxReward())
    {
      cout << endl <<"Wow!" << endl << endl
           << "You got " << rewardCounter << " rewards!" << endl

           << "The max and most amount of rewards "
           << "possible from all the paths avaliable!" << endl;
    }
    // message for getting less than max possible rewards
    else
    {
      cout << endl << "Luckily, you got " << rewardCounter
           << " rewards!" << endl << endl

           << "Sadly, you didn't take the longest path which has "
           << maxReward() << " rewards." << endl;
    }

    cout << endl << Italic
         << "You collected " << gold << " gold and "
         << rock << " rock(s)!" << endl << endl
         
         << " - - - - - - - - -" << endl
         << setw(10)
         << Red << Italic << Blink
         << "Game over!"
         << Reset << endl
         << " - - - - - - - - -" << endl;
    hitEnter();

    return;
  }
  else
  {
    // convert p->answer to upper case
    for(int i = 0; i < p->answer.length() ;i++)
      p->answer[i] = toupper(p->answer[i]);

    string input = inputValidiation(p);

    rewardCounter++;
    // if user enters the right answer go left on tree
    if(input == p->answer)
    {
      cout << "You are correct!" << endl
           
           << "You get a gold coin!" << endl << endl
           
           << "A door to the left opens and you climb the tree to the next room."
           << endl;

      cout << Blue;
      cout << "       _______" << endl
           << "      |* ___ *|" << endl
           << "      | |   | |" << endl
           << "      | |___| |" << endl
           << "      |  ___ o|" << endl
           << "      | |   | |" << endl
           << "      | |___| |" << endl
           << "      |*_____*|" << endl
           << Reset
           << "     _ _ _ _ _ _" << endl
           << "   _|_|_|_|_|_| |_" << endl
           << " _|_|_| |_|_|_|_|_|_" << endl
           << "__|_|_|_|_|_|_| |_|__" << endl
           << endl;
      hitEnter();
      Clear;
      gold++;
      gameR(p->left);
    }
    // if user enters the wrong answer go right on tree
    else
    {
      cout << "You are wrong!" << endl

           << "You get a rock!" << endl << endl

           << "A door to the right opens and you climb the tree to the next room."
           << endl;
           
      cout << Red;
      cout << "       _______" << endl
           << "      |  ___  |" << endl
           << "      | |   | |" << endl
           << "      | |   | |" << endl
           << "      | |   |o|" << endl
           << "      | |   | |" << endl
           << "      | |___| |" << endl
           << "      |_______|" << endl
           << Reset
           << "     _ _ _ _ _ _" << endl
           << "   _|_|_|_|_|_| |_" << endl
           << " _|_|_|_| |_|_|_|_|_" << endl
           << "__|_|_|_|_|_|_|_| |__" << endl
           << endl;
      hitEnter();
      Clear;
      rock++;
      gameR(p->right);
    }
  }
}

// getting user input and converting to uppercase and asking question over and over until user enters correct input
string BT::inputValidiation(Node* p)
{
  // variable to store user input
  string input;

  while(true)
  {
    // asking user the question
    cout << p->question << endl
         << " - - - - - - - - - - - - - - - -" << endl
         << Italic
         << " Is this true or false? (T or F)"
         << Reset << endl;
    
    getline(cin, input);
    
    // converting user input to uppercase
    for(int i = 0; i < input.length(); i++)
      input[i] = toupper(input[i]);

    // if input was "T" then convert to "TRUE"
    if(input == "T")
      input = "TRUE";

    // if input was "F" then convert to "FALSE"
    if(input == "F")
      input = "FALSE";

    // if input is true or false, exit loop
    if(input == "TRUE" || input == "FALSE")
      break;
    // else prompt user to answer again
    else
      cout << endl
           << Red << Italic
           << "Incorrect input. Please try again."
           << Reset << endl;
  }
  cout << endl;
  return input;
}

// to print the list of nodes in the tree
void BT::print(ofstream &fout)
{
  printR(root, fout);
}

// called by print function to print the parents, lefts, and rights of the tree, helper function for print
void BT::printR(Node* p, ofstream &fout)
{
  if(p == nullptr)
    return;

  // printing the parent node
  fout << "Parent: " << p->question;

  fout << endl;
  
  // printing the left node
  fout << "Left: ";
  // if the left node is nullptr print nullptr else print the question
  if(p->left == nullptr)
    fout << "Nullptr";
  else
    fout << p->left->question;

  fout << endl;

  // if the right node is nullptr print nullptr else print the question
  fout << "Right: ";  
  if(p->right == nullptr)
    fout << "Nullptr";
  else
    fout << p->right->question;

  fout << endl << endl;
  
  printR(p->left, fout);
  printR(p->right, fout);
}

// displays game intro
void BT::display()
{
  // user welcome message (introduction)
  cout << setw(28) << " - - - - - - - - " << endl
       << setw(12) << "|" << Blink << Green
       << " Tree of Trials "
       << Reset << "|" << endl
       << setw(28) << " - - - - - - - - " << endl;
  
  cout << "       ,.,\n"
       << "       MMMM_    ,..,\n"
       << "         \"_ \"__\"MMMMM          ,...,,\n"
       << "  ,..., __.\" --\"    ,.,     _-\"MMMMMMM\n"
       << " MMMMMM\"___ \"_._   MMM\"_.\"\" _ \"\"\"\"\"\n"
       << "  \"\"\"\"    \"\" , \\_.   \"_. .\"\n"
       << "         ,., _\"__ \\__./ .\"\n"
       << "        MMM_\"  \"_    ./\n"
       << "         ''''     (    )\n"
       << "                  |    |\n"
       << "                  |    |\n"
       << "                __|____|__\n";


  hitEnter();

  cout << endl << "Make your way up the Tree of Trial and win rewards!" << endl
       << "The path you take is filled with many questions, and where you" << endl
       << "go and rewards you get all depend on your answer..." << endl
       << "Good Luck!" << endl;

  hitEnter();

  Clear;

  cout << "You enter the first room on the path and need to answer your first question!" << endl << endl;
  
  cout << Yellow;
  cout << "       _______" << endl
       << "      |* ___ *|" << endl
       << "      | | _ | |" << endl
       << "      | || || |" << endl
       << "      | || ||o|" << endl
       << "      | ||_|| |" << endl
       << "      | |___| |" << endl
       << "      |*_____*|" << endl
       << Reset
       << "     _ _ _ _ _ _" << endl
       << "   _|_|_|_|_|_| |_" << endl
       << "  |_|_|_| |_|_ _|_|_" << endl
       << "__|_|_|_ _|_|_|_| |__" << endl
       << endl;
  hitEnter();
  Clear;
}

// function to have program wait until user hits enter
void BT::hitEnter()
{
  // \x1b[3m -> itailic font , \x1b[0m -> reset font to default
  cout << endl << "Hit \""<<Blink<<Italic<<"Enter"<<Reset<<"\" to continue.";
  cin.clear();
  // ignore all characters inputted before new line
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}