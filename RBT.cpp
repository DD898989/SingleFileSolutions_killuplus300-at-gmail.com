//edited from https://www.sanfoundry.com/cpp-program-implement-red-black-tree/

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#define INDENT_STEP  4
using namespace std;


template <class T> struct Node
{
private:
	bool color;//0:red , 1:black      set private because of get_clr(),leaf node have null children with color black

public:
	int key;
	T value;
	Node *dir[2], *parent;
	bool get_clr() { return this == NULL ? true : color; }
	void set_clr(bool c) { color = c; }
};

struct Node_Check
{
	Node_Check *parent;
	bool clr;
	int dir[2];//-1:null 0:left 1:right
	int level;
	int blackPathed;
};

template <class T> class RBTree
{
public:
	//-------------------------------------------
	RBTree<T>(){this->_root = NULL;}
	//-------------------------------------------
	void insert(int key, T value)
	{
		Node<T>* inserted_node = NULL;
		if (this->_root == NULL)
		{
			inserted_node =  new_node(key, value);
			this->_root = inserted_node;
		}
		else
		{
			Node<T>* n = this->_root;
			while (true)
			{
				if (key == n->key)
				{
					n->value = value;
					return;
				}
				else
				{
					if (n->dir[key > n->key] == NULL)
					{
						inserted_node =  new_node(key, value);
						n->dir[key > n->key] = inserted_node;
						break;
					}
					else
					{
						n = n->dir[key > n->key];
					}
				}
			}
			inserted_node->parent = n;
		}
		insert_cases(inserted_node);
	}
	//-------------------------------------------
	void erase(int key)
	{
		Node<T>* child;
		Node<T>* n = search_node(key);
		if (n == NULL)
			return;

		if (n->dir[0] != NULL && n->dir[1] != NULL)
		{
			Node<T>* pred = maximum_node(n->dir[0]);
			n->key   = pred->key;
			n->value = pred->value;
			n = pred;
		}

		child = n->dir[1] == NULL ? n->dir[0]  : n->dir[1];

		if (n->get_clr())
		{
			n->set_clr(child->get_clr());
			erase_cases(n);
		}

		replace_node(n, child);
		free(n);
	}
	//-------------------------------------------
	void print_tree()
	{
		print_tree_helper(this->_root, 0);
		puts("");
	}
	//-------------------------------------------
	bool checkValidTree()
	{
		traversal(this->_root,true);

		//rule 1: _root must be black
		if(!this->_root->get_clr())
			return false;


		//rule 2: start from any node to its any descendant node must passed same count of black nodes~~~~~~not exact checked
		vector<Node_Check> vec_leaves(_all);
		for(int i=vec_leaves.size()-1;i>=0;i--)
		{
			if(vec_leaves[i].dir[0] != -1 || vec_leaves[i].dir[1] != -1)//erase all node except leaves
				vec_leaves.erase(vec_leaves.begin() + i);
		}
		for (vector<Node_Check>::iterator it=vec_leaves.begin(); it != vec_leaves.end()-1; ++it)
		{
			if(it->blackPathed!=(it+1)->blackPathed)
				return false;
		}


		//rule 3: red node must have two black chindren
		for(int i=_all.size()-1;i>=0;i--)
		{
			if(_all[i].clr==0)
			{
				if(_all[i].dir[0]==0)
					return false;
				if(_all[i].dir[1]==0)
					return false;
			}
		}


		return true;
	}
	//-------------------------------------------
	Node<T>* search_node(int key)
	{
		Node<T>* n = this->_root;
		while (n != NULL)
		{
			if (key == n->key)
				return n;
			else
				n = n->dir[key > n->key];
		}
		return NULL;
	}
	//-------------------------------------------

private:
	//-------------------------------------------
	Node<T>* _root;
	//-------------------------------------------
	vector<Node_Check> _all;
	//-------------------------------------------
	Node<T>* grandparent(Node<T>* n)
	{
		return n->parent->parent;
	}
	//-------------------------------------------
	Node<T>* sibling(Node<T>* n)
	{
		return n->parent->dir[n == n->parent->dir[0]];
	}
	//-------------------------------------------
	Node<T>* uncle(Node<T>* n)
	{
		return sibling(n->parent);
	}
	//-------------------------------------------
	Node<T>* new_node(int k, T v)
	{
		Node<T>* result = new Node<T>;
		result->key = k;
		result->value = v;
		result->set_clr(false);
		result->dir[0] = NULL;
		result->dir[1] = NULL;
		result->parent = NULL;
		return result;
	}
	//-------------------------------------------
	Node<T>* maximum_node(Node<T>* n)//returns maximum Node
	{
		while (n->dir[1] != NULL)
			n = n->dir[1];
		return n;
	}
	//-------------------------------------------
	void replace_node(Node<T>* oldn, Node<T>* newn)//replace a Node
	{
		if (oldn->parent == NULL)
			this->_root = newn;
		else
			oldn->parent->dir[oldn != oldn->parent->dir[0]] = newn;

		if (newn != NULL)
			newn->parent = oldn->parent;
	}
	//-------------------------------------------
	void rotate(Node<T>* n, bool bDir)//bDir---false:left rotate,true:right rotate
	{
		Node<T>* N = n->dir[bDir];
		replace_node(n, N);

		Node<T>* temp = N->dir[!bDir];

		n->dir[bDir] = temp;
		if (temp != NULL)
			temp->parent = n;
		N->dir[!bDir] = n;

		n->parent = N;
	}
	//-------------------------------------------
	void insert_cases(Node<T>* n)
	{
		if (n->parent == NULL)//case 1
			n->set_clr(true);
		else if (n->parent->get_clr())//case 2
			return;
		else if (!uncle(n)->get_clr())//case 3
		{
			n->parent->set_clr(true);
			uncle(n)->set_clr(true);
			grandparent(n)->set_clr(false);
			insert_cases(grandparent(n));
		}
		else//case 4 & 5
		{
			//case 4
			if (n == n->parent->dir[1] && n->parent == grandparent(n)->dir[0])
			{
				rotate(n->parent,true);
				n = n->dir[0];
			}
			else if (n == n->parent->dir[0] && n->parent == grandparent(n)->dir[1])
			{
				rotate(n->parent,false);
				n = n->dir[1];
			}

			//case 5
			n->parent->set_clr(true);
			grandparent(n)->set_clr(false);
			if (n == n->parent->dir[0] && n->parent == grandparent(n)->dir[0])
				rotate(grandparent(n),false);
			else
				rotate(grandparent(n),true);
		}
	}
	//-------------------------------------------
	void erase_cases(Node<T>* n)
	{
		if (n->parent == NULL)//case 1
		{
			return;
		}
		else if (!sibling(n)->get_clr())//case 2
		{
			n->parent->set_clr(false);
			sibling(n)->set_clr(true);
			rotate(n->parent,n == n->parent->dir[0]);
		}

		//case 3
		if (n->parent->get_clr() && 
			sibling(n)->get_clr() &&
			sibling(n)->dir[0]->get_clr() && 
			sibling(n)->dir[1]->get_clr())
		{
			sibling(n)->set_clr(false);
			erase_cases(n->parent);
		}
		//case 4
		else if (!n->parent->get_clr() && 
			sibling(n)->get_clr() &&
			sibling(n)->dir[0]->get_clr() && 
			sibling(n)->dir[1]->get_clr())
		{
			sibling(n)->set_clr(false);
			n->parent->set_clr(true);
		}
		else//case 5&6
		{
			//case 5
			for(int b=0;b<=1;b++)
			{
				if (n == n->parent->dir[b] && 
					sibling(n)->get_clr() &&
					!sibling(n)->dir[b]->get_clr() && 
					sibling(n)->dir[!b]->get_clr())
				{
					sibling(n)->set_clr(false);
					sibling(n)->dir[b]->set_clr(true);
					rotate(sibling(n),b);
					break;
				}
			}

			//case 6
			sibling(n)->set_clr(n->parent->get_clr());
			n->parent->set_clr(true);

			bool flag = (n == n->parent->dir[0]);
			sibling(n)->dir[flag]->set_clr(true);
			rotate(n->parent,flag);
		}
	}
	//-------------------------------------------
	void print_tree_helper(Node<T>* n, int indent)
	{
		if (n == NULL)
		{
			fputs("<empty tree>", stdout);
			return;
		}

		if (n->dir[1] != NULL)
			print_tree_helper(n->dir[1], indent + INDENT_STEP);

		for(int i = 0; i < indent; i++)
			fputs(" ", stdout);

		if (n->get_clr())
			cout<<"b";
		else
			cout<<"r";

		cout<<n->key<<endl;

		if (n->dir[0] != NULL)
			print_tree_helper(n->dir[0], indent + INDENT_STEP);
	}
	//-------------------------------------------
	void traversal(Node<T>* p,bool bStart,Node_Check* parent=NULL)
	{
		static int level;
		Node_Check* node_add;

		if (p == NULL) 
			return;

		node_add =  new Node_Check;

		if(bStart)
		{
			_all.clear();
			level = 0;
			node_add->blackPathed=0;
		}
		else
		{
			node_add->parent = parent;
			node_add->blackPathed=node_add->parent->blackPathed;
		}

		
		node_add->level = ++level;
		//cout << p->key<<"["<<level<<"]"<<",";
		node_add->clr = p->get_clr();

		if(node_add->clr)
			node_add->blackPathed++;

		if(p->dir[0]==NULL)
			node_add->dir[0]=-1;
		else
			node_add->dir[0]=p->dir[0]->get_clr();

		if(p->dir[1]==NULL)
			node_add->dir[1]=-1;
		else
			node_add->dir[1]=p->dir[1]->get_clr();

		_all.push_back(*node_add);

		traversal(p->dir[0],false,node_add);
		traversal(p->dir[1],false,node_add);
		level--;
	}
};

int getNumBetween10to99()
{
	static bool flag = true;
	if(flag)
	{
		srand(time(NULL));//for rand()
		flag = false;
	}
	return rand() % 90 + 10;
}

int main()//testing
{
	RBTree<double> rbt;
	int testKey =  -1;

	//loop insert
	for (int i = 0; i < 120; i++)
	{
		int x = getNumBetween10to99(); testKey = x;
		double y = x+(double)x/100;
		rbt.insert(x, y);
		if(!rbt.checkValidTree()){
			cout<<"error";system("pause");}
	}rbt.print_tree();


	//print existing 
	cout << endl;
	cout << testKey << endl;
	cout << rbt.search_node(testKey)->value << endl;
	cout << endl;


	//loop delete
	for (int i = 0; i < 170; i++)
	{
		int x = getNumBetween10to99(); testKey = x;
		rbt.erase(x);
		if(!rbt.checkValidTree()){
			cout<<"error";system("pause");}
	}rbt.print_tree();


	//print non-existing 
	cout<<endl;
	cout << testKey << endl;
	if(rbt.search_node(testKey)==NULL)
		cout << "NULL" << endl;
	else
		cout << rbt.search_node(testKey) << endl;
	cout<<endl;


	system("pause");
	return 0;
}
