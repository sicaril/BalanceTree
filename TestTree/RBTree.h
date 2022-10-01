#pragma once
#include "Tree.h"

class RBTree : public Tree
{
public:
	RBTree(void);
	virtual ~RBTree(void);

	bool  Insert(T& Data); 

	bool  Insert2(T& Data); 

	bool Delete(T& Data);

	bool Delete2(T& Data);

	bool Check();

	char * GetTreeName(){return "RBTree Recursive";}

private:

	TreeNode*  _Insert(TreeNode** ppNode, T& Data, bool * bSign );
	TreeNode*  _Insert2(TreeNode** ppNode, T& Data, bool * bSign );

	bool _Check(TreeNode * Node);

	bool _Delete(TreeNode** Node, T& Data, bool * bSign);

	bool _Delete2(TreeNode** Node, T& Data, bool * bSign);

	//bool _Delete2(TreeNode** ppNode, T& Data, bool * bSign);

};
