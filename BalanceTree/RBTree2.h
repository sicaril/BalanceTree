#pragma once
#include "tree.h"
class RBTree2 :
	public Tree
{
public:
	RBTree2(void);
	virtual ~RBTree2(void);

	bool Insert(T& Data);
	bool Delete(T& Data);

	bool Check();
	char* GetTreeName(){return "RB Recursion2";}

private:
	bool _Insert(TreeNode ** Node, T& Data, bool * bSign);
	bool _Delete(TreeNode ** Node, T& Data, bool * bSign);

	TreeNode * FixRotateWithLeft(TreeNode ** pNode, bool * sSign);
	TreeNode * FixRotateWithRight(TreeNode ** pNode, bool * sSign);

	TreeNode* SingleRotateWithLeft(TreeNode * Node);
	TreeNode* SingleRotateWithRight(TreeNode * Node);
	TreeNode* DoubleRotateWithLeft(TreeNode * Node);
	TreeNode* DoubleRotateWithRight(TreeNode * Node);

private:

	int GetBlackNodeLeft(TreeNode * Node);
	int GetBlackNodeRight(TreeNode * Node);
	bool _Check(TreeNode * Node);
};

