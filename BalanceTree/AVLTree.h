#pragma once
#include "tree.h"

class AVLTree :
	public Tree
{
public:
	AVLTree(void);
	~AVLTree(void);

	bool Insert(T& Data);
	bool Delete(T& Data);

	bool Check();
	char* GetTreeName(){return "AVL Tree";}

private:

	TreeNode * BalanceRotateWithLeft(TreeNode * Node);
	TreeNode * BalanceRotateWithRight(TreeNode * Node);

	TreeNode * SingleRotateWithLeft(TreeNode* Node);
	TreeNode * DoubleRotateWithLeft(TreeNode* Node);
	TreeNode * SingleRotateWithRight(TreeNode* Node);
	TreeNode * DoubleRotateWithRight(TreeNode* Node);

private:
	bool CheckNode(TreeNode * Node,PF_Show pfShow);
	bool _Check(TreeNode * Node,PF_Show pfShow);

};

