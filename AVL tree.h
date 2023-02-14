#pragma once
#include"Node.h"
#include <vector>
struct AVL
{
	node data;
	int height;
	AVL* left;
	AVL* right;

	AVL(node set)
	{
		this->data = set;
		this->height = 1;
		this->left = this->right = NULL;
	}
};

int height(AVL* p)
{
	if (p == NULL)
	{
		return 0;
	}
	else
	{
		return p->height;
	}
}

AVL* successor(AVL* root)
{
	AVL* temp = root;
	while (temp->left != NULL && temp)
	{
		temp = temp->left;
	}
	return temp;
}

int Balance(AVL* root)
{
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		return (height(root->left)) - (height(root->right));
	}
}

AVL* RR(AVL* root)
{
	AVL* x = root->left;
	AVL* y = x->right;

	x->right = root;
	root->left = y;

	x->height = max(height(x->left), height(x->right)) + 1;
	root->height = max(height(root->left), height(root->right)) + 1;

	return x;
}

AVL* LR(AVL* root) {
	AVL* x = root->right;
	AVL* T2 = x->left;

	x->left = root;
	root->right = T2;

	root->height = max(height(root->left), height(root->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;
	
	return x;
}

AVL* insert(node val, AVL* root)
{
	if (root == NULL)
	{

		return new AVL(val);
	}
	if (val.id < root->data.id)
	{
		root->left = insert(val, root->left);
	}
	else if (val.id > root->data.id)
	{
		root->right = insert(val, root->right);
	}
	else
	{
		//root->left = insert(val, root->left);
		return root;
	}


	root->height = max(height(root->left), height(root->right)) + 1;

	node balance_Factor = Balance(root);

	//Left case
	if (balance_Factor.id > 1)
	{
		if (val.id < root->left->data.id)
		{
			root = RR(root);
		}
	}
	//Right case
	if (balance_Factor.id < -1)
	{
		if (val.id > root->right->data.id)
		{
			root = LR(root);
		}
	}
	//Left Right case
	if (balance_Factor.id > 1)
	{
		if (val.id > root->left->data.id)
		{
			root->left = LR(root->left);
			root = RR(root);
		}
	}
	//Right Left case
	if (balance_Factor.id < -1)
	{
		if (val.id < root->right->data.id)
		{
			root->right = RR(root->right);
			root = LR(root);
		}
	}

	return root;
}

AVL* delete_node(int val, AVL* root)
{
	if (root == NULL)
	{
		return NULL;
	}
	else if (val < root->data.id)
	{
		root->left = delete_node(val, root->left);
	}
	else if (val > root->data.id)
	{
		root->right = delete_node(val, root->right);
	}
	else
	{
		if (root->left == NULL)
		{
			AVL* temp = root->right;
			delete root;
			return temp;
		}
		else if (root->right == NULL)
		{
			AVL* temp = root->left;
			delete root;
			return temp;
		}
		else
		{
			AVL* temp = successor(root->right);
			root->data = temp->data;
			root->right = delete_node(temp->data.id, root->right);

		}
	}

	if (root == NULL)
	{
		return root;
	}

	int BalanceFactor = Balance(root);

	if (BalanceFactor > 1)
	{
		if (height(root->left) > -1)
			root = RR(root);
	}

	// Left Right Case 
	if (BalanceFactor > 1)
	{
		if (height(root->left) <= -1)
			root->left = LR(root->left),
			root = RR(root);
	}

	// Right Right Case 
	if (BalanceFactor < -1)
		if (height(root->right) < 1)
			root = LR(root);

	// Right Left Case 
	if (BalanceFactor < -1)
	{
		if (height(root->right) > 0)
			root->right = RR(root->right),
			root = LR(root);
	}

	return root;
}


//Point searchs
void AVLPointSearchID(AVL* p, int key)
{
	if (p != 0)
	{
		if (p->data.id == key) {
			cout << p->data << ' ';
		}
		AVLPointSearchID(p->left, key);
		AVLPointSearchID(p->right, key);

	}

}

void AVLPointSearchDB(AVL* p, float key)
{
	if (p != 0)
	{
		if (p->data.DR == key) {
			cout << p->data << ' ';
		}
		AVLPointSearchDB(p->left, key);
		AVLPointSearchDB(p->right, key);

	}

}

void AVLPointSearchYear(AVL* p, int key)
{
	if (p != 0)
	{
		if (p->data.year == key) {
			cout << p->data << ' ';
		}
		AVLPointSearchYear(p->left, key);
		AVLPointSearchYear(p->right, key);

	}

}

void AVLPointSearchD(AVL* p, int key)
{
	if (p != 0)
	{
		if (p->data.deaths == key) {
			cout << p->data << ' ';
		}
		AVLPointSearchD(p->left, key);
		AVLPointSearchD(p->right, key);

	}

}

void AVLPointSearchCause(AVL* p, string key)
{
	if (p != 0)
	{
		if (p->data.cause == key) {
			cout << p->data << ' ';
		}
		AVLPointSearchCause(p->left, key);
		AVLPointSearchCause(p->right, key);

	}

}

void AVLPointSearchState(AVL* p, string key)
{
	if (p != 0)
	{

		AVLPointSearchCause(p->left, key);
		if (p->data.state == key) {
			cout << p->data << ' ';
		}
		AVLPointSearchCause(p->right, key);

	}

}

//Ranger searchs
void AVLRangeSearchID(AVL* p, int low, int high)
{
	if (p != 0)
	{

		AVLRangeSearchID(p->left, low, high);
		if (p->data.id >= low && p->data.id <= high) {
			cout << p->data << ' ';
		}
		AVLRangeSearchID(p->right, low, high);

	}
}

void AVLRangeSearchYear(AVL* p, int low, int high)
{
	if (p != 0)
	{

		AVLRangeSearchYear(p->left, low, high);
		if (p->data.year >= low && p->data.year <= high) {
			cout << p->data << ' ';
		}
		AVLRangeSearchYear(p->right, low, high);

	}
}

void AVLRangeSearchD(AVL* p, int low, int high)
{
	if (p != 0)
	{

		AVLRangeSearchD(p->left, low, high);
		if (p->data.deaths >= low && p->data.deaths <= high) {
			cout << p->data << ' ';
		}
		AVLRangeSearchD(p->right, low, high);

	}
}

void AVLRangeSearchDR(AVL* p, int low, int high)
{
	if (p != 0)
	{

		AVLRangeSearchDR(p->left, low, high);
		if (p->data.DR >= low && p->data.DR <= high) {
			cout << p->data << ' ';
		}
		AVLRangeSearchDR(p->right, low, high);

	}
}


//Triversals
void AVLPostOrderTransversal(AVL* p)
{

	if (p != 0)
	{


		AVLPostOrderTransversal(p->left);
		AVLPostOrderTransversal(p->right);
		cout << p->data << ' ';

	}
}

void AVLInOrderTransversal(AVL* p)
{
	if (p != 0)
	{

		AVLInOrderTransversal(p->left);

		cout << p->data << ' ';

		AVLInOrderTransversal(p->right);

	}
}

void AVLPreOrderTransversal(AVL* p)
{
	if (p != 0)
	{

		cout << p->data << ' ';

		AVLPreOrderTransversal(p->left);
		AVLPreOrderTransversal(p->right);

	}
}

//UpdateQuery
void AVLUpdateQuery(AVL* p,int id) {

	string cause;
	string state;

	if (p != 0)
	{

		AVLUpdateQuery(p->left,id);
		if (p->data.id == id) {
			int temp;
			cout << p->data;
			cout << "Select Query to Update:\n\t1-Year Of Death\n\t2-Cause of Death\n\t3-State\n\t4-No of Deaths\n\t5-Death Rate\n\t6-Go Back\nEnter Your Choice : ";
			cin >> temp;
			switch (temp) {
			case 1:
				int year;
				cout << "Enter New Year of Death : ";
				cin >> year;
				p->data.year = year;
				break;
			case 2:
				cout << "Enter New Cause of Death : ";
				cin >> cause;
				p->data.cause = cause;
				break;
			case 3:
				cout << "Enter New State of Death : ";
				cin >> state;
				p->data.state = state;
				break;
			case 4:
				int deaths;
				cout << "Enter New No of Death : ";
				cin >> deaths;
				p->data.deaths = deaths;
				break;
			case 5:
				int DR;
				cout << "Enter New Death Rate of Deaths : ";
				cin >> DR;
				p->data.DR = DR;
				break;
			case 6:
				return;
				break;
			}


			return;
		}
		AVLUpdateQuery(p->right,id);

	}
}




void AVLGetNodes(AVL*p,vector<node>& Nodes) {
	if (p != 0)
	{

		AVLGetNodes(p->left,Nodes);

		Nodes.push_back(p->data);
		AVLGetNodes(p->right,Nodes);

	}
}

void AVLPointSearchhwhereYS(AVL* p, int key, string state)
{
	if (p != 0)
	{
		if (p->data.year == key && p->data.state == state) {
			cout << p->data << ' ';
		}
		AVLPointSearchhwhereYS(p->left, key,state);
		AVLPointSearchhwhereYS(p->right, key,state);

	}

}


void AVLPointSearchhwhereYC(AVL* p, int key, string state)
{
	if (p != 0)
	{
		if (p->data.year == key && p->data.cause == state) {
			cout << p->data << ' ';
		}
		AVLPointSearchhwhereYS(p->left, key, state);
		AVLPointSearchhwhereYS(p->right, key, state);

	}

}