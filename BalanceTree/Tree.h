#pragma once
#include "TreeNode.h"
#include <new>
using namespace std;


// Ç°Ðò(¸ù×óÓÒ DLR)£¬ÖÐÐò(×ó¸ùÓÒ LDR)£¬ºóÐò(×óÓÒ¸ù LRD)
#define NS_INORDER		0
#define NS_PREORDER		1
#define NS_POSTORDER	2

class Tree
{
public:
	Tree(void);
	virtual ~Tree(void);

	void Init();
	void Release();

public:

	virtual bool Insert(T& Data);
	virtual bool Delete(T& Data);
	virtual bool Insert2(T& Data){return false;}
	virtual bool Delete2(T& Data){return false;}
	virtual bool Check(){return false;}
	virtual char* GetTreeName(){return "basic tree";}

public:

	int Size();
	void Clear();
	void Traverse(PF_Show pfShow, int nType = NS_PREORDER);
	void Traverse(PF_Show2 pfShow2, int nType = NS_PREORDER);

	TreeNode** GetParent(TreeNode * Node);

	TreeNode * FindMin(TreeNode * Node);
	TreeNode * FindMin2(TreeNode * Node);	// µÝ¹é

private:

	bool _Insert(TreeNode ** ppNode, T& Data);
	bool _Delete(TreeNode ** ppNode, T& Data);

	int _Size(TreeNode * Node);
	void _Clear(TreeNode ** ppNode);

	void _Tranvers(TreeNode * Node, PF_Show pfShow, int nType);
	void _Tranvers(TreeNode * Node, PF_Show2 pfShow2, int nType);

public:
	TreeNode * m_root;
};
