#include"operateProgram.h"
using namespace std;
//debuged
void operateProgram::startProgram()
{
	cout << "& ";
	char order[30];
	int ifEndPro = 0;
	cin.getline(order, 29);
	if (strcmp(order, "endpro") == 0)
		ifEndPro = 1;
	while (ifEndPro == 0)
	{
		while (ifEndPro == 0 && strcmp(order, "c"))
		{
			cout << "& ";
			cin.getline(order, 29);
			if (strcmp(order, "endpro") == 0)
				ifEndPro = 1;
		}
		if (ifEndPro == 0)
		{
			startMyCalculator();
			cout << "& ";
			cin.getline(order, 29);
		}
		if (strcmp(order, "endpro") == 0)
			ifEndPro = 1;
	}
}
//debuged
void operateProgram::startMyCalculator()
{

	cout << "welcome to myCalulator!" << endl;
	char expression[200];
	int ifquit = 0;
	doHistory dohistory;
	while (ifquit == 0)
	{
		cout << "please input your expression:";
		cin.getline(expression, 195);
		while(expression[0]=='\0')
			cin.getline(expression, 195);
		if (strcmp(expression, "quit"))
		{
			cout << "*********************************************\n";
			Complex operateComplex;
			if (strcmp(expression, "upturning") == 0)
			{
				dohistory.upTurning();
			}
			else if (strcmp(expression, "downturning") == 0)
			{
				dohistory.downTurning();
			}
			else if (strcmp(expression, "show history") == 0)
			{
				dohistory.showLastFiveHistory();
			}
			else if (strcmp(expression, "compare complex") == 0)
			{
				operateComplex.compareComplex();
			}
			else if (strcmp(expression, "get distance") == 0)
			{
				operateComplex.dis();
			}
			else if (strcmp(expression, "get exponent")==0)
			{
				operateComplex.turnE();
			}
			else
			{
				history* newhistory=operateComplex.showAns(expression);
				if (newhistory != NULL)
				{
					dohistory.updateHistory(newhistory);
					dohistory.historyInFile();
				}
			}
			cout << "***********************************************\n";
		}
		else
			ifquit = 1;
	}
}
