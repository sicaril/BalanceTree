#include "StdAfx.h"
#include "AVLTree_BFactor.h"

AVLTree_BFactor::AVLTree_BFactor(void)
{
}

AVLTree_BFactor::~AVLTree_BFactor(void)
{
}

bool AVLTree_BFactor::Insert(T& Data)
{
	bool bSign = true;
	//bool bSign = false;
	_Insert(&m_root, Data, &bSign);

	return true;
}

TreeNode* AVLTree_BFactor::SingleRotateWithLeft(TreeNode * Node)
{
	TreeNode * mid = Node->m_lchild;
	TreeNode * temp = mid->m_lchild;

	Node->m_lchild = mid->m_rchild;
	mid->m_rchild = Node;

	Node->u.m_bf = 0;
	mid->u.m_bf = 0;

	return mid;
}

TreeNode* AVLTree_BFactor::SingleRotateWithRight(TreeNode * Node)
{
	TreeNode * mid = Node->m_rchild;
	TreeNode * temp = mid->m_rchild;

	Node->m_rchild = mid->m_lchild;
	mid->m_lchild = Node;

	Node->u.m_bf = 0;
	mid->u.m_bf = 0;

	return mid;
}

TreeNode* AVLTree_BFactor::DoubleRotateWithLeft(TreeNode * Node)
{
	TreeNode * mid = Node->m_lchild;
	TreeNode * temp = mid->m_rchild;

	Node->m_lchild = temp->m_rchild;
	temp->m_rchild = Node;

	mid->m_rchild = temp->m_lchild;
	temp->m_lchild = mid;
	
	switch( temp->u.m_bf )
	{
	case 0:
		{
			Node->u.m_bf = 0;
			mid->u.m_bf = 0;
			break;
		}
	case -1:
		{
			Node->u.m_bf = 1;
			mid->u.m_bf = 0;
			break;
		}
	case 1:
		{
			Node->u.m_bf = 0;
			mid->u.m_bf = -1;
			break;
		}
	}

	temp->u.m_bf = 0;
	return temp;
}

