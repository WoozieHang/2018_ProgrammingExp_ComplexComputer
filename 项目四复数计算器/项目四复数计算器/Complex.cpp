
#include"Complex.h"
using namespace std;
//debuged
void Complex::hl(char order[], int l, int r)
{
	cout << order;
	cout << endl;
	for (int i = 0; i < r; i++)
	{
		if (i > l)
			cout << "-";
		else cout << " ";
	}
	cout << endl;
}
void Complex::strcp(char a[], char b[])
{
	int i;
	for (i = 0; b[i] != '\0'; i++)
		a[i] = b[i];
	a[i] = '\0';
}
//debuged
void Complex::strca(char a[], char b[])
{
	int i = 0;
	while (a[i] != '\0')
		i++;
	for (int j = 0; b[j] != '\0'; j++)
	{
		a[i] = b[j];
		i++;
	}
	a[i] = '\0';
}
//debuged
int Complex::wrongModePlace(char order[])
{
	int num = 0;
	int i = 0;
	for (i = 0; order[i] != '\0'; i++)
	{
	
		if (order[i] == '|')
		{
			num++;
		}
		
	}
	if (num % 2 == 1)
	{
		while (order[i] != '|')
			i--;
		return i;
	}
	else return -1;
	
}
int Complex::wrongBracketPlace(char order[])
{
	for (int i = 0; order[i] != '\0'; i++)
	{
		if (order[i] == '(')
		{
			int r = 0;
			for (int j = i +1 ; order[j] != '\0'&&r < 1; j++)
			{
				if (order[j] == '(')
					r--;
				else if (order[j] == ')')
					r++;
			}
			if (r != 1)
				return i;
		}
		else if (order[i] == ')')
		{
			int l = 0;
			for (int j = i - 1; j>=0&&l< 1; j--)
			{
				if (order[j] == ')')
					l--;
				else if (order[j] == '(')
					l++;
			}
			if (l!= 1)
				return i;
		}
	}
	return -1;
}
bool Complex::ifLe(char orde[])
{
	char order[200];
	strcp(order, orde);
	bool Legal = 1;
	if (wrongDotPlace(order))
	{
	
		return 0;
	}
	if (getBracketNum(order) == -1)
	{
		
		return 0;
	}
	if (wrongModePlace(order) != -1)
	{
		return 0;
	}
	//判断开头
	char headChar = order[0];
	if ((headChar<'0' || headChar>'9') && headChar != 'i'&&headChar != '-'&&headChar != '|'&&headChar != '(')
	{
		if (strlen(order) > 4 && ((order[0] == 'a' && order[1] == 'r' &&order[2] == 'g' &&order[3] != '(') || (order[0] == 'c'&& order[1] == 'j' && order[2] == 'g' && order[3] == '(')))
			;
		else
		{
			return 0;
		}
	}

	//判断结尾
	int i = 0;
	int absNum = 0;
	for (; order[i] != '\0'; i++)
	{
	}
	i--;
	if ((order[i]<'0' || order[i]>'9') && order[i] != 'i'&&order[i] != '|'&&order[i] != ')')
	{
		
		return 0;
	}

	//判断中间部分字符细节
	for (i = 0; order[i] != '\0'; i++)
	{

		if (order[i] == '|')
			absNum++;
		//判断加减乘除
		if (order[i] == '+' || order[i] == '-' || order[i] == '*' || order[i] == '/')
		{
			//除号后为0如何处理？
			if ((order[i + 1]<'0' || order[i + 1]>'9') && order[i + 1] != 'i'&&order[i + 1] != '|'&&order[i + 1] != '(')
			{
				if (order[i + 1] != '\0'&&order[i + 2] != '\0'&&order[i + 3] != '\0'&&order[i + 4] != '\0')
				{
					if ((order[i + 1] != 'a' || order[i + 2] != 'r' || order[i + 3] != 'g' || order[i + 4] != '(') && (order[i + 1] != 'c' || order[i + 2] != 'j' || order[i + 3] != 'g' || order[i + 4] != '('))
					{
						
						return 0;
					}
				}
				else
				{
					
					return 0;
				}
			}
			else if (order[i + 1] == '|'&&absNum % 2 == 1)
			{
				
				return 0;
			}
			else if (order[i] == '/'&&order[i + 1] == '(')
			{
				int r = 0;
				for (int j = i + 2; r != 1; j++)
				{
					if (order[j] == '(')
						r--;
					else if (order[j] == ')')
						r++;
				}
				char so[40];
				getSonCha(order, i, r, so);
				if (ifLe(so) && calculateRight(so))
				{
					if (calculate(so).real == 0 && calculate(so).imag == 0)
					{
						return 0;
					}
				}
			}
		}
		else if (order[i] == '^')
		{
			int ll = i;
			int rr = i + 1;
			if (order[rr] == '(')
			{
				rr++;
				int rb = 0;
				while (rb != 1)
				{
					if (order[rr] == '(')
						rb--;
					else if (order[rr] == ')')
						rb++;
					rr++;
				}
			}
			else
			{
				while ((order[rr] >= '0'&&order[rr] <= '9') || order[rr] == '.')
					rr++;
			}
			char soo[40];
			getSonCha(order, ll, rr, soo);
			aComplex t = turnComplex(soo);
			if (t.imag - 0 > 0.00000001 || t.real - (int)t.real > 0.00000001)
			{
				return 0;
			}
		}
		//判断实数后
		if (order[i] >= '0'&&order[i] <= '9')
		{

			if ((order[i + 1]<'0'||order[i + 1]>'9')&&order[i + 1] != '.'&&order[i + 1] != '\0'&&order[i + 1] != '|'&&order[i + 1] != ')'&&order[i + 1] != '+'&&order[i + 1] != '-'&&order[i + 1] != '*'&&order[i + 1] != '/'&&order[i + 1] != 'i')
			{
				
					return 0;
				

			}
			else if (order[i + 1] == '|'&&absNum % 2 == 0)
			{
				
				return 0;
			}
		}
		//判断i的前后
		if (order[i] == 'i')
		{
			//i前
			if (i != 0 && order[i - 1] != '|'&&order[i - 1] != '+'&&order[i - 1] != '-'&&order[i - 1] != '*'&&order[i - 1] != '/' && (order[i - 1]<'0' || order[i - 1]>'9') && order[i - 1] != ')'&&order[i-1]!='(')
			{
				
				return 0;
			}
			//括号内是否是实数,注意对于ajg,直接括号内无所谓是不是实数，添加一个*即可
			if (order[i - 1] == ')')
			{
				int laji = 0;
				int r = i - 1;
				int l = i - 2;
				while (laji != 1 && l >= 0)
				{
					if (order[l] == '(')
						laji++;
					else if (order[l] == ')')
						laji--;
					l--;
				}
				if (laji != 1)
				{
					
					return 0;
				}
				else if (l >= 2 && order[l - 2] == 'a'&&order[l - 1] == 'r'&&order[l] == 'g')
				{
					char ccc[10] = "*";
					insertStr(order, i - 1, i, ccc);
					i++;
				}
				else
				{
					if (order[l] == 'g')
					{
						l -= 3;
						r++;
					}
					else
					{
						l++;
					}
					char son[50];
					getSonCha(order, l, r, son);
					if (ifLe(son) == 0)
					{
						return 0;
					}
					else if (calculateRight(son) == 1)
					{
						aComplex c;
						c = calculate(son);
						if (c.imag - 0 > 0.000000001)
						{
							return 0;
						}
						else
						{
							char ccc[10] = "*";
							insertStr(order, i - 1, i, ccc);
							i++;
						}
					}
					else
					{
						
						return 0;
					}
				}
			}
			//i后
			if (order[i + 1] != '\0'&&order[i + 1] != ')'&&order[i + 1] != '+'&&order[i + 1] != '-'&&order[i + 1] != '*'&&order[i + 1] != '/'&&order[i + 1] != '^')
			{
				if (order[i + 1] != '|' || absNum % 2 == 0)
				{
					
					return 0;
				}
			}
		}
		//判断左括号
		if (order[i] == '(')
		{
			if (order[i + 1] != '('&&(order[i + 1]<'0'||order[i + 1]>'9')&&order[i + 1] != 'i')
			{

				
				return 0;
			}

		}
		//判断右括号
		if (order[i] == ')')
		{
			if (order[i + 1] != '\0'&&order[i + 1] != 'i'&&order[i + 1] != '+'&&order[i + 1] != '-'&&order[i + 1] != '*'&&order[i + 1] != '/'&&order[i + 1] != ')')
			{
				if (order[i + 2] != '\0'&&order[i + 1] == '^' && (order[i + 2] == '(' || (order[i + 2] >= '0'&&order[i + 2] <= '9')))
					;
				else if (order[i + 1] = '|'&&absNum % 2 == 1)
					;
				else
				{
					
					return 0;
				}
			}
		}
		//判断小数点
		if (order[i] == '.')
		{
			if (order[i - 1]<'0' || order[i - 1]>'9' || order[i + 1]<'0' || order[i + 1]>'9')
			{

				
				return 0;
			}
		}
		//判断^后
		if (order[i] == '^')
		{
			if (order[i + 1] != '(' && (order[i + 1]<'0' || order[i + 1]>'9'))
			{
			
				return 0;
			}
		}
	}
	return 1;
}
bool Complex::ifLegal(char order[])
{
	bool Legal = 1;
	if (wrongDotPlace(order))
	{
		int w = wrongDotPlace(order);
		int k = 0;
		int p= 0;
		for (int k = 0; k < w; p++)
		{
			if (order[p] == '.')
				k++;
		}
		hl(order, p - 2, p);
		cout << "error: the usage of dot is wrong!" << endl;
		return 0;
	}
	if (getBracketNum(order) == -1)
	{
		int n = wrongBracketPlace(order);
		if (n == -1)
			cout << "program is wrong"<<endl;
		else hl(order, n - 1, n + 1);
		cout << "error: the bracket dismatched" << endl;
		return 0;
	}
	if (wrongModePlace(order) != -1)
	{
		int p = wrongModePlace(order);
		hl(order, p - 1, p + 1);
		cout << "error: Mode dismatch"<<endl;
		return 0;
	}
		//判断开头
	char headChar = order[0];
	if ((headChar<'0'||headChar>'9')&&headChar != 'i'&&headChar != '-'&&headChar != '|'&&headChar != '(')
	{
		if (strlen(order) > 4 && ((order[0] == 'a' && order[1] == 'r' &&order[2] == 'g' &&order[3]== '(') || (order[0] == 'c'&& order[1] == 'j' && order[2] == 'g' && order[3] == '(')))
			;
		else
		{	hl(order, -1, 1);
			cout << "error: the head of the expression is wrong" << endl;
			return 0;
		}
	}

	//判断结尾
	int i = 0;
	int absNum = 0;
	for (; order[i] != '\0'; i++)
	{
	}
	i--;
	if ((order[i]<'0'||order[i]>'9')&&order[i] != 'i'&&order[i] != '|'&&order[i] != ')')
	{
		hl(order, i - 1, i + 1);
		cout << "error: the end of the expression is wrong"<<endl;
		return 0;
	}

	//判断中间部分字符细节
	for (i = 0; order[i] != '\0'; i++)
	{
		
		if (order[i] == '|')
			absNum++;
		//判断加减乘除
		if (order[i] == '+' || order[i] == '-' || order[i] == '*' || order[i] == '/')
		{
			//除号后为0如何处理？
			if ((order[i + 1]<'0'||order[i + 1]>'9')&&order[i + 1] != 'i'&&order[i + 1] != '|'&&order[i + 1] != '(')
			{
				if (order[i + 1] != '\0'&&order[i + 2] != '\0'&&order[i + 3] != '\0'&&order[i + 4] != '\0')
				{
					if ((order[i + 1] != 'a' || order[i + 2] != 'r' || order[i + 3] != 'g' || order[i + 4] != '(') && (order[i + 1] != 'c' || order[i + 2] != 'j' || order[i + 3] != 'g' || order[i + 4] != '('))
					{
						hl(order, i - 1, i + 1);
						cout << "error: the usage of "<<order[i]<<" is wrong" << endl;
						return 0;
					}
				}
				else
				{
					hl(order, i - 1, i + 1);
					cout << "error: the usage of" << order[i] << "is wrong" << endl;
					return 0;
				}
			}
			else if (order[i + 1] == '|'&&absNum % 2 == 1)
			{
				hl(order, i, i + 2);
				cout << "error: the left of this model can not be +,-,*,/" << endl;
				return 0;
			}
			else if (order[i]=='/')
			{
				if (order[i + 1] == '(')
				{
					int r = 0;
					int j;
					for (j = i + 2; r != 1; j++)
					{
						if (order[j] == '(')
							r--;
						else if (order[j] == ')')
							r++;
					}
					char so[40];
					getSonCha(order, i, j, so);
					if (ifLe(so) && calculateRight(so))
					{
						if (calculate(so).real == 0 && calculate(so).imag == 0)
						{
							hl(order, i, j);
							cout << "error: the right of / can not be zero" << endl;
							return 0;
						}
					}
				}
				else
				{
					int j;
					for (j = i + 1;(order[j]>='0'&&order[j]<='9')||order[j]=='.'; j++)
					{
					}
					char so[40];
					getSonCha(order, i, j, so);
					if (ifLe(so) && calculateRight(so))
					{
						if (calculate(so).real == 0 && calculate(so).imag == 0)
						{
							hl(order, i, j);
							cout << "error: the right of / can not be zero" << endl;
							return 0;
						}
					}
				}
			}
		}
		else if (order[i] == '^')
		{
			int ll = i;
			int rr = i + 1;
			if (order[rr] == '(')
			{
				rr++;
				int rb = 0;
				while (rb!=1)
				{
					if (order[rr] == '(')
						rb--;
					else if (order[rr] == ')')
						rb++;
					rr++;
				}
			}
			else 
			{
				while ((order[rr] >= '0'&&order[rr] <= '9') || order[rr] == '.')
					rr++;
			}
			char soo[40];
			getSonCha(order, ll, rr, soo);
			aComplex t = calculate(soo);
			if (t.imag - 0 > 0.00000001 || t.real - (int)t.real > 0.00000001)
			{
				hl(order, i - 1, i + 1);
				cout << "error: the right of ^ is not a integer"<<endl;
				return 0;
			}
		}
		//判断实数后
		if (order[i] >= '0'&&order[i] <= '9')
		{

			if ((order[i+1]<'0'||order[i + 1]>'9')&&order[i+1]!='.'&&order[i + 1] != '\0'&&order[i + 1] != '|'&&order[i + 1] != ')'&&order[i + 1] != '+'&&order[i + 1] != '-'&&order[i + 1] != '*'&&order[i + 1] != '/'&&order[i + 1] != 'i')
			{
				if (order[i + 2] != '\0')
				{
					if (order[i + 1] != '^' || (order[i + 2] != '('&&order[i+2]<'0'&&order[i+2]>'9') )
					{
						hl(order, i - 1, i + 1);
						cout << "error: the right of the number is wrong"<< endl;
						return 0;
					}
				}
				else
				{
					hl(order, i - 1, i + 1);
					cout << "error: the right of the number is wrong" << endl;
					return 0;
				}
				
			}
			else if (order[i + 1] == '|'&&absNum % 2 == 0)
			{
				hl(order, i, i + 2);
				cout << "error: the left of this model can not be number" << endl;
				return 0;
			}
		}
		//判断i的前后
		if (order[i] == 'i')
		{
			//i前
			if (i != 0 && order[i - 1] != '|'&&order[i - 1] != '+'&&order[i - 1] != '-'&&order[i - 1] != '*'&&order[i - 1] != '/'&&(order[i - 1]<'0'||order[i - 1]>'9')&&order[i - 1] != ')'&&order[i-1]!='(')
			{
				hl(order, i - 1, i + 1);
				
				cout << "error: the left of i is wrong"<< endl;
				return 0;
			}
			//括号内是否是实数,注意对于ajg,直接括号内无所谓是不是实数，添加一个*即可
			if (order[i - 1] == ')')
			{
				int laji = 0;
				int r = i-1;
				int l = i - 2;
				while (laji!=1&&l>=0)
				{
					if (order[l] == '(')
						laji++;
					else if (order[l] == ')')
						laji--;
					l--;
				}
				if (laji!=1)
				{
					hl(order, r - 1, r + 1);
					cout << "error: bracket dismatch" << endl;
					return 0;
				}
				else if (l >= 2 && order[l - 2] == 'a'&&order[l - 1] == 'r'&&order[l] == 'g')
				{
					char ccc[10] = "*";
					insertStr(order, i - 1, i, ccc);
					i++;
				}
				else
				{
					if (order[l] == 'g')
					{
						l -= 3;
						r++;
					}
					else
					{
						l++;
					}
					char son[50];
					getSonCha(order, l, r, son);
					if (ifLe(son) == 0)
					{
						hl(order, i - 1, i + 1);
						cout << "err: the left of i is wrong" << endl;
						return 0;
					}
					else if (calculateRight(son) == 1)
					{
						aComplex c;
						c = calculate(son);
						if (c.imag - 0 > 0.000000001||c.imag-0<-0.0000000001)
						{
							hl(order, l, r);
							cout << "error: the left of i must be a real number!" << endl;
							return 0;
						}
						else
						{
							char ccc[10] = "*";
							insertStr(order, i - 1, i, ccc);
							i++;
						}
					}
					else
					{
						hl(order, i - 1, i + 1);
						cout << "error: the left of i is wrong";
						return 0;
					}
				}
			}
			//i后
			if (order[i + 1] != '\0'&&order[i + 1] != ')'&&order[i + 1] != '+'&&order[i + 1] != '-'&&order[i + 1] != '*'&&order[i + 1] != '/'&&order[i+1]!='^')
			{
				if (order[i + 1] != '|' || absNum % 2 == 0)
				{
					hl(order, i - 1, i + 1);
					cout << "error: the right of i is wrong" << endl;
					return 0;
				}
			}
		}
		//判断左括号
		if (order[i] == '(')
		{
			if (order[i + 1] != '('&&(order[i + 1]<'0'||order[i + 1]>'9')&&order[i + 1] != 'i'&&order[i+1]!='-')
			{
					
						hl(order, i - 1, i + 1);
						cout << "the right of ( is wrong" << endl;
						return 0;
			}

		}
		//判断右括号
		if (order[i] == ')')
		{
			if (order[i + 1] != '\0'&&order[i + 1] != 'i'&&order[i + 1] != '+'&&order[i + 1] != '-'&&order[i + 1] != '*'&&order[i + 1] != '/'&&order[i + 1] != ')')
			{
				if (order[i + 2] != '\0'&&order[i + 1] == '^' && (order[i + 2] == '(' || (order[i + 2] >= '0'&&order[i + 2] <= '9')))
					;
				else if (order[i + 1]== '|'&&absNum % 2 == 1)
					;
				else
				{
					hl(order, i - 1, i + 1);
					cout << "error: the right of ( is wrong" << endl;
					return 0;
				}
			}
		}
		//判断小数点
		if (order[i] == '.')
		{
			if (order[i - 1]<'0' || order[i - 1]>'9' || order[i + 1]<'0' || order[i + 1]>'9')
			{

				hl(order, i - 1, i + 1);
				cout << "error: the wrong usage in dot"<< endl;
				return 0;
			}
		}
		//判断^后
		if (order[i] == '^')
		{
			if (order[i + 1] != '(' && (order[i + 1]<'0' || order[i + 1]>'9'))
			{
				hl(order, i - 1, i + 1);
				cout << "error: the right of ^ is wrong"<< endl;
				return 0;
			}
		}
	}
	return 1;
}
//debuged
aComplex Complex::plus(aComplex a, aComplex b)
{ 
	a.real += b.real;
	a.imag += b.imag;
	return a;
}
//debuged
aComplex Complex::minus(aComplex a, aComplex b)
{
	a.real -= b.real;
	a.imag -= b.imag;
	return a;
}
//debuged
aComplex Complex::multiply(aComplex a, aComplex b)
{
	aComplex c;
	c.real = a.real*b.real - a.imag*b.imag;
	c.imag = a.real*b.imag + a.imag*b.real;
	return c;
}
//debuged
aComplex Complex::divide(aComplex a, aComplex b)
{
	aComplex c;
	c.real = (a.real*b.real + a.imag*b.imag) / (b.real*b.real + b.imag*b.imag);
	c.imag = (a.imag*b.real - a.real*b.imag) / (b.real*b.real + b.imag*b.imag);
	return c;
}
//debuged
int Complex::getBracketNum(char order[])
{
	int left = 0;
	int right = 0;
	for (int index = 0; order[index] != '\0'; index++)
	{
		if (order[index] == '(')
			left++;
		else if (order[index] == ')')
			right++;
	}
	if (left == right)
		return left;
	else
	{
		
		return -1;
	}
}
//debuged
int Complex::getRightBracketPosition(int n,char order[])
{
	int right = 0;
	int i = 0;
	while (right < n)
	{
		if (order[i] == ')')
			right++;
		i++;
	}
	i--;
	return i;
}
//debuged
int Complex::getLeftBracketPosition(int n, char order[])
{
	int i = getRightBracketPosition(n, order);
	int j = i - 1;
	int left = 0;
	while (left!=1&&j>=0)
	{
		if (order[j] == '(')
			left++;
		else if (order[j] == ')')
			left--;
		j--;
	}
	j++;
	if (left !=1)
		return -1;
	else return j;
}
//debuged
double Complex::getMode(aComplex c)
{
	return pow((c.real*c.real + c.imag*c.imag),0.5);
}
//debuged
double Complex::getArg(aComplex c)
{
	return atan(c.imag / c.real);
}
aComplex Complex::getPow(aComplex c, int e)
{
	aComplex d;
	d.real = 1;
	d.imag = 0;
	//d==1
	if (e == 0)
	{
		
		return d;
	}
	else if (e == 1)
	{
		return c;
	}
	else if (e == -1)
	{
		return divide(d, c);
	}
	else if (e > 0)
	{
		return multiply(c, getPow(c, e - 1));
	}
	else
	{

		return multiply(getPow(c,-1), getPow(c,e+1));
	}
}
//debuged
aComplex Complex::getCjg(aComplex c)
{
	c.imag *= -1;
	return c;
}
//debuged
void Complex::compareComplex()
{
	cout << "please put in the first complex";
	char first[30];
	cin >> first;
	cout << "please put in the second complex:";
	char second[30];
	cin >> second;
	aComplex a;
	aComplex b;
	if (ifLegal(first) && calculateRight(first) && ifLegal(second) && calculateRight(second))
	{
		a = calculate(first);
		b = calculate(second);

		if (getMode(a) > getMode(b))
		{
			cout << "the mode of first one is bigger" << endl;
		}
		else if (getMode(a) < getMode(b))
		{
			cout << "the mode of second one is bigger" << endl;
		}
		else
		{
			cout << "equal" << endl;
		}
	}
}
//debuged
void Complex::dis()
{
	cout << "please put int the first complex:";
	char first[30];
	cin >> first;
	cout << "please put int the second complex:";
	char second[30];
	cin >> second;
	aComplex a;
	aComplex b;
	if (ifLegal(first) && calculateRight(first) && ifLegal(second) && calculateRight(second))
	{
		a = calculate(first);
		b = calculate(second);
		a.real = pow(((a.real - b.real)*(a.real - b.real) + (a.imag - b.imag)*(a.imag - b.imag)), 0.5);
		a.imag = 0;
		cout << "the distance:";
		showAComplex(a);
	}
}
void Complex::turnE()
{
	cout << "please put int the complex:";
	char s[30];
	cin >> s;
	aComplex a;
	if (ifLegal(s) && calculateRight(s))
	{
		a = calculate(s);
		cout << getMode(a) << "*e^(" << getArg(a) << "i)" << endl;
	}
}
//debuged
int Complex::ifSimple(char order[])//返回值  0：不是最简形式 1：a 2：-a 3：bi 4：-bi 5：a+bi 6：a-bi 7:-a+bi 8:-a-bi 9:i 10:-i 11:a+i 12:a-i  13:-a+i 14-a-i 
{	
	int i = 0;
	if((order[0] >= '0'&&order[0] <= '9')||(order[i]=='.'))
	{
		i++;
		while ((order[i] >= '0'&&order[i] <= '9') || (order[i] == '.'))
			i++;
		if (order[i] == '\0')
			return 1;
		else if (order[i] == 'i'&&order[i + 1] == '\0')
			return 3;
		else if (order[i] == '+')
		{
			i++;
			if (order[i] == 'i'&&order[i + 1] == '\0')
				return 11;
			if ((order[i] >= '0'&&order[i] <= '9') || (order[i] == '.'))
			{
				i++;
				while ((order[i] >= '0'&&order[i] <= '9') || (order[i] == '.'))
					i++;
				if (order[i] == 'i'&&order[i + 1] == '\0')
					return 5;
				else return 0;
			}
			else return 0;
		}
		else if (order[i] == '-')
		{
			i++;
			if (order[i] == 'i'&&order[i + 1] == '\0')
				return 12;
			else if ((order[i] >= '0'&&order[i] <= '9') || (order[i] == '.'))
			{
				i++;
				while ((order[i] >= '0'&&order[i] <= '9') || (order[i] == '.'))
					i++;
				if (order[i] == 'i'&&order[i + 1] == '\0')
					return 6;
				else return 0;
			}
			else return 0;
		}
		else return 0;
	}
	else if (order[0] == '-')
	{
		i++;
		if (order[i] == 'i'&&order[i + 1] == '\0')
			return 10;
		else if ((order[i] >= '0'&&order[i] <= '9') || (order[i] == '.'))
		{
			i++;
			while ((order[i] >= '0'&&order[i] <= '9') || (order[i] == '.'))
				i++;
			if (order[i] == '\0')
				return 2;
			else if (order[i] == 'i'&&order[i + 1] == '\0')
				return 4;
			else if (order[i] == '-')
			{
				i++;
				if (order[i] == 'i'&&order[i + 1] == '\0')
					return 14;
				else if ((order[i] >= '0'&&order[i] <= '9') || (order[i] == '.'))
				{
					i++;
					while ((order[i] >= '0'&&order[i] <= '9') || (order[i] == '.'))
						i++;
					if (order[i] == 'i'&&order[i + 1] == '\0')
						return 8;
					else return 0;
				}
				else return 0;
			}
			else if (order[i] == '+')
			{
				i++;
				if (order[i] == 'i'&&order[i + 1] == '\0')
					return 13;
				else if ((order[i] >= '0'&&order[i] <= '9') || (order[i] == '.'))
				{
					i++;
					while ((order[i] >= '0'&&order[i] <= '9') || (order[i] == '.'))
						i++;
					if (order[i] == 'i'&&order[i + 1] == '\0')
						return 7;
					else return 0;
				}
				else return 0;
			}
			else return 0;
		}
		else return 0;
	}
	else if (order[0] == 'i'&&order[1] == '\0')
		return 9;
	else return 0;
}
//debuged
int Complex::wrongDotPlace(char order[])//返回错误的小数点的位置（第几个小数点），正确返回0
{
	char a[200];
	int j = 0;
	for (int i = 0; order[i] != '\0'; i++)
	{
		if (order[i]<'0'||order[i]>'9')
		{
			a[j] = order[i];
			j++;
		}
	}
	a[j] = '\0';
	int d = 0;
	for (int i = 0;a[i]!='\0'; i++)
	{
		if (a[i] == '.')
			d++;
		if (a[i] == '.'&&a[i + 1] == '.')
		{
			return d;
		}
	}
	return 0;
}
//debuged
aComplex Complex::turnComplex(char order[])
{
	aComplex c;
	c.imag = 0;
	c.real = 0;
	// 1：a 2：-a 3：bi 4：-bi 5：a+bi 6：a-bi 7:-a+bi 8:-a-bi 9:i 10:-i 11:a+i 12:a-i  13:-a+i 14-a-i
	int f = ifSimple(order);
	if (f == 1)
	{//a
		c.real = order[0]-'0';
		int i = 1;
		while (order[i] != '\0'&&order[i] != '.')
		{
			c.real *= 10;
			c.real += order[i] - '0';
			i++;
		}
		if (order[i] == '\0')
			return c;
		else
		{
			double s = 0;
			while (order[i] != '\0')
				i++;
			i--;
			while (order[i] != '.')
			{
				s /= 10;
				s += order[i] - '0';
				i--;
			}
			s /= 10;
			c.real += s;
			return c;
		}
	}
	else if (f == 2)
	{//-a
		c.real = order[1] - '0';
		int i = 2;
		while (order[i] != '\0'&&order[i] != '.')
		{
			c.real *= 10;
			c.real += order[i] - '0';
			i++;
		}
		
		if (order[i] == '\0')
		{
			c.real *= -1;
			return c;
		}
		else
		{
			double s = 0;
			while (order[i] != '\0')
				i++;
			i--;
			while (order[i] != '.')
			{
				s /= 10;
				s += order[i] - '0';
				i--;
			}
			s /= 10;
			c.real += s;
			c.real *= -1;
			return c;
		}
	}
	else if (f == 3)
	{//bi
		c.imag = order[0] - '0';
		int i = 1;
		while (order[i] != 'i'&&order[i] != '.')
		{
			c.imag *= 10;
			c.imag += order[i] - '0';
			i++;
		}
		if (order[i] == 'i')
			return c;
		else
		{
			double s = 0;
			while (order[i] != 'i')
				i++;
			i--;
			while (order[i] != '.')
			{
				s /= 10;
				s += order[i] - '0';
				i--;
			}
			s /= 10;
			c.imag += s;
			return c;
		}
	}
	else if (f == 4)
	{//-bi
		c.imag = order[1] - '0';
		int i = 2;
		while (order[i] != 'i'&&order[i] != '.')
		{
			c.imag *= 10;
			c.imag += order[i] - '0';
			i++;
		}
		if (order[i] == 'i')
		{
			c.imag *= -1;
			return c;
		}
		else
		{
			double s = 0;
			while (order[i] != 'i')
				i++;
			i--;
			while (order[i] != '.')
			{
				s /= 10;
				s += order[i] - '0';
				i--;
			}
			s /= 10;
			c.imag += s;
			c.imag *= -1;
			return c;
		}
	}
	else if (f == 5)
	{
		//a + bi 
		c.real = order[0]-'0';
		int i = 1;
		while (order[i] != '+'&&order[i] != '.')
		{
			c.real *= 10;
			c.real += order[i] - '0';
			i++;
		}
		if (order[i] == '.')
		{
			double s = 0;
			while (order[i] != '+')
				i++;
			i--;
			while (order[i] != '.')
			{
				s /= 10;
				s += order[i] - '0';
				i--;
			}
			s /= 10;
			c.real += s;
		}
		while (order[i] != '+')
			i++;
		i++;
		c.imag = order[i]-'0';
		i++;
		while (order[i] != 'i'&&order[i] != '.')
		{
			c.imag *= 10;
			c.imag += order[i] - '0';
			i++;
		}
		if (order[i] == 'i')
			return c;
		else
		{
			double s = 0;
			while (order[i] != 'i')
				i++;
			i--;
			while (order[i] != '.')
			{
				s /= 10;
				s += order[i] - '0';
				i--;
			}
			s /= 10;
			c.imag += s;
			return c;
		}
	}
	else if (f == 6)
	{
		//a - bi 
		c.real = order[0] - '0';
		int i = 1;
		while (order[i] != '-'&&order[i] != '.')
		{
			c.real *= 10;
			c.real += order[i] - '0';
			i++;
		}
		if (order[i] == '.')
		{
			double s = 0;
			while (order[i] != '-')
				i++;
			i--;
			while (order[i] != '.')
			{
				s /= 10;
				s += order[i] - '0';
				i--;
			}
			s /= 10;
			c.real += s;
		}
		while (order[i] != '-')
			i++;
		i++;
		c.imag = order[i]-'0';
		i++;
		while (order[i] != 'i'&&order[i] != '.')
		{
			c.imag *= 10;
			c.imag += order[i] - '0';
			i++;
		}
		if (order[i] == 'i')
		{
			c.imag *= -1;
			return c;
		}
		else
		{
			double s = 0;
			while (order[i] != 'i')
				i++;
			i--;
			while (order[i] != '.')
			{
				s /= 10;
				s += order[i] - '0';
				i--;
			}
			s /= 10;
			c.imag += s;
			c.imag *= -1;
			return c;
		}
	}
	else if (f == 7)
	{
		//-a + bi 
		c.real = order[1] - '0';
		int i = 2;
		while (order[i] != '+'&&order[i] != '.')
		{
			c.real *= 10;
			c.real += order[i] - '0';
			i++;
		}
		if (order[i] == '.')
		{
			double s = 0;
			while (order[i] != '+')
				i++;
			i--;
			while (order[i] != '.')
			{
				s /= 10;
				s += order[i] - '0';
				i--;
			}
			s /= 10;
			c.real += s;
		}
		c.real *= -1;
		while (order[i] != '+')
			i++;
		i++;
		c.imag = order[i]-'0';
		i++;
		while (order[i] != 'i'&&order[i] != '.')
		{
			c.imag *= 10;
			c.imag += order[i] - '0';
			i++;
		}
		if (order[i] == 'i')
			return c;
		else
		{
			double s = 0;
			while (order[i] != 'i')
				i++;
			i--;
			while (order[i] != '.')
			{
				s /= 10;
				s += order[i] - '0';
				i--;
			}
			s /= 10;
			c.imag += s;
			return c;
		}
	}
	else if (f == 8)
	{
		//-a - bi 
		c.real = order[1] - '0';
		int i = 2;
		while (order[i] != '-'&&order[i] != '.')
		{
			c.real *= 10;
			c.real += order[i] - '0';
			i++;
		}
		if (order[i] == '.')
		{
			double s = 0;
			while (order[i] != '-')
				i++;
			i--;
			while (order[i] != '.')
			{
				s /= 10;
				s += order[i] - '0';
				i--;
			}
			s /= 10;
			c.real += s;
		}
		c.real *= -1;
		while (order[i] != '-')
			i++;
		i++;
		c.imag = order[i]-'0';
		i++;
		while (order[i] != 'i'&&order[i] != '.')
		{
			c.imag *= 10;
			c.imag += order[i] - '0';
			i++;
		}
		if (order[i] == 'i')
		{
			c.imag *= -1;
			return c;
		}
		else
		{
			double s = 0;
			while (order[i] != 'i')
				i++;
			i--;
			while (order[i] != '.')
			{
				s /= 10;
				s += order[i] - '0';
				i--;
			}
			s /= 10;
			c.imag += s;
			c.imag *= -1;
			return c;
		}
	}
	else if (f == 9)
	{
		// i
		c.imag = 1;
		return c;
	}
	else if (f == 10)
	{
		//  -i 
		c.imag = -1;
		return c;
	}
	else if (f == 11)
	{
		//a + i 
		c.real = order[0] - '0';
		int i = 1;
		while (order[i] != '+'&&order[i] != '.')
		{
			c.real *= 10;
			c.real += order[i] - '0';
			i++;
		}
		if (order[i] == '.')
		{
			double s = 0;
			while (order[i] != '+')
				i++;
			i--;
			while (order[i] != '.')
			{
				s /= 10;
				s += order[i] - '0';
				i--;
			}
			s /= 10;
			c.real += s;
		}
		c.imag = 1;
		return c;
	}
	else if (f == 12)
	{
		// a - i  
		c.real = order[0] - '0';
		int i = 1;
		while (order[i] != '-'&&order[i] != '.')
		{
			c.real *= 10;
			c.real += order[i] - '0';
			i++;
		}
		if (order[i] == '.')
		{
			double s = 0;
			while (order[i] != '-')
				i++;
			i--;
			while (order[i] != '.')
			{
				s /= 10;
				s += order[i] - '0';
				i--;
			}
			s /= 10;
			c.real += s;
		}
		c.imag = -1;
		return c;
	}
	else if (f ==13)
	{
		// -a + i 
		c.real = order[1] - '0';
		int i = 2;
		while (order[i] != '+'&&order[i] != '.')
		{
			c.real *= 10;
			c.real += order[i] - '0';
			i++;
		}
		if (order[i] == '.')
		{
			double s = 0;
			while (order[i] != '+')
				i++;
			i--;
			while (order[i] != '.')
			{
				s /= 10;
				s += order[i] - '0';
				i--;
			}
			s /= 10;
			c.real += s;
		}
		c.real *= -1;
		c.imag = 1;
		return c;
	}
	else
	{
		//- a - i
		c.real = order[1] - '0';
		int i = 2;
		while (order[i] != '-'&&order[i] != '.')
		{
			c.real *= 10;
			c.real += order[i] - '0';
			i++;
		}
		if (order[i] == '.')
		{
			double s = 0;
			while (order[i] != '-')
				i++;
			i--;
			while (order[i] != '.')
			{
				s /= 10;
				s += order[i] - '0';
				i--;
			}
			s /= 10;
			c.real += s;
		}
		c.real *= -1;
		c.imag = -1;
		return c;
	}

}
//debuged
int Complex::getDotLeftNum(double d)
{
	int a =(int) d;
	int Num = 0;
	while (a - 0>0.0000001)
	{
		a /= 10;
		Num++;
	}
	return Num;
}
//debuged
int Complex::getDotRightNum(double d)
{
	int Num = 0;
	while (Num!=8&&(d-(int)d>0.0000001)&&(Num!=1||d - (int)d>0.000001)&& (Num != 2|| d - (int)d>0.00001)&& (Num != 3 || d - (int)d>0.0001)&& (Num != 4 || d - (int)d>0.0001)&& (Num != 5|| d - (int)d>0.001)&& (Num != 6 || d - (int)d>0.001))
	{
		d *= 10;
		Num++;
	}
	return Num;
}
//debuged
void Complex::turnCharactor(aComplex c, char cha[])
{
	
	int signR, signI;
	if (c.real > 0)
		signR = 1;
	else 
	{
		signR = 0; 
		c.real *= -1;
	}
	if (c.imag > 0)
		signI = 1;
	else
	{
		signI = 0;
		c.imag *= -1;
	}
	c.real = c.real +0.00000000005;
	c.imag = c.imag+0.00000000005;
	char rbc[30];
	char rsc[30];
	char ibc[30];
	char isc[30];
	int RRN = getDotRightNum(c.real);
	int RLN = getDotLeftNum(c.real);
	int IRN= getDotRightNum(c.imag);
	int ILN= getDotLeftNum(c.imag);
	int rb=(int)c.real;
	int rs = (int)((c.real - rb)*pow(10,RRN)+0.005);
	int ib =(int)c.imag;
	int is=(int)((c.imag - ib)*pow(10, IRN)+0.005);
	int i = 0;
	for (i = 0; i < RLN; i++)
	{
		rbc[i] =(int) (rb / pow(10, RLN -1- i)) % 10 + '0';
	}
	if (i == 0)
	{
		rbc[0] = '0';
		i++;
	}
	rbc[i] = '\0';
	for (i = 0; i < RRN; i++)
	{
		rsc[i] = (int)(rs / pow(10, RRN - 1 - i)) % 10 + '0';
	}
	if (i == 0)
	{
		rsc[0] = '0';
		i++;
	}
	rsc[i] = '\0';
	for (i = 0; i < ILN; i++)
	{
		ibc[i] = (int)(ib / pow(10, ILN - 1 - i)) % 10 + '0';
	}
	if (i == 0)
	{
		ibc[0] = '0';
		i++;
	}
	ibc[i] = '\0';
	for ( i = 0; i < IRN; i++)
	{
		isc[i] = (int)(is / pow(10, IRN - 1 - i)) % 10 + '0';
	}
	if (i == 0)
	{
		isc[0] = '0';
		i++;
	}
	isc[i] = '\0';
	//组合
	if (RLN == 0 && RRN == 0&&ILN==0&&IRN==0)
	{
		cha[0] = '0';
		cha[1] = '\0';
	}
	else if (RLN == 0 && RRN == 0)
	{
		if (ILN == 0)
		{
			if (signI == 0)
			{
				cha[0] = '-';
				cha[1] = '0';
				cha[2] = '.';
				cha[3] = '\0';
			}
			else
			{
				cha[0] = '0';
				cha[1] = '.';
				cha[2] = '\0';
			}
			strca(cha,isc);
			strca(cha, "i");
		}
		else if (IRN == 0)
		{
			if (signI == 0)
			{
				cha[0] = '-';
				
				cha[1] = '\0';
			}
			else
			{
				cha[0] = '\0';
				
			}
			if(ibc[0]!='1'||ibc[1]!='\0')
			strca(cha,ibc);
			strca(cha, "i");
		}
		else
		{
			if (signI == 0)
			{
				cha[0] = '-';

				cha[1] = '\0';
			}
			else
			{
				cha[0] = '\0';
			}
			strca(cha,  ibc);
			strca(cha, ".");
			strca(cha,  isc);
			strca(cha, "i");
		}
	}
	else if (ILN == 0 && IRN == 0)
	{
		if (RLN == 0)
		{
			if (signR == 0)
			{
				cha[0] = '-';
				cha[1] = '0';
				cha[2] = '.';
				cha[3] = '\0';
			}
			else
			{
				cha[0] = '0';
				cha[1] = '.';
				cha[2] = '\0';
			}
			strca(cha, rsc);
		}
		else if (RRN == 0)
		{
			if (signR== 0)
			{
				cha[0] = '-';

				cha[1] = '\0';
			}
			else
			{
				cha[0] = '\0';

			}
			strca(cha, rbc);
		}
		else
		{
			if (signR == 0)
			{
				cha[0] = '-';

				cha[1] = '\0';
			}
			else
			{
				cha[0] = '\0';
			}
			strca(cha,  rbc);
			strca(cha,  ".");
			strca(cha,  rsc);
		}
	}
	else
	{
		if (signR == 0)
		{
			cha[0] = '-';
			
			cha[1] = '\0';
		}
		else
		{
			cha[0] = '\0';
		}
		if (RLN == 0)
		{
			strca(cha, "0.");
			strca(cha,  rsc);
		}
		else if (RRN == 0)
		{
			strca(cha,  rbc);
		}
		else
		{
			strca(cha, rbc);
			strca(cha,  ".");
			strca(cha, rsc);
		}
		//
		if (signI == 0)
		{
			strca(cha, "-");
		}
		else
		{
			strca(cha,  "+");
		}
		if (ILN == 0)
		{
			strca(cha, "0.");
			strca(cha,  isc);
			strca(cha, "i");
		}
		else if (IRN == 0)
		{
			if (ibc[0] != '1' || ibc[1] != '\0')
			strca(cha,  ibc);
			strca(cha,  "i");
		}
		else
		{
			strca(cha, ibc);
			strca(cha,  ".");
			strca(cha,  isc);
			strca(cha, "i");
		}
	}
}
//debuged
void Complex::getSonCha(char cha[], int left, int right,char son[])
{

	int i = 0;
	for (int j = left+1; j < right; j++)
	{
		son[i] = cha[j];
		i++;
		son[i] = '\0';
	}
}
//debuged
void Complex::insertStr(char cha[], int left, int right, char s[])
{
	char a[100];
	char b[100];
	int i = 0;
	for (i = 0; i <= left; i++)
		a[i] = cha[i];
	a[i] = '\0';
	int j = 0;
	for (i = right; cha[i] != '\0'; i++)
	{
		b[j] = cha[i];
		j++;
	}
	b[j] = '\0';
	strcp(cha, a);
	strca(cha,s);
	strca(cha, b);
}
//debuged
int Complex::ifExpressionSimple(char expression[])
{
	for (int i = 0; expression[i] != '\0'; i++)
		if (expression[i] != '('&&expression[i] != ')'&&expression[i] != '|'&&(expression[i]<'0'||expression[i]>'9')&&expression[i] != 'i'&&expression[i] != '.'&&expression[i] != '+'&&expression[i] != '-'&&expression[i] != '*'&&expression[i] != '/')
			return 0;
	int n = getBracketNum(expression);
	if (n == -1)
		return -1;
	for (int i = 1; i < n+1; i++)
		{
			int left = getLeftBracketPosition(i, expression);
			int right = getRightBracketPosition(i, expression);
			if (left == -1 || left >= right)
				return -1;
			char son[50];
			getSonCha(expression, left, right, son);
			int ifSonSimple = ifExpressionSimple(son);
			if (ifSonSimple != 1)
				return ifSonSimple;
			else if (ifSimple(son) == 0)
				return 0;
		}
	for (int i = 0; expression[i] != '\0'; i++)
	{
		if (expression[i] == '|')
		{
			int l = i;
			int r;
			for ( r = i + 1; expression[r] != '\0'&&expression[r] != '|'; r++)
				;
			if (expression[r] == '\0')
				return -1;
			if ( r==l+1)
				return -1;
			char son[50];
			getSonCha(expression, l, r, son);
			int ifSonSimple = ifExpressionSimple(son);
			if (ifSonSimple != 1)
				return ifSonSimple;
			else if (ifSimple(son) == 0)
				return 0;
			i = r + 1;
		}
	}
	return 1;
}
//debuged
aComplex Complex::calculate(char order[])
{

	int n = getBracketNum(order);
	for (int i = 1; i < n + 1; i++)
	{
		int left = getLeftBracketPosition(i, order);
		int right = getRightBracketPosition(i, order);
		char son[50];
		getSonCha(order, left, right, son);
		int ifSonSimple = ifSimple(son);
		 if (ifSonSimple == 0)
		{
			aComplex ac;
			ac = calculate(son);
			char a[100];
			turnCharactor(ac, a);
			insertStr(order, left, right, a);
		}
	}
	for (int i = 0; order[i] != '\0'; i++)
	{
		if (order[i] == '|')
		{
			int l = i;
			int r;
			for (r = i + 1; order[r] != '\0'&&order[r] != '|'; r++)
				;
			
			char son[50];
			getSonCha(order, l, r, son);
			int ifSonSimple = ifSimple(son);
			if (ifSonSimple== 0)
			{
				aComplex ac;
				ac = calculate(son);
				double m = getMode(ac);
				ac.real = m;
				ac.imag = 0;
				char a[100];
				turnCharactor(ac, a);
				insertStr(order, l - 1, r + 1, a);
			}
		}
	}
	for (int i = 0; order[i] != '\0'; i++)
	{
		if (order[i] == 'a')
		{
			int l = i + 3;
			int r = i + 4;
			while (order[r] != ')')
				r++;
			char a[100];
			getSonCha(order, l, r, a);
			aComplex ac = turnComplex(a);
			double arg = getArg(ac);
			ac.real = arg;
			ac.imag = 0;
			strcp(a, "\0");
			turnCharactor(ac, a);
			insertStr(order, i - 1, r + 1, a);
		}
		else if (order[i] == 'c')
		{

			int l = i + 3;
			int r = i + 4;
			while (order[r] != ')')
				r++;
			char a[50];
			getSonCha(order, l, r, a);
			aComplex ac = turnComplex(a);
			ac = getCjg(ac);
			strcp(a, "(");
			char b[100];
			turnCharactor(ac, b);
			strca(a, b);
			strca(a, ")");
			insertStr(order, i - 1, r + 1, a);
		}
		else if (order[i] == '^')
		{
			int dr = i - 1;
			int dl;
			if (order[dr] == ')')
			{
				dl = i - 2;
				while (order[dl] != '(')
					dl--;
			}
			else
			{
				dr = i;
				dl = i - 1;
				while ((order[dl] > '0'&&order[dl] < '9') || order[dl] == '.')
					dl--;
			}
			int zl = i + 1;
			int zr;
			if (order[zl] == '(')
			{
				zr = i + 2;
				while (order[zr] != ')')
					zr++;
			}
			else
			{
				zl = i;
				zr = i + 1;
				while ((order[zr] > '0'&&order[zr] < '9') || order[zr] == '.')
					zr++;
			}
			char a[50];
			getSonCha(order, dl, dr, a);
			aComplex ac;
			ac = turnComplex(a);
			strcp(a, "\0");
			getSonCha(order, zl, zr, a);
			aComplex bc;
			bc = turnComplex(a);
			aComplex cc;
			cc = getPow(ac, (int)bc.real);
			strcp(a, "(");
			char b[100];
			turnCharactor(cc, b);
			strca(a, b);
			strca(a, ")");
			if (order[dl] == '(')
			{
				dl--;
			}
			if (order[zr] == ')')
				zr++;
			insertStr(order, dl, zr, a);
		}
	}
	//对最简单形式具体的计算来了


//乘除
	for (int i = 0; order[i] != '\0'; i++)
	{
		if (order[i] == '*' || order[i] == '/')
		{
			aComplex z, y, x;
			int zy = i - 1;
			int zz = i - 2;
			int yz = i + 1;
			int yy = i + 2;
			if (order[zy] == ')'&&order[yz] == '(')
			{
				while (order[zz] != '(')
					zz--;
				while (order[yy] != ')')
					yy++;
				char a[50];
				getSonCha(order, zz, zy, a);
				z = turnComplex(a);
				strcp(a, "\0");
				getSonCha(order, yz, yy, a);
				y = turnComplex(a);
				if (order[i] == '*')
					x = multiply(z, y);
				else if (order[i] == '/')
				{
						x = divide(z, y);
				}
				char xc[100];
				turnCharactor(x, xc);
				insertStr(order, zz, yy, xc);
			}
			else if (order[zy] == ')')
			{
				yz = i;
				while (order[zz] != '(')
					zz--;
				while (order[yy] != '+'&&order[yy] != '-'&&order[yy] != '*'&&order[yy] != '/'&&order[yy] != '\0')
					yy++;
				char a[50];
				getSonCha(order, zz, zy, a);
				z = turnComplex(a);
				strcp(a, "\0");
				getSonCha(order, yz, yy, a);
				y = turnComplex(a);
				if (order[i] == '*')
					x = multiply(z, y);
				else if (order[i] == '/')
				{
					
						x = divide(z, y);
				}
				char xc[100];
				turnCharactor(x, xc);
				strca(xc, ")");
				insertStr(order, zz, yy, xc);
			}
			else if (order[yz] == '(')
			{
				zy = i;
				while (order[yy] != ')')
					yy++;
				while (order[zz] != '+'&&order[zz] != '-'&&order[zz] != '*'&&order[zz] != '/'&&zz >= 0)
					zz--;
				char a[50];
				getSonCha(order, zz, zy, a);
				z = turnComplex(a);
				strcp(a, "\0");
				getSonCha(order, yz, yy, a);
				y = turnComplex(a);
				if (order[i] == '*')
					x = multiply(z, y);
				else if (order[i] == '/')
				{
						x = divide(z, y);
			
				}
				char xc[100];
				turnCharactor(x, xc);
				char xcc[40];
				xcc[0] = '(';
				xcc[1] = '\0';
				strca(xcc, xc);
				insertStr(order, zz, yy, xcc);
			}
			else
			{
				zy = i;
				yz = i;
				while (order[yy] != '+'&&order[yy] != '-'&&order[yy] != '*'&&order[yy] != '/'&&order[yy] != '\0')
					yy++;
				while (order[zz] != '+'&&order[zz] != '-'&&order[zz] != '*'&&order[zz] != '/'&&zz >= 0)
					zz--;
				char a[50];
				getSonCha(order, zz, zy, a);
				z = turnComplex(a);
				strcp(a, "\0");
				getSonCha(order, yz, yy, a);
				y = turnComplex(a);
				if (order[i] == '*')
					x = multiply(z, y);
				else if (order[i] == '/')
				{
						x = divide(z, y);
				}
				char xc[100];
				turnCharactor(x, xc);
				char xcc[40];
				xcc[0] = '(';
				xcc[1] = '\0';
				strca(xcc, xc);
				strca(xcc, ")");
				insertStr(order, zz, yy, xcc);
			}
			i = zz;
		}
	}
	//加减
	for (int i = 0; order[i] != '\0'; i++)
	{
		aComplex z, y, x;
		int zy = 0;
		int zz = 0;
		int yz = 0;
		int yy = 0;
		if (order[0] == '(')
		{
			zy = 1;
			while (order[zy] != ')')
				zy++;
			if (order[zy + 1] == '\0')
			{
				char ans[40];
				int al, ar;
				al = 0;
				ar = 1;
				while (order[ar] != ')')
					ar++;
				getSonCha(order, al, ar, ans);
				return (turnComplex(ans));
			}
			yz = zy + 2;
			char a[50];
			getSonCha(order, zz, zy, a);
			z = turnComplex(a);
			if (order[yz] == '(')
			{
				yy = yz + 1;
				while (order[yy] != ')')
					yy++;
				char b[50];
				getSonCha(order, yz, yy, b);
				y = turnComplex(b);
				if (order[yz - 1] == '*')
					x = multiply(z, y);
				else
				{
						x = divide(z, y);
					
				}
				char xc[100];
				turnCharactor(x, xc);
				insertStr(order, zz, yy, xc);
				i = 0;
			}
			else
			{
				yz--;
				yy = yz + 1;
				while (order[yy] != '+'&&order[yy] != '-'&&order[yy] != '\0')
					yy++;
				char b[50];
				getSonCha(order, yz, yy, b);
				y = turnComplex(b);
				if (order[yz] == '*')
					x = multiply(z, y);
				else
				{
						x = divide(z, y);
				}
				char xc[100];
				turnCharactor(x, xc);
				strca(xc, ")");
				insertStr(order, zz, yy, xc);
				i = 0;
			}
		}
		else
		{
			zz = -1;
			zy = 0;
			while (order[zy] != '+'&&order[zy] != '-'&&order[zy] != '\0')
				zy++;
			if (order[zy] == '\0')
			{
				return (turnComplex(order));
			}
			yz = zy + 1;
			char a[50];
			getSonCha(order, zz, zy, a);
			z = turnComplex(a);
			if (order[yz] == '(')
			{
				yy = yz + 1;
				while (order[yy] != ')')
					yy++;
				char b[50];
				getSonCha(order, yz, yy, b);
				y = turnComplex(b);
				if (order[yz - 1] == '*')
					x = multiply(z, y);
				else
				{						
						x = divide(z, y);			
				}
				char xc[100];
				char xcc[100];
				xcc[0] = '(';
				xcc[1] = '\0';
				turnCharactor(x, xc);
				strca(xcc, xc);
				insertStr(order, zz, yy, xcc);
				i = 0;
			}
			else
			{
				yz = zy;
				yy = yz + 1;
				while (order[yy] != '+'&&order[yy] != '-'&&order[yy] != '\0')
					yy++;
				char b[50];
				getSonCha(order, yz, yy, b);
				y = turnComplex(b);
				if (order[yz] == '*')
					x = multiply(z, y);
				else
				{
						x = divide(z, y);
				}
				char xc[100];
				turnCharactor(x, xc);
				strca(xc, ")");
				char xcc[40];
				xcc[0] = '(';
				xcc[1] = '\0';
				strca(xcc, xc);
				insertStr(order, zz, yy, xc);
				i = 0;
			}
		}
	}
}
//debuged
bool Complex::calculateRight(char order[])
{
	//和上一个函数一样，仅仅是返回值的区别

	int n = getBracketNum(order);
	for (int i = 1; i < n + 1; i++)
	{
		int left = getLeftBracketPosition(i, order);
		int right = getRightBracketPosition(i, order);
		char son[50];
		getSonCha(order, left, right, son);
		int ifSonSimple = ifExpressionSimple(son);
		if (ifSonSimple == -1)
			return 0;
		if (calculateRight(son) == 0)
			return 0;
		else if (ifSimple(son) == 0)
		{
			aComplex ac;
			ac = calculate(son);
			char a[100];
			turnCharactor(ac, a);
			insertStr(order, left, right, a);
		}
	}
	for (int i = 0; order[i] != '\0'; i++)
	{
		if (order[i] == '|')
		{
			int l = i;
			int r;
			for (r = i + 1; order[r] != '\0'&&order[r] != '|'; r++)
				;
			if (order[r] == '\0')
				return 0;
			if (r == l + 1)
				return 0;
			char son[50];
			getSonCha(order, l, r, son);
			int ifSonSimple = ifExpressionSimple(son);
			if (ifSonSimple ==-1)
				return 0;
			if (calculateRight(son) == 0)
				return 0;
			else if (ifSimple(son) == 0)
			{
				l = i;
				for (r = i + 1; order[r] != '\0'&&order[r] != '|'; r++)
					;
				aComplex ac;
				ac = calculate(son);
				double m = getMode(ac);
				ac.real = m;
				ac.imag = 0;
				char a[100];
				turnCharactor(ac, a);
				insertStr(order, l-1, r+1, a);
			}
		}
	}
	for (int i = 0; order[i] != '\0'; i++)
	{
		if (order[i] == 'a')
		{
			int l = i + 3;
			int r = i + 4;
			while (order[r] != ')')
				r++;
			char a[100];
			getSonCha(order, l, r, a);
			aComplex ac=turnComplex(a);
			double arg = getArg(ac);
			ac.real = arg;
			ac.imag = 0;
			strcp(a, "\0");
			turnCharactor(ac, a);
			insertStr(order, i - 1, r + 1, a);
		}
		else if (order[i] == 'c')
		{

			int l = i + 3;
			int r = i + 4;
			while (order[r] != ')')
				r++;
			char a[100];
			getSonCha(order, l, r, a);
			aComplex ac = turnComplex(a);
			ac = getCjg(ac);
			strcp(a, "(");
			char b[100];
			turnCharactor(ac, b);
			strca(a, b);
			strca(a, ")");
			insertStr(order, i - 1, r + 1, a);
		}
		else if (order[i] == '^')
		{
			int dr = i - 1; 
			int dl; 
			if (order[dr] == ')')
			{
				dl = i - 2;
				while (order[dl] != '(')
					dl--;
			}
			else
			{
				dr = i;
				dl = i - 1;
				while ((order[dl] > '0'&&order[dl] < '9') || order[dl] == '.')
					dl--;
			}
			int zl = i + 1;
			int zr;
			if (order[zl] == '(')
			{
				zr = i + 2;
				while (order[zr] != ')')
					zr++;
			}
			else
			{
				zl = i;
				zr = i + 1;
				while ((order[zr] > '0'&&order[zr] < '9') || order[zr] == '.')
					zr++;
			}
			char a[100];
			getSonCha(order, dl, dr, a);
			aComplex ac;
			ac = turnComplex(a);
			strcp(a, "\0");
			getSonCha(order, zl, zr, a);
			aComplex bc;
			bc = turnComplex(a);
			aComplex cc;
			cc = getPow(ac, (int)bc.real);
			strcp(a, "(");
			char b[100];
			turnCharactor(cc, b);
			strca(a, b);
			strca(a, ")");
			if (order[dl] == '(')
			{
				dl--;
			}
			if (order[zr] == ')')
				zr++;
			insertStr(order, dl, zr, a);
		}
	}
	//乘除
	for (int i = 0; order[i] != '\0'; i++)
	{
		if (order[i] == '*' || order[i] == '/')
		{
			aComplex z, y, x;
			int zy = i - 1;
			int zz=i-2;
			int yz = i + 1;
			int yy = i + 2;
			if (order[zy] == ')'&&order[yz]=='(')
			{
				while (order[zz] != '(')
					zz--;
				while (order[yy] != ')')
					yy++;
				char a[50];
				getSonCha(order, zz, zy, a);
				z = turnComplex(a);
				strcp(a, "\0");
				getSonCha(order, yz, yy, a);
				y = turnComplex(a);
				if (order[i] == '*')
					x = multiply(z, y);
				else if (order[i] == '/')
				{
					if (y.imag == 0 && y.real == 0)
					{
						
						return 0;
					}
					else
					{
						x = divide(z, y);
					}
				}
				char xc[100];
				turnCharactor(x, xc);
				insertStr(order, zz, yy, xc);
			}
			else if (order[zy] == ')')
			{
				yz = i;
				while (order[zz] != '(')
					zz--;
				while (order[yy] != '+'&&order[yy]!='-'&&order[yy]!='*'&&order[yy]!='/'&&order[yy]!='\0')
					yy++;
				char a[50];
				getSonCha(order, zz, zy, a);
				z = turnComplex(a);
				strcp(a, "\0");
				getSonCha(order, yz, yy, a);
				y = turnComplex(a);
				if (order[i] == '*')
					x = multiply(z, y);
				else if (order[i] == '/')
				{
					if (y.imag == 0 && y.real == 0)
					{
						return 0;
					}
					else
					{
						x = divide(z, y);
					}
				}
				char xc[100];
				turnCharactor(x, xc);
				strca(xc, ")");
				insertStr(order, zz, yy, xc);
			}
			else if (order[yz] == '(')
			{
				zy = i;
				while (order[yy] != ')')
					yy++;
				while (order[zz] != '+'&&order[zz] != '-'&&order[zz] != '*'&&order[zz] != '/'&&zz>=0)
					zz--;
				char a[50];
				getSonCha(order, zz, zy, a);
				z = turnComplex(a);
				strcp(a, "\0");
				getSonCha(order, yz, yy, a);
				y = turnComplex(a);
				if (order[i] == '*')
					x = multiply(z, y);
				else if (order[i] == '/')
				{
					if (y.imag == 0 && y.real == 0)
					{
						
						return 0;
					}
					else
					{
						x = divide(z, y);
					}
				}
				char xc[100];
				turnCharactor(x, xc);
				char xcc[40];
				xcc[0] ='(';
				xcc[1] = '\0';
				strca(xcc, xc);
				insertStr(order, zz, yy, xcc);
			}
			else
			{
				zy = i;
				yz = i;
				while (order[yy] != '+'&&order[yy] != '-'&&order[yy] != '*'&&order[yy] != '/'&&order[yy]!='\0')
					yy++;
				while (order[zz] != '+'&&order[zz] != '-'&&order[zz] != '*'&&order[zz] != '/'&&zz >= 0)
					zz--;
				char a[50];
				getSonCha(order, zz, zy, a);
				z = turnComplex(a);
				strcp(a, "\0");
				getSonCha(order, yz, yy, a);
				y = turnComplex(a);
				if (order[i] == '*')
					x = multiply(z, y);
				else if (order[i] == '/')
				{
					if (y.imag == 0 && y.real == 0)
					{
					
						return 0;
					}
					else
					{
						x = divide(z, y);
					}
				}
				char xc[100];
				turnCharactor(x, xc);
				char xcc[40];
				xcc[0] = '(';
				xcc[1] = '\0';
				strca(xcc, xc);
				strca(xcc, ")");
				insertStr(order, zz, yy, xcc);
			}
			i = zz;
		}
	}
	//i前那个省略
	//加减
	for (int i = 0; order[i] != '\0'; i++)
	{
		aComplex z, y, x;
		int zy = 0;
		int zz = 0;
		int yz = 0;
		int yy = 0;
		if (order[0] == '(')
		{
			zy = 1;
			while (order[zy] != ')')
				zy++;
			if (order[zy + 1] == '\0')
			{
				return 1;
			}
			yz = zy + 2;
			char a[50];
			getSonCha(order, zz, zy, a);
			z = turnComplex(a);
			if (order[yz] == '(')
			{
				yy = yz + 1;
				while (order[yy] != ')')
					yy++;
				char b[50];
				getSonCha(order, yz, yy, b);
				y = turnComplex(b);
				if (order[yz-1] == '+')
					x = plus(z, y);
				else 
				{
					
						x = minus(z, y);
					
				}
				char xc[100];
				turnCharactor(x, xc);
				insertStr(order, zz, yy, xc);
				i = 0;
			}
			else
			{
				yz--;
				yy = yz + 1;
				while (order[yy] != '+'&&order[yy]!='-'&&order[yy]!='\0')
					yy++;
				char b[50];
				getSonCha(order, yz, yy, b);
				y = turnComplex(b);
				if (order[yz] == '+')
					x = plus(z, y);
				else
				{

					x = minus(z, y);

				}
				char xc[100];
				turnCharactor(x, xc);
				strca(xc, ")");
				insertStr(order, zz, yy, xc);
				i = 0;
			}
		}
		else 
		{
			zz = -1;
			zy = 0;
			if (order[0] == '-')
				zy++;
			while (order[zy] != '+'&&order[zy]!='-'&&order[zy]!='\0')
				zy++;
			if (order[zy] == '\0')
			{
				
				return 1;
			}
			yz = zy + 1;
			char a[50];
			getSonCha(order, zz, zy, a);
			z = turnComplex(a);
			if (order[yz] == '(')
			{
				yy = yz + 1;
				while (order[yy] != ')')
					yy++;
				char b[50];
				getSonCha(order, yz, yy, b);
				y = turnComplex(b);
				if (order[yz - 1] == '+')
					x = plus(z, y);
				else
				{

					x = minus(z, y);

				}
				char xc[100];
				char xcc[100];
				xcc[0] = '(';
				xcc[1] = '\0';
				turnCharactor(x, xc);
				strca(xcc, xc);
				insertStr(order, zz, yy, xcc);
				i = 0;
			}
			else
			{
				yz=zy;
				yy = yz + 1;
				while (order[yy] != '+'&&order[yy] != '-'&&order[yy] != '\0')
					yy++;
				char b[50];
				getSonCha(order, yz, yy, b);
				y = turnComplex(b);
				if (order[yz] == '+')
					x = plus(z, y);
				else
				{

					x = minus(z, y);

				}
				char xc[100];
				turnCharactor(x, xc);
				strca(xc, ")");
				char xcc[100];
				xcc[0] = '(';
				xcc[1] = '\0';
				strca(xcc, xc);
				insertStr(order, zz, yy, xcc);
				i = 0;
			}
		}
	}
}
//debuged
history* Complex::showAns(char order[])
{
	char o[100];
	strcp(o, order);
	if (ifLegal(order) && calculateRight(order))
	{
		aComplex c = calculate(order);
		cout << "result:";
		showAComplex(c);
		history *newhistory = new history;
		newhistory->c = c;
		strcp(newhistory->order, o);
		return newhistory;
	}
	else
		return NULL;
}
//debuged
void Complex::showAComplex(aComplex c)
{
	if (c.real > 0)
	{
		printf("%.6f", c.real);
	}
	else if (c.real < 0)
	{
		cout << "-";
		c.real = c.real*-1;
		printf("%.6f", c.real);
	}
	if (c.imag > 0)
	{
		if(c.real!=0)
		cout << "+";
		printf("%.6f", c.imag);
		cout << "i"<<endl;
	}
	else  if (c.imag < 0)
	{
		cout << '-';
		c.imag = c.imag * (-1);
		printf("%.6f", c.imag);
		cout << "i" << endl;
	}
	else cout << endl;
	if (c.real == 0 && c.imag == 0)
		cout << "0.000000" << endl;
}