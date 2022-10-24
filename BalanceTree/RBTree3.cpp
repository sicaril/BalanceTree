#include "stdafx.h"
#include "RBTree3.h"


RBTree3::RBTree3(void)
{
}


RBTree3::~RBTree3(void)
{
}

TreeNode* RBTree3::SingleRotateWithLeft(TreeNode * Node)
{
	TreeNode * mid = Node->m_lchild;
	Node->m_lchild = mid->m_rchild;
	mid->m_rchild = Node;

	return mid;
}

TreeNode* RBTree3::DoubleRotateWithLeft(TreeNode * Node)
{
	TreeNode * mid = Node->m_lchild;
	TreeNode * tmp = mid->m_rchild;

	Node->m_lchild = tmp->m_rchild;
	mid->m_rchild = tmp->m_lchild;
	tmp->m_lchild = mid;
	tmp->m_rchild = Node;

	return tmp;
}

TreeNode* RBTree3::SingleRotateWithRight(TreeNode * Node)
{
	TreeNode * mid = Node->m_rchild;

	Node->m_rchild = mid->m_lchild;
	mid->m_lchild = Node;

	return mid;
}

TreeNode* RBTree3::DoubleRotateWithRight(TreeNode * Node)
{

	TreeNode * mid = Node->m_rchild;
	TreeNode * tmp = mid->m_lchild;

	Node->m_rchild = tmp->m_lchild;
	mid->m_lchild = tmp->m_rchild;

	tmp->m_lchild = Node;
	tmp->m_rchild = mid;

	return tmp;
}

bool RBTree3::Insert(T& Data)
{
	bool bSign = true; 
	bool bRet = _Insert(&m_root, Data, &bSign);
	if ( m_root )
		m_root->u.m_color = NS_BLACK;
	return bRet;
}

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