TreeNode* AVLTree_BFactor::DoubleRotateWithRight(TreeNode * Node)
{
	TreeNode * mid = Node->m_rchild;
	TreeNode * temp = mid->m_lchild;

	mid->m_lchild = temp->m_rchild;
	temp->m_rchild = mid;

	Node->m_rchild = temp->m_lchild;
	temp->m_lchild = Node;

	switch( temp->u.m_bf )
	{
	case 0:
		{
			Node->u.m_bf = 0;
			mid->u.m_bf = 0;
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

	temp->u.m_bf = 0;
	return temp;
}

TreeNode* AVLTree_BFactor::_Insert(TreeNode ** ppNode, T& Data, bool* bSign)
{
	TreeNode * pNode = *ppNode;
	if ( pNode == NULL )
	{
		*ppNode = new TreeNode(Data);
		//*bSign = true;
		return *ppNode;
	}

	if ( Data < pNode->m_Data )
	{
		_Insert( &pNode->m_lchild, Data,  bSign );

		if( *bSign )
		{
			--pNode->u.m_bf;

			if( pNode->u.m_bf == -2 )
			{ 
				if ( Data < pNode->m_lchild->m_Data)
					*ppNode = SingleRotateWithLeft(pNode);
				else
					*ppNode = DoubleRotateWithLeft(pNode);

				*bSign = false;
			}
			else
			{
				if ( (*ppNode)->u.m_bf == 0 )	// 添加后若为0 则不需要调整（因为高度不变）
					*bSign = false;
			}
		}
	}
	else if ( Data > pNode->m_Data )
	{
		_Insert( &pNode->m_rchild, Data, bSign );

		if( *bSign )
		{
			++pNode->u.m_bf;

			if( pNode->u.m_bf == 2 )
			{
				if ( Data > pNode->m_rchild->m_Data)
					*ppNode = SingleRotateWithRight(pNode);
				else
					*ppNode = DoubleRotateWithRight(pNode);

				*bSign = false;
			}
			else
			{
				if ( (*ppNode)->u.m_bf == 0 )
					*bSign = false;
			}
		}
	}
	else
	{
		*bSign = false; //
	}
	return *ppNode;
}

bool AVLTree_BFactor::Delete(T& Data)
{
	bool Sign = false;
	return _Delete(&m_root, Data, &Sign);
}

TreeNode* AVLTree_BFactor::BalanceRotateWithLeft(TreeNode * Node)
{
	TreeNode * mid = Node->m_lchild;
	bool lleft = IsLeaf( mid->m_lchild );
	bool rleft = IsLeaf( mid->m_rchild );

	if ( lleft && rleft )
	{
		// 左为空 右为空 左单旋 (3层结构)
		Node->m_lchild = mid->m_rchild;
		mid->m_rchild = Node;

		Node->u.m_bf = -1;
		mid->u.m_bf = 1;
	}
	else
	{
		// 左不空 左单旋
		Node->m_lchild = mid->m_rchild;
		mid->m_rchild = Node;

		mid->u.m_bf = 1;
		Node->u.m_bf = -1;
	}
	return mid;
}

TreeNode* AVLTree_BFactor::BalanceRotateWithRight(TreeNode * Node)
{
	TreeNode * mid = Node->m_rchild;
	bool lleft = IsLeaf( mid->m_lchild );
	bool rleft = IsLeaf( mid->m_rchild );

	if ( rleft && lleft )
	{
		// 右为空 左为空 右单旋
		Node->m_rchild = mid->m_lchild;
		mid->m_lchild = Node;

		Node->u.m_bf = 1;
		mid->u.m_bf = -1;
	}
	else
	{
		// 左不空 右单旋
		Node->m_rchild = mid->m_lchild;
		mid->m_lchild = Node;

		mid->u.m_bf = -1;
		Node->u.m_bf = 1;
	}
	return mid;
}

bool AVLTree_BFactor::_Delete(TreeNode ** ppNode, T& Data, bool* bSign)
{
	bool bDelete = false;
	TreeNode * pNode = *ppNode;
	if ( pNode == NULL )
		return false;
	
	if ( Data < pNode->m_Data )
	{
		bDelete = _Delete(&pNode->m_lchild, Data, bSign);

		if ( *bSign )
		{
			++pNode->u.m_bf;

			if ( pNode->u.m_bf == 2 )
			{
				// 删左边 调整右边
				switch( pNode->m_rchild->u.m_bf )
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

			// 删除后 若高度不为0 则不需要调整（只是删除了叶节点，高度保持不变）
			if ( (*ppNode)->u.m_bf != 0 )
				*bSign = false;
		}
		
	}
	else if ( Data > pNode->m_Data )
	{

		bDelete = _Delete(&pNode->m_rchild, Data, bSign);

		if ( *bSign )
		{
			--pNode->u.m_bf;

			if ( pNode->u.m_bf == -2 )
			{

				switch( pNode->m_lchild->u.m_bf )
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
			TreeNode * Temp = FindMin(pNode->m_rchild);

			pNode->m_Data = Temp->m_Data;

			bDelete = _Delete( &pNode->m_rchild, pNode->m_Data, bSign);

			if ( *bSign )
			{
				--pNode->u.m_bf;

				if ( pNode->u.m_bf == -2 )
				{

					switch( pNode->m_lchild->u.m_bf )
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
			TreeNode * Temp = pNode->m_lchild;

			delete pNode;

			*bSign = true;

			bDelete = true;

			*ppNode = Temp;
		}
	}
	return bDelete;
}

bool AVLTree_BFactor::Check()
{
	return _Check(m_root, ShowError);
}

bool AVLTree_BFactor::Check(PF_Show pfShow)
{
	return _Check(m_root, pfShow);
}

bool AVLTree_BFactor::CheckNode(TreeNode * Node,PF_Show pfShow)
{
	if ( Node == NULL )
		return true;

	int nLeft = GetNodeHeightDeep( Node->m_lchild );
	int nRight = GetNodeHeightDeep( Node->m_rchild );

	if ( nLeft > nRight )
	{
		if ( Node->u.m_bf != -1 )
		{
			if( pfShow )
				pfShow(Node->m_Data);
			return false;
		}
		if ( nLeft - nRight > 1 )
		{
			if( pfShow )
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
				if( pfShow )
					pfShow(Node->m_Data);
				return false;
			}
		}
		else if( nLeft < nRight )
		{
			if ( Node->u.m_bf != 1 )
			{
				if( pfShow )
					pfShow(Node->m_Data);
				return false;
			}
		}

		if ( nRight - nLeft > 1 )
		{
			if( pfShow )
				pfShow(Node->m_Data);
			return false;
		}
	}

	return true;
}

bool AVLTree_BFactor::_Check(TreeNode * Node,PF_Show pfShow)
{
	if ( Node == NULL )
		return true;

	if ( CheckNode(Node, pfShow) == false )
		return false;

	return  _Check(Node->m_lchild, pfShow) && _Check(Node->m_rchild, pfShow);
}