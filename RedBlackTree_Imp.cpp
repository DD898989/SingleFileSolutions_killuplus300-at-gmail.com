#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#define INDENT_STEP  4
using namespace std;

//記得寫 template、check valid tree、test search(vector)
//記得寫 template、check valid tree、test search(vector)
//記得寫 template、check valid tree、test search(vector)還有關於duplicated keys: 餵入的東西的特徵要是獨一無二  ex:單字,時間,空間,身分證字號  甚至可用前兩位元納入這四個東西
//記得寫 template、check valid tree、test search(vector)還有因為紅黑樹跟字典樹相銃康  所以無法共存
//記得寫 template、check valid tree、test search(vector)你在字典樹  是不是不用浪費空間? 指向null就好這樣??
//記得寫 template、check valid tree、test search(vector)
//記得寫 template、check valid tree、test search(vector)

struct node
{
private:
	bool color;//0:red , 1:black

public:
	int key,value;
	node *dir[2], *parent;
	bool clr() { return this == NULL ? true : color; }
	void clr(bool c) { color = c; }
};


class RBTree
{
public:
	node *root;
	RBTree(){this->root = NULL;}
	int search(int);
	void insert(int,int);
	void erase(int);

private:
	node* new_node(int,int);
	node* maximum_node(node*);
	node* search_node(int);
	void replace_node(node*,node*);
	void rotate(node*,bool);
	
	void insert_cases(node*);
	void delete_cases(node*);

	node* grandparent(node*);
	node* sibling(node*);
	node* uncle(node*);
};

//Return Grandparent of Node 
node* RBTree::grandparent(node* n)
{
	return n->parent->parent;
}

//Return Sibling of Node 
node* RBTree::sibling(node* n)
{
	return n->parent->dir[n == n->parent->dir[0]];
}

//Return Uncle of Node 
node* RBTree::uncle(node* n)
{
	return sibling(n->parent);
}

//Creating New Node of Reb Black Tree
node* RBTree::new_node(int k, int v)
{
	node* result = new node;
	result->key = k;
	result->value = v;
	result->clr(false);
	result->dir[0] = NULL;
	result->dir[1] = NULL;
	result->parent = NULL;
	return result;
}

//Look Up through Node
node* RBTree::search_node(int key)
{
	node* n = this->root;
	while (n != NULL)
	{
		if (key == n->key)
			return n;
		else
			n = n->dir[key > n->key];
	}
	return n;
}

//RbTree Look Up
int RBTree::search(int key)
{
	node* n = search_node(key);
	return n == NULL ? NULL : n->value;
}

//Rotate left
void RBTree::rotate(node* n, bool bDir)//bDir---false:left rotate,true:right rotate
{
	node* N = n->dir[bDir];
	replace_node(n, N);

	node* temp = N->dir[!bDir];
	
	n->dir[bDir] = temp;
	if (temp != NULL)
		temp->parent = n;
	N->dir[!bDir] = n;

	n->parent = N;
}

//Replace a node*
void RBTree::replace_node(node* oldn, node* newn)
{
	if (oldn->parent == NULL)
		this->root = newn;
	else
		oldn->parent->dir[oldn != oldn->parent->dir[0]] = newn;

	if (newn != NULL)
		newn->parent = oldn->parent;
}

