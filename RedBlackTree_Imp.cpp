//this solution comes from https://github.com/zyi23/Red-Black-Tree/blob/master/rbtree.cpp

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;


#define __TEST__

template <class T>
class rbtree;

template <class T>
struct _rbTreeNode
{
	friend class rbtree<T>;
	T getkey()
	{
		return key;
	}

private:
	T key;
	_rbTreeNode<T> *left;
	_rbTreeNode<T> *right;
	_rbTreeNode<T> *parent;
	bool color;			// true == red  &&  false == black
};


template <class T>
class rbtree
{
public:
	rbtree()
		:nil( new _rbTreeNode<T> ), root( nil ) 
	{ 
		nil->left = 0; 
		nil->parent = 0; 
		nil->right = 0; 
		nil->color = false; 
	}

	void insert( T key );
	_rbTreeNode<T> * search( T key );
	void erase( T key );

#ifdef __TEST__
	void display();
#endif

private:

#ifdef __TEST__
	void _display( _rbTreeNode<T> * );
#endif


	void leftRotate(  _rbTreeNode<T> * );
	void rightRotate(  _rbTreeNode<T> * );

	void rbDelete(  _rbTreeNode<T> * );
	void rbDeleteFixup(  _rbTreeNode<T> * );

	void rbInsertFixup( _rbTreeNode<T> * );

	_rbTreeNode<T>* treeSuccessor(  _rbTreeNode<T> * );

	_rbTreeNode<T> *nil;			//空结点
	_rbTreeNode<T> *root;

};

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
		if( key < x->key )
			x = x->left;
		else
			x = x->right;
	}

	t->parent = y;
	if( y == nil )
		root = t;
	else
	{
		if ( t->key < y->key )
			y->left = t;
		else
			y->right = t;
	}

	t->left = nil;
	t->right = nil;
	t->color = true;


	cout<<"---------插入後--------"<<endl;   display();
	
	rbInsertFixup( t );

	cout<<"---------排列後--------"<<endl;   display();
	
}

template <class T>
_rbTreeNode<T> * rbtree<T>::search( T key )
{
	_rbTreeNode<T> * x = root;
	while( x != nil && key != x->key )
	{
		if( key < x->key )
			x = x->left;
		else
			x = x->right;
	}

	return x;
}

template <class T>
void rbtree<T>::erase( T key )
{
	_rbTreeNode<T> * x = search( key );
	if( x != nil )
		rbDelete( x );
}

template <class T>
_rbTreeNode<T> * rbtree<T>::treeSuccessor( _rbTreeNode<T> *x )
{
	if( x->right != nil )
	{
		while( x->left != nil )
			x = x->left;
		return x;
	}

	_rbTreeNode<T> * y = x->parent;
	while( y != nil && x == y->right )
	{
		x = y;
		y = y->parent;
	}

	return y;
}

template <class T>
void rbtree<T>::leftRotate( _rbTreeNode<T> *x )  // x->right != nil
{		
	_rbTreeNode<T> * y = x->right;
	if( x->parent == nil )
		root = y;
	else
	{
		if( x == x->parent->left )
			x->parent->left = y;
		else
			x->parent->right = y;
	}

	y->parent = x->parent;
	x->right = y->left;
	y->left->parent = x;
	y->left = x;
	x->parent = y;
}

template <class T>
void rbtree<T>::rightRotate( _rbTreeNode<T> *x )
{
	_rbTreeNode<T> * y = x->left;
	if( x->parent == nil )
		root = y;
	else
	{
		if( x == x->parent->left )
			x->parent->left = y;
		else
			x->parent->right = y;
	}

	y->parent = x->parent;
	x->left = y->right;
	y->right->parent = x;
	y->right = x;
	x->parent = y;
}

template <class T>
void rbtree<T>::rbInsertFixup( _rbTreeNode<T> *z )
{
	while( z->parent->color)
	{
		if( z->parent == z->parent->parent->left ) //if(){大括號內容根else相反的全都是方向}
		{
			_rbTreeNode<T> * y = z->parent->parent->right;
			if( y->color)
			{
				z->parent->color = false;
				y->color = false;
				z->parent->parent->color = true;
				z = z->parent->parent;
			}
			else
			{
				if( z == z->parent->right )
				{
					z = z->parent;
					leftRotate( z );
				}
				z->parent->color = false;
				z->parent->parent->color = true;
				z->parent->right->color = false;
				rightRotate( z->parent->parent );
			}

		}
		else									//else{大括號內容根if相反的全都是方向}
		{
			_rbTreeNode<T> * y = z->parent->parent->left;
			if( y->color == true )
			{
				z->parent->color = false;
				y->color = false;
				z->parent->parent->color = true;
				z = z->parent->parent;
			}
			else
			{
				if( z == z->parent->left )
				{
					z = z->parent;
					rightRotate( z );
				}

				z->parent->color = false;
				z->parent->parent->color = true;
				z->parent->left->color = false;
				leftRotate( z->parent->parent );
			}

		}

	}

	root->color = false;
}

