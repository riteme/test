#include <iostream>
#include <cstdio>
#include <stack>
#include <cctype>
#include <cstring>
using namespace std;
static int pos;
static char buf[100];
void _putchar(char c) {
    putchar(c);
    buf[pos++] = c;
}
int main()
{
	char str[1000];
	scanf("%s",str);
	int rank[256];
	rank['+'] = 1;	rank['-'] = 1;
	rank['*'] = 2;  rank['/'] = 2;

	stack<char> stk;

	for(int i = 0 ; str[i] ; i ++)
	{
		char c = str[i];
		if(isdigit(c)) _putchar(c);
		else if(c == ')')
		{
			while(stk.top() != '(')
			{
				_putchar(stk.top());
				stk.pop();
			}
			stk.pop();
		}
        else if (c == '(')
            stk.push(c);
		else
		{
			while(!stk.empty() && stk.top() != '(' && rank[stk.top()] >= rank[c])
			{
				_putchar(stk.top());
				stk.pop();
			}
			stk.push(c);
		}
	}
	while(!stk.empty())
	{
		if(stk.top() != '(')_putchar(stk.top());
		stk.pop();
	}
    printf(" %s",buf);
	return 0;
}
//8-(3+2*6)/5+4
