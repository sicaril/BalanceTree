#include "stdafx.h"
#include "RBTree.h"


RBTree::RBTree(void)
{
}


RBTree::~RBTree(void)
{
}

TreeNode* RBTree::SingleRotateWithLeft(TreeNode * Node)
{
	TreeNode * mid = Node->m_lchild;

	if ( mid->m_rchild )
		mid->m_rchild->m_parent = Node;

	Node->m_lchild = mid->m_rchild;
	mid->m_rchild = Node;

	mid->m_parent = Node->m_parent;
	Node->m_parent = mid;

	return mid;
}

TreeNode* RBTree::DoubleRotateWithLeft(TreeNode * Node)
{
	TreeNode * mid = Node->m_lchild;
	TreeNode * tmp = mid->m_rchild;

	Node->m_lchild = tmp->m_rchild;
	mid->m_rchild = tmp->m_lchild;

	if (tmp->m_rchild)
		tmp->m_rchild->m_parent = Node;
	if (tmp->m_lchild)
		tmp->m_lchild->m_parent = mid;

	tmp->m_lchild = mid;
	tmp->m_rchild = Node;

	tmp->m_parent = Node->m_parent;
	mid->m_parent = tmp;
	Node->m_parent = tmp;

	return tmp;
}

TreeNode* RBTree::SingleRotateWithRight(TreeNode * Node)
{
	TreeNode * mid = Node->m_rchild;

	if ( mid->m_lchild )
		mid->m_lchild->m_parent = Node;

	Node->m_rchild = mid->m_lchild;
	mid->m_lchild = Node;

	mid->m_parent = Node->m_parent;
	Node->m_parent = mid;

	return mid;
}

TreeNode* RBTree::DoubleRotateWithRight(TreeNode * Node)
{
	TreeNode * mid = Node->m_rchild;
	TreeNode * tmp = mid->m_lchild;

	Node->m_rchild = tmp->m_lchild;
	mid->m_lchild = tmp->m_rchild;

	if (tmp->m_lchild)
		tmp->m_lchild->m_parent = Node;
	if (tmp->m_rchild)
		tmp->m_rchild->m_parent = mid;

	tmp->m_rchild = mid;
	tmp->m_lchild = Node;

	tmp->m_parent = Node->m_parent;
	mid->m_parent = tmp;
	Node->m_parent = tmp;

	return tmp;
}

bool RBTree::Insert(T& Data)
{
	TreeNode * _cur = m_root;
	TreeNode * _parent = NULL;

	while ( _cur )
	{
		if ( Data < _cur->m_Data )
		{
			_parent = _cur;
			_cur = _cur->m_lchild;
		}
		else if ( Data > _cur->m_Data )
		{
			_parent = _cur;
			_cur = _cur->m_rchild;
		}
		else
		{
			return false;
		}
	}

	_cur = new(std::nothrow) TreeNode(Data);
	if (_cur == NULL )
		return false;
	_cur->m_parent = _parent;
	
	if ( _parent == NULL )
	{
		m_root = _cur;
		m_root->u.m_color = NS_BLACK;
		return true;
	}

	bool bLeft = false;
	if ( Data < _parent->m_Data )
	{
		bLeft = true;
		_parent->m_lchild = _cur;
	}
	else
	{
		_parent->m_rchild = _cur;
	}

	while ( _parent->u.m_color == NS_RED )
	{
		TreeNode * _grandpa = _parent->m_parent;
		if ( _grandpa == NULL )
		{
			_parent->u.m_color = NS_BLACK;
			break;
		}

		if ( _parent == _grandpa->m_lchild )
		{
			if ( IsRightRed(_grandpa))
			{
				SwapColor(_grandpa);
			}
			else
			{
				TreeNode ** ppGrandpa = GetParent(_grandpa);
				if ( bLeft )
					*ppGrandpa = SingleRotateWithLeft(_grandpa);
				else
					*ppGrandpa = DoubleRotateWithLeft(_grandpa);
				
				(*ppGrandpa)->u.m_color = NS_BLACK;
				(*ppGrandpa)->m_rchild->u.m_color = NS_RED;
				break;
			}
		}
		else
		{
			if ( IsLeftRed(_grandpa))
			{
				SwapColor(_grandpa);
			}
			else
			{
				TreeNode ** ppGrandpa = GetParent(_grandpa);
				if ( bLeft == false )
					*ppGrandpa = SingleRotateWithRight(_grandpa);
				else
					*ppGrandpa = DoubleRotateWithRight(_grandpa);

				(*ppGrandpa)->u.m_color = NS_BLACK;
				(*ppGrandpa)->m_lchild->u.m_color = NS_RED;
				break;
			}
		}

		_cur = _grandpa;
		_parent = _cur->m_parent;

		if ( _parent == NULL )
		{
			_cur->u.m_color = NS_BLACK;
			break;
		}

		bLeft = false;
		if ( _cur == _parent->m_lchild )
			bLeft = true;
	}

	return true;
}

