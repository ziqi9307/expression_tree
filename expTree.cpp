// Name        : expTree.cpp
// Author      : Ziqi Zhao
// Course      : CSCI 301
// Section     : 1
// Project     : 11
// Due Date    : Wednesday, May 1
// Description : This is a program used a pointer-based binary tree to
// implement and exercise expressions. Expressions represented in a binary
// tree are easy to compute recursively and when we print expressions, they
// can be represented to preorder, inorder and postorder. We also can
// compute the value of expression recursively.
//===============================================================

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <string.h>
using namespace std;

class Exptree {
public:
	//Constructor, initialized empty.
	Exptree() {root = NULL;}

	//Destructor.
	~Exptree();

	//Build the tree corresponding to a fully parenthesized
	//infix expression from the file stream.
	void build(istream & in_f);

	//Evaluate the expression such a tree represents.
	int value();

	//Preorder traversal and print expression of the tree.
	void prefix();

	//Postorder traversal and print expression of the tree.
	void postfix();

	//Inorder traversa and print expression of the tree.
	void infix();

private:
	//Declartions.

	struct Node {
		int operand;
		char optr;
		Node * left;
		Node * right;
	};
	Node * root;

	//private destructor function, delete nodes of the tree
	//base case: the tree is empty
	//smaller solution: delete left subtree, then right subtree, finally root
	void destroy(Node * r);

	//private build node function, called by th public one
	//base case: only one operand in the tree, just build it as a node,
	//left and right pointers are NULL;
	Node * r_build(istream & in_f);

	//private evaluate function
	//precondition: the parameter r is not NULL
	//base case: r only have operand
	int r_value(Node * r);

	//print the expression in preorder
	void r_prefix(Node * r);

	//print the expression in postorder
	void r_postfix(Node * r);

	//print the expression in inorder
	void r_infix(Node * r);
};

Exptree::~Exptree() {
	destroy(root);
}

void Exptree::destroy(Node * r) {
	if (r != NULL) {
		destroy(r->left);
		destroy(r->right);
		delete r;
	}

}

void Exptree::build(istream & in_f) {
	destroy(root);
	root = r_build(in_f);
}
Exptree::Node * Exptree::r_build(istream & in_f) {
	char ch;
	Node * temp;
	in_f >> ch;
	if (isdigit(ch)) {
		temp = new Node;
		temp->operand = ch - '0';
		temp->left = NULL;
		temp->right = NULL;
	}
	else {
		temp = new Node;
		temp->left = r_build(in_f);
		in_f >> temp->optr;
		temp->right = r_build(in_f);
		in_f >> ch;
	}
	return temp;
}

int Exptree::value(){
	return r_value(root);
}

int Exptree::r_value(Node * r) {
	if (r->left == NULL) {
		return r->operand;
	}
	else {
		int l_val = r_value(r->left);
		int r_val = r_value(r->right);
		if (r->optr == '+')
			return l_val + r_val;
		else if (r->optr == '-')
			return l_val - r_val;
		else if (r->optr == '*')
			return l_val * r_val;
		else
			return l_val / r_val;
	}
}

void Exptree::prefix() {
	r_prefix(root);
}

void Exptree::r_prefix(Node * r) {
	if (r->left == NULL) {
		cout << r->operand <<' ';
	}
	else {
		cout << r->optr << ' ';
		r_prefix(r->left);
		r_prefix(r->right);
	}
}

void Exptree::postfix() {
	r_postfix(root);
}

void Exptree::r_postfix(Node * r) {
	if (r->left == NULL) {
		cout << r->operand << ' ';
	}
	else {
		r_postfix(r->left);
		r_postfix(r->right);
		cout << r->optr << ' ';
	}
}

void Exptree::infix() {
	r_infix(root);
}

void Exptree::r_infix(Node * r) {
	if (r->left == NULL) {
		cout << r->operand << ' ';
	}
	else {
		cout << " ( ";
		r_infix(r->left);
		cout << r->optr <<' ';
		r_infix(r->right);
		cout << " ) ";
	}
}

int main() {
	Exptree * tree = new Exptree();
	fstream file;
	string name;

	char buffer[256];
	cout << "Enter input file name: ";
	cin >> name;
	cout << endl;
	file.open(name.c_str(), ios::in);

	while (!file.eof()) {
		file.getline(buffer,256, '\n');
		tree->build(file);
		cout << "Preorder:  ";
		tree->prefix();
		cout << endl;
		cout << "Inorder:  ";
		tree->infix();
		cout << endl;
		cout << "Postorder: ";
		tree->postfix();
		cout << endl;
		cout << "Value = " << tree->value() << endl;
		cout << endl;
	}
	file.close();

	return 0;
}
