/*
 * Evaluates arithmetic expressions composed of 1 digit numbers
 */
#include <iostream>
#include <cstring>                                  // for strlen()

const int LEN = 80;                                 // length of expression in characters
const  int MAX = 40;                                // size of stack
class Stack
{
private:
	char st[MAX];									// stack array of chars
	int top;                                        // number of top of stack
public:
	Stack()                                         // Constructor no arguments
	{ top = 0; }
	void push(char var)                             // put char on stack
	{
		st[++top] = var;
	}
	char pop()                                      // take char off the stack
	{
		return st[top--];
	}
	int getTop()                                    // get top of stack
	{
		return top;
	}
};
class Expression                                    // class Expression
{
private:
	Stack s;                                        // stack for analysis
	char* pointerStr;                               // pointer to input string
	int length;                                     // length of input string
public:
	Expression(char* pointer)                       // constructor 1 argument
	{
		pointerStr = pointer;                       // set pointer to string
		length = strlen(pointerStr);                // set length
	}
	void parse();                                   // parse the inout string
	int solve();                                    // evaluate the stack
	
};

void Expression::parse() {                          // add items to stack
	char ch;                                        // char from input string
	char lastVal;                                   // last value
	char lastTop;                                   // last operator
	
	
	for (int i = 0; i < length ; i++) {             // for each input character
		ch = pointerStr[i];                         // get next character
		
		if (ch >='0' && ch <='9')                   // if it's a digit
		s.push(ch-'0');                             // save numerical value
													// if it's operator
		else if (ch == '+' || ch == '-' || ch =='*' || ch =='/')
		{
			if(s.getTop()==1)                       // if it's 1st operator
			s.push(ch);                             // put on stack
			else
			{
				lastVal = s.pop();                  // get previous digit
				lastTop = s.pop();                  // get previous operator
				
				// if this is * or / AND last operator was + or -
				if( (ch == '*' || ch=='/' )&& (lastTop =='+' || lastTop == '-'))
				{
					s.push(lastTop);                // restore last two pops
					s.push(lastVal);
				} else                              // in all other cases
				{
					switch(lastTop)                 // do last operation
					{
						case '+': s.push(s.pop() + lastVal);
							break;
						case '-': s.push(s.pop() - lastVal);
							break;
						case '*': s.push(s.pop() * lastVal);
							break;
						case '/': s.push(s.pop() / lastVal);
							break;
						default:
						std::cout << "\nUnknown operator";
							exit(1);
					}                               // end switch
				}                                   // end else in all other cases
				s.push(ch);                         // put current operator on stack
			}                                       // end of else, not first operator
		}                                           // end else if, it's an operator
		else { std::cout << "\nUnknow input character"; exit(1);}   // unknown character
	}                                               // end FOR loop
}                                                   // end parse()

int Expression::solve() {                           // remove items from stack
	char lastVal;                                   // previous value
	
	while (s.getTop() > 1)
	{
		lastVal = s.pop();                          // get previous value
		switch (s.pop())                            // get previous operator
		{                                           // dp operation push answer
			case '+': s.push(s.pop() + lastVal);
				break;
			case '-': s.push(s.pop() - lastVal);
				break;
			case '*': s.push(s.pop() * lastVal);
				break;
			case '/': s.push(s.pop() / lastVal);
				break;
			default:
				std::cout << "\nUnknown operator";
				exit(1);
		}                                           // end switch
	}                                               // end while
	return int(s.pop());                            // last item on stack is ans
}                                                   // end solve

int main() {
 
	char answer;                                    // y or n
	char string[LEN];                               // input string from user
	
	std::cout << "\nEnter an arithmetic expression"
	          "\nof the form 2+3*4/3-2"
	          "\nNo number may have more than one digit"
	          "\nDo not use any spaces or parentheses";
	do {
		std::cout << "\nEnter expression: ";
		std::cin >> string;                         // input from user
		Expression* expressionPtr = new Expression(string); // make expression
		expressionPtr->parse();                     // parse it
		std::cout << "\nThe numerical value is: " << expressionPtr->solve();    // solve it
		delete expressionPtr;                       // delete expression
		std::cout << "\nDo another? (y or n)?";
		std::cin >> answer;
	}while (answer == 'y');
	system("pause");
    return 0;
}