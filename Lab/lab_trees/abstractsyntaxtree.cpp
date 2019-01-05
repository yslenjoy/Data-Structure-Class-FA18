#include "abstractsyntaxtree.h"
#include "binarytree.h"
#include <iostream>
#include <stack>
#include <vector>
#include <string>

using namespace std;

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...
    return eval(root);
}
double AbstractSyntaxTree::eval(Node* subRoot) const{
	if (subRoot == NULL) {
		return 0.0;
	}
	if (subRoot->left == NULL && subRoot->right == NULL) {
		double value = stod(subRoot->elem);
		return value;
	}
	// if (subRoot->left == NULL && subRoot->right != NULL) {

	// }
	double leftValue = eval(subRoot->left);
	double rightValue = eval(subRoot->right);
	string rootValue = subRoot->elem;
	if (rootValue == "+") {
		return leftValue + rightValue;
	}
	else if (rootValue == "-") {
		return leftValue - rightValue;
	}
	else if (rootValue == "*") {
		return leftValue * rightValue;
	} else {
		return leftValue / rightValue; 
	}
	// if (rootValue == "/") {
	// 	return leftValue / rightValue;
	// }
}

