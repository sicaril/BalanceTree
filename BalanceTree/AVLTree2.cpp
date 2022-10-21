#include "stdafx.h"
#include "AVLTree2.h"


AVLTree2::AVLTree2(void)
{
}


AVLTree2::~AVLTree2(void)
{
}

TreeNode * AVLTree2::SingleRotateWithLeft(TreeNode* Node)
{
	TreeNode * mid = Node->m_lchild;

	Node->m_lchild = mid->m_rchild;
	mid->m_rchild = Node;

	mid->u.m_bf = 0;
	Node->u.m_bf = 0;

	return mid;
}

TreeNode * AVLTree2::DoubleRotateWithLeft(TreeNode* Node)
{
	TreeNode * mid = Node->m_lchild;
	TreeNode * tmp = mid->m_rchild;

	Node->m_lchild = tmp->m_rchild;
	mid->m_rchild = tmp->m_lchild;

	tmp->m_lchild = mid;
	tmp->m_rchild = Node;

	switch ( tmp->u.m_sign )
	{
	case 0:
		{
			mid->u.m_bf = 0;
			Node->u.m_bf = 0;
			break;
		}
	case -1:
		{
			mid->u.m_bf = 0;
			Node->u.m_bf = 1;
			break;
		}
	case 1:
		{
			mid->u.m_bf = -1;
			Node->u.m_bf = 0;
			break;
		}
	}
	tmp->u.m_bf = 0;

	return tmp;
}

TreeNode * AVLTree2::SingleRotateWithRight(TreeNode* Node)
{
	TreeNode * mid = Node->m_rchild;

	Node->m_rchild = mid->m_lchild;
	mid->m_lchild = Node;

	mid->u.m_bf = 0;
	Node->u.m_bf = 0;

	return mid;
}

TreeNode * AVLTree2::DoubleRotateWithRight(TreeNode* Node)
{
	TreeNode * mid = Node->m_rchild;
	TreeNode * tmp = mid->m_lchild;

	Node->m_rchild = tmp->m_lchild;
	mid->m_lchild = tmp->m_rchild;

	tmp->m_lchild = Node;
	tmp->m_rchild = mid;

	switch ( tmp->u.m_bf )
	{
	case 0:
		{
			mid->u.m_bf = 0;
			Node->u.m_bf = 0;
			break;
		}
	case -1:
		{
			Node->u.m_bf = 0;
			mid->u.m_bf = 1;
			break;
		}
	case 1:
		{
			Node->u.m_bf = -1;
			mid->u.m_bf = 0;
			break;
		}
	}
	tmp->u.m_bf = 0;

	return tmp;
}

bool AVLTree2::Insert(T& Data)
{
	bool bSign = true;
	return _Insert(&m_root, Data ,&bSign);
}

bool AVLTree2::_Insert(TreeNode ** ppNode, T& Data, bool * bSign)
{
	bool bRet = false;
	TreeNode * pNode = *ppNode;
	if ( pNode == NULL )
	{
		*ppNode = new(std::nothrow) TreeNode(Data);
		if ( *ppNode == NULL )
		{
			*bSign = false;
			return bRet;
		}
		return true;
	}

	if ( Data < pNode->m_Data )
	{
		bRet = _Insert(&pNode->m_lchild, Data, bSign );

		if ( *bSign )
		{
			--pNode->u.m_bf;

			if ( pNode->u.m_bf == -2 )
			{
				if ( pNode->m_lchild->u.m_sign == -1 )
					*ppNode = SingleRotateWithLeft(pNode);
				else
					*ppNode = DoubleRotateWithLeft(pNode);
				*bSign = false;
			}
			else
			{
				if ( pNode->u.m_bf == 0 )
					*bSign = false;
			}
		}
	}
	else if ( Data > pNode->m_Data )
	{
		bRet = _Insert(&pNode->m_rchild, Data , bSign);

		if ( *bSign )
		{
			++pNode->u.m_bf;

			if ( pNode->u.m_bf == 2 )
			{
				if ( pNode->m_rchild->u.m_sign == 1)
					*ppNode = SingleRotateWithRight(pNode);
				else
					*ppNode = DoubleRotateWithRight(pNode);
				*bSign = false;
			}
			else
			{
				if ( pNode->u.m_bf == 0 )
					*bSign = false;
			}
		}
	}
	else
	{
		*bSign = false;
		return false;
	}
	return bRet;
}

TreeNode * AVLTree2::BalanceRotateWithLeft(TreeNode * Node)
{
	TreeNode * mid = Node->m_lchild;

	Node->m_lchild = mid->m_rchild; // Node->m_lchild = mid->m_rchild;
	mid->m_rchild = Node;

	mid->u.m_bf = 1;
	Node->u.m_bf = -1;

	return mid;
}

