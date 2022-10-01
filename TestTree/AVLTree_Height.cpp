#include "StdAfx.h"
#include "AVLTree_Height.h"

AVLTree_Height::AVLTree_Height(void)
{
}

AVLTree_Height::~AVLTree_Height(void)
{
}

bool AVLTree_Height::Insert(T& Data)
{
	bool bSign = true;	// 添加后若高度不变 则无需调整 
	_Insert(&m_root, Data, &bSign);

	return true;
}

inline int GetHeight(TreeNode * Node)
{
	if ( Node == NULL )
		return -1;
	return Node->u.m_height;
}

inline int GetNodeHeight(TreeNode * Node)
{
	if ( Node == NULL )
		return -1;

	int nLeft = GetHeight(Node->m_lchild);
	int nRight = GetHeight(Node->m_rchild);

	if ( nLeft > nRight )
		return nLeft + 1;
	return nRight + 1;
}


void AVLTree_Height::FixNodeHeight(TreeNode* Node)
{
	if ( Node == NULL )
		Node->u.m_height = -1;
	else
	{
		int nLeft = GetHeight(Node->m_lchild);
		int nRight = GetHeight(Node->m_rchild);

		if ( nLeft > nRight )
			Node->u.m_height = nLeft + 1;
		else
			Node->u.m_height = nRight + 1;
	}
}

TreeNode* AVLTree_Height::SingleRotateWithLeft(TreeNode * Node)
{
	TreeNode * mid = Node->m_lchild;
	Node->m_lchild = mid->m_rchild;
	mid->m_rchild = Node;

	FixNodeHeight(Node);
	mid->u.m_height = Node->u.m_height + 1;

	return mid;
}

TreeNode* AVLTree_Height::SingleRotateWithRight(TreeNode * Node)
{
	TreeNode * mid = Node->m_rchild;
	Node->m_rchild = mid->m_lchild;
	mid->m_lchild = Node;

	FixNodeHeight(Node);
	mid->u.m_height = Node->u.m_height + 1;

	return mid;
}

TreeNode* AVLTree_Height::DoubleRotateWithLeft(TreeNode * Node)
{
	TreeNode * mid = Node->m_lchild;
	TreeNode * temp = mid->m_rchild;

	Node->m_lchild = temp->m_rchild;
	temp->m_rchild = Node;

	mid->m_rchild = temp->m_lchild;
	temp->m_lchild = mid;

	FixNodeHeight(Node);
	mid->u.m_height = Node->u.m_height;
	temp->u.m_height = Node->u.m_height + 1;

	return temp;
}

TreeNode* AVLTree_Height::DoubleRotateWithRight(TreeNode * Node)
{

	TreeNode * mid = Node->m_rchild;
	TreeNode * temp = mid->m_lchild;

	mid->m_lchild = temp->m_rchild;
	temp->m_rchild = mid;

	Node->m_rchild = temp->m_lchild;
	temp->m_lchild = Node;

	FixNodeHeight(Node);
	mid->u.m_height = Node->u.m_height;
	temp->u.m_height = Node->u.m_height + 1;

	return temp;
}
TreeNode* AVLTree_Height::_Insert(TreeNode ** ppNode, T& Data, bool * bSign)
{
	TreeNode * pNode = *ppNode;
	if ( pNode == NULL )
	{
		*ppNode = new TreeNode(Data);
		return *ppNode;
	}

	if ( Data < pNode->m_Data )
	{
		_Insert( &pNode->m_lchild, Data, bSign );

		if ( *bSign )
		{
			int height = GetNodeHeight( *ppNode );
			if ( height == (*ppNode)->u.m_height )
			{
				*bSign = false;
			}
			else
			{
				if ( GetNodeHeight(pNode->m_lchild) - GetNodeHeight(pNode->m_rchild) == 2 )
				{
					if ( Data < pNode->m_lchild->m_Data)
						*ppNode = SingleRotateWithLeft(pNode);
					else
						*ppNode = DoubleRotateWithLeft(pNode);

					*bSign = false;
				}
				else
				{
					(*ppNode)->u.m_height = height;
				}
			}
		}
	}
	else if ( Data > pNode->m_Data )
	{
		_Insert( &pNode->m_rchild, Data, bSign );

		if ( *bSign )
		{
			int height = GetNodeHeight( *ppNode );
			if ( height == (*ppNode)->u.m_height )
			{
				*bSign = false;
			}
			else
			{
				if ( GetNodeHeight(pNode->m_rchild) - GetNodeHeight(pNode->m_lchild) == 2 )
				{
					if ( Data > pNode->m_rchild->m_Data)
						*ppNode = SingleRotateWithRight(pNode);
					else
						*ppNode = DoubleRotateWithRight(pNode);

					*bSign = false;
				}
				else
				{
					(*ppNode)->u.m_height = height;
				}
			}
		}
	}
	else
	{
		*bSign = false; //
	}
	return *ppNode;
}

bool AVLTree_Height::Delete(T& Data)
{
	bool bSign = false;
	return _Delete(&m_root, Data, &bSign);
}

inline TreeNode * GetLeftLeaf(TreeNode * Node)
{
	if ( Node->m_lchild )
		return Node->m_lchild;
	return Node->m_rchild;
}

inline TreeNode * GetRightLeaf(TreeNode * Node)
{
	if ( Node->m_rchild )
		return Node->m_rchild;
	return Node->m_lchild;
}

