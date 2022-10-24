#include "stdafx.h"
#include "BSTree2.h"


BSTree2::BSTree2(void)
{
}


BSTree2::~BSTree2(void)
{
}

TreeNode* BSTree2::SingleRotateWithLeft(TreeNode * Node)
{
	TreeNode * mid = Node->m_lchild;
	Node->m_lchild = mid->m_rchild;
	mid->m_rchild = Node;

	Node->FixHeight();
	mid->u.m_height = Node->u.m_height + 1;

	return mid;
}

TreeNode* BSTree2::DoubleRotateWithLeft(TreeNode * Node)
{
	TreeNode * mid = Node->m_lchild;
	TreeNode * tmp = mid->m_rchild;

	Node->m_lchild = tmp->m_rchild;
	mid->m_rchild = tmp->m_lchild;
	tmp->m_lchild = mid;
	tmp->m_rchild = Node;

	Node->FixHeight();
	mid->u.m_height = Node->u.m_height;
	tmp->u.m_height = Node->u.m_height + 1;

	return tmp;
}

TreeNode* BSTree2::SingleRotateWithRight(TreeNode * Node)
{
	TreeNode * mid = Node->m_rchild;

	Node->m_rchild = mid->m_lchild;
	mid->m_lchild = Node;

	Node->FixHeight();
	mid->u.m_height = Node->u.m_height + 1;

	return mid;
}

TreeNode* BSTree2::DoubleRotateWithRight(TreeNode * Node)
{

	TreeNode * mid = Node->m_rchild;
	TreeNode * tmp = mid->m_lchild;

	Node->m_rchild = tmp->m_lchild;
	mid->m_lchild = tmp->m_rchild;
	
	tmp->m_lchild = Node;
	tmp->m_rchild = mid;

	Node->FixHeight();
	mid->u.m_height = Node->u.m_height;
	tmp->u.m_height = Node->u.m_height + 1;

	return tmp;
}

bool BSTree2::Insert(T& Data)
{
	bool bSign = true;
	return _Insert(&m_root, Data, &bSign);
}

bool BSTree2::_Insert(TreeNode ** ppNode, T& Data, bool * bSign)
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
		bRet = _Insert( &pNode->m_lchild, Data, bSign );

		if ( *bSign )
		{
			int height = (*ppNode)->u.m_height;
			if ( height == (*ppNode)->FixHeight() )
			{
				*bSign = false;
			}
			else
			{
				if ( pNode->m_lchild->Height() - pNode->m_rchild->Height() == 2 )
				{
					if ( Data < pNode->m_lchild->m_Data)
						*ppNode = SingleRotateWithLeft(pNode);
					else
						*ppNode = DoubleRotateWithLeft(pNode);

					*bSign = false;
				}
			}
		}
	}
	else if ( Data > pNode->m_Data )
	{
		bRet = _Insert( &pNode->m_rchild, Data, bSign );

		if ( *bSign )
		{
			int height = (*ppNode)->u.m_height;
			if ( height == (*ppNode)->FixHeight() )
			{
				*bSign = false;
			}
			else
			{
				if ( pNode->m_rchild->Height() - pNode->m_lchild->Height() == 2 )
				{
					if ( Data > pNode->m_rchild->m_Data)
						*ppNode = SingleRotateWithRight(pNode);
					else
						*ppNode = DoubleRotateWithRight(pNode);

					*bSign = false;
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

bool BSTree2::Delete(T& Data)
{
	bool bSign = false;
	return _Delete(&m_root, Data, &bSign);
}

bool BSTree2::_Delete(TreeNode ** ppNode, T& Data, bool * bSign)
{
	bool bRet = false;
	TreeNode * pNode = *ppNode;
	if ( pNode == NULL )
	{
		return bRet;
	}

	if ( Data < pNode->m_Data )
	{
		bRet = _Delete(&pNode->m_lchild, Data, bSign);

		if ( *bSign )
		{
			int height = (*ppNode)->u.m_height;

			if ( pNode->m_rchild->Height() - pNode->m_lchild->Height() == 2 )
			{
				TreeNode * mid = pNode->m_rchild;
				if ( mid->m_rchild->Height() >= mid->m_lchild->Height() )
					*ppNode = SingleRotateWithRight(pNode);
				else
					*ppNode = DoubleRotateWithRight(pNode);
			}
			
			if ( height == (*ppNode)->FixHeight())
				*bSign = false;
		}
	}
	else if ( Data > pNode->m_Data )
	{
		bRet = _Delete(&pNode->m_rchild, Data, bSign);

		if ( *bSign )
		{
			int height = (*ppNode)->u.m_height;

			if ( pNode->m_lchild->Height() - pNode->m_rchild->Height() == 2 )
			{
				TreeNode * mid = pNode->m_lchild;
				if ( mid->m_lchild->Height() >= mid->m_rchild->Height())
					*ppNode = SingleRotateWithLeft(pNode);
				else
					*ppNode = DoubleRotateWithLeft(pNode);
			}
			
			if ( height == (*ppNode)->FixHeight())
				*bSign = false;
		}
	}
	else
	{
		if ( pNode->m_rchild )
		{
			TreeNode * Temp = FindMin(pNode->m_rchild);

			pNode->m_Data = Temp->m_Data;

			bRet = _Delete( &pNode->m_rchild, pNode->m_Data , bSign);

			if ( *bSign )
			{
				int height = (*ppNode)->u.m_height;

				if ( pNode->m_lchild->Height() - pNode->m_rchild->Height() == 2 )
				{
					TreeNode * mid = pNode->m_lchild;
					if ( mid->m_lchild->Height() >= mid->m_rchild->Height())
						*ppNode = SingleRotateWithLeft(pNode);
					else
						*ppNode = DoubleRotateWithLeft(pNode);
				}

				if ( height == (*ppNode)->FixHeight())
					*bSign = false;
			}
		}
		else
		{
			TreeNode * Temp = pNode->m_lchild;	
			delete pNode;
			*ppNode = Temp;
			*bSign = true;
			bRet = true;
		}
	}

	return bRet;
}

bool BSTree2::Check()
{
	return _Check(m_root , ShowError);
}

bool BSTree2::CheckNode(TreeNode * Node,PF_Show pfShow)
{
	if ( Node == NULL )
		return true;

	//int nLeft = GetHeight( Node->m_lchild );
	//int nRight = GetHeight( Node->m_rchild );

	int nLeft = Node->m_lchild->Height();
	int nRight = Node->m_rchild->Height();

	if ( nLeft > nRight )
	{
		if ( nLeft - nRight > 1 )
		{
			if( pfShow != NULL )
				pfShow(Node->m_Data);
			return false;
		}
	}
	else
	{
		if ( nRight - nLeft > 1 )
		{
			if( pfShow != NULL )
				pfShow(Node->m_Data);
			return false;
		}
	}

	return true;
}

bool BSTree2::_Check(TreeNode * Node,PF_Show pfShow)
{
	if ( Node == NULL )
		return true;

	if ( CheckNode(Node, pfShow) == false )
		return false;

	return  _Check(Node->m_lchild, pfShow) && _Check(Node->m_rchild, pfShow);
}