bool RBTree::Delete(T& Data)
{
	TreeNode * _cur = m_root;
	TreeNode * _parent = NULL;
	T _Data = Data;
	TreeNode * _min = NULL;

	while ( _cur )
	{
		if ( _Data < _cur->m_Data )
		{
			_cur = _cur->m_lchild;
		}
		else if ( _Data > _cur->m_Data )
		{
			_cur = _cur->m_rchild;
		}
		else
		{
			if ( _cur->m_rchild == NULL )
				break;
			
			_min = FindMin(_cur->m_rchild);
			_cur->m_Data = _min->m_Data;
			_Data = _min->m_Data;
			_cur = _min;
		}
	}

	if ( _cur == NULL )
		return false;
	_parent = _cur->m_parent;
	TreeNode * tmp = _cur->m_lchild;
	if ( tmp )
		tmp->m_parent = _parent;

	bool bLeft = false;
	if ( _parent == NULL )
	{
		delete _cur;
		m_root = tmp;
		if ( tmp )
			tmp->u.m_color = NS_BLACK;
		return true;
	}
	else
	{
		if ( _cur->u.m_color == NS_RED ||
			IsLeftRed(_cur) 
			)
		{
			
			if ( _cur == _parent->m_lchild )
			{
				_parent->m_lchild = tmp;
			}
			else
			{
				_parent->m_rchild = tmp;
			}

			delete _cur;

			if ( tmp &&
				tmp->u.m_color == NS_RED )
			{
				tmp->u.m_color = NS_BLACK;
			}

			return true;
		}
	}

	if ( _cur == _parent->m_lchild )
		bLeft = true;
	_min = _cur;

	bool bSign = false;
	do 
	{
		if ( _cur->u.m_color == NS_RED )
		{
			_cur->u.m_color = NS_BLACK;
			break;
		}
		else
		{
			if ( bLeft )
			{
				TreeNode ** ppParent = GetParent(_parent);
				TreeNode * mid = _parent->m_rchild;
				if ( mid->u.m_color == NS_BLACK )
				{
					if ( IsRightRed(mid))
					{
						*ppParent = SingleRotateWithRight(_parent);

						(*ppParent)->u.m_color = (*ppParent)->m_lchild->u.m_color;
						(*ppParent)->m_lchild->u.m_color = NS_BLACK;
						(*ppParent)->m_rchild->u.m_color = NS_BLACK;

						bSign = true;
					}
					else if ( IsLeftRed(mid))
					{
						*ppParent = DoubleRotateWithRight(_parent);

						(*ppParent)->u.m_color = (*ppParent)->m_lchild->u.m_color;
						(*ppParent)->m_lchild->u.m_color = NS_BLACK;

						bSign = true;
					}
					else
					{
						mid->u.m_color = NS_RED;
					}
				}
				else
				{
					*ppParent = SingleRotateWithRight(_parent);

					(*ppParent)->u.m_color = (*ppParent)->m_lchild->u.m_color;
					(*ppParent)->m_lchild->u.m_color = NS_RED;

					continue;
				}
			}
			else
			{
				TreeNode ** ppParent = GetParent(_parent);
				TreeNode * mid = _parent->m_lchild;
				if ( mid->u.m_color == NS_BLACK )
				{
					if ( IsLeftRed(mid))
					{
						*ppParent = SingleRotateWithLeft(_parent);

						(*ppParent)->u.m_color = (*ppParent)->m_rchild->u.m_color;
						(*ppParent)->m_lchild->u.m_color = NS_BLACK;
						(*ppParent)->m_rchild->u.m_color = NS_BLACK;

						bSign = true;
					}
					else if ( IsRightRed(mid))
					{
						*ppParent = DoubleRotateWithLeft(_parent);

						(*ppParent)->u.m_color = (*ppParent)->m_rchild->u.m_color;
						(*ppParent)->m_rchild->u.m_color = NS_BLACK;

						bSign = true;
					}
					else
					{
						mid->u.m_color = NS_RED;
					}
				}
				else
				{
					*ppParent = SingleRotateWithLeft(_parent);

					(*ppParent)->u.m_color = (*ppParent)->m_rchild->u.m_color;
					(*ppParent)->m_rchild->u.m_color = NS_RED;

					continue;
				}
			}

			// del 
			if ( _cur == _min )
			{
				delete _cur;

				if ( bLeft )
					_parent->m_lchild = tmp;
				else
					_parent->m_rchild = tmp;

				//_cur = tmp;
			}
		}

		if ( bSign )
			break;

		_cur = _parent;
		_parent = _cur->m_parent;

		if ( _parent == NULL )
		{
			_cur->u.m_color = NS_BLACK;
			break;
		}

		bLeft = false;
		if ( _cur == _parent->m_lchild )
			bLeft = true;

	} while (true);

	return true;
}

bool RBTree::Check()
{
	if ( m_root && 
		m_root->u.m_color != NS_BLACK )
		return false;
	return _Check( m_root );
}

int RBTree::GetBlackNodeLeft(TreeNode * Node)
{
	if ( Node == NULL )
		return -1;
	int nBlock = Node->u.m_color == NS_BLACK;
	return GetBlackNodeLeft(Node->m_lchild) + nBlock;
}

int RBTree::GetBlackNodeRight(TreeNode * Node)
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
