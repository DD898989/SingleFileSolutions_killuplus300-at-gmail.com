#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#define INDENT_STEP  4
using namespace std;

//還有關於duplicated keys: 餵入的東西的特徵要是獨一無二  ex:單字,時間,空間,身分證字號  甚至可用前兩位元納入這四個東西
//還有因為紅黑樹跟字典樹相銃康  所以無法共存
//你在字典樹  是不是不用浪費空間? 指向null就好這樣??
//Node 不能由code直接存取  而是RBT內部做存取  要怎麼做??
//只有color有get太奇怪  照理來說每個都要有  所以這邊考慮用friend class 可是怎麼用呢

template <class T> struct Node
{
	//friend class RBTree<T>;

private:
	bool color;//0:red , 1:black      set private because of get_clr()

public:
	int key;
	T value;
	Node *dir[2], *parent;
	bool get_clr() { return this == NULL ? true : color; }
	void set_clr(bool c) { color = c; }
};

template <class T> class RBTree
{
public:
	RBTree<T>(){this->_root = NULL;}
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
		return n;
	}
	Node<T>* get_root(){return this->_root;}//for checking valid rbt
	void print_tree(Node<T>* n)
	{
		print_tree_helper(n, 0);
		puts("");
	}
	void checkValidRBT(RBTree<T> &rbt)
{
	traversal(rbt.get_root(),true);
	if(rbt.get_root()->get_clr())//_root一定是黑色。
	{}
	else
		cout<<"no ok"<<endl;
	vector<node_check> ve2(vec);//站在任何一個Node上，所有從該Node走到其任意descendant leaf的path上之黑色Node數必定相同~~~~~~不完全版驗證
	for(int i=ve2.size()-1;i>=0;i--)
		if(ve2[i].dir[0]!=-1||ve2[i].dir[1]!=-1)
			ve2.erase(ve2.begin() + i);
	//cout<<ve2.front().includeMehowmanyBlacck<<endl;
	//cout<<ve2.back().includeMehowmanyBlacck<<endl;
	for (vector<node_check>::iterator it=ve2.begin(); it != ve2.end()-1; ++it)
	{
		if(it->includeMehowmanyBlacck!=(it+1)->includeMehowmanyBlacck)
			cout<<"no ok"<<endl;
	}
	vector<node_check> ve3(vec);//如果某個Node是紅色，那麼其兩個child必定是黑色，不能有兩個紅色Node相連
	for(int i=ve3.size()-1;i>=0;i--)
	{
		if(ve3[i].clr!=0)
			ve3.erase(ve3.begin() + i);
	}
	for (vector<node_check>::iterator it=ve3.begin(); it != ve3.end(); ++it)
	{
		if(it->dir[0]==0)
			cout<<"no ok"<<endl;
		if(it->dir[1]==0)
			cout<<"no ok"<<endl;
	}
}

private:
	Node<T>* _root;
	Node<T>* grandparent(Node<T>* n)
	{
		return n->parent->parent;
	}
	Node<T>* sibling(Node<T>* n)
	{
		return n->parent->dir[n == n->parent->dir[0]];
	}
	Node<T>* uncle(Node<T>* n)
	{
		return sibling(n->parent);
	}
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
	Node<T>* maximum_node(Node<T>* n)//returns maximum Node
	{
		while (n->dir[1] != NULL)
			n = n->dir[1];
		return n;
	}
	void replace_node(Node<T>* oldn, Node<T>* newn)//replace a Node
	{
		if (oldn->parent == NULL)
			this->_root = newn;
		else
			oldn->parent->dir[oldn != oldn->parent->dir[0]] = newn;

		if (newn != NULL)
			newn->parent = oldn->parent;
	}
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


		cout<<n->key<<endl;

		if (n->dir[0] != NULL)
			print_tree_helper(n->dir[0], indent + INDENT_STEP);
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

struct node_check
{
	node_check *parent;
	bool clr;
	int key,value;
	int dir[2];
	int level;
	int includeMehowmanyBlacck;
};

vector<node_check> vec;

template <class T> void traversal(Node<T>* p,bool _root,node_check* parent=NULL)
{
	static int level;
	if(_root){vec.clear();level=0;}

	if (!p) {return;}
	level++;
	//cout << p->key<<"["<<level<<"]"<<",";    // 先輸出樹根


	node_check* add=  new node_check;
	if(!_root)
		add->parent = parent;
	add->clr=p->get_clr();

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
		add->dir[0]=p->dir[0]->get_clr();
	if(p->dir[1]==NULL)
		add->dir[1]=-1;
	else
		add->dir[1]=p->dir[1]->get_clr();
	vec.push_back(*add);



	traversal(p->dir[0],false,add); // 次輸出左子樹
	traversal(p->dir[1],false,add);// 後輸出右子樹
	level--;
}

int main()//testing
{
	RBTree<double> rbt;
	int test =  -1;

	//loop insert
	for (int i = 0; i < 120; i++)
	{
		int x = getNumBetween10to99(); test = x;
		double y = x+(double)x/100;
		rbt.insert(x, y);
		rbt.checkValidRBT(rbt);
	}rbt.print_tree(rbt.get_root());


	//print existing 
	cout << endl;
	cout << test << endl;
	cout << rbt.search_node(test)->value << endl;
	cout << endl;


	//loop delete
	for (int i = 0; i < 170; i++)
	{
		int x = getNumBetween10to99(); test = x;
		rbt.erase(x);
		rbt.checkValidRBT(rbt);
	}rbt.print_tree(rbt.get_root());


	//print non-existing 
	cout<<endl;
	cout << test << endl;
	if(rbt.search_node(test)==NULL)
		cout << "NULL" << endl;
	else
		cout << rbt.search_node(test) << endl;
	cout<<endl;


	//print existing 
	cout << endl;
	cout << rbt.get_root()->key << endl;
	cout << rbt.search_node(rbt.get_root()->key)->value << endl;
	cout << endl;



	system("pause");
	return 0;
}
