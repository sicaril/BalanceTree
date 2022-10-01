#pragma once
#include "Tree.h"

class RBTree_Optimize : public Tree
{
public:
	RBTree_Optimize(void);
	virtual ~RBTree_Optimize(void);

	bool Insert(T& Data);

	bool Delete(T& Data);

	bool Check();

	char * GetTreeName(){return "RBTree non-recursive";}

private:
	TreeNode ** GetParentNode(TreeNode* Node);

	TreeNode * SingleRotateWithLeft(TreeNode * Node);
	TreeNode * DoubleRotateWithLeft(TreeNode * Node);
	TreeNode * SingleRotateWithRight(TreeNode * Node);
	TreeNode * DoubleRotateWithRight(TreeNode * Node);

private:
	bool _Check(TreeNode * Node);
	int GetBlackNodeLeft(TreeNode * Node);
	int GetBlackNodeRight(TreeNode * Node);
};