bool RBTree3::_Insert(TreeNode ** ppNode, T& Data, bool * bSign)
{
	bool bRet = false;
	TreeNode * pNode = *ppNode;
	if ( pNode == NULL )
	{
		*ppNode = new(std::nothrow) TreeNode(Data);
		if ( *ppNode == NULL )
		{
			*bSign = false;
			return false;
		}
		return true;
	}

	if ( Data < pNode->m_Data )
	{
		bRet = _Insert(&pNode->m_lchild, Data, bSign );
		if(*bSign)
		{
			TreeNode * mid = pNode->m_lchild;
			if ( mid->u.m_color == NS_RED )
			{
				if ( IsLeftRed(mid) )
				{
					if ( IsRightRed(pNode))
					{
						SwapColor(pNode);
					}
					else
					{
						*ppNode = SingleRotateWithLeft(pNode);

						(*ppNode)->u.m_color = NS_BLACK;
						(*ppNode)->m_rchild->u.m_color = NS_RED;

						*bSign = false;
					}
				}
				else if ( IsRightRed(mid) )
				{
					if ( IsRightRed(pNode))
					{
						SwapColor(pNode);
					}
					else
					{
						*ppNode = DoubleRotateWithLeft(pNode);

						(*ppNode)->u.m_color = NS_BLACK;
						(*ppNode)->m_rchild->u.m_color = NS_RED;

						*bSign = false;
					}
				}
			}
		}
	}
	else if ( Data > pNode->m_Data )
	{
		bRet = _Insert(&pNode->m_rchild, Data, bSign );
		if(*bSign)
		{
			TreeNode * mid = pNode->m_rchild;
			if ( mid->u.m_color == NS_RED )
			{
				if ( IsRightRed(mid) )
				{
					if ( IsLeftRed(pNode))
					{
						SwapColor(pNode);
					}
					else
					{
						*ppNode = SingleRotateWithRight(pNode);

						(*ppNode)->u.m_color = NS_BLACK;
						(*ppNode)->m_lchild->u.m_color = NS_RED;

						*bSign = false;
					}
				}
				else if ( IsLeftRed(mid) )
				{
					if ( IsLeftRed(pNode))
					{
						SwapColor(pNode);
					}
					else
					{
						*ppNode = DoubleRotateWithRight(pNode);

						(*ppNode)->u.m_color = NS_BLACK;
						(*ppNode)->m_lchild->u.m_color = NS_RED;

						*bSign = false;
					}
				}
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

bool RBTree3::Delete(T& Data)
{
	bool bSign = false;
	bool bRet = _Delete(&m_root, Data, &bSign);
	if ( m_root )
		m_root->u.m_color = NS_BLACK;	
	return bRet;
}

TreeNode * RBTree3::FixBlackTreeWithLeft(TreeNode * Node)
{
	TreeNode * mid = Node->m_lchild;
	if ( IsLeftRed(mid) && IsRightRed(mid) )
	{
		Node = SingleRotateWithLeft(Node);
		SwapColor(Node);
	}
	else if ( IsRightRed(mid) )
	{
		Node = DoubleRotateWithLeft(Node);

		Node->m_rchild->u.m_color = NS_BLACK;
	}
	else
	{
		Node = SingleRotateWithLeft(Node);
	}

	return Node;
}

TreeNode * RBTree3::FixBlackTreeWithRight(TreeNode * Node)
{
	TreeNode * mid = Node->m_rchild;
	if ( IsLeftRed(mid) && IsRightRed(mid) )
	{
		Node = SingleRotateWithRight(Node);
		SwapColor(Node);
	}
	else if ( IsLeftRed(mid) )
	{
		Node = DoubleRotateWithRight(Node);

		Node->m_lchild->u.m_color = NS_BLACK;
	}
	else
	{
		Node = SingleRotateWithRight(Node);
	}

	return Node;
}


bool RBTree3::_Delete(TreeNode ** ppNode, T& Data, bool * bSign)
{
	bool bRet = false;
	TreeNode * pNode = *ppNode;

	if ( pNode == NULL )
		return false;

	if ( Data < pNode->m_Data )
	{
		bRet = _Delete(&pNode->m_lchild, Data, bSign);
		if ( *bSign )
		{
			if ( pNode->u.m_color == NS_BLACK )
			{
				TreeNode * mid = pNode->m_rchild;
				if ( mid->u.m_color == NS_BLACK )
				{
					if ( IsRightRed(mid) )
					{
						*ppNode = SingleRotateWithRight(pNode);

						(*ppNode)->m_rchild->u.m_color = NS_BLACK;
						*bSign = false;
					}
					else if ( IsLeftRed(mid))
					{
						*ppNode = DoubleRotateWithRight(pNode);

						(*ppNode)->u.m_color = NS_BLACK;
						*bSign = false;
					}
					else
					{
						mid->u.m_color = NS_RED;	// goon
					}
				}
				else
				{
					// ºÚºìºÚºÚ
					*ppNode = SingleRotateWithRight(pNode);

					(*ppNode)->u.m_color = NS_BLACK;
					(*ppNode)->m_lchild->u.m_color = NS_RED;

					// ¶þ´Îµ÷Õû
					(*ppNode)->m_lchild = FixBlackTreeWithRight((*ppNode)->m_lchild);
					*bSign = false;
				}
			}
			else
			{
				// ºìºÚ XX
				TreeNode * mid = pNode->m_rchild;
				if ( IsLeftRed(mid) )
				{
					*ppNode = DoubleRotateWithRight(pNode);

					(*ppNode)->m_lchild->u.m_color = NS_BLACK;
					*bSign = false;
				}
				else
				{
					*ppNode = SingleRotateWithRight(pNode);

					*bSign = false;
				}
			}
		}
	}
	else if ( Data > pNode->m_Data )
	{
		bRet = _Delete(&pNode->m_rchild, Data, bSign);
		if ( *bSign )
		{
			if ( pNode->u.m_color == NS_BLACK )
			{
				TreeNode * mid = pNode->m_lchild;
				if ( mid->u.m_color == NS_BLACK )
				{
					if ( IsLeftRed(mid) )
					{
						*ppNode = SingleRotateWithLeft(pNode);

						(*ppNode)->m_lchild->u.m_color = NS_BLACK;
						*bSign = false;
					}
					else if ( IsRightRed(mid))
					{
						*ppNode = DoubleRotateWithLeft(pNode);

						(*ppNode)->u.m_color = NS_BLACK;
						*bSign = false;
					}
					else
					{
						mid->u.m_color = NS_RED;	// goon
					}
				}
				else
				{
					// ºÚºìºÚºÚ
					*ppNode = SingleRotateWithLeft(pNode);

					(*ppNode)->u.m_color = NS_BLACK;
					(*ppNode)->m_rchild->u.m_color = NS_RED;

					// ¶þ´Îµ÷Õû
					(*ppNode)->m_rchild = FixBlackTreeWithLeft((*ppNode)->m_rchild);
					*bSign = false;
				}
			}
			else
			{
				// ºìºÚ XX
				TreeNode * mid = pNode->m_lchild;
				if ( IsRightRed(mid) )
				{
					*ppNode = DoubleRotateWithLeft(pNode);

					(*ppNode)->m_rchild->u.m_color = NS_BLACK;
					*bSign = false;
				}
				else
				{
					*ppNode = SingleRotateWithLeft(pNode);

					*bSign = false;
				}
			}
		}
	}
	else
	{
		if ( pNode->m_rchild )
		{
			TreeNode * tmp = FindMin( pNode->m_rchild );
			pNode->m_Data = tmp->m_Data;

			bRet = _Delete(&pNode->m_rchild, pNode->m_Data, bSign);
			if ( *bSign )
			{
				if ( pNode->u.m_color == NS_BLACK )
				{
					TreeNode * mid = pNode->m_lchild;
					if ( mid->u.m_color == NS_BLACK )
					{
						if ( IsLeftRed(mid) )
						{
							*ppNode = SingleRotateWithLeft(pNode);

							(*ppNode)->m_lchild->u.m_color = NS_BLACK;
							*bSign = false;
						}
						else if ( IsRightRed(mid))
						{
							*ppNode = DoubleRotateWithLeft(pNode);

							(*ppNode)->u.m_color = NS_BLACK;
							*bSign = false;
						}
						else
						{
							mid->u.m_color = NS_RED;	// goon
						}
					}
					else
					{
						// ºÚºìºÚºÚ
						*ppNode = SingleRotateWithLeft(pNode);

						(*ppNode)->u.m_color = NS_BLACK;
						(*ppNode)->m_rchild->u.m_color = NS_RED;

						// ¶þ´Îµ÷Õû
						(*ppNode)->m_rchild = FixBlackTreeWithLeft((*ppNode)->m_rchild);
						*bSign = false;
					}
				}
				else
				{
					// ºìºÚ XX
					TreeNode * mid = pNode->m_lchild;
					if ( IsRightRed(mid) )
					{
						*ppNode = DoubleRotateWithLeft(pNode);

						(*ppNode)->m_rchild->u.m_color = NS_BLACK;
						*bSign = false;
					}
					else
					{
						*ppNode = SingleRotateWithLeft(pNode);

						*bSign = false;
					}
				}
			}
		}
		else
		{
			TreeNode * tmp = pNode->m_lchild;

			if ( pNode->u.m_color == NS_BLACK )
				*bSign = true;
			
			delete pNode;
			*ppNode = tmp;

			if ( tmp && tmp->u.m_color == NS_RED )
			{
				tmp->u.m_color = NS_BLACK;
				*bSign = false;
			}

			bRet = true;
		}
	}

	return bRet;
}

bool RBTree3::Check()
{
	if ( m_root && 
		m_root->u.m_color != NS_BLACK )
		return false;
	return _Check( m_root );
}

int RBTree3::GetBlackNodeLeft(TreeNode * Node)
{
	if ( Node == NULL )
		return -1;
	int nBlock = Node->u.m_color == NS_BLACK;
	return GetBlackNodeLeft(Node->m_lchild) + nBlock;
}

int RBTree3::GetBlackNodeRight(TreeNode * Node)
{
	if ( Node == NULL )
		return -1;
	int nBlock = Node->u.m_color == NS_BLACK;
	return GetBlackNodeRight(Node->m_rchild) + nBlock;
}

bool RBTree3::_Check(TreeNode * Node)
{
	if ( Node == NULL )
		return true;

	int nLeft = GetBlackNodeLeft(Node->m_lchild);
	int nRight = GetBlackNodeRight(Node->m_rchild);

	// 	if ( Node == m_root )
	// 	{
	// 		printf("Root left Black Node %d right Black Node %d \r\n",nLeft + 1, nRight + 1);
	// 	}

	if( nLeft != nRight)
	{
		printf("Data %d left Black Node %d != right Black Node %d \r\n", Node->m_Data, nLeft + 1, nRight + 1);
		return false;
	}

	if ( Node->u.m_color == NS_RED )
	{
		if ( Node->m_lchild && Node->m_lchild->u.m_color == NS_RED )
		{
			printf("double L red %d-->%d \r\n", Node->m_Data, Node->m_lchild->m_Data );
			return false;
		}

		if ( Node->m_rchild && Node->m_rchild->u.m_color == NS_RED )
		{
			printf("double R red %d-->%d \r\n", Node->m_Data, Node->m_rchild->m_Data );
			return false;
		}
	}

	if ( _Check(Node->m_lchild) == false )
		return false;

	if ( _Check(Node->m_rchild) == false )
		return false;

	return true;
}