TreeNode * AVLTree2::BalanceRotateWithRight(TreeNode * Node)
{
	TreeNode * mid = Node->m_rchild;

	Node->m_rchild = mid->m_lchild;
	mid->m_lchild = Node;

	mid->u.m_bf = -1;
	Node->u.m_bf = 1;

	return mid;
}

bool AVLTree2::Delete(T& Data)
{
	bool bSign = false;
	return _Delete(&m_root, Data, &bSign);
}

bool AVLTree2::_Delete(TreeNode ** ppNode, T& Data, bool * bSign)
{
	bool bRet = false;
	TreeNode * pNode = *ppNode;
	if ( pNode == NULL )
		return bRet;

	if ( Data < pNode->m_Data )
	{
		bRet = _Delete(&pNode->m_lchild, Data, bSign );

		if ( *bSign )
		{
			++pNode->u.m_bf;

			if ( pNode->u.m_bf == 2 )
			{
				switch ( pNode->m_rchild->u.m_bf )
				{
				case 0:
					{
						*ppNode = BalanceRotateWithRight(pNode);
						break;
					}
				case 1:
					{
						*ppNode = SingleRotateWithRight(pNode);
						break;
					}
				case -1:
					{
						*ppNode = DoubleRotateWithRight(pNode);
						break;
					}
				}
			}

			if ( (*ppNode)->u.m_bf != 0 )
				*bSign = false;
		}
	}
	else if ( Data > pNode->m_Data )
	{
		bRet = _Delete(&pNode->m_rchild, Data, bSign );

		if ( *bSign )
		{

			--pNode->u.m_bf;

			if ( pNode->u.m_bf == -2 )
			{
				switch ( pNode->m_lchild->u.m_bf )
				{
				case 0:
					{
						*ppNode = BalanceRotateWithLeft(pNode);
						break;
					}
				case -1:
					{
						*ppNode = SingleRotateWithLeft(pNode);
						break;
					}
				case 1:
					{
						*ppNode = DoubleRotateWithLeft(pNode);
						break;
					}
				}
			}

			if ( (*ppNode)->u.m_bf != 0 )
				*bSign = false;
		}
	}
	else
	{
		if ( pNode->m_rchild )
		{
			TreeNode * _min = FindMin(pNode->m_rchild);
			pNode->m_Data = _min->m_Data;

			bRet = _Delete( &pNode->m_rchild, pNode->m_Data, bSign );

			if ( *bSign )
			{

				--pNode->u.m_bf;

				if ( pNode->u.m_bf == -2 )
				{
					switch ( pNode->m_lchild->u.m_bf )
					{
					case 0:
						{
							*ppNode = BalanceRotateWithLeft(pNode);
							break;
						}
					case -1:
						{
							*ppNode = SingleRotateWithLeft(pNode);
							break;
						}
					case 1:
						{
							*ppNode = DoubleRotateWithLeft(pNode);
							break;
						}
					}
				}

				if ( (*ppNode)->u.m_bf != 0 )
					*bSign = false;
			}

		}
		else
		{
			TreeNode * tmp = pNode->m_lchild;
			delete pNode;
			*ppNode = tmp;
			*bSign = true;
			bRet = true;
		}
	}

	return bRet;
}



bool AVLTree2::Check()
{
	return _Check(m_root, ShowError);
}

bool AVLTree2::CheckNode(TreeNode * Node,PF_Show pfShow)
{
	if ( Node == NULL )
		return true;

	int nLeft = GetNodeHeightDeep( Node->m_lchild );
	int nRight = GetNodeHeightDeep( Node->m_rchild );

	if ( nLeft > nRight )
	{
		if ( Node->u.m_bf != -1 )
		{
			if( pfShow != NULL )
				pfShow(Node->m_Data);
			return false;
		}
		if ( nLeft - nRight > 1 )
		{
			if( pfShow != NULL )
				pfShow(Node->m_Data);
			return false;
		}
	}
	else
	{
		if ( nLeft == nRight)
		{
			if ( Node->u.m_bf != 0 )
			{
				if( pfShow != NULL )
					pfShow(Node->m_Data);
				return false;
			}
		}
		else if( nLeft < nRight )
		{
			if ( Node->u.m_bf != 1 )
			{
				if( pfShow != NULL )
					pfShow(Node->m_Data);
				return false;
			}
		}

		if ( nRight - nLeft > 1 )
		{
			if( pfShow != NULL )
				pfShow(Node->m_Data);
			return false;
		}
	}

	return true;
}

bool AVLTree2::_Check(TreeNode * Node,PF_Show pfShow)
{
	if ( Node == NULL )
		return true;

	if ( CheckNode(Node, pfShow) == false )
		return false;

	return  _Check(Node->m_lchild, pfShow) && _Check(Node->m_rchild, pfShow);
}