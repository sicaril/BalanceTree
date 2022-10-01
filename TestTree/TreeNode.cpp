#include "StdAfx.h"
#include "TreeNode.h"

TreeNode::TreeNode(void)
{
	Init();
}

TreeNode::TreeNode(T& Data)
{
	Init();
	m_Data = Data;
}

TreeNode::TreeNode(T& Data, TreeNode* Parent)
{
	Init();
	m_Data = Data;
	m_Parent = Parent;
}

TreeNode::~TreeNode(void)
{
	Release();
}

void TreeNode::Init()
{
	m_lchild = NULL;
	m_rchild = NULL;
	u.m_sign = 0;
}

void TreeNode::Release()
{

}