template <class T>
void rbtree<T>::rbDelete( _rbTreeNode<T> *z )
{
	_rbTreeNode<T> * x = nil;
	_rbTreeNode<T> * y = nil;
	if( z->left == nil || z->right == nil )
		y = z;
	else
		y = treeSuccessor( z );
	if( y->left != nil )
		x = y->left;
	else
		x = y->right;
	x->parent = y->parent;
	if( y->parent == nil )
		root = x;
	else
	{
		if( y == y->parent->left )
			y->parent->left = x;
		else
			y->parent->right = x;
	}

	if( y != z )
		z->key = y->key;
	if( y->color == false )
		rbDeleteFixup( x );
	delete y;
}

template <class T>
void rbtree<T>::rbDeleteFixup(_rbTreeNode<T> * x)
{
	while( x != root && x->color == false )
	{
		_rbTreeNode<T> * w = 0;
		if( x->parent->left == x )
		{
			w = x->parent->right;
			if( w->color == true )
			{
				w->color = false;
				x->parent->color = true;
				leftRotate( x->parent );
				w = x->parent->right;
			}

			if( w->left->color == false && w->right->color == false )
			{
				w->color = true;
				x = x->parent;
			}

			else
			{
				if( w->right->color == false )
				{
					w->left->color = false;
					w->color = true;
					rightRotate( w );
					w = x->parent->right;
				}

				w->color = x->parent->color;
				x->parent->color = false;
				w->right->color = false;
				leftRotate( x->parent );
				x = root;
			}

		}

		else
		{
			w = x->parent->left;
			if( w->color == true )
			{
				w->color = false;
				x->parent->color = true;
				rightRotate( x->parent );
				w = x->parent->left;
			}

			if( w->right->color == false && w->left->color == false )
			{
				w->color = true;
				x = x->parent;
			}

			else
			{
				if( w->left->color == false )
				{
					w->right->color = false;
					w->color = true;
					leftRotate( w );
					w = x->parent->left;
				}

				w->color = x->parent->color;
				x->parent->color = false;
				w->left->color = false;
				rightRotate( x->parent );
				x = root;
			}

		}

	}

	x->color = false;
}


#ifdef __TEST__

template <class T>
void rbtree<T>::display()
{
	if( root != nil )
		_display( root );
	else
		cout << "Tree is empty! " << endl;
}


template <class T>
void rbtree<T>::_display( _rbTreeNode<T> * x )
{
	if( x->left != nil )
		_display( x->left );
	if( x != nil )
	{
		int wid=10;

		
		if( x->parent != nil )
			cout << setw(wid) << ' '<< x->parent->key;
		else
			cout << setw(wid)<< "  　";

		cout<<endl;//-----------------------------------------

		cout<< setw(wid) <<"【"<< x->key << "】";


		if( x->color == true )
			cout << "R";
		else
			cout << "B";

		
		cout<<endl;//-----------------------------------------


		if( x->left != nil )
			cout << setw(wid/2)<< x->left->key << ' ';
		else
			cout << setw(wid/2)<< " 　";

		


		if( x->right != nil )
			cout << setw(wid)<< x->right->key << ' ';
		else
			cout << setw(1.5*wid)<< "　";


		
		cout<<endl;//-----------------------------------------
	}

	cout << endl;
	if( x->right != nil )
		_display( x->right );
}

#endif


int main()
{
	rbtree<int> test;

	test.insert(5);
	test.insert(6);
	test.insert(7);
	test.insert(4);
	test.insert(3);
	test.insert(2);

	
	int a;
	test.display();
	cout<<"開始移除:"<<endl;;
	while( cin >> a )
	{
		test.erase( a );
		test.display();
		cout<<"開始移除:"<<endl;;
	}


	system("pause");
	return 0;
}
