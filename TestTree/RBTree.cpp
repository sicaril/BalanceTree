#include "StdAfx.h"
#include "RBTree.h"

RBTree::RBTree(void)
{
}

RBTree::~RBTree(void)
{
}

#define NS_BRT_ROTATE_NOT_FIX_COLOR


bool RBTree::Insert(T& Data)
{
	bool bSign = false;
	_Insert(&m_root, Data, &bSign);
	if ( m_root )
		m_root->u.m_color = NS_BLACK;
	return true;
}

bool RBTree::Insert2(T& Data)
{
	bool bSign = false;
	_Insert2(&m_root, Data, &bSign);
	if ( m_root )
		m_root->u.m_color = NS_BLACK;
	return true;
}

inline TreeNode * SingleRotateWithLeft(TreeNode * Node)
{
	TreeNode * mid = Node->m_lchild;
	TreeNode * temp = mid->m_lchild;

	Node->m_lchild = mid->m_rchild;
	mid->m_rchild = Node;

	// ������ ���ٺ��

	// �Ƶ����
#ifndef NS_BRT_ROTATE_NOT_FIX_COLOR
	mid->u.m_color = NS_BLACK;
	//temp->u.m_color = NS_RED;
	Node->u.m_color = NS_RED;
#endif

	return mid;
}

inline TreeNode * DoubleRotateWithLeft(TreeNode * Node)
{
	TreeNode * mid = Node->m_lchild;
	TreeNode * temp = mid->m_rchild;

	Node->m_lchild = temp->m_rchild;
	mid->m_rchild = temp->m_lchild;

	temp->m_lchild = mid;
	temp->m_rchild = Node;

	// �Ƶ����
#ifndef NS_BRT_ROTATE_NOT_FIX_COLOR
	temp->u.m_color = NS_BLACK;
	//mid->u.m_color = NS_RED;
	Node->u.m_color = NS_RED;
#endif

	return temp;
}

inline TreeNode * SingleRotateWithRight(TreeNode * Node)
{
	TreeNode * mid = Node->m_rchild;
	TreeNode * temp = mid->m_rchild;

	Node->m_rchild = mid->m_lchild;
	mid->m_lchild = Node;

	// �Ƶ����
#ifndef NS_BRT_ROTATE_NOT_FIX_COLOR
	mid->u.m_color = NS_BLACK;
	//temp->u.m_color = NS_RED;
	Node->u.m_color = NS_RED;
#endif

	return mid;
}

inline TreeNode * DoubleRotateWithRight(TreeNode * Node)
{
	TreeNode * mid = Node->m_rchild;
	TreeNode * temp = mid->m_lchild;

	Node->m_rchild = temp->m_lchild;
	mid->m_lchild = temp->m_rchild;

	temp->m_rchild = mid;
	temp->m_lchild = Node;

	// �Ƶ����
#ifndef NS_BRT_ROTATE_NOT_FIX_COLOR
	temp->u.m_color = NS_BLACK;
	//mid->u.m_color = NS_RED;
	Node->u.m_color = NS_RED;
#endif

	return temp;
}

//////////////////////////////////////////////////////////////////////////

inline void AdjustColorWithLeft(TreeNode * Node)
{
	Node->u.m_color = NS_RED;
	Node->m_lchild->u.m_color = NS_BLACK;
	Node->m_rchild->u.m_color = NS_BLACK;
}

