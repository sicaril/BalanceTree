#include "StdAfx.h"
#include "TreeNode.h"

TreeNode::TreeNode(void)
{
	Init();
}

TreeNode::TreeNode(T& Data)
{
	m_Data = Data;
	Init();
}

TreeNode::~TreeNode(void)
{
	Release();
}

void TreeNode::Init()
{
	m_lchild = NULL;
	m_rchild = NULL;
	m_parent = NULL;
	u.m_sign = 0;
}

void TreeNode::Release()
{

}

int TreeNode::Height()
{
	if ( this == NULL )
		return -1;
	return u.m_height;
}

int TreeNode::FixHeight()
{
	int nLeft = m_lchild->Height();
	int nRight = m_rchild->Height();

	if ( nLeft > nRight )
		u.m_height = nLeft + 1;
	else
		u.m_height = nRight + 1;
	return u.m_height;
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

// bool IsLeftRed(TreeNode * Node)
// {
// 	if ( Node->m_lchild && 
// 		Node->m_lchild->u.m_color == NS_RED )
// 		return true;
// 	return false;
// }
// 
// bool IsRightRed(TreeNode * Node)
// {
// 	if ( Node->m_rchild && 
// 		Node->m_rchild->u.m_color == NS_RED )
// 		return true;
// 	return false;
// }

inline bool IsLeftRed(TreeNode * Node)
{
	if ( Node->m_lchild && Node->m_lchild->u.m_color == NS_RED )
		return true;
	return false;
}

inline bool IsRightRed(TreeNode * Node)
{
	if ( Node->m_rchild && Node->m_rchild->u.m_color == NS_RED )
		return true;
	return false;
}

inline void SwapColor(TreeNode * Node)
{
	Node->u.m_color = NS_RED;
	Node->m_lchild->u.m_color = NS_BLACK;
	Node->m_rchild->u.m_color = NS_BLACK;
}

void Show(T& Data)
{
	printf("%d ",Data);
}

void Show2(T& Data, int nSign)
{
	printf("%d(%d) ",Data,nSign);
}

void ShowError(T& Data)
{
	printf("\r\ncheck false %d\r\n", Data);
}