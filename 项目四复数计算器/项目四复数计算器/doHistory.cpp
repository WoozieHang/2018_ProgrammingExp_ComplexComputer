#include "Complex.h"
using namespace std;
doHistory::doHistory()
{
	historyHead = NULL;
	nowIndex = NULL;
	historyOutFile();
}
void doHistory::historyOutFile()
{
	errno_t err;
	FILE *fp;
	Complex c;
	err = fopen_s(&fp, "history.txt", "r+");
	if (fp != NULL)
	{
		char order[9][200];
		char ex[9][50];
		int i = 0;
		while (!feof(fp))
		{
			order[i][0] = '\0';
			ex[i][0] = '\0';
			fgets(order[i], 200, fp);
			while(order[i][0]=='\n'&&!feof(fp))
				fgets(order[i], 200, fp);
			if (order[i][0] != '\0'&&order[i][0] != '\n')
			{
				fgets(ex[i], 50, fp);
				while (ex[i][0]== '\n' && !feof(fp))
					fgets(ex[i], 200, fp);
			}
			for (int j = 0; order[i][j] != '\0'; j++)
				if (order[i][j] == '\n')
					order[i][j] = '\0';
			for (int j = 0; ex[i][j] != '\0'; j++)
				if (ex[i][j] == '\n')
					ex[i][j] = '\0';
			if(order[i][0]!='\0'&&order[i][0] != '\n'&&ex[i][0]!='\0'&&ex[i][0] != '\n')
			i++;
		}
		
		if (i > 0)
		{
			for (int j = 0; j < i; j++)
			{
				history * nh=new history;
				nh->c = c.turnComplex(ex[j]);
				nh->next = NULL;
				c.strcp(nh->order, order[j]);
				if (historyHead == NULL)
				{
					historyHead = nh;
					nowIndex = nh;
					nh->last = NULL;
				}
				else
				{
					nowIndex->next = nh;
					nh->last = nowIndex;
					nowIndex = nh;
				}
			}
		}
		fclose(fp);
	}

}
void doHistory::historyInFile()
{
	errno_t err;
	FILE *fp;
	Complex c;
	err = fopen_s(&fp, "history.txt", "w");;
	history *a = historyHead;
	while (a != NULL)
	{
		for (int i = 0; a->order[i] != '\0'; i++)
			if (a->order[i] == '\n')
				a->order[i] = '\0';
		fputs(a->order, fp);
		fputs("\n", fp);
		char cc[50];
		c.turnCharactor(a->c, cc);
		fputs(cc, fp);
		fputs("\n", fp);
		a = a->next;
	}
	fclose(fp);
}
void doHistory::updateHistory(history *aNewHistory)
{
	history *a = historyHead;
	if (a == NULL)
	{
		historyHead = aNewHistory;
		historyHead->last = NULL;
		historyHead->next= NULL;
	}
	else
	{
		int n = 1;
		while (a->next != NULL)
		{
			a = a->next;
			n++;
		}
		a->next = aNewHistory;
		aNewHistory->last = a;
		aNewHistory->next = NULL;
		if (n > 4)
		{
			a = historyHead;
			historyHead = historyHead->next;
			historyHead->last = NULL;
			delete a;
		}
	}
	nowIndex = aNewHistory;
}
void doHistory::upTurning()
{
	Complex c;
	if (nowIndex->last != NULL)
	{
		nowIndex = nowIndex->last;
		cout << "expression:";
		cout << nowIndex->order << endl;
		cout << "result:";
		c.showAComplex(nowIndex->c);
	}
	else cout << "Already the first history!" << endl;
}
void doHistory::downTurning()
{
	Complex c;
	if (nowIndex->next != NULL)
	{
		nowIndex = nowIndex->next;
		cout << "expression:";
		cout << nowIndex->order << endl;
		cout << "result:";
		c.showAComplex(nowIndex->c);
	}
	else cout << "Already the last history" << endl;
}
void doHistory::showLastFiveHistory()
{
	Complex c;
	int i = 1;
	for (history *h = historyHead; h != NULL; h = h->next)
	{
		cout << "(" << i << ")   " << endl;
		cout << "expression:";
		cout << h->order << endl;
		cout << "result:";
		c.showAComplex(h->c);
		i++;
	}
}

