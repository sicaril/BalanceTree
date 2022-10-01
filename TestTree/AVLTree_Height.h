#pragma once

#include "Tree.h"

class AVLTree_Height : public Tree
{
public:
	AVLTree_Height(void);
	virtual ~AVLTree_Height(void);

public:
	bool Insert(T& Data);

	bool Delete(T& Data);

	bool Check();

	bool Check(PF_Show pfShow);

	char * GetTreeName(){return "AVLTree Recursive With Node Height";}

private:
	TreeNode* _Insert( TreeNode ** Node, T& Data, bool * bSign);

	bool _Delete( TreeNode ** Node, T& Data, bool * bSign);

	bool CheckNode(TreeNode * Node,PF_Show pfShow);

	bool _Check(TreeNode * Node,PF_Show pfShow);

private:

	bool IsSingleRototeWithRight(TreeNode * pNode);
	bool IsSingleRototeWithLeft(TreeNode * pNode);

	void FixNodeHeight(TreeNode* Node);

	TreeNode* SingleRotateWithLeft(TreeNode * Node);
	TreeNode* SingleRotateWithRight(TreeNode * Node);
	TreeNode* DoubleRotateWithLeft(TreeNode * Node);
	TreeNode* DoubleRotateWithRight(TreeNode * Node);

};

