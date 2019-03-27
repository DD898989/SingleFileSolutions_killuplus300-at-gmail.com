#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

int largestPerimeterTriangle(vector<int> A) //copy
{
	if(A.size()<3)
		return 0;

	sort(A.begin(), A.end(),greater<int>()); //quick sort: ave~N*log(N)   worst~N^2

	for(int i=0;i<A.size()-2;i++)
	{
		if(A[i]<A[i+1]+A[i+2])
			return (A[i]+A[i+1]+A[i+2]);
	}
	return 0;
}

bool validMountainArray(const vector<int>& A) 
{

	if(A.size()<3)
		return false;

	int n = A.size();

	if(A[0]>=A[1] || A[n-1]>=A[n-2])
		return false;

	int i=0;

	for(;i<n-1;i++)
	{
		if(A[i]>A[i+1]) 
			break;
	}

	for(;i<n-1;i++)
	{
		if(A[i]<A[i+1])
			return false;
	}

	return true;
}

struct TreeNode 
{
	int val;
	TreeNode *left;
	TreeNode *right;
};

bool isSameTree_InOrder(const TreeNode* p, const TreeNode* q) 
{
	if(p==NULL && q==NULL)
		return true;
	else if(p==NULL || q==NULL)
		return false;
	else if(p->val == q->val)
		return isSameTree_InOrder(p->left,q->left) && isSameTree_InOrder(p->right,q->right);//if difference exist in very left node, then &&(right) would never in
	else
		return false;
}

bool isSameTree_LevelOrder( TreeNode* P, TreeNode* Q)//const will error 
{
	queue<TreeNode*> p;
	queue<TreeNode*> q;

	p.push(P);  
	q.push(Q);  

	while(true)
	{          
		if(p.empty() && q.empty())
			return true;
		else if(p.empty() || q.empty())
			return false;
		else if(p.front()->val == q.front()->val)
		{
			TreeNode *current;
			
			current = p.front();  p.pop(); 
			if (current->left != NULL) 
				p.push(current->left);
			if (current->right != NULL) 
				p.push(current->right);

			current = q.front();  q.pop(); 
			if (current->left != NULL) 
				q.push(current->left);
			if (current->right != NULL) 
				q.push(current->right);
		}
		else
			return false;
	}
}


void printSpecial(vector<int> A)
{
	int len = A.size();

	vector<int> B(len,1);

	int n;

	n= 1;
	for(int i=1;i<len;i++)
	{
		n*=A[i-1];
		B[i]=n;
	}
	
	n= 1;
	for(int i=len-2;i>-1;i--)
	{
		n*=A[i+1];
		B[i]*=n;
	}

	for (std::vector<int>::const_iterator i = B.begin(); i != B.end(); ++i)
		cout << *i << ' ';
	cout<<endl;
}


