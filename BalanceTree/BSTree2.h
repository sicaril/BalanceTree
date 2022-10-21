#pragma once
#include "Tree.h"

class BSTree2 :
	public Tree
{
public:
	BSTree2(void);
	virtual ~BSTree2(void);

public:
	bool Insert(T& Data);
	bool Delete(T& Data);
	bool Check();

	char* GetTreeName(){return "BS Recursion";}

private:
	bool _Insert( TreeNode ** Node, T& Data, bool * bSign);
	bool _Delete( TreeNode ** Node, T& Data, bool * bSign);

	TreeNode* SingleRotateWithLeft(TreeNode * Node);
	TreeNode* SingleRotateWithRight(TreeNode * Node);
	TreeNode* DoubleRotateWithLeft(TreeNode * Node);
	TreeNode* DoubleRotateWithRight(TreeNode * Node);

private:

	bool CheckNode(TreeNode * Node,PF_Show pfShow);
	bool _Check(TreeNode * Node,PF_Show pfShow);
};

