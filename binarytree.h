#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <iomanip>
using namespace std;

#define Clear cout << "\033c" // esc -> ascii

// extern used to tell compiler that the variables exist and are defined in another file
// blink
extern string Blink;
// reset
extern string Reset;
// italic
extern string Italic;
// green
extern string Green;
// yellow
extern string Yellow;
// red
extern string Red;
// blue
extern string Blue;

class BT{
  public:
  BT();
  ~BT();
  int maxReward(); // height(maximum rewards)
  void insert(string, string); // insert question and answer
  void game(); 
  void print(ofstream&);
  void display();
  void hitEnter();
  
  private:
  class Node{
    public:
    string question;
    string answer;
    Node* left;
    Node* right;
  };
  Node* root;
  int rewardCounter; // reward counter
  int gold;
  int rock;

  int maxRewardR(Node*);
  void insertR(Node*&, string, string);
  void deleteNode(Node*&);
  void gameR(Node*); // goes through nodes and traverses through them depending on the user's answer
  void printR(Node*, ofstream&); // to print tree of nodes
  string inputValidiation(Node*); // to validate user input
};