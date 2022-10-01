#pragma once

#include "TreeNode.h"

class Tree
{
public:
	Tree(void);
	virtual ~Tree(void);

	void Init();
	void Release();

	virtual bool Insert(T& Data);

	virtual bool Insert2(T& Data);

	virtual bool Delete(T& Data){return false;}

	virtual bool Delete2(T& Data){return false;}

	virtual bool Check(){return false;}

	virtual char * GetTreeName(){return "base tree";}

public:
	//TreeNode* Insert(T& Data);

	TreeNode* Find(T& Data);

	//void Insert2(T& Data);

	void Traverse(PF_Show pfShow);

	void Traverse(PF_Show2 pfShow);

	int Size();

	void Clear();

	TreeNode * FindMin(TreeNode * Node);

public:

	TreeNode* _Insert( TreeNode * Node, T& Data);

	TreeNode* _Insert( TreeNode ** Node, T& Data);

	TreeNode* _Find(TreeNode * Node, T& Data);

	void _Traverse(TreeNode * Node, PF_Show pfShow);

	void _Traverse(TreeNode * Node, PF_Show2 pfShow);

	int _Size(TreeNode * Node);

	void _Clear(TreeNode** Node);

public:
	TreeNode * m_root;
};

bool IsLeaf(TreeNode * Node);

int GetNodeHeightDeep(TreeNode * Node);

void Show(T& Data);

void Show2(T& Data, int i);

void ShowError(T& Data);