inline void AdjustColorWithRight(TreeNode * Node)
{
	Node->u.m_color = NS_RED;
	Node->m_lchild->u.m_color = NS_BLACK;
	Node->m_rchild->u.m_color = NS_BLACK;
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


TreeNode* RBTree::_Insert(TreeNode** ppNode, T& Data, bool * bSign)
{
	TreeNode* pNode = *ppNode;
	if ( pNode == NULL )
	{
		*ppNode = new TreeNode(Data);
		*bSign = true;
		return *ppNode;
	}
	else if( Data < pNode->m_Data )
	{
		_Insert( &pNode->m_lchild, Data, bSign);

		if ( *bSign )
		{
			TreeNode * mid = pNode->m_lchild;
			if( mid->u.m_color == NS_RED )
			{
				bool bRightRed = false;
				if( pNode->m_rchild && 
					pNode->m_rchild->u.m_color == NS_RED )
					bRightRed = true;

				if( mid->m_lchild && 
					mid->m_lchild->u.m_color == NS_RED )
				{
					//if ( IsRightRed(pNode))
					if( bRightRed )
					{
						pNode->u.m_color = NS_RED;
						pNode->m_lchild->u.m_color = NS_BLACK;
						pNode->m_rchild->u.m_color = NS_BLACK;
					}
					else
					{
						// ���� �� ������ɫ
						*ppNode = SingleRotateWithLeft(pNode);	// 3,2,==> 3,2,1 ==> 2,1,3

					#ifdef NS_BRT_ROTATE_NOT_FIX_COLOR
						(*ppNode)->u.m_color = NS_BLACK;
						(*ppNode)->m_rchild->u.m_color = NS_RED;
					#endif
						
						*bSign = false;
					}
				}
				else if ( mid->m_rchild && 
					mid->m_rchild->u.m_color == NS_RED )
				{
					//if ( IsRightRed(pNode))
					if ( bRightRed )
					{
						pNode->u.m_color = NS_RED;
						pNode->m_lchild->u.m_color = NS_BLACK;
						pNode->m_rchild->u.m_color = NS_BLACK;
					}
					else
					{
						// ��3�� ��˫��
						*ppNode = DoubleRotateWithLeft(pNode);

					#ifdef NS_BRT_ROTATE_NOT_FIX_COLOR
						(*ppNode)->u.m_color = NS_BLACK;
						(*ppNode)->m_rchild->u.m_color = NS_RED;
					#endif

						*bSign = false;
					}
				}
			}
		}
		
	}
	else if ( Data > pNode->m_Data )
	{
		_Insert( &pNode->m_rchild, Data, bSign);

		if ( *bSign )
		{
			TreeNode * mid = pNode->m_rchild;
			if( mid->u.m_color == NS_RED )
			{
				bool bLeftRed = false;
				if( pNode->m_lchild && 
					pNode->m_lchild->u.m_color == NS_RED )
					bLeftRed = true;

				if ( mid->m_rchild && 
					mid->m_rchild->u.m_color == NS_RED )
				{
					if ( bLeftRed )
					{
						pNode->u.m_color = NS_RED;
						pNode->m_lchild->u.m_color = NS_BLACK;
						pNode->m_rchild->u.m_color = NS_BLACK;
					}
					else
					{
						// �ҵ��� �� ������ɫ
						*ppNode = SingleRotateWithRight(pNode);

					#ifdef NS_BRT_ROTATE_NOT_FIX_COLOR
						(*ppNode)->u.m_color = NS_BLACK;
						(*ppNode)->m_lchild->u.m_color = NS_RED;
					#endif

						*bSign = false;
					}
				}
				else if ( mid->m_lchild && 
					mid->m_lchild->u.m_color == NS_RED )
				{
					if ( bLeftRed)
					{
						pNode->u.m_color = NS_RED;
						pNode->m_lchild->u.m_color = NS_BLACK;
						pNode->m_rchild->u.m_color = NS_BLACK;
					}
					else
					{
						// ��3�� ��˫��
						*ppNode = DoubleRotateWithRight(pNode);

					#ifdef NS_BRT_ROTATE_NOT_FIX_COLOR
						(*ppNode)->u.m_color = NS_BLACK;
						(*ppNode)->m_lchild->u.m_color = NS_RED;
					#endif

						*bSign = false;
					}
				}
			}
		}

	}
	else
	{
		// ��� ������ֵ�滻
	}

	return *ppNode;
}


TreeNode* RBTree::_Insert2(TreeNode** ppNode, T& Data, bool * bSign)
{
	TreeNode* pNode = *ppNode;
	if ( pNode == NULL )
	{
		*ppNode = new TreeNode(Data);
		*bSign = true;
		return *ppNode;
	}
	else if( Data < pNode->m_Data )
	{
		_Insert2( &pNode->m_lchild, Data, bSign);

		if ( *bSign )
		{
			if ( IsLeftRed(pNode))
			{
				if ( IsLeftRed(pNode->m_lchild) )  // �嵽���
				{
					if ( IsRightRed(pNode))
					{
						AdjustColorWithLeft(pNode);
					}
					else
					{
						// ���� �� ������ɫ
						*ppNode = SingleRotateWithLeft(pNode);
#ifdef NS_BRT_ROTATE_NOT_FIX_COLOR
						(*ppNode)->u.m_color = NS_BLACK;
						(*ppNode)->m_rchild->u.m_color = NS_RED;
#endif
						*bSign = false;
					}
					
				}
				else if ( IsRightRed(pNode->m_lchild) )
				{
					if ( IsRightRed(pNode))
					{
						AdjustColorWithLeft(pNode);
					}
					else
					{
						// ��3�� ��˫��
						*ppNode = DoubleRotateWithLeft(pNode);
#ifdef NS_BRT_ROTATE_NOT_FIX_COLOR
						(*ppNode)->u.m_color = NS_BLACK;
						(*ppNode)->m_rchild->u.m_color = NS_RED;
#endif
						*bSign = false;
					}
				}
			}
		}

	}
	else if ( Data > pNode->m_Data )
	{
		_Insert2( &pNode->m_rchild, Data, bSign);

		if ( *bSign )
		{
			if ( IsRightRed(pNode) )
			{
				if ( IsRightRed(pNode->m_rchild))
				{
					if ( IsLeftRed(pNode))
					{
						// �ұ�ɫ
						AdjustColorWithRight(pNode);
					}
					else
					{
						// �ҵ��� �� ������ɫ
						*ppNode = SingleRotateWithRight(pNode);		// ֻ�ᾭ������
#ifdef NS_BRT_ROTATE_NOT_FIX_COLOR
						(*ppNode)->u.m_color = NS_BLACK;
						(*ppNode)->m_lchild->u.m_color = NS_RED;
#endif
						*bSign = false;
					}
				}
				else if ( IsLeftRed(pNode->m_rchild))
				{
					if ( IsLeftRed(pNode))
					{
						// �ұ�ɫ
						AdjustColorWithRight(pNode);
					}
					else
					{
						// ��3�� ��˫��
						*ppNode = DoubleRotateWithRight(pNode);
#ifdef NS_BRT_ROTATE_NOT_FIX_COLOR
						(*ppNode)->u.m_color = NS_BLACK;
						(*ppNode)->m_lchild->u.m_color = NS_RED;
#endif
						*bSign = false;
					}
					
				}
			}
		}

	}
	else
	{
		// ��� ������ֵ�滻
	}

	return *ppNode;
}


bool RBTree::Check()
{
	return _Check( m_root );
}

int GetBlackNodeLeft(TreeNode * Node)
{
	if ( Node == NULL )
		return -1;
	int nBlock = Node->u.m_color == NS_BLACK;
	return GetBlackNodeLeft(Node->m_lchild) + nBlock;
}

int GetBlackNodeRight(TreeNode * Node)
{
	if ( Node == NULL )
		return -1;
	int nBlock = Node->u.m_color == NS_BLACK;
	return GetBlackNodeRight(Node->m_rchild) + nBlock;
}

bool RBTree::_Check(TreeNode * Node)
{
	if ( Node == NULL )
		return true;

	int nLeft = GetBlackNodeLeft(Node->m_lchild);
	int nRight = GetBlackNodeRight(Node->m_rchild);
	
	if( nLeft != nRight)
	{
		printf("==> Node:%d Lheight:%d Rheight %d \r\n", Node->m_Data, nLeft, nRight );
		return false;
	}

	if ( Node->u.m_color == NS_RED )
	{
		if ( Node->m_lchild && Node->m_lchild->u.m_color == NS_RED )
		{
			printf("==> double L red %d-->%d \r\n", Node->m_Data, Node->m_lchild->m_Data );
			return false;
		}

		if ( Node->m_rchild && Node->m_rchild->u.m_color == NS_RED )
		{
			printf("==> double R red %d-->%d \r\n", Node->m_Data, Node->m_rchild->m_Data );
			return false;
		}
	}

	if ( Node->m_lchild && Node->m_rchild == NULL )
	{
		if ( Node->m_lchild->u.m_color != NS_RED )
		{
			return false;
		}
	}

	if ( Node->m_rchild && Node->m_lchild == NULL )
	{
		if ( Node->m_rchild->u.m_color != NS_RED )
		{
			return false;
		}
	}

	if ( _Check(Node->m_lchild) == false )
		return false;
	
	if ( _Check(Node->m_rchild) == false )
		return false;

	return true;
}


bool RBTree::Delete(T& Data)
{
	bool bSign = false;
	bSign = _Delete(&m_root, Data, &bSign);
	if ( m_root )
		m_root->u.m_color = NS_BLACK;
	
	return bSign;
}

inline bool IsRed(TreeNode * Node)
{
	if ( Node && Node->u.m_color == NS_RED )
		return true;
	return false;
}

TreeNode * FixWithBlackTreeLeft(TreeNode * Node)
{
	// ��->��
	TreeNode * mid = Node->m_lchild;

	bool bRightRed = IsRed(mid->m_rchild);

	if ( IsRed(mid->m_lchild) )
	{
		// ����
		Node = SingleRotateWithLeft(Node);

		if ( bRightRed )
		{
			// ��ɫ
			Node->u.m_color = NS_RED;
			Node->m_lchild->u.m_color = NS_BLACK;
			Node->m_rchild->u.m_color = NS_BLACK;
		}
	}
	else if ( bRightRed )
	{
		Node = DoubleRotateWithLeft(Node);

		Node->m_rchild->u.m_color = NS_BLACK;
	}
	else
	{
		// ˫�ڽڵ�
		// ����
		Node = SingleRotateWithLeft(Node);

	}

	return Node;
}

TreeNode * FixWithBlackTreeRight(TreeNode * Node)
{
	// ��->��
	TreeNode * mid = Node->m_rchild;

	bool bLeftRed = IsRed(mid->m_lchild);

	if ( IsRed(mid->m_rchild) )
	{
		// ����
		Node = SingleRotateWithRight(Node);

		if ( bLeftRed )
		{
			// ��ɫ
			Node->u.m_color = NS_RED;
			Node->m_lchild->u.m_color = NS_BLACK;
			Node->m_rchild->u.m_color = NS_BLACK;
		}
	}
	else if ( bLeftRed )
	{
		Node = DoubleRotateWithRight(Node);

		Node->m_lchild->u.m_color = NS_BLACK;
	}
	else
	{
		// ˫�ڽڵ�
		// ����
		Node = SingleRotateWithRight(Node);

	}

	return Node;
}

bool FixDoubleRedLeft(TreeNode ** ppNode, bool * bSign)
{
	bool bDoubleRed = false;
	TreeNode * pNode = *ppNode;

	// ���� ��ƽ��-���� ���
	if ( IsRed(pNode->m_lchild) )
	{
		bool bRightRed = IsRed( pNode->m_rchild );

		TreeNode * mid = pNode->m_lchild;
		if ( IsRed( mid->m_lchild) )
		{
			bDoubleRed = true;

			if ( bRightRed )
			{
				pNode->u.m_color = NS_RED;
				pNode->m_lchild->u.m_color = NS_BLACK;
				pNode->m_rchild->u.m_color = NS_BLACK;

				// ��ɫ�󷵻غ� ��������
			}
			else
			{
				*ppNode = SingleRotateWithLeft( pNode );

				(*ppNode)->u.m_color = NS_BLACK;
				(*ppNode)->m_rchild->u.m_color = NS_RED;

				*bSign = true;
			}

		}
		else if( IsRed( mid->m_rchild) )
		{
			bDoubleRed = true;

			if ( bRightRed )
			{
				pNode->u.m_color = NS_RED;
				pNode->m_lchild->u.m_color = NS_BLACK;
				pNode->m_rchild->u.m_color = NS_BLACK;

				// ��ɫ�󷵻غ� ��������
			}
			else
			{
				*ppNode = DoubleRotateWithLeft( pNode );

				(*ppNode)->u.m_color = NS_BLACK;
				(*ppNode)->m_rchild->u.m_color = NS_RED;

				*bSign = true;
			}
		}
	}

	return bDoubleRed;
}

bool FixDoubleRedRight(TreeNode ** ppNode, bool * bSign)
{
	bool bDoubleRed = false;
	TreeNode * pNode = *ppNode;

	// ���� ��ƽ��-���� ���
	if ( IsRed(pNode->m_rchild) )
	{
		bool bLeftRed = IsRed( pNode->m_lchild );

		TreeNode * mid = pNode->m_rchild;
		if ( IsRed( mid->m_rchild) )
		{
			bDoubleRed = true;

			if ( bLeftRed )
			{
				pNode->u.m_color = NS_RED;
				pNode->m_lchild->u.m_color = NS_BLACK;
				pNode->m_rchild->u.m_color = NS_BLACK;

				// ��ɫ�󷵻غ� ��������
			}
			else
			{
				*ppNode = SingleRotateWithRight( pNode );

				(*ppNode)->u.m_color = NS_BLACK;
				(*ppNode)->m_lchild->u.m_color = NS_RED;

				*bSign = true;
			}

		}
		else if( IsRed( mid->m_lchild) )
		{
			bDoubleRed = true;

			if ( bLeftRed )
			{
				pNode->u.m_color = NS_RED;
				pNode->m_lchild->u.m_color = NS_BLACK;
				pNode->m_rchild->u.m_color = NS_BLACK;

				// ��ɫ�󷵻غ� ��������
			}
			else
			{
				*ppNode = DoubleRotateWithRight( pNode );

				(*ppNode)->u.m_color = NS_BLACK;
				(*ppNode)->m_lchild->u.m_color = NS_RED;

				*bSign = true;
			}
		}
	}

	return bDoubleRed;
}

bool RBTree::_Delete(TreeNode** ppNode, T& Data, bool * bSign)
{
	bool bRet = false;
	TreeNode * pNode = *ppNode;
	if ( pNode == NULL )
		return bRet;

	if ( Data < pNode->m_Data )
	{
		bRet = _Delete(&pNode->m_lchild, Data, bSign);

		if ( *bSign ) // ɾ�˺��� ��Ҫ����
		{
			if ( FixDoubleRedLeft(&pNode, bSign) == false )
			{
				// ɾ�� ����
				if ( pNode->m_rchild )
				{
					// �ڶ���
					if ( pNode->u.m_color == NS_BLACK )
					{
						if ( pNode->m_rchild->u.m_color == NS_BLACK )
						{
							// �ں�
							if ( IsRed(pNode->m_rchild->m_lchild) )
							{
								// ���� +1
								*ppNode = DoubleRotateWithRight(pNode);
								(*ppNode)->u.m_color = NS_BLACK;

								*bSign = false;
							}
							else
							{
								// �Һ� -1 ==> ������
								*ppNode = SingleRotateWithRight(pNode);
								(*ppNode)->m_lchild->u.m_color = NS_RED;
							}
						}
						else
						{
							// �ں� ==> ��ɫ����

							// ���ÿ����Ƿ�������ڵ� ������������Ҳ�ƽ��
							*ppNode = SingleRotateWithRight(pNode);

							(*ppNode)->u.m_color = NS_BLACK;
							(*ppNode)->m_lchild->u.m_color = NS_RED;

							// ���ε�ƽ�������������ӽ��е�ƽ

							(*ppNode)->m_lchild = FixWithBlackTreeRight((*ppNode)->m_lchild);

							*bSign = false;
						}
					}
					else
					{
						// ��<-��
						if ( IsRed( pNode->m_lchild) )
						{
							// �²�������� ����һ��ȥ����
							*bSign = true;
						}
						else
						{
							// ��->��|/_��

							if ( IsRed(pNode->m_rchild->m_lchild) )
							{
								*ppNode = DoubleRotateWithRight(pNode);

								// ��+1������ڣ�
								//(*ppNode)->u.m_color = NS_RED;
								(*ppNode)->m_lchild->u.m_color = NS_BLACK;

								*bSign = false;		// �췵�� ����Ҫ����
							}
							else
							{
								// ��+1������ڣ�
								*ppNode = SingleRotateWithRight(pNode);

								*bSign = false;	
							}
						}
					}
				}
			}
			
		}
	}
	else if ( Data > pNode->m_Data )
	{
		bRet = _Delete(&pNode->m_rchild, Data, bSign);
		if ( *bSign ) // ɾ�˺��� ��Ҫ����
		{
			if ( FixDoubleRedRight( &pNode, bSign) == false )
			{
				// ɾ������
				if ( pNode->m_lchild )
				{
					// �ڶ���
					if ( pNode->u.m_color == NS_BLACK )
					{
						if ( pNode->m_lchild->u.m_color == NS_BLACK )
						{
							// �ں�
							if ( IsRed(pNode->m_lchild->m_rchild) )
							{
								// �Ҳ�� +1
								*ppNode = DoubleRotateWithLeft(pNode);
								(*ppNode)->u.m_color = NS_BLACK;

								*bSign = false;	
							}
							else
							{
								// ��� -1 ==> ������
								*ppNode = SingleRotateWithLeft(pNode);
								(*ppNode)->m_rchild->u.m_color = NS_RED;
							}
						}
						else
						{
							// �ں� ==> ��ɫ����
							// ���ÿ����Ƿ�������ڵ� ������������Ҳ�ƽ��
							*ppNode = SingleRotateWithLeft(pNode);

							(*ppNode)->u.m_color = NS_BLACK;
							(*ppNode)->m_rchild->u.m_color = NS_RED;

							(*ppNode)->m_rchild = FixWithBlackTreeLeft((*ppNode)->m_rchild);

							*bSign = false;
						}
					}
					else
					{
						if ( IsRed( pNode->m_rchild) )
						{
							// �²�������� ����һ��ȥ����
							*bSign = true;
						}
						else
						{
							// �춥�� ��ڵ��Ϊ��

							if ( IsRed(pNode->m_lchild->m_rchild) )
							{
								*ppNode = DoubleRotateWithLeft(pNode);

								// ��+1������ڣ�
								//(*ppNode)->u.m_color = NS_RED;
								(*ppNode)->m_rchild->u.m_color = NS_BLACK;

								*bSign = false;		// �췵�� ����Ҫ����
							}
							else
							{
								// ��+1������ڣ�
								*ppNode = SingleRotateWithLeft(pNode);

								*bSign = false;	
							}
						}
					}
				}
			}
			
		}
	}
	else
	{
		// Find 
		if ( pNode->m_rchild )
		{
			TreeNode * temp = FindMin(pNode->m_rchild);

			pNode->m_Data = temp->m_Data;

			bRet = _Delete( &pNode->m_rchild, pNode->m_Data, bSign );

			if ( *bSign )
			{
				// ����ȫΪ�� ==> ���ת

				// ����Ϊ�� �������� ==> ��� over
				// ����Ϊ�� �������� ==> �������� over
				// ����ת��Ϊ�� ==> ����ڣ�ԭ��ת���� -1��+1��over

				if ( FixDoubleRedRight( &pNode, bSign) == false )
				{
					// ɾ������
					if ( pNode->m_lchild )
					{
						// �ڶ���
						if ( pNode->u.m_color == NS_BLACK )
						{
							if ( pNode->m_lchild->u.m_color == NS_BLACK )
							{
								// �ں�
								if ( IsRed(pNode->m_lchild->m_rchild) )
								{
									// �Ҳ�� +1
									*ppNode = DoubleRotateWithLeft(pNode);
									(*ppNode)->u.m_color = NS_BLACK;

									*bSign = false;	
								}
								else
								{
									// ��� -1 ==> ������
									*ppNode = SingleRotateWithLeft(pNode);
									(*ppNode)->m_rchild->u.m_color = NS_RED;
								}
							}
							else
							{
								// �ں� ==> ��ɫ����
								// ���ÿ����Ƿ�������ڵ� ������������Ҳ�ƽ��

								*ppNode = SingleRotateWithLeft(pNode);

								(*ppNode)->u.m_color = NS_BLACK;
								(*ppNode)->m_rchild->u.m_color = NS_RED;

								(*ppNode)->m_rchild = FixWithBlackTreeLeft((*ppNode)->m_rchild);

								*bSign = false;
							}
						}
						else
						{

							if ( IsRed( pNode->m_rchild) )
							{
								// �²�������� ����һ��ȥ����
								*bSign = true;
							}
							else
							{
								// �춥�� ��ڵ��Ϊ��

								if ( IsRed(pNode->m_lchild->m_rchild) )
								{
									*ppNode = DoubleRotateWithLeft(pNode);

									// ��+1������ڣ�
									//(*ppNode)->u.m_color = NS_RED;
									(*ppNode)->m_rchild->u.m_color = NS_BLACK;

									*bSign = false;		// �췵�� ����Ҫ����
								}
								else
								{
									// ��+1������ڣ�
									*ppNode = SingleRotateWithLeft(pNode);

									*bSign = false;	
								}
							}
						}
					}
				}
			}
		}
		else
		{
			// ��������

			TreeNode * temp = pNode->m_lchild;

			// ɾ�ڲ������
			if ( pNode->u.m_color == NS_BLACK )
				*bSign = true;

			delete pNode;

			*ppNode = temp;

			bRet = true;

			// ���ֱ��ɾ ==> over
			// �ڵĿ����·� ������ ==> over
			// ɾ������|ɾ������ ������ ������ ==> over

			if ( *bSign && temp && temp->u.m_color == NS_RED )
			{
				temp->u.m_color = NS_BLACK;
				*bSign = false;
			}
		}

	}

	return bRet;
}

//////////////////////////////////////////////////////////////////////////
//	ģ�·ǵݹ�ģʽ�ĵݹ�ʵ��
//////////////////////////////////////////////////////////////////////////

bool RBTree::Delete2(T& Data)
{
	bool bSign = false;
	bSign = _Delete2(&m_root, Data, &bSign);
	if ( m_root )
		m_root->u.m_color = NS_BLACK;

	return bSign;
}

TreeNode* AdjustBalanceWithLeft(TreeNode* Node,  T& Data, bool * bSign, bool * bRet)
{
	TreeNode * _Node = Node;	

	if ( IsLeftRed( Node->m_lchild) )
	{
		Node = SingleRotateWithLeft(Node);

		Node->u.m_color = Node->m_rchild->u.m_color;
		Node->m_lchild->u.m_color = NS_BLACK;
		Node->m_rchild->u.m_color = NS_BLACK;

		_Node = Node->m_rchild;

		*bSign = false;
	}
	else if ( IsRightRed( Node->m_lchild) )
	{
		Node = DoubleRotateWithLeft(Node);

		Node->u.m_color = Node->m_rchild->u.m_color;
		Node->m_rchild->u.m_color = NS_BLACK;

		_Node = Node->m_rchild;

		*bSign = false;
	}
	else
	{
		// ˫���� or Ҷ�ӽڵ�
		Node->m_lchild->u.m_color = NS_RED;

		if( Node->u.m_color == NS_RED )
		{
			Node->u.m_color = NS_BLACK;
			*bSign = false;
		}
	}

	if ( _Node->m_rchild->m_Data == Data )
	{
		TreeNode * tmp = _Node->m_rchild->m_lchild;

		delete _Node->m_rchild;

		_Node->m_rchild = tmp;

		*bRet = true;
	}

	return Node;
}

TreeNode* AdjustBalanceWithRight(TreeNode* Node, T& Data, bool * bSign, bool * bRet)
{
	// Make sure right is Black

	TreeNode * _Node = Node;

	if ( IsRightRed( Node->m_rchild) )
	{
		Node = SingleRotateWithRight(Node);

		Node->u.m_color = Node->m_lchild->u.m_color;
		Node->m_lchild->u.m_color = NS_BLACK;
		Node->m_rchild->u.m_color = NS_BLACK;

		_Node = Node->m_lchild;

		*bSign = false;
	}
	else if ( IsLeftRed( Node->m_rchild) )
	{
		Node = DoubleRotateWithRight(Node);

		Node->u.m_color = Node->m_lchild->u.m_color;
		Node->m_lchild->u.m_color = NS_BLACK;

		_Node = Node->m_lchild;

		*bSign = false;
	}
	else
	{
		// ˫���� or Ҷ�ӽڵ�
		Node->m_rchild->u.m_color = NS_RED;

		if( Node->u.m_color == NS_RED )
		{
			Node->u.m_color = NS_BLACK;
			*bSign = false;
		}
	}

	if ( _Node->m_lchild->m_Data == Data )
	{
		TreeNode * tmp = _Node->m_lchild->m_lchild;

		delete _Node->m_lchild;

		_Node->m_lchild = tmp;

		*bRet = true;
	}

	return Node;
}

bool RBTree::_Delete2(TreeNode** ppNode, T& Data, bool * bSign)
{
	bool bRet = false;
	TreeNode * pNode = *ppNode;
	if ( pNode == NULL )
		return bRet;

	if ( Data < pNode->m_Data )
	{
		bRet = _Delete2( &pNode->m_lchild, Data, bSign );

		//if ( *bSign && pNode->m_lchild )
		if ( *bSign )
		{
			//if(pNode->m_rchild)
			{
				if(pNode->m_rchild->u.m_color == NS_BLACK)
				{
					*ppNode = AdjustBalanceWithRight(pNode, Data, bSign, &bRet);
				}
				else
				{
					*ppNode = SingleRotateWithRight(pNode);

					(*ppNode)->u.m_color = NS_BLACK;
					(*ppNode)->m_lchild->u.m_color = NS_RED;

					//if( (*ppNode)->m_lchild->m_rchild )
						(*ppNode)->m_lchild = AdjustBalanceWithRight((*ppNode)->m_lchild, Data, bSign, &bRet);
				}
			}
		}
			
	}
	else if ( Data > pNode->m_Data )
	{
		bRet = _Delete2( &pNode->m_rchild, Data, bSign );

		//if ( *bSign && pNode->m_rchild )
		if ( *bSign )
		{
			//if(pNode->m_lchild)
			{
				if(pNode->m_lchild->u.m_color == NS_BLACK)
				{
					*ppNode = AdjustBalanceWithLeft(pNode, Data, bSign, &bRet);
				}
				else
				{
					*ppNode = SingleRotateWithLeft(pNode);

					(*ppNode)->u.m_color = NS_BLACK;
					(*ppNode)->m_rchild->u.m_color = NS_RED;

					//if( (*ppNode)->m_rchild->m_lchild )
						(*ppNode)->m_rchild = AdjustBalanceWithLeft((*ppNode)->m_rchild, Data, bSign, &bRet);
				}
			}
		}
	}
	else
	{
		if ( pNode->m_rchild )
		{
			TreeNode * temp = FindMin(pNode->m_rchild);

			pNode->m_Data = temp->m_Data;

			T _Data = pNode->m_Data;

			//Data = pNode->m_Data;

			bRet = _Delete2( &pNode->m_rchild, _Data, bSign );

			//if ( *bSign && pNode->m_rchild )
			if ( *bSign )
			{
				//if(pNode->m_lchild)
				{
					if(pNode->m_lchild->u.m_color == NS_BLACK)
					{
						*ppNode = AdjustBalanceWithLeft(pNode, _Data, bSign, &bRet);
					}
					else
					{
						*ppNode = SingleRotateWithLeft(pNode);

						(*ppNode)->u.m_color = NS_BLACK;
						(*ppNode)->m_rchild->u.m_color = NS_RED;

						//if( (*ppNode)->m_rchild->m_lchild )
							(*ppNode)->m_rchild = AdjustBalanceWithLeft((*ppNode)->m_rchild, _Data, bSign, &bRet);
					}
				}
			}
		}
		else
		{
			TreeNode * temp = pNode->m_lchild;

			if ( pNode->u.m_color == NS_RED || 
				(temp && temp->u.m_color == NS_RED) || 
				pNode == m_root )
			{
				delete pNode;

				*ppNode = temp;

				if ( temp )
				{
					temp->u.m_color = NS_BLACK;
				}

				bRet = true;	
			}
			else
			{
				// ������Ҫʱ��ɾ
				*bSign = true;
			}
		}
	}

	return bRet;
}