#pragma once
#include "tree.h"

class AVLTree2 :
	public Tree
{
public:
	AVLTree2(void);
	virtual ~AVLTree2(void);

	bool Insert(T& Data);
	bool Delete(T& Data);

	bool Check();
	char* GetTreeName(){return "AVL Recursion";}

private:

	bool _Insert(TreeNode ** ppNode, T& Data, bool * bSign);
	bool _Delete(TreeNode ** ppNode, T& Data, bool * bSign);

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

