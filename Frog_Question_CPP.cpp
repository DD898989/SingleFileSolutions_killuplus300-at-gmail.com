// SFSDF87984.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
bool Jump(int t[]);
void Print(int t[]);
void Change(int *m, int *n);


const int LEN = 51;

int main()
{
	int t[LEN];

	for(int i=0;i<(LEN-1)/2;i++)
		t[i] = 1;

	t[(LEN-1)/2] = 0;

	for(int i=(LEN-1)/2+1;i<LEN;i++)
		t[i] = 2;

	while(!Jump(t))
	{
		Print(t);
	}
}

bool Jump(int t[])
{

	bool bFinished = true;

	for(int i=0;i<(LEN-1)/2;i++)
		if(t[i] != 2)
			bFinished = false;

	for(int i=(LEN-1)/2+1;i<LEN;i++)
		if(t[i] != 1)
			bFinished = false;

	if(bFinished)
		return true;


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