#include <iostream>
#include <string> 

using namespace std;
 
int moves;

void towersOfHanoi(int n, int from, int to, int spare);

void towersOfHanoi(int n, int from, int to, int spare)
{
  if(n == 1)
    {
      //cout <<  "moving the disk from " << from << " to " << to << endl;
      moves++;
    }   
  else
    {   
      towersOfHanoi(n-1, from, spare, to);
      towersOfHanoi(1, from, to, spare);
      towersOfHanoi(n-1, spare, to, from);
    }
}

int main()
{
  moves = 0;
   towersOfHanoi(3,1,3,2);
  cout<<"moves: "<< moves <<endl;

  moves = 0;
  towersOfHanoi(5,1,3,2);
  cout<<"moves: "<< moves <<endl;

  moves = 0;
  towersOfHanoi(10,1,3,2);
  cout<<"moves: "<< moves <<endl;

  moves = 0;
  towersOfHanoi(20,1,3,2);
  cout<<"moves: "<< moves <<endl;

  moves = 0;
  towersOfHanoi(30,1,3,2);
  cout<<"moves: "<< moves <<endl;

}
