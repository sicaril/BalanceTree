#pragma once
#include "Tree.h"

class BSTree : public Tree
{
public:
	BSTree(void);
	virtual ~BSTree(void);

	bool Insert(T& Data);
	bool Delete(T& Data);

	bool Check();
	char* GetTreeName(){return "BS Tree";}

public:

	TreeNode * SingleRotateWithLeft(TreeNode * Node);
	TreeNode * DoubleRotateWithLeft(TreeNode * Node);
	TreeNode * SingleRotateWithRight(TreeNode * Node);
	TreeNode * DoubleRotateWithRight(TreeNode * Node);

private:

	bool CheckNode(TreeNode * Node,PF_Show pfShow);
	bool _Check(TreeNode * Node,PF_Show pfShow);

};
