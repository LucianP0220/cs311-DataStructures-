/**********************************
Lucian Pate
#25
CS311
homework
***********************************/

#include<iostream>
#include<string>
#include"stack_L_T.h"
using namespace std;

//prototypes
bool isOperand(char ch);
bool isOperator(char ch);
int priorityOperator(char ch);
int charToInt(char ch);
double doMath(double opr1, char opt, double opr2);
template<class T>
string convert(Stack<T>& s, string& inExpr);
double evaluate(string& postExpr); 

int main()
{
  Stack<char> s;
  string inExpr = "";
  string postExpr = "";
try
  {
    cin>> inExpr;
    postExpr = convert(s,inExpr);
    cout<< postExpr<<endl;
    evaluate(postExpr);
    
  }

 catch(Stack<int>::Underflow)
   {
     cout<< "Error:Stack is Empty";
   }
 
 catch(const char* msg)
   {
     cout<< msg <<endl;
   }

 return 0;
}

template<class T>
string convert(Stack<T>& s, string& inExpr)
{

  string postfix ="";

  for(int i = 0; i < inExpr.length(); ++i)
    {
      if(!isOperator(inExpr[i]) && !isOperand(inExpr[i]))  
	{
	  throw "The expression is in a wrong format";
	}
      else if(isOperator( inExpr[i] ))
	{
	  s.push(inExpr[i]);
	}
      else if( inExpr[i] == '(' )
	{
	  s.push(inExpr[i]);
	}
      else if( inExpr[i] == ')' )
	{
	  for(int j = i; j != '('; --j)
	    {
	      if( isOperator(inExpr[j]) )
		{
		  s.pop();
		  postfix += inExpr[j] ;
		}
	      else if(inExpr[j] == '(' || inExpr[j] == ')')
		{
		  s.pop();
		}
	    } 
	}
      else  
	{
	  postfix += inExpr[i];
	}
    }
  return postfix; 
}

double evaluate(string& postExpr)
{
  Stack<double> s;
  char opt;
  double opr1, opr2;//2 operands
  
  double result, finalResult;
  for(int i = 0; i < postExpr.length(); i++)
    {
      opt = postExpr[i];
      if(isOperand(opt))//if operand
	s.push(charToInt(opt));
      else if(isOperator(opt))//if operator
	{
	  opr1 = s.getTop();//pop right
	  s.pop();
	  opr2 = s.getTop();//pop left
	  s.pop();
	  result = doMath(opr2, opt, opr1);
	  s.push(result);
	}
      else
	throw "The expression is in a wrong format";
    }
  
  if(!s.empty())
    {
      finalResult = s.getTop();
      s.pop();
    
      if(!s.empty())
	throw "The expression is in a wrong format.";
      else
	return finalResult;
    }
  else
    throw "The expression is in a wrong format";
}

/*******************************************
This function returns the result of opr1 opt and opr2

opr1 is an integer
opt is character
opr2 is an integer
*******************************************/
double doMath(double opr1, char opt, double opr2)
{
  switch(opt)
    {
    case '+':
      return (opr1 + opr2);
      break;
    case'-':
      return (opr1 - opr2);
      break;
    case'*':
      return (opr1 * opr2);
      break;
    case'/':
      return (opr1 / opr2);
      break;
    }
}

/***********************************************
This function converts a char to an integer

ch is a character
***********************************************/
int charToInt(char ch)
{
  return (ch - 48);
}

/*******************************************
This function checks the operator and assigns a priority number

ch is a character
************************************************************************/
int priorityOperator(char ch)
{
  if( ch == '+' or ch == '-') 
    return 1;
  else if ( ch == '*' or ch == '/') 
    return 2;
   
} 
/*******************************************
This function checks to see if the passed character is an operand
It returns true if it is one of the operand, otherwise returns false.

ch is a character
************************************************************************/
bool isOperand(char ch)
{
  if(ch >= '0' && ch <= '9')
    return true;
  else
    return false;
}

/********************************************
This function checks to see if character is an operator
returns true if it is, otherwise false

ch is a character
******************************************/
bool isOperator(char ch)
{
  if(ch =='+' || ch =='-' || ch =='*' || ch =='/')
    return true;
  else
    return false;
}