bool AVLTree_Height::IsSingleRototeWithRight(TreeNode * pNode)
{
	int nLeft = GetHeight(pNode->m_lchild);
	int nRight = GetHeight(pNode->m_rchild);

	if ( nLeft > nRight )
	{
		return false;
	}
	else if( nLeft < nRight )
	{
		return true;
	}
	else
	{
		TreeNode * Leaf = GetRightLeaf(pNode);
		return Leaf->m_Data > pNode->m_Data;
	}
}

bool AVLTree_Height::IsSingleRototeWithLeft(TreeNode * pNode)
{
	int nLeft = GetHeight(pNode->m_lchild);
	int nRight = GetHeight(pNode->m_rchild);

	if ( nLeft > nRight )
	{
		return true;
	}
	else if( nLeft < nRight )
	{
		return false;
	}
	else
	{
		TreeNode * Leaf = GetLeftLeaf(pNode);
		return Leaf->m_Data < pNode->m_Data;
	}
}

bool AVLTree_Height::_Delete(TreeNode ** ppNode, T& Data, bool * bSign)
{
	bool bDelete = false;
	TreeNode * pNode = *ppNode;
	if ( pNode == NULL )
	{
		return bDelete;
	}
	
	if ( Data < pNode->m_Data )
	{
		bDelete = _Delete(&pNode->m_lchild, Data, bSign);

		if ( *bSign )
		{
			int height = GetNodeHeight( *ppNode );

			if ( GetNodeHeight(pNode->m_rchild) - GetNodeHeight(pNode->m_lchild) == 2 )
			{
				if ( IsSingleRototeWithRight(pNode->m_rchild) )
					*ppNode = SingleRotateWithRight(pNode);
				else
					*ppNode = DoubleRotateWithRight(pNode);

				if ( height == (*ppNode)->u.m_height )
					*bSign = false;
			}
			else
			{
				if ( height == (*ppNode)->u.m_height )
				{
					*bSign = false;
				}
				else
				{
					(*ppNode)->u.m_height = height;
				}
			}
		}
	}
	else if ( Data > pNode->m_Data )
	{
		bDelete = _Delete(&pNode->m_rchild, Data, bSign);

		if ( *bSign )
		{
			int height = GetNodeHeight( *ppNode );

			if ( GetNodeHeight(pNode->m_lchild) - GetNodeHeight(pNode->m_rchild) == 2 )
			{
				if ( IsSingleRototeWithLeft(pNode->m_lchild) )
					*ppNode = SingleRotateWithLeft(pNode);
				else
					*ppNode = DoubleRotateWithLeft(pNode);

				if ( height == (*ppNode)->u.m_height )
					*bSign = false;
			}
			else
			{
				if ( height == (*ppNode)->u.m_height )
				{
					*bSign = false;
				}
				else
				{
					(*ppNode)->u.m_height = height;
				}
			}
		}
	}
	else
	{
		if ( pNode->m_rchild )
		{
			TreeNode * Temp = FindMin(pNode->m_rchild);

			pNode->m_Data = Temp->m_Data;

			bDelete = _Delete( &pNode->m_rchild, pNode->m_Data , bSign);

			if ( *bSign )
			{
				int height = GetNodeHeight( *ppNode );

				if ( GetNodeHeight(pNode->m_lchild) - GetNodeHeight(pNode->m_rchild) == 2 )
				{
					if ( IsSingleRototeWithLeft(pNode->m_lchild) )
						*ppNode = SingleRotateWithLeft(pNode);
					else
						*ppNode = DoubleRotateWithLeft(pNode);

					if ( height == (*ppNode)->u.m_height )
						*bSign = false;
				}
				else
				{
					if ( height == (*ppNode)->u.m_height )
					{
						*bSign = false;
					}
					else
					{
						(*ppNode)->u.m_height = height;
					}
				}
			}
		}
		else
		{
			// 8,5,10,12 (Del 8)--> 10,5,10',12 (Del 10') --> 10,5,12,12' --> (Del 12') 
			TreeNode * Temp = pNode->m_lchild;	
			//if ( pNode->m_rchild )
			//	Temp = pNode->m_rchild;  // 不存在右子树，但不一定是叶子，比如根节点 (8,5) --> Del 8

			delete pNode;

			*bSign = true;

			bDelete = true;

			*ppNode = Temp;
		}
	}
	return bDelete;
}

bool AVLTree_Height::Check()
{
	return _Check(m_root , ShowError);
}


bool AVLTree_Height::Check(PF_Show pfShow)
{
	return _Check(m_root, pfShow);
}

bool AVLTree_Height::CheckNode(TreeNode * Node,PF_Show pfShow)
{
	if ( Node == NULL )
		return true;

	int nLeft = GetHeight( Node->m_lchild );
	int nRight = GetHeight( Node->m_rchild );

	if ( nLeft > nRight )
	{
		if ( nLeft - nRight > 1 )
		{
			if( pfShow )
				pfShow(Node->m_Data);
			return false;
		}
	}
	else
	{
		if ( nRight - nLeft > 1 )
		{
			if( pfShow )
				pfShow(Node->m_Data);
			return false;
		}
	}

	return true;
}

bool AVLTree_Height::_Check(TreeNode * Node,PF_Show pfShow)
{
	if ( Node == NULL )
		return true;

	if ( CheckNode(Node, pfShow) == false )
		return false;

	return  _Check(Node->m_lchild, pfShow) && _Check(Node->m_rchild, pfShow);
}