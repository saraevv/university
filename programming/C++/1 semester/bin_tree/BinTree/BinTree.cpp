#include "pch.h"
#include <iostream>
#include <algorithm>
using namespace std;

struct Node
{
	int key;
	Node* left;
	Node* right;
	Node* ancestor;
};

class Tree
{
private:
	Node *  root;
public:
	Tree() :root(nullptr) {}

	void Push(int x)
	{
		Node* q = new Node;
		q->key = x;
		q->left = nullptr;
		q->right = nullptr;
		if (root == nullptr)
		{
			root = q;
			root->ancestor = nullptr;
		}
		else
		{
			Node* i = root;
			bool flag = true;
			while (flag)
			{
				if (q->key < i->key)
				{
					if (i->left == nullptr)
					{
						i->left = q;
						i->left->ancestor = q;
						flag = false;

					}
					else
					{
						i = i->left;
					}
				}
				else
				{
					if (i->right == nullptr)
					{
						i->right = q;
						i->right->ancestor = q;
						flag = false;
					}
					else
					{
						i = i->right;
					}
				}
			}
		}
	}

	void Print()
	{
		Print(root);
		cout << endl;
	}

	void Print(Node * t)
	{
		if (t)
		{
			Print(t->left);
			cout << t->key << " ";
			Print(t->right);
		}
	}

	int MaxLenght()
	{
		int n = 0;
		MaxLenght(n, root);
		if (root->left == 0 || root->right == 0)
			return n;
		else
			return n - 1;
	}

	int MaxLenght(int& ans, Node* pos)
	{
		if (pos == nullptr)
		{
			return 0;
		}
		int l = MaxLenght(ans, pos->left);
		int r = MaxLenght(ans, pos->right);
		ans = max(ans, l + r + 1);
		return max(l, r) + 1;
	}
};

int main()
{
	Tree T;
	cout << "Enter number of elements: ";
	int n;
	cin >> n;
	cout << "Enter elements:" << endl;
	int x;
	for (int i = 0; i < n; ++i)
	{
		cin >> x;
		T.Push(x);
	}
	T.Print();
	cout << T.MaxLenght() << endl;
	return 0;
}
