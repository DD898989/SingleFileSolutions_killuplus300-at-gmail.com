//https://github.com/zyi23/Red-Black-Tree/blob/master/rbtree.cpp
#include "stdafx.h"
#include <iostream>
#include <iomanip>
using namespace std;
template <class T>
class rbtree;
//----------------------------------------------------------
template <class T>
struct _rbTreeNode
{
	friend class rbtree<T>;

private:
	T key;
	_rbTreeNode<T> *dir[2]; // 0:left  1:right
	_rbTreeNode<T> *parent;
	bool color;	// true:red   false:black
};
//----------------------------------------------------------
template <class T>
class rbtree
{
private:
	void Rotate(  _rbTreeNode<T> * ,bool bDir);//true:left rotate    false: right rotate
	void rbDeleteFixup(  _rbTreeNode<T> * );
	void rbInsertFixup( _rbTreeNode<T> * );
	_rbTreeNode<T> *treeSuccessor(  _rbTreeNode<T> * );
	_rbTreeNode<T> *nil;//null node

public:
	rbtree()
		:nil( new _rbTreeNode<T> ), root( nil ) //root must below nil in class declaration
	{ 
		nil->dir[0] = 0; 
		nil->dir[1] = 0; 
		nil->parent = 0; 
		nil->color = false; 
	}

