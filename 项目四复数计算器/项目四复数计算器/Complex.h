#include<cstring>
#include<string>
#include<cmath>
#include<iostream>
struct aComplex
{
	double real;
	double imag;
};
struct history
{
	char order[200];
	aComplex c;
	history * next;
	history * last;
};
class doHistory
{
	history *historyHead;
	history *nowIndex;
public:
	doHistory();
	void historyOutFile();
	void historyInFile();
	void updateHistory(history *aNewHistory);
	void upTurning();
	void downTurning();
	void showLastFiveHistory();
};

class Complex
{
public:
	void hl(char order[], int l, int r);
	bool ifLe(char orde[]);
	bool ifLegal(char order[]);
	aComplex plus(aComplex a, aComplex b);
	aComplex minus(aComplex a, aComplex b);
	aComplex multiply(aComplex a, aComplex b);
	aComplex divide(aComplex a, aComplex b);
	int getBracketNum(char order[]);
	int getRightBracketPosition(int n,char order[]);
	int getLeftBracketPosition(int n, char order[]);
	double getMode(aComplex c);
	double getArg(aComplex c);
	aComplex getPow(aComplex c, int e);
	aComplex getCjg(aComplex c);
	void turnCharactor(aComplex c,char cha[]);
	void compareComplex();
	void dis();
	void turnE();
	aComplex calculate(char order[]);
	bool calculateRight(char order[]);
	int wrongDotPlace(char order[]);
	int wrongBracketPlace(char order[]);
	int wrongModePlace(char order[]);
	int ifSimple(char order[]);
	aComplex turnComplex(char order[]);
	int getDotLeftNum(double d);
	int getDotRightNum(double d);
	void getSonCha(char cha[], int left, int right,char son[]);
	void insertStr(char cha[], int left, int right, char s[]);
	int ifExpressionSimple(char expression[]);
	history* showAns(char order[]);
	void showAComplex(aComplex c);
	void strcp(char a[], char b[]);
	void strca(char a[], char b[]);
};

