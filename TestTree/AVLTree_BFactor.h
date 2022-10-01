#pragma once

#include "Tree.h"

class AVLTree_BFactor : public Tree
{
public:
	AVLTree_BFactor(void);
	virtual ~AVLTree_BFactor(void);

public:
	bool Insert(T& Data);	// ·µ»Ø root

	bool Delete(T& Data);	// ·µ»Ø root

	bool Check();

	bool Check(PF_Show pfShow);

	char * GetTreeName(){return "AVLTree Recursive With Balance factor";}

private:
	TreeNode* _Insert( TreeNode ** Node, T& Data,bool* bSign);

	bool _Delete( TreeNode ** Node, T& Data, bool* bSign);

	bool CheckNode(TreeNode * Node,PF_Show pfShow);

	bool _Check(TreeNode * Node,PF_Show pfShow);

private:

	TreeNode* BalanceRotateWithLeft(TreeNode * Node);
	TreeNode* BalanceRotateWithRight(TreeNode * Node);

	TreeNode* SingleRotateWithLeft(TreeNode * Node);
	TreeNode* SingleRotateWithRight(TreeNode * Node);
	TreeNode* DoubleRotateWithLeft(TreeNode * Node);
	TreeNode* DoubleRotateWithRight(TreeNode * Node);

};


