#pragma once
#include "tree.h"
class RBTree3 :
	public Tree
{
public:
	RBTree3(void);
	virtual ~RBTree3(void);

	bool Insert(T& Data);
	bool Delete(T& Data);

	bool Check();
	char* GetTreeName(){return "RB Recursion3";}

private:
	bool _Insert(TreeNode ** Node, T& Data, bool * bSign);
	bool _Delete(TreeNode ** Node, T& Data, bool * bSign);

	TreeNode * FixBlackTreeWithLeft(TreeNode * Node);
	TreeNode * FixBlackTreeWithRight(TreeNode * Node);

	TreeNode* SingleRotateWithLeft(TreeNode * Node);
	TreeNode* SingleRotateWithRight(TreeNode * Node);
	TreeNode* DoubleRotateWithLeft(TreeNode * Node);
	TreeNode* DoubleRotateWithRight(TreeNode * Node);

private:

	int GetBlackNodeLeft(TreeNode * Node);
	int GetBlackNodeRight(TreeNode * Node);
	bool _Check(TreeNode * Node);
};