	void erase(T key);
	void insert(T key);
	void display( _rbTreeNode<T> * x );
	_rbTreeNode<T> *root;//public for display
	_rbTreeNode<T> *search( T key );
};
//----------------------------------------------------------
template <class T>
_rbTreeNode<T> * rbtree<T>::search( T key )
{
	_rbTreeNode<T> * x = root;

	while( x != nil && key != x->key )
			x = x->dir[(key > x->key)];

	return x;
}
//----------------------------------------------------------
template <class T>
void rbtree<T>::erase( T key )
{
	_rbTreeNode<T> * z = search( key );

	if( z != nil )
	{
		_rbTreeNode<T> * x = nil;
		_rbTreeNode<T> * y = nil;

		if( z->dir[0] == nil || z->dir[1] == nil )
			y = z;
		else
			y = treeSuccessor( z );

		if( y->dir[0] != nil )
			x = y->dir[0];
		else
			x = y->dir[1];

		x->parent = y->parent;

		if( y->parent == nil )
			root = x;
		else
		{
			if( y == y->parent->dir[0] )
				y->parent->dir[0] = x;
			else
				y->parent->dir[1] = x;
		}

		if( y != z )
			z->key = y->key;
		
		cout<<"---------after erase--------"<<endl;   display(this->root);

		if( y->color == false )
			rbDeleteFixup( x );
		
		cout<<"---------after balance--------"<<endl;   display(this->root);

		delete y;
	}
}
//----------------------------------------------------------
template <class T>
void rbtree<T>::insert( T key )
{
	_rbTreeNode<T>* t = new _rbTreeNode<T>;
	t->key = key;
	_rbTreeNode<T>* x = root;
	_rbTreeNode<T>* y = nil;

	while( x != nil )
	{
		y = x;
		x = x->dir[(key > x->key)];
	}

	t->parent = y;
	if( y == nil )
		root = t;
	else
		y->dir[(t->key > y->key)] = t;

	t->dir[0] = nil;
	t->dir[1] = nil;
	t->color = true;

	cout<<"---------after insert--------"<<endl;   display(this->root);

	rbInsertFixup( t );

	cout<<"---------after balance--------"<<endl;   display(this->root);
}
//----------------------------------------------------------
template <class T>
_rbTreeNode<T> * rbtree<T>::treeSuccessor( _rbTreeNode<T> *x )
{
	if( x->dir[1] != nil )
	{
		while( x->dir[0] != nil )
			x = x->dir[0];
		return x;
	}
	else
	{
		_rbTreeNode<T> * y = x->parent;
		while( y != nil && x == y->dir[1] )
		{
			x = y;
			y = y->parent;
		}
		return y;
	}
}
//----------------------------------------------------------
template <class T>
void rbtree<T>::Rotate( _rbTreeNode<T> *x,bool bDir )  // x->dir[1] != nil
{		
	_rbTreeNode<T> * y = x->dir[bDir];

	if( x->parent == nil )
		root = y;
	else
		x->parent->dir[(x != x->parent->dir[0])] = y;

	y->parent = x->parent;
	x->dir[bDir] = y->dir[!bDir];
	y->dir[!bDir]->parent = x;
	y->dir[!bDir] = x;
	x->parent = y;
}
//----------------------------------------------------------
template <class T>
void rbtree<T>::rbInsertFixup( _rbTreeNode<T> *z )
{
	while( z->parent->color)
	{
		bool bDir = (z->parent == z->parent->parent->dir[0]);

		_rbTreeNode<T> * y = z->parent->parent->dir[bDir];
		if( y->color)
		{
			z->parent->color = false;
			y->color = false;
			z->parent->parent->color = true;
			z = z->parent->parent;
		}
		else
		{
			if( z == z->parent->dir[bDir] )
			{
				z = z->parent;
				Rotate( z,bDir );
			}
			z->parent->color = false;
			z->parent->parent->color = true;
			z->parent->dir[bDir]->color = false;
			Rotate( z->parent->parent,!bDir );
		}

	}
	root->color = false;
}
//----------------------------------------------------------
template <class T>
void rbtree<T>::rbDeleteFixup(_rbTreeNode<T> * x)
{
	while( x != root && x->color == false )
	{
		_rbTreeNode<T> * w = 0;
		bool bDir = (x->parent->dir[0] == x);
		w = x->parent->dir[bDir];

		if(w->color)
		{
			w->color = false;
			x->parent->color = true;
			Rotate( x->parent,bDir );
			w = x->parent->dir[bDir];
		}

		if( w->dir[!bDir]->color == false && w->dir[bDir]->color == false )
		{
			w->color = true;
			x = x->parent;
		}
		else
		{
			if( w->dir[bDir]->color == false )
			{
				w->dir[!bDir]->color = false;
				w->color = true;
				Rotate( w,!bDir );
				w = x->parent->dir[bDir];
			}

			w->color = x->parent->color;
			x->parent->color = false;
			w->dir[bDir]->color = false;
			Rotate( x->parent,bDir );
			x = root;
		}
	}

	x->color = false;
}
//----------------------------------------------------------
template <class T>
void rbtree<T>::display( _rbTreeNode<T> * x )
{
	if( root == nil )
		cout << "Tree is empty!" << endl;
	else
	{
		if( x->dir[0] != nil )
			display( x->dir[0] );

		if( x != nil )
		{
			int wid=10;

			if( x->parent != nil )
				cout << setw(wid) << ' '<< x->parent->key;
			else
				cout << setw(wid)<< "  　";

			cout<<endl;//-----------------------------------------

			cout<< setw(wid) <<"【"<< x->key << "】";

			if( x->color)
				cout << "R";
			else
				cout << "B";

			cout<<endl;//-----------------------------------------

			if( x->dir[0] != nil )
				cout << setw(wid/2)<< x->dir[0]->key << ' ';
			else
				cout << setw(wid/2)<< " 　";

			if( x->dir[1] != nil )
				cout << setw(wid)<< x->dir[1]->key << ' ';
			else
				cout << setw(1.5*wid)<< "　";

			cout<<endl;//-----------------------------------------
		}

		cout << endl;
		if( x->dir[1] != nil )
			display( x->dir[1] );
	}
}
//----------------------------------------------------------
int main()
{
	rbtree<int> test;

	test.insert(5);
	test.insert(6);
	test.insert(7);
	test.insert(4);
	test.insert(3);
	test.insert(2);

	test.erase(6);
	test.erase(5);
	test.erase(4);
	test.erase(2);
	test.erase(3);

	system("pause");
	return 0;
}
//----------------------------------------------------------
