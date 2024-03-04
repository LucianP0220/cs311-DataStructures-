/************************************
Template created by Kazumi Slott
CS311
Homework on radix sort

Description of this program: 
Your name: Lucian Pate
Your programmer number: 25
Hours spent: 3-4
Any difficulties?: radixSort
************************************/

#include <iostream>
#include <fstream>

using namespace std;

const int LEN = 3; //the length of words
const int ALPHABET = 26; //total number of letters

class Node
{
  friend class LL;
private:
  string el;
  Node* next;
public:
  Node(const string& s){el = s; next = NULL;}
  string getElem() const {return el;}
};

class LL
{
private:
  Node* front;
  Node* rear;
  int num;
public:
  LL(){front = rear = NULL; num = 0;}
  ~LL();
  bool empty()const{return (front == NULL && rear == NULL && num == 0);}
  void addRear(const string& s);
  void addRear(Node* p);
  void append(const LL& other);
  void clear(){front = rear = NULL; num = 0;}
  Node* begin() const{return front;}
  Node* goToNext(Node* curr) const{return curr->next;}
  int size() const{return num;}
};

LL::~LL()
{
  cout << "destructor is called" << endl;
  Node* p = front;
  while(!empty())
    {
      front = front->next;
      delete p;
      p = front;
      if(front == NULL)
	rear = NULL;
      num--;
    }
}

//add a new node at the end of this list. The element of the new node is s.
void LL::addRear(const string& s)
{
  //This function is just like what you made in LL class from CS211.
  Node* p = new Node(s);

  if(empty())
    front = rear = p;
  else
    {
      rear->next = p;
      rear = rear->next;
    }    
  num++;
}

//Implementing this function
//add the node pointed to by p (p points to one of the nodes in all list) at the end of this list
void LL::addRear(Node* p)
{
  //Don't make a new node.

  //You need a special case when the list is empty
  if(empty())
    front = rear = p;
  else
    {
      this->rear->next = p;
      rear = rear->next;
    }

  //you don't need to place NULL in the next field of the rear node of this list.
  //don't forget to increment num
  num++;
  //Note: this function should have complexity O(1). There is no loop required. 
}

//Implement this function
//appending another linked list at the end of this linked list 
void LL::append(const LL& other)
{
  //Don't forget to update num of this list
  //close the end of this list by putting NULL in the next field of the rear node
  //Note: this function should have complexity O(1). There is no loop required
  LL* temp = new LL(other);
  this->rear = temp->front;
  temp->rear = NULL;
  rear = temp->rear;
}

void radixSort(LL& all);
void printLL(const LL& l);
void checkBuckets(const LL buckets[], int n);
void combineLists(LL& all, LL buckets[]);
void makeLL(LL& all);

int main()
{
  LL all; //holds all words
  makeLL(all); //all contains strings in the original order
  radixSort(all);
  cout << "Final result ----" << endl;
  printLL(all); //all contains strings in sorted sorter
  cout << endl;

  return 0;
}

//Implement this function
//using the radix sort algorithm to sort strings that contain lowercase letters. 
void radixSort(LL& all)
{
  Node* curr;
  int i; //used to iterate all list. i is the position.
  LL buckets[ALPHABET]; //bucket[0] is for 'a'. There are 26 buckets
  string s; //current string

  //Each slot of the buckets array is a LL object.
  for(int p = LEN - 1; p >= 0; p--) //checking each place
    {
      //To go through each string in all list, check printLL() to see how to iterate
      for(i = 0, curr = all.begin(); i < all.size(); i++, curr = all.goToNext(curr))
      {
	s = curr->getElem(); //get current string
	buckets[s[p] - 'a'].addRear(curr); 
      }
      combineLists(all,buckets);  
    }
}

//Implement this function
//combining all lists from buckets
void combineLists(LL& all, LL buckets[])
{
  all.clear();  //call clear() to reset the all list. All the nodes went to correct buckets already.
  //populate the all list by combining the lists from the buckets by calling append()
  for(int i = 0; i < ALPHABET; i++)
    {
      all.append(buckets[i]);
      i++;
      buckets[i].clear();  //reset each list in b[i] by calling clear(). All the nodes were moved to the all list already.
    }
}

//Make a linked list of words from an input file  
void makeLL(LL& all)
{
  string s;  
  fstream fin;
  fin.open("radix.in");

  fin >> s;
  while(fin)
    {
      all.addRear(s);
      fin >> s;
    }
}

//This function shows the contents of all the buckets
void checkBuckets(const LL buckets[], int n)
{
  for(int i = 0; i < n; i++)
    {
      cout << i << ": ";
      printLL(buckets[i]);
      cout << endl;
    }
}

//This function prints all the elements in l
void printLL(const LL& l)
{
  int i;
  Node* p;

  //iterate l from the first node to last node
  for (i = 0, p = l.begin(); i < l.size(); i++, p = l.goToNext(p))
    cout << p->getElem() << ' ';
}

