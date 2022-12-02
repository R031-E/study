#include <iostream>
#include <string>

using namespace std;


struct Tree
{
	int key;
	int height;
	Tree* Left; //Smaller offspring
	Tree* Right; //Bigger offspring
	Tree(int k)
	{
		key = k;
		Left = Right = NULL;
		height = 1;
	}
};

struct Trunk
{
	Trunk* prev;
	string str;

	Trunk(Trunk* prev, string str)
	{
		this->prev = prev;
		this->str = str;
	}
};

#pragma region check
void Check(int value) // проверка ввода
{
	while ((cin.fail()) || (cin.get() != '\n') || (value < 1) || (value > 6))
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Invalid input. Try again: ";
		cin >> value;
	}
}

void CheckElement(int value) // проверка ввода
{
	while ((cin.fail()) || (cin.get() != '\n'))
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Invalid input. Try again: ";
		cin >> value;
	}
}
#pragma endregion check

int getkey(Tree* P) 
{
	return P ? P->height : 0;
}

int height(Tree* P)
{
	return P ? P->height : 0;
}

int bfactor(Tree* P)
{
	return height(P->Right) - height(P->Left);
}

void fixheight(Tree* P)
{
	int hL = height(P->Left);
	int hR = height(P->Right);
	P->height = ((hL > hR) ? hL : hR) + 1;
}

Tree* rotateright(Tree* P)
{
	Tree* Q = P->Left;
	P->Left = Q->Right;
	Q->Right = P;
	fixheight(P);
	fixheight(Q);
	return Q;
}

Tree* rotateleft(Tree* Q)
{
	Tree* P = Q->Right;
	Q->Right = P->Left;
	P->Left = Q;
	fixheight(Q);
	fixheight(P);
	return P;
}

Tree* balance(Tree* P)
{
	fixheight(P);
	if (bfactor(P) == 2) 
	{
		if (bfactor(P->Right) < 0) P->Right = rotateright(P->Right);
		return rotateleft(P);
	}
	if (bfactor(P) == -2)
	{
		if (bfactor(P->Left) > 0) P->Left = rotateleft(P->Left);
		return rotateright(P);
	}
	return P;
}

Tree* insert(Tree* P, int k)
{
	if (!P) return new Tree(k);
	if (k < P->key) P->Left = insert(P->Left, k);
	else P->Right = insert(P->Right, k);
	return balance(P);
}

Tree* findmin(Tree* P)
{
	return P->Left ? findmin(P->Left) : P;
}

Tree* removemin(Tree* P) 
{
	if (P->Left == NULL) return P->Right;
	P->Left = removemin(P->Left);
	return balance(P);
}

Tree* remove(Tree* P, int k) 
{
	if (!P) return 0;
	if (k < P->key) P->Left = remove(P->Left, k);
	else if (k > P->key) P->Right = remove(P->Right, k);
	else 
	{
		Tree* q = P->Left;
		Tree* r = P->Right;
		delete P;
		if (!r) return q;
		Tree* min = findmin(r);
		min->Right = removemin(r);
		min->Left = q;
		return balance(min);
	}
	return balance(P);
}

Tree* search(Tree*& P, int _key, int steps)
{
	if (_key == P->key)
	{
		cout << "Found value: " << P->key << " in " << steps++ << " steps.\n";
		return P;
	}
	steps++;
	if (_key < P->key)
	{
		if (P->Left == NULL)
		{
			cout << "No such element in the tree.\n";
			return NULL;
		}
			steps++;
			search(P->Left, _key, steps);
	}
	else
	{
		if (P->Right == NULL)
		{
			cout << "No such element in the tree.\n";
			return NULL;
		}
			steps++;
			search(P->Right, _key, steps);
	}
}

void showTrunks(Trunk* p)
{
	if (p == nullptr) {
		return;
	}

	showTrunks(p->prev);
	cout << p->str;
}

void printTree(Tree* root, Trunk* prev, bool isLeft)
{
	if (root == nullptr) {
		return;
	}

	string prev_str = "    ";
	Trunk* trunk = new Trunk(prev, prev_str);

	printTree(root->Right, trunk, true);

	if (!prev) {
		trunk->str = "———";
	}
	else if (isLeft)
	{
		trunk->str = ".———";
		prev_str = "   |";
	}
	else {
		trunk->str = "`———";
		prev->str = prev_str;
	}

	showTrunks(trunk);
	cout << " " << root->key << endl;

	if (prev) {
		prev->str = prev_str;
	}
	trunk->str = "   |";

	printTree(root->Left, trunk, false);
}

void showlist(Tree* P)
{
	if (!P) return;
	showlist(P->Left);
	cout << P->key << "	";
	showlist(P->Right);
}

void print_child(Tree* P, Tree* parent) {
	if (!P || P == parent) return;
	print_child(P->Left, parent);
	cout << P->key << " ";
	print_child(P->Right, parent);
}
void print_parent(Tree* parent) {
	cout << "Родитель: " << parent->key << ". Потомки: ";
	if (parent->Left != NULL) {
		Tree* child = parent->Left;
		print_child(child, parent);
	}
	if (parent->Right != NULL) {
		Tree* child = parent->Right;
		print_child(child, parent);
	}
	cout << "\n";
}
void prev(Tree* P) {
	if (!P || (P->Left == NULL && P->Right == NULL)) return;
	prev(P->Left);
	print_parent(P);
	prev(P->Right);
}

int main()
{
	setlocale(LC_ALL, "ru");
	int option, element;
	Tree* Root = NULL;
	do
	{
		cout << "1) Add element\n2) Remove element\n3) Search element\n4) Show tree\n5) Show in list\n6) Show parents and offsprings\n7) Exit\n";
		cin >> option;
		cout << endl;
		Check(option);
		switch (option)
		{
		case 1:
			cout << "Element: ";
			cin >> element;
			CheckElement(element);
			cout << "\n";
			if (Root != NULL) 
			{
				if (search(Root, element, 0) != NULL)
				{
					cout << "Unique elements only.\n";
					break;
				}
				else 
				{
					Root = insert(Root, element);
					cout << "Added.\n";
					break;
				}
			}
			Root = insert(Root, element);
			cout << "Added.\n";
			break;
		case 2:
			cout << "Element: ";
			cin >> element;
			CheckElement(element);
			cout << "\n";
			Root = remove(Root, element);
			cout << "Element removed.\n";
			break;
		case 3:
			cout << "Element: ";
			cin >> element;
			CheckElement(element);
			cout << "\n";
			search(Root, element, 0);
			break;
		case 4:
			printTree(Root, nullptr, false);
			break;
		case 5:
			showlist(Root);
			cout << "\n";
			break;
		case 6:
			prev(Root);
			break;
		case 7:
			return 0;
		}
	} while (option != 6);
}