void main()
{
	vector<int> A;


	
	int arr0[] = {2, 3, 4,5,6,7,8};
	A = vector<int>(arr0, arr0+sizeof(arr0)/sizeof(int));
	printSpecial(A);



	int arr1[] = {0, 1, 2, 3, 10,12,22};
	A = vector<int>(arr1, arr1+sizeof(arr1)/sizeof(int));
	cout<<largestPerimeterTriangle(A)<<endl;
	

	
	int arr2[] = {3,4,5,1};
	A = vector<int>(arr2, arr2+sizeof(arr2)/sizeof(int));
	cout<<validMountainArray(A)<<endl;





	//				6
	//		/				\
	//		2				9
	//	/		\		/
	//	1		4		7
	//		/		\		\
	//		3		5		8
	TreeNode A_node_6; A_node_6.val = 6; A_node_6.left = NULL; A_node_6.right = NULL;
	TreeNode A_node_2; A_node_2.val = 2; A_node_2.left = NULL; A_node_2.right = NULL;
	TreeNode A_node_9; A_node_9.val = 9; A_node_9.left = NULL; A_node_9.right = NULL;
	TreeNode A_node_1; A_node_1.val = 1; A_node_1.left = NULL; A_node_1.right = NULL;
	TreeNode A_node_4; A_node_4.val = 4; A_node_4.left = NULL; A_node_4.right = NULL;
	TreeNode A_node_7; A_node_7.val = 7; A_node_7.left = NULL; A_node_7.right = NULL;
	TreeNode A_node_3; A_node_3.val = 3; A_node_3.left = NULL; A_node_3.right = NULL;
	TreeNode A_node_5; A_node_5.val = 5; A_node_5.left = NULL; A_node_5.right = NULL;
	TreeNode A_node_8; A_node_8.val = 8; A_node_8.left = NULL; A_node_8.right = NULL;
	A_node_6.left = &A_node_2;
	A_node_6.right = &A_node_9;
	A_node_2.left = &A_node_1;
	A_node_2.right = &A_node_4;
	A_node_4.left = &A_node_3;
	A_node_4.right = &A_node_5;
	A_node_9.left = &A_node_7;
	A_node_7.right = &A_node_8;
	TreeNode B_node_6; B_node_6.val = 6; B_node_6.left = NULL; B_node_6.right = NULL;
	TreeNode B_node_2; B_node_2.val = 2; B_node_2.left = NULL; B_node_2.right = NULL;
	TreeNode B_node_9; B_node_9.val = 9; B_node_9.left = NULL; B_node_9.right = NULL;
	TreeNode B_node_1; B_node_1.val = 1; B_node_1.left = NULL; B_node_1.right = NULL;
	TreeNode B_node_4; B_node_4.val = 4; B_node_4.left = NULL; B_node_4.right = NULL;
	TreeNode B_node_7; B_node_7.val = 7; B_node_7.left = NULL; B_node_7.right = NULL;
	TreeNode B_node_3; B_node_3.val = 3; B_node_3.left = NULL; B_node_3.right = NULL;
	TreeNode B_node_5; B_node_5.val = 5; B_node_5.left = NULL; B_node_5.right = NULL;
	TreeNode B_node_8; B_node_8.val = 8; B_node_8.left = NULL; B_node_8.right = NULL;
	B_node_6.left = &B_node_2;
	B_node_6.right = &B_node_9;
	B_node_2.left = &B_node_1;
	B_node_2.right = &B_node_4;
	B_node_4.left = &B_node_3;
	B_node_4.right = &B_node_5;
	B_node_9.left = &B_node_7;
	B_node_7.right = &B_node_8;
	cout<<"--------------------"<<endl;
	cout<<isSameTree_InOrder(&A_node_6,&B_node_6);	cout<<isSameTree_LevelOrder(&A_node_6,&B_node_6)<<endl;
	B_node_7.val = 10;
	cout<<isSameTree_InOrder(&A_node_6,&B_node_6);	cout<<isSameTree_LevelOrder(&A_node_6,&B_node_6)<<endl;
	B_node_7.val = 7;
	cout<<isSameTree_InOrder(&A_node_6,&B_node_6);	cout<<isSameTree_LevelOrder(&A_node_6,&B_node_6)<<endl;
	B_node_1.val = 2;
	cout<<isSameTree_InOrder(&A_node_6,&B_node_6);	cout<<isSameTree_LevelOrder(&A_node_6,&B_node_6)<<endl;
	B_node_1.val = 1;
	cout<<isSameTree_InOrder(&A_node_6,&B_node_6);	cout<<isSameTree_LevelOrder(&A_node_6,&B_node_6)<<endl;
	B_node_4.val = 5;
	cout<<isSameTree_InOrder(&A_node_6,&B_node_6);	cout<<isSameTree_LevelOrder(&A_node_6,&B_node_6)<<endl;
	B_node_4.val = 4;
	cout<<isSameTree_InOrder(&A_node_6,&B_node_6);	cout<<isSameTree_LevelOrder(&A_node_6,&B_node_6)<<endl;
	cout<<"--------------------"<<endl;

	return;
}
