#pragma once
#include "tree.h"

class RBTree :
	public Tree
{
public:
	RBTree(void);
	virtual ~RBTree(void);

	bool Insert(T& Data);
	bool Delete(T& Data);

	bool Check();
	char* GetTreeName(){return "RB Tree";}

private:

	TreeNode* SingleRotateWithLeft(TreeNode * Node);
	TreeNode* DoubleRotateWithLeft(TreeNode * Node);
	TreeNode* SingleRotateWithRight(TreeNode * Node);
	TreeNode* DoubleRotateWithRight(TreeNode * Node);

private:

	int GetBlackNodeLeft(TreeNode * Node);
	int GetBlackNodeRight(TreeNode * Node);
	bool _Check(TreeNode * Node);


};