//Insert node* into RBTree
void RBTree::insert(int key, int value)
{
	node* inserted_node = NULL;
	if (this->root == NULL)
	{
		inserted_node =  new_node(key, value);
		this->root = inserted_node;
	}
	else
	{
		node* n = this->root;
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
void RBTree::insert_cases(node* n)
{
	if (n->parent == NULL)//case 1
		n->clr(true);
	else if (n->parent->clr())//case 2
		return;
	else if (!uncle(n)->clr())//case 3
	{
		n->parent->clr(true);
		uncle(n)->clr(true);
		grandparent(n)->clr(false);
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
		n->parent->clr(true);
		grandparent(n)->clr(false);
		if (n == n->parent->dir[0] && n->parent == grandparent(n)->dir[0])
			rotate(grandparent(n),false);
		else
			rotate(grandparent(n),true);
	}
}

//Delete Node from RBTree
void RBTree::erase(int key)
{
	node* child;
	node* n = search_node(key);
	if (n == NULL)
		return;

	if (n->dir[0] != NULL && n->dir[1] != NULL)
	{
		node* pred = maximum_node(n->dir[0]);
		n->key   = pred->key;
		n->value = pred->value;
		n = pred;
	}

	child = n->dir[1] == NULL ? n->dir[0]  : n->dir[1];

	if (n->clr())
	{
		n->clr(child->clr());
		delete_cases(n);
	}

	replace_node(n, child);
	free(n);
}
void RBTree::delete_cases(node* n)
{
	if (n->parent == NULL)//case 1
		return;
	else if (!sibling(n)->clr())//case 2
	{
		n->parent->clr(false);
		sibling(n)->clr(true);
		rotate(n->parent,n == n->parent->dir[0]);
	}
	
	//case 3
	if (n->parent->clr() && 
		sibling(n)->clr() &&
		sibling(n)->dir[0]->clr() && 
		sibling(n)->dir[1]->clr())
	{
		sibling(n)->clr(false);
		delete_cases(n->parent);
	}
	//case 4
	else if (!n->parent->clr() && 
		sibling(n)->clr() &&
		sibling(n)->dir[0]->clr() && 
		sibling(n)->dir[1]->clr())
	{
		sibling(n)->clr(false);
		n->parent->clr(true);
	}
	else//case 5&6
	{
		//case 5
		for(int b=0;b<=1;b++)
		{
			if (n == n->parent->dir[b] && 
				sibling(n)->clr() &&
				!sibling(n)->dir[b]->clr() && 
				sibling(n)->dir[!b]->clr())
			{
				sibling(n)->clr(false);
				sibling(n)->dir[b]->clr(true);
				rotate(sibling(n),b);
				break;
			}
		}
		
		//case 6
		sibling(n)->clr(n->parent->clr());
		n->parent->clr(true);

		bool flag = (n == n->parent->dir[0]);
		sibling(n)->dir[flag]->clr(true);
		rotate(n->parent,flag);
	}
}

//Returns Maximum node*
node* RBTree::maximum_node(node* n)
{
	while (n->dir[1] != NULL)
		n = n->dir[1];
	return n;
}

//Print RBTRee
void print_tree_helper(node* n, int indent)
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

	if (n->clr())
		cout<<"b";


	cout<<n->key<<endl;

	if (n->dir[0] != NULL)
		print_tree_helper(n->dir[0], indent + INDENT_STEP);
}
void print_tree(node* n)
{
	print_tree_helper(n, 0);
	puts("");
}

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



struct node2
{
	node2 *parent;
	bool clr;
	int key,value;
	int dir[2];
	int level;
	int includeMehowmanyBlacck;
};


vector<node2> vec;
void traversal(node* p,bool root,node2* parent=NULL)
{
	static int level;
	if(root){vec.clear();level=0;}

	if (!p) {return;}
	level++;
	//cout << p->key<<"["<<level<<"]"<<",";    // 先輸出樹根


	node2* add=  new node2;
	if(!root)
		add->parent = parent;
	add->clr=p->clr();

	if(level==1)
		add->includeMehowmanyBlacck=0;
	else
		add->includeMehowmanyBlacck=add->parent->includeMehowmanyBlacck;
	if(add->clr)
		add->includeMehowmanyBlacck++;


	add->key=p->key;
	add->level=level;
	add->value=p->value;
	if(p->dir[0]==NULL)
		add->dir[0]=-1;
	else
		add->dir[0]=p->dir[0]->clr();
	if(p->dir[1]==NULL)
		add->dir[1]=-1;
	else
		add->dir[1]=p->dir[1]->clr();
	vec.push_back(*add);



	traversal(p->dir[0],false,add); // 次輸出左子樹
    traversal(p->dir[1],false,add);// 後輸出右子樹
	level--;
}



//Main Contains Menu
int main()
{
	RBTree rbt;

	int test =  -1;
	for (int i = 0; i < 120; i++)
	{
		int x = getNumBetween10to99();
		int y = x*10;
		test = x;
		rbt.insert(x, y);
	}print_tree(rbt.root);



	//-------------------------------
	traversal(rbt.root,true);
	//-------------------------------
	vector<node2> ve2(vec);
	for(int i=ve2.size()-1;i>=0;i--)
		if(ve2[i].dir[0]!=-1||ve2[i].dir[1]!=-1)
			ve2.erase(ve2.begin() + i);
	auto max = max_element( ve2.begin(), ve2.end(), []( const node2 &a, const node2 &b ) {return a.level < b.level;} )->level; 
	auto min = min_element( ve2.begin(), ve2.end(), []( const node2 &a, const node2 &b ) {return a.level < b.level;} )->level; 
	if(min*2>=max)
		cout<<"ok"<<endl;
	if(rbt.root->clr()==true)
		cout<<"ok"<<endl;
	cout<<ve2.front().includeMehowmanyBlacck<<endl;
	cout<<ve2.back().includeMehowmanyBlacck<<endl;
	for (vector<node2>::iterator it=ve2.begin(); it != ve2.end()-1; ++it)
	{
		if(it->includeMehowmanyBlacck!=(it+1)->includeMehowmanyBlacck)
			cout<<"no ok"<<endl;
	}

	vector<node2> ve3(vec);
	for(int i=ve3.size()-1;i>=0;i--)
	{//這邊一定要大括弧
		if(ve3[i].clr!=0)
			ve3.erase(ve3.begin() + i);
	}
	for (vector<node2>::iterator it=ve3.begin(); it != ve3.end(); ++it)
	{
		if(it->dir[0]==0)
			cout<<"no ok"<<endl;
		if(it->dir[1]==0)
			cout<<"no ok"<<endl;
	}
	//-------------------------------




	cout<<endl;
	cout << test << endl;
	cout << rbt.search(test) << endl;
	cout<<endl;


	for (int i = 0; i < 170; i++)
	{
		int x = getNumBetween10to99();
		rbt.erase(x);
	}print_tree(rbt.root);
	

	system("pause");
	return 0;
}
