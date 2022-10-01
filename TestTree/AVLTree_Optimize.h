#pragma once
#include "Tree.h"

class AVLTree_Optimize : public Tree
{
public:
	AVLTree_Optimize(void);
	virtual ~AVLTree_Optimize(void);

	bool Insert(T& Data);

	bool Delete(T& Data);

	bool Check();

	bool Check(PF_Show pfShow);

	char * GetTreeName(){return "AVLTree non-recursive";}

	T GetRootData(){
		if( m_root == NULL )
			return -1;
		return m_root->m_Data; 
	}

private:

	bool CheckNode(TreeNode * Node,PF_Show pfShow);
	bool _Check(TreeNode * Node,PF_Show pfShow);

	TreeNode ** GetParentNode(TreeNode* Node);

	TreeNode* BalanceRotateWithLeft(TreeNode * Node);
	TreeNode* BalanceRotateWithRight(TreeNode * Node);

	TreeNode* SingleRotateWithLeft(TreeNode * Node);
	TreeNode* SingleRotateWithRight(TreeNode * Node);
	TreeNode* DoubleRotateWithLeft(TreeNode * Node);
	TreeNode* DoubleRotateWithRight(TreeNode * Node);

};
