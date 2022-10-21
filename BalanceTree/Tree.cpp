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

bool Tree::Insert(T& Data)
{
	return _Insert(&m_root, Data);
}

bool Tree::_Insert(TreeNode ** ppNode, T& Data)
{
	bool bRet = false;
	TreeNode * pNode = *ppNode;
	if ( pNode == NULL )
	{
		*ppNode = new TreeNode(Data);
		return *ppNode != NULL;
	}

	if ( Data < pNode->m_Data )
	{
		bRet = _Insert(&pNode->m_lchild, Data);
	}
	else if ( Data > pNode->m_Data )
	{
		bRet = _Insert(&pNode->m_rchild, Data);
	}
	else
	{
		bRet = false;
	}
	return bRet;
}

bool Tree::Delete(T& Data)
{
	return _Delete(&m_root, Data);
}

bool Tree::_Delete(TreeNode ** ppNode, T& Data)
{
	bool bRet = false;
	TreeNode * pNode = *ppNode;

	if ( Data < pNode->m_Data )
	{
		bRet = _Delete(&pNode->m_lchild, Data);
	}
	else if( Data > pNode->m_Data )
	{
		bRet = _Delete(&pNode->m_rchild, Data);
	}
	else
	{
		if ( pNode->m_rchild )
		{
			TreeNode * tmp = FindMin(pNode->m_rchild);
			pNode->m_Data = tmp->m_Data;

			bRet = _Delete(&pNode->m_rchild, pNode->m_Data );
		}
		else
		{
			TreeNode * tmp = pNode->m_lchild;

			delete pNode;

			*ppNode = tmp;
		}
	}
	return bRet;
}

int Tree::Size()
{
	return _Size(m_root);
}

int Tree::_Size(TreeNode * Node)
{
	if ( Node == NULL )
		return 0;
	return _Size(Node->m_lchild) + _Size(Node->m_rchild) + 1;
}

void Tree::Clear()
{
	_Clear(&m_root);
}

void Tree::_Clear(TreeNode ** ppNode)
{
	if ( *ppNode == NULL )
		return ;

	_Clear(&(*ppNode)->m_lchild);
	_Clear(&(*ppNode)->m_rchild);

	delete *ppNode;
	*ppNode = NULL;
}

void Tree::Traverse(PF_Show pfShow, int nType)
{
	_Tranvers(m_root, pfShow, nType);
}

void Tree::Traverse(PF_Show2 pfShow2, int nType)
{
	_Tranvers(m_root, pfShow2, nType);
}

TreeNode** Tree::GetParent(TreeNode * Node)
{
	TreeNode * _parent = Node->m_parent;

	if ( _parent == NULL )
		return &m_root;
	
	if ( Node == _parent->m_lchild )
		return &_parent->m_lchild;
	return &_parent->m_rchild;
}

void Tree::_Tranvers(TreeNode * Node, PF_Show pfShow, int nType)
{
	if ( Node == NULL )
		return;

	switch(nType)
	{
	case NS_PREORDER:
		{
			if(pfShow != NULL)
				pfShow(Node->m_Data);
			_Tranvers(Node->m_lchild, pfShow, nType);
			_Tranvers(Node->m_rchild, pfShow, nType);
			break;
		}
	case NS_INORDER:
		{
			_Tranvers(Node->m_lchild, pfShow, nType);
			if(pfShow != NULL)
				pfShow(Node->m_Data);
			_Tranvers(Node->m_rchild, pfShow, nType);
			break;
		}
	case NS_POSTORDER:
		{
			_Tranvers(Node->m_lchild, pfShow, nType);
			_Tranvers(Node->m_rchild, pfShow, nType);
			if(pfShow != NULL)
				pfShow(Node->m_Data);
			break;
		}
	}
}

void Tree::_Tranvers(TreeNode * Node, PF_Show2 pfShow2, int nType)
{
	if ( Node == NULL )
		return;

	switch(nType)
	{
	case NS_PREORDER:
		{
			if(pfShow2 != NULL)
				pfShow2(Node->m_Data, Node->u.m_sign);
			_Tranvers(Node->m_lchild, pfShow2, nType);
			_Tranvers(Node->m_rchild, pfShow2, nType);
			break;
		}
	case NS_INORDER:
		{
			_Tranvers(Node->m_lchild, pfShow2, nType);
			if(pfShow2 != NULL)
				pfShow2(Node->m_Data, Node->u.m_sign);
			_Tranvers(Node->m_rchild, pfShow2, nType);
			break;
		}
	case NS_POSTORDER:
		{
			_Tranvers(Node->m_lchild, pfShow2, nType);
			_Tranvers(Node->m_rchild, pfShow2, nType);
			if(pfShow2 != NULL)
				pfShow2(Node->m_Data, Node->u.m_sign);
			break;
		}
	}
}


TreeNode * Tree::FindMin(TreeNode * Node)
{
	if( Node == NULL )
		return Node;
	while ( Node->m_lchild )
		Node = Node->m_lchild;
	return Node;
}

TreeNode * Tree::FindMin2(TreeNode * Node)
{
	if ( Node == NULL )
		return Node;
	if ( Node->m_lchild == NULL )
		return Node;
	return FindMin2(Node->m_lchild);
}


