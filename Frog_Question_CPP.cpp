// SFSDF87984.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>

bool Jump(int t[]);
bool IsFinished(int t[]);
void Print(int t[]);
void Change(int *m, int *n);


const int LEN = 55;
const int ROCK = 8;

int main()
{
	int t[LEN];

	for(int i=0;i<(LEN-1);i++)
		t[i] = 1;

	t[ROCK-1] = 0;

	for(int i=ROCK;i<LEN;i++)
		t[i] = 2;

	Print(t);

	while(!IsFinished(t))
	{
		Jump(t);
		Print(t);
	}

	system("pause");
}


bool IsFinished(int t[])
{
	if(t[0]==2 && t[LEN-1]==1)
	{
		int i=0;

		for(;i<LEN-1;i++)
		{
			if(t[i]!=2) 
			{
				if(t[i]==0)
					break;
				else
					return false;
			}
		}

		i++;

		for(;i<LEN-1;i++)
		{
			if(t[i]!=1)
				return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}

bool Jump(int t[])
{
	for(int i = 0;i<LEN;i++)
	{
		if( i<=LEN-3  &&  t[i]==1&&t[i+1]==2&&t[i+2]==0)
		{
			Change(&t[i],&t[i+2]);
			return false;
		}
	}

	for(int i = 0;i<LEN;i++)
	{
		if( i<=LEN-3  &&  t[i]==0&&t[i+1]==1&&t[i+2]==2)
		{
			Change(&t[i],&t[i+2]);
			return false;
		}
	}

	for(int i = 0;i<LEN;i++)
	{
		if(
			(i<=LEN-2 && t[i]==1 && t[i+1]==0)
			&&
			(
			(i>LEN-3 || i<1)
			||
			(t[i-1]!=t[i+2])
			)
			)
		{
			Change(&t[i],&t[i+1]);
			return false;
		}
	}

	for(int i = 0;i<LEN;i++)
	{
		if(
			(i<=LEN-2 && t[i]==0 && t[i+1]==2)
			&&
			(
			(i>LEN-3 || i<1)
			||
			(t[i-1]!=t[i+2])
			)
			)
		{
			Change(&t[i],&t[i+1]);
			return false;
		}
	}

	return false;
}

void Print(int t[])
{
	for(int i = 0;i<LEN;i++)
	{
		printf("%i",t[i]);
	}
	printf("\n");
}

void Change(int *m, int *n)
{
	int temp = *m;
	*m = *n;
	*n = temp;
}
