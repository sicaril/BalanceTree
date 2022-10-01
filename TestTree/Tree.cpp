#include "StdAfx.h"
#include "Tree.h"

Tree::Tree(void)
{
	Init();
}

Tree::~Tree(void)
{
	Release();
}

void Tree::Init()
{
	m_root = NULL;
}

void Tree::Release()
{
	Clear();
}

void Tree::Clear()
{
	_Clear(&m_root);
}

void Tree::_Clear(TreeNode** Node)
{
	if ( *Node == NULL )
		return;

	_Clear( &(*Node)->m_lchild );
	_Clear( &(*Node)->m_rchild );

	delete *Node;
	*Node = NULL;

}

bool Tree::Insert(T& Data)
{
	m_root = _Insert(m_root, Data);

	return true;
}

// TreeNode* Tree::Insert(T& Data)
// {
// 	m_root = _Insert(m_root, Data);
// 
// 	return m_root;
// }

TreeNode* Tree::_Insert( TreeNode * Node, T& Data)
{
	if ( Node == NULL )
	{
		Node = new TreeNode(Data);
		return Node;
	}

	if ( Data < Node->m_Data )
	{
		Node->m_lchild = _Insert( Node->m_lchild , Data);
	}
	else if ( Data > Node->m_Data )
	{
		Node->m_rchild = _Insert( Node->m_rchild, Data);
	}
	else
	{
		// 
	}
	return Node;
}

bool Tree::Insert2(T& Data)
{
	_Insert(&m_root, Data);

	return true;
}

TreeNode* Tree::_Insert(TreeNode ** ppNode, T& Data)
{
	TreeNode * pNode = *ppNode;
	if ( pNode == NULL )
	{
		*ppNode = new TreeNode(Data);
		return *ppNode;
	}

	if ( Data < pNode->m_Data )
	{
		_Insert( &pNode->m_lchild, Data );
	}
	else if ( Data > pNode->m_Data )
	{
		_Insert( &pNode->m_rchild, Data );
	}
	else
	{
		//
	}
	return *ppNode;
}

int Tree::Size()
{
	return _Size( m_root );
}

int Tree::_Size(TreeNode * Node)
{
	if ( Node == NULL )
		return 0;
	return _Size(Node->m_lchild) + _Size(Node->m_rchild) + 1;
}

TreeNode* Tree::Find(T& Data)
{
	return _Find(m_root, Data);
}

TreeNode* Tree::_Find(TreeNode * Node, T& Data)
{
	if ( Node == NULL )
		return NULL;

	if ( Data == Node->m_Data )
		return Node;
	else if( Data < Node->m_Data )
		return _Find(Node->m_lchild, Data);
	else
		return _Find(Node->m_rchild, Data);
}

TreeNode * Tree::FindMin(TreeNode * Node)
{
	if ( Node == NULL )
		return Node;
	if ( Node->m_lchild == NULL )
		return Node;
	return FindMin( Node->m_lchild );
}

void Tree::Traverse(PF_Show pfShow)
{
	_Traverse(m_root, pfShow);
}

void Tree::_Traverse(TreeNode * Node, PF_Show pfShow)
{
	if ( Node == NULL )
		return;
	if( pfShow )
		pfShow( Node->m_Data );
	_Traverse(Node->m_lchild, pfShow);
	_Traverse(Node->m_rchild, pfShow);
}

void Tree::Traverse(PF_Show2 pfShow)
{
	_Traverse(m_root, pfShow);
}

void Tree::_Traverse(TreeNode * Node, PF_Show2 pfShow)
{
	if ( Node == NULL )
		return;
	if( pfShow )
		pfShow( Node->m_Data, Node->u.m_sign );
	_Traverse(Node->m_lchild, pfShow);
	_Traverse(Node->m_rchild, pfShow);
}

bool IsLeaf(TreeNode * Node)
{
	return Node->m_lchild == NULL && Node->m_rchild == NULL; 
}

int GetNodeHeightDeep(TreeNode * Node)
{
	if ( Node == NULL )
		return -1;

	int nLeft = GetNodeHeightDeep(Node->m_lchild);
	int nRight = GetNodeHeightDeep(Node->m_rchild);

	if ( nLeft > nRight )
		return nLeft + 1;
	return nRight + 1;
}

void Show(T& Data)
{
	printf("%d ",Data);
}

void Show2(T& Data, int i)
{
	printf("%d(%d) ",Data, i);
}

void ShowError(T& Data)
{
	printf("\r\ncheck false %d\r\n", Data);